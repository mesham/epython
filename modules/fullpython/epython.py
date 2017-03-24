#!/usr/bin/python
import os
import sys
import functools
import thread
import atexit
import os.path
import subprocess
from threading import Thread, Lock
import inspect
import re

toepython_pipe_name="toepython"
fromepython_pipe_name="fromepython"
popen=None
ePythonFunctionTable=None
number_of_cores=0
activeCores=None
thisCore=0
active=True
globalVars=[]
outstandingLaunches=[]
schuedulerMutex = Lock()

def executeOnEpiphany():
	global popen
	for line in iter(popen.stdout.readline, b''):
		print line,
	popen.stdout.close()

def pingEpython():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "10\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	raw_data=os.read(rp, 1024)
	os.close(rp)

def stopEpython():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "11\n")
	os.close(wp)

def getExportableFunctionTable():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "9\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	raw_data=os.read(rp, 8192)
	os.close(rp)
	exportedFunctions={}
	if raw_data != "-":
		for line in raw_data.splitlines():
			exportedFunctions[line.split('>')[0]]=int(line.split('>')[1])
	return exportedFunctions

def sendrecv(data, pid):
	command_to_send="8 "+str(pid)+" "
	if type(data) is int:
		command_to_send+="0 "
	elif type(data) is float:
		command_to_send+="1 "
	elif type(data) is bool:
		command_to_send+="3 "
	command_to_send+="0 "+str(data)+"\n"
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def underlyingSend(data, pid, isFunctionPointer=False):
	command_to_send="1 "+str(pid)+" "
	if isFunctionPointer:
		command_to_send+="5 "
	else:
		if type(data) is int:
			command_to_send+="0 "
		elif type(data) is float:
			command_to_send+="1 "
		elif type(data) is bool:
			command_to_send+="3 "
	command_to_send+="0 "+str(data)+"\n"
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)

def send(data, pid, length=None, isFunctionPointer=False):
	length=None
	try:
		length=len(data)
	except TypeError:
		pass
	if length is None:
		underlyingSend(data, pid, isFunctionPointer=isFunctionPointer)
	else:
		i=0
		while i<length:
			underlyingSend(data[i], pid, isFunctionPointer=isFunctionPointer)
			i+=1

def probe(pid):
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "12 "+str(pid)+"\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
	return bool(items[2])

def underlyingRecv(pid):
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "2 "+str(pid)+"\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def recv(pid, len=None):
	if len is None:
		return underlyingRecv(pid)
	else:
		toRet=[0]*len
		i=0
		while i<len:
			toRet[i]=underlyingRecv(pid)
			i+=1
		return toRet

def reduce(data, operator):
	command_to_send="6 "
	if operator=="sum":
		command_to_send+="0 "
	elif operator=="min":
		command_to_send+="1 "
	elif operator=="max":
		command_to_send+="2 "
	elif operator=="prod":
		command_to_send+="3 "
	else:
		print "Operator "+operator+" not found"

	if type(data) is int:
		command_to_send+="0 "
	elif type(data) is float:
		command_to_send+="1 "
	elif type(data) is bool:
		command_to_send+="3 "
	command_to_send+="0 "+str(data)+"\n"

	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)

	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def bcast(data, root):
	command_to_send="7 "+str(root)

	if type(data) is int:
		command_to_send+=" 0 "
	elif type(data) is float:
		command_to_send+=" 1 "
	elif type(data) is bool:
		command_to_send+=" 3 "
	command_to_send+="0 "+str(data)+"\n"

	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)

	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def numcores():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "3\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def coreid():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "4\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def sync():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "5\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)

def ishost():
		return true

def isdevice():
		return false

def receiveKernelReturnValue(coreId):
	length=recv(coreId)
	if (length==0):
		data=recv(coreId)
	else:
		data=recv(coreId, length)
	activeCores[coreId]=False
	return data

class KernelExecutionHandler:
	def __init__(self, running_coreids, num_scheduled):
		self.running_coreids=running_coreids
		self.num_scheduled=num_scheduled
	def getRunningCoreIds(self):
		return self.running_coreids
	def appendRunningCoreIds(self, cids):
		self.running_coreids.extend(cids)
	def wait(self):
		while (self.num_scheduled > 0) : pass
		returnVals=[]
		index=0
		for pid in self.running_coreids:
			returnVals.append(receiveKernelReturnValue(pid))
			index+=1
		return returnVals
	def wait_any(self):
		while True:
			while len(self.running_coreids == 0): pass
			for pid in self.running_coreids:
				if (probe(pid)):
					self.running_coreids.remove(pid)
					return {pid : receiveKernelReturnValue(pid)}
	def number_running(self):
		return len(self.running_coreids)
	def number_outstanding(self):
		return len(self.running_coreids) + self.num_scheduled
	def getNumberScheduled(self):
		return self.num_scheduled
	def setNumberScheduled(self, num_scheduled):
		self.num_scheduled=num_scheduled
	def test(self):
		if self.num_scheduled > 0 : return false
		for pid in self.running_coreids:
			if not probe(pid): return false
		return true

def testKernelCompletion(pid):
	if (isinstance(pid, KernelExecutionHandler)):
		return pid.test()
	else:
		return probe(pid)

def waitForKernelCompletion(pid):
	if (isinstance(pid, KernelExecutionHandler)):
		return pid.wait()
	else:
		return receiveKernelReturnValue(pid)

def doPhysicalEpiphanyLaunch(pid, function_name, *args):
	send(len(args), pid)
	send(ePythonFunctionTable[function_name], pid, isFunctionPointer=True)
	for arg in args:
		try:
			send(len(arg), pid)
		except TypeError:
			send(0, pid)
		send(arg, pid)

def waitAll(*args):
	results=[]
	for handler in args:
		results.append(handler.wait())
	return results

class OutstandingLaunch:
	def __init__(self, num_outstanding, func_name, *args):
		self.num_outstanding=num_outstanding
		self.func_name=func_name
		self.args=args
	def setHandler(self, handler):
		self.handler=handler
	def getHandler(self):
		return self.handler
	def getNumOutstanding(self):
		return self.num_outstanding
	def setNumOutstanding(self, num_outstanding):
		self.num_outstanding=num_outstanding
	def getFunctionName(self):
		return self.func_name
	def getArgs(self):
		return self.args

def copy_from_epiphany(var):
	try:
		varId=globalVars.index(var)
		return issueKernelLaunches("copyFromGlobal", False, None, None, True, [varId])
	except ValueError:
		print "Error, can not find global variable " +str(var)+" for copying from the Epiphany"
		quit()

def define_on_epiphany(var):
	pass

def copy_to_epiphany(var, data):
	try:
		varId=globalVars.index(var)
		issueKernelLaunches("copyToGlobal", False, None, None, True, [varId, data])
	except ValueError:
		print "Error, can not find global variable " +str(var)+" for copying to Epiphany"
		quit()

def issueKernelLaunches(kernelName, isAsync, myTarget, myAuto, myAll, args):
	outstandingLaunch=None
	if not myAuto is None:
		pidtarget=[]
		schuedulerMutex.acquire()
		try:
			for kernelinstance in range(0,myAuto):
				idx=activeCores.index(False)
				activeCores[idx]=True
				pidtarget.append(idx)
		except ValueError:
			outstandingLaunch=OutstandingLaunch(myAuto-kernelinstance, kernelName, *args)
			outstandingLaunches.append(outstandingLaunch)
		schuedulerMutex.release()
	elif myAll:
		pidtarget=range(0,number_of_cores)
		pidtarget.remove(thisCore)
	elif not myTarget is None:
		if isinstance(myTarget, list):
			pidtarget=myTarget
		else:
			pidtarget=[myTarget]
	for pid in pidtarget:
		activeCores[pid]=True
		doPhysicalEpiphanyLaunch(pid, kernelName, *args)
	handler=KernelExecutionHandler(pidtarget, 0 if outstandingLaunch is None else outstandingLaunch.getNumOutstanding())
	if not outstandingLaunch is None: outstandingLaunch.setHandler(handler)
	if isAsync:
		return handler
	else:
		return handler.wait()

def epiphany(test_func=None,async=False,target=None, auto=None, all=True):
	if not test_func:
		return functools.partial(epiphany, async=async,target=target, auto=auto, all=all)
	@functools.wraps(test_func)
	def f(*args, **kwargs):
		global outstandingLaunches
		isAsync=async
		myTarget=target
		myAuto=auto
		myAll=all
		return issueKernelLaunches(test_func.func_name, isAsync, myTarget, myAuto, myAll, args)
	return f

def epiphany_single(test_func):
	return epiphany(test_func=test_func, async=True, target=None, auto=1, all=False)

def epiphany_multiple(test_func=None, cores=None):
	if cores is None:
		print "Error - you must specify the number of Epiphany cores to use with the multiple decorator"
		quit()
	return epiphany(test_func=test_func, async=True, target=None, auto=cores, all=False)

def shutdownEpython():
	global popen, active, outstandingLaunches
	while len(outstandingLaunches) > 0: pass
	active=False
	for pid in range(0,number_of_cores):
		if not pid == thisCore: send(-1,pid)
	stopEpython()
	popen.wait()

def pollEpiphanyScheduler():
	while active:
		for outstanding in outstandingLaunches:
			pidtarget=[]
			schuedulerMutex.acquire()
			try:
				for launchId in range(0,outstanding.getNumOutstanding()):
					idx=activeCores.index(False)
					activeCores[idx]=True
					pidtarget.append(idx)
			except ValueError:
				pass
			schuedulerMutex.release()
			if len(pidtarget) > 0:
				outstanding.setNumOutstanding(outstanding.getNumOutstanding() - len(pidtarget))
				if outstanding.getNumOutstanding() == 0: outstandingLaunches.remove(outstanding)
				for pid in pidtarget:
					doPhysicalEpiphanyLaunch(pid, outstanding.getFunctionName(), *outstanding.getArgs())
				outstanding.getHandler().appendRunningCoreIds(pidtarget)
				outstanding.getHandler().setNumberScheduled(outstanding.getHandler().getNumberScheduled()-len(pidtarget))
				break	# This enforces strict ordering of processing kernels in the order that they are scheduled
			else:
				break  # This enforces strict ordering of processing kernels in the order that they are scheduled

def initialise():
	global globalVars
	insideKernel=False
	firstAddition=False
	runningCoProcessor=False
	importCode="import coprocessor\n"
	generatedCode=""
	kernelsCode=""
	global_definitions={}
	with open(sys.argv[0], 'rU') as f:
		for line in f:
			if not line.startswith((' ', '\t')):
				if (re.search(r'\w+=.+',line)):
					global_definitions[line.split('=')[0]]=line.split('=')[1]
			if firstAddition and not line.startswith((' ', '\t')):
				insideKernel=False
			if insideKernel:
				if (re.search(r'\s*import .*',line) or re.search(r'\s*from .*',line)):
					importCode+=line.lstrip()
				else:
					kernelsCode+=line
				firstAddition=True
			if "define_on_epiphany("  in line:
				var=line.split('(')[1].replace(',',')').split(')')[0]
				if not var in globalVars:
					globalVars.append(var)
					generatedCode+=var+"="+global_definitions[var]+"\nregisterGlobalVariable("+var+")\n"
			if "@epiphany" in line:
				runningCoProcessor=True
				insideKernel=True
				firstAddition=False
				kernelsCode+="@exportable\n"
	if runningCoProcessor:
		global popen, ePythonFunctionTable, number_of_cores, activeCores, thisCore
		atexit.register(shutdownEpython)
		fo = open("pythonkernels.py", "wb")
		fo.write(importCode+generatedCode+"worker()\n"+kernelsCode);
		fo.close()
		#popen = subprocess.Popen("./epython-host -fullpython -h 2 pythonkernels.py", shell=True, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
		popen = subprocess.Popen("./epython.sh -fullpython pythonkernels.py", shell=True, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
		thread.start_new_thread(executeOnEpiphany,())
		thread.start_new_thread(pollEpiphanyScheduler,())
		pingEpython()
		ePythonFunctionTable=getExportableFunctionTable()
		number_of_cores=numcores()
		thisCore=coreid()
		activeCores=[False]*number_of_cores
		activeCores[thisCore]=True

initialise()
