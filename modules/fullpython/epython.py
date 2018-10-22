#!/usr/bin/python
from __future__ import print_function
import os
import stat
import sys
import functools
import atexit
import os.path
import subprocess
from threading import Thread, Lock, Condition
import inspect
import re
import __main__ as main

useNumpy=False

if useNumpy: import numpy as np

interactivePython=not hasattr(main, '__file__')

toepython_pipe_name="/tmp/toepython"
fromepython_pipe_name="/tmp/fromepython"
epythonfile_name="/tmp/pythonkernels.py"
popen=None
ePythonFunctionTable=None
number_of_cores=0
activeCores=None
thisCore=0
active=True
globalVars=[]
outstandingLaunches=[]
schuedulerMutex = Lock()
schedulerCondition = Condition()

interactive_sourcecode=""

ALL_DEVICES=0
EPIPHANY_DEVICE=1

def getInteractiveSourceCode(ref_module):
	source_code=""
	all_functions=inspect.getmembers(ref_module)
	for function in all_functions:
		if (function[0]=="In"):
			for line in function[1]:
				source_code+=line+"\n"
	return source_code

def executeOnCoProcessor():
	global popen
	for line in iter(popen.stdout.readline, b''):
		print(line, end="")
	popen.stdout.close()

def pingEpython():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "10\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	raw_data=str(os.read(rp, 1024))
	os.close(rp)

def stopEpython():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "11\n".encode())
	os.close(wp)

def getExportableFunctionTable():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "9\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	raw_data=str(os.read(rp, 8192).decode('ascii'))
	os.close(rp)
	exportedFunctions={}
	if raw_data != "-":
		for line in raw_data.splitlines():
		  if (line.count(">") > 0):
			  exportedFunctions[line.split('>')[0]]=int(line.split('>')[1])
	return exportedFunctions

def getTypeFromData(data):
	if type(data) is int:
		return 0
	elif type(data) is float:
		return 1
	elif type(data) is bool:
		return 3
	else:
		if useNumpy:
			if type(data) is np.int:
				return 0
			elif type(data) is np.float64 or type(data) is np.float32:
				return 1
			elif type(data) is np.bool:
				return 3
	print ("Error, can not map data to type "+str(type(data)))
	quit()

def sendrecv(data, pid):
	command_to_send="8 "+str(pid)+" "+str(getTypeFromData(data))+" "
	command_to_send+="0 "+str(data)+"\n"
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send.encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)
	items = recv_data.split(" ")
	if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def underlyingSend(data, pid, length, isFunctionPointer=False):
	command_to_send="1 "+str(pid)+" "
	if isFunctionPointer:
		command_to_send+="5 "
	else:
		if (length > 1):
			command_to_send+=str(getTypeFromData(data[0]))+" "
		else:
			command_to_send+=str(getTypeFromData(data))+" "
	command_to_send+="0 "+str(length)+" "
	if (length > 1):
		i=0
		while i<length:
			command_to_send+=str(data[i])+" "
			i+=1
	else:
		command_to_send+=str(data)

	command_to_send+="\n"
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send.encode())
	os.close(wp)

def send(data, pid, length=None, isFunctionPointer=False):
	length=1
	try:
		length=len(data)
	except TypeError:
		pass
	underlyingSend(data, pid, length, isFunctionPointer=isFunctionPointer)

def probe(pid):
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, ("12 "+str(pid)+"\n").encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)
	items = recv_data.split(" ")
	return bool(items[2])

def underlyingRecv(pid):
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, ("2 "+str(pid)+"\n").encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
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
		print ("Operator "+operator+" not found")

	command_to_send+=str(getTypeFromData(data))+" "
	command_to_send+="0 "+str(data)+"\n"

	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send.encode())
	os.close(wp)

	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
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

	command_to_send+=str(getTypeFromData(data))+" "
	command_to_send+="0 "+str(data)+"\n"

	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, command_to_send.encode())
	os.close(wp)

	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def numcores():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "3\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)
	return int(recv_data)

def coreid():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "4\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)
	return int(recv_data)

def sync():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "5\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)

def restartePython():
	wp=os.open(toepython_pipe_name, os.O_WRONLY)
	os.write(wp, "13\n".encode())
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=str(os.read(rp, 1024).decode('ascii'))
	os.close(rp)

def ishost():
		return True

def isdevice():
		return False

def receiveKernelReturnValue(coreId):
	length=recv(coreId)
	if (length==0):
		data=recv(coreId)
	else:
		data=recv(coreId, length)
	activeCores[coreId]=False
	schedulerCondition.acquire()
	schedulerCondition.notify()
	schedulerCondition.release()
	return data

class KernelExecutionHandler:
	def __init__(self, running_coreids=None, num_scheduled=None):
		self.running_coreids=[] if running_coreids is None else running_coreids
		self.num_scheduled=0 if num_scheduled is None else num_scheduled
	def append(self, handler_to_append):
		self.appendRunningCoreIds(handler_to_append.getRunningCoreIds())
		self.num_scheduled+=handler_to_append.getNumberScheduled()
	def getRunningCoreIds(self):
		return sorted(self.running_coreids)
	def appendRunningCoreIds(self, cids):
		self.running_coreids.extend(cids)
	def wait(self):
		while (self.num_scheduled > 0) : pass
		returnVals=[]
		index=0
		for pid in sorted(self.running_coreids):
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
		if self.num_scheduled > 0 : return False
		for pid in self.running_coreids:
			if not probe(pid): return False
		return True

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

def doPhysicalCoprocessorLaunch(pid, function_name, *args):
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
	def __init__(self, num_outstanding, func_name, args):
		self.num_outstanding=num_outstanding
		self.func_name=func_name
		self.args=args
		self.handler=None
	def setHandler(self, handler):
		self.handler=handler
	def getHandler(self):
		return self.handler
	def getFunctionName(self):
		return self.func_name
	def getArgs(self):
		return self.args

class AnyCoresOutstandingLaunch(OutstandingLaunch):
	def __init__(self, num_outstanding, func_name, *args):
		OutstandingLaunch.__init__(self,num_outstanding,func_name, args)
		self.num_outstanding=num_outstanding
	def getNumOutstanding(self):
		return self.num_outstanding
	def setNumOutstanding(self, num_outstanding):
		self.num_outstanding=num_outstanding

class SpecificCoresOutstandingLaunch(OutstandingLaunch):
	def __init__(self, outstandingpids, func_name, *args):
		OutstandingLaunch.__init__(self,len(outstandingpids),func_name, args)
		self.outstandingpids=outstandingpids
	def getNumOutstanding(self):
		return len(self.outstandingpids)
	def getOutstandingCores(self):
		return self.outstandingpids
	def setOutstandingCores(self, outstandingpids):
		self.outstandingpids=outstandingpids
	def appendCoreId(self, coreid):
		self.outstandingpids.append(coreid)
	def removeCoreIds(self, listtoremove):
		self.outstandingpids = [x for x in self.outstandingpids if x not in listtoremove]

def copy_from_device(var, target=None, async=False):
	try:
		varId=globalVars.index(var)
		return issueKernelLaunches("copyFromGlobal", async, target, None, True if target == None else False, [varId])
	except ValueError:
		print ("Error, can not find global variable " +str(var)+" for copying from the device")
		quit()

def define_on_device(var):
	pass

def copy_to_device(var, data, target=None, async=False):
	try:
		varId=globalVars.index(var)
		return issueKernelLaunches("copyToGlobal", async, target, None, True if target == None else False, [varId, data])
	except ValueError:
		print ("Error, can not find global variable " +str(var)+" for copying to device")
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
			outstandingLaunch=AnyCoresOutstandingLaunch(myAuto-kernelinstance, kernelName, *args)
		schuedulerMutex.release()
	elif not myTarget is None:
		if isinstance(myTarget, list):
			pidtarget=myTarget
		else:
			pidtarget=[myTarget]
	elif myAll:
		pidtarget=list(range(0,number_of_cores))
		pidtarget.remove(thisCore)
	schuedulerMutex.acquire()
	busyPids=[]
	runningCoreIds=[]
	for pid in pidtarget:
		if (not myAuto is None or activeCores[pid] == False):
			activeCores[pid]=True
			doPhysicalCoprocessorLaunch(pid, kernelName, *args)
			runningCoreIds.append(pid)
		else:
			busyPids.append(pid)
	schuedulerMutex.release()
	if (len(busyPids) > 0):
		outstandingLaunch=SpecificCoresOutstandingLaunch(busyPids, kernelName, *args)
	handler=KernelExecutionHandler(runningCoreIds, 0 if outstandingLaunch is None else outstandingLaunch.getNumOutstanding())
	if not outstandingLaunch is None:
		outstandingLaunch.setHandler(handler)
		schuedulerMutex.acquire()
		outstandingLaunches.append(outstandingLaunch)
		schuedulerMutex.release()
	if isAsync:
		return handler
	else:
		return handler.wait()

def offload(test_func=None,async=False,target=None, auto=None, all=True, device=ALL_DEVICES):
	if not test_func:
		return functools.partial(offload, async=async,target=target, auto=auto, all=all)
	@functools.wraps(test_func)
	def f(*args, **kwargs):
		global outstandingLaunches
		if (interactivePython):
			newSource=getInteractiveSourceCode(inspect.getmodule(test_func))
			refreshePythonSourceExecutionIfNeeded(newSource)			
		isAsync=async
		myTarget=target
		myAuto=auto
		myAll=all
		for arg in kwargs:
			if (arg == "target"):
				myTarget=kwargs[arg]
			elif (arg == "async"):
				isAsync=kwargs[arg]
			elif (arg == "auto"):
				myAuto=kwargs[arg]
			elif (arg == "all"):
				myAll=kwargs[arg]
		return issueKernelLaunches(test_func.__name__, isAsync, myTarget, myAuto, myAll, args)
	return f

def offload_single(test_func=None, device=ALL_DEVICES):
	return offload(test_func=test_func, async=True, target=None, auto=1, all=False, device=device)

def offload_multiple(test_func=None, cores=None, device=ALL_DEVICES):
	if cores is None:
		print ("Error - you must specify the number of device cores to use with the multiple decorator")
		quit()
	return offload(test_func=test_func, async=True, target=None, auto=cores, all=False, device=device)

def shutdownEpython():
	global popen, active, outstandingLaunches
	while len(outstandingLaunches) > 0: pass
	active=False
	schedulerCondition.acquire()
	schedulerCondition.notify()
	schedulerCondition.release()
	for pid in range(0,number_of_cores):
		if not pid == thisCore: send(-1,pid)
	stopEpython()
	popen.wait()
	try:
		os.remove(toepython_pipe_name)
	except OSError:
		pass
	try:
		os.remove(fromepython_pipe_name)
	except OSError:
		pass
	try:
		os.remove(epythonfile_name)
	except OSError:
		pass

def pollScheduler():
	while active:
		for outstanding in outstandingLaunches:
			pidtarget=[]
			if (isinstance(outstanding, AnyCoresOutstandingLaunch)):
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
			elif (isinstance(outstanding, SpecificCoresOutstandingLaunch)):
				schuedulerMutex.acquire()
				for launchId in outstanding.getOutstandingCores():
					if (activeCores[launchId] == False):
						activeCores[launchId]=True
						pidtarget.append(launchId)
				schuedulerMutex.release()
				if len(pidtarget) > 0:
					outstanding.removeCoreIds(pidtarget)

			if len(pidtarget) > 0:
				if outstanding.getNumOutstanding() == 0: outstandingLaunches.remove(outstanding)
				for pid in pidtarget:
					doPhysicalCoprocessorLaunch(pid, outstanding.getFunctionName(), *outstanding.getArgs())
				outstanding.getHandler().appendRunningCoreIds(pidtarget)
				outstanding.getHandler().setNumberScheduled(outstanding.getHandler().getNumberScheduled()-len(pidtarget))
				break	# This enforces strict ordering of processing kernels in the order that they are scheduled
			else:
				break  # This enforces strict ordering of processing kernels in the order that they are scheduled
		schedulerCondition.acquire()
		schedulerCondition.wait()
		schedulerCondition.release()

def parseSourceCode(source_text):
	global globalVars
	insideKernel=False
	firstAddition=False
	runningCoProcessor=False
	importCode="import coprocessor\n"
	generatedCode=""
	kernelsCode=""
	global_definitions={}

	split_by_line=source_text
	if (isinstance(split_by_line, str)): split_by_line=split_by_line.splitlines()

	for line in split_by_line:
		if line.isspace(): continue
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
				if (not line.endswith("\n")): kernelsCode+="\n"
			firstAddition=True
		if "define_on_device(" in line or "epython.define_on_device(" in line:
			var=line.split('(')[1].replace(',',')').split(')')[0]
			if not var in globalVars:
				globalVars.append(var)
				generatedCode+=var+"="+global_definitions[var]+"\nregisterGlobalVariable("+var+")\n"
		if "@offload" in line or "@epython.offload" in line:
			runningCoProcessor=True
			insideKernel=True
			firstAddition=False
			kernelsCode+="@exportable\n"
	return runningCoProcessor, importCode+generatedCode+"worker()\n"+kernelsCode

def refreshePythonSourceExecutionIfNeeded(sourceCodeContent):
	global interactive_sourcecode
	runningCoProcessor, targetKernels=parseSourceCode(sourceCodeContent)
	if (runningCoProcessor and interactive_sourcecode != targetKernels):
		global ePythonFunctionTable
		issueKernelLaunches("stopCores", False, None, None, True, [])
		interactive_sourcecode=targetKernels
		fo = open(epythonfile_name, "w")
		fo.write(targetKernels)
		fo.close()
		restartePython()
		pingEpython()
		ePythonFunctionTable=getExportableFunctionTable()

def initialise(sourceCodeContent, interactive=False):
	runningCoProcessor, targetKernels=parseSourceCode(sourceCodeContent)
	if runningCoProcessor or interactive:
		global popen, ePythonFunctionTable, number_of_cores, activeCores, thisCore
		atexit.register(shutdownEpython)
		fo = open(epythonfile_name, "w")
		fo.write(targetKernels)
		fo.close()
		try:
			os.mkfifo(toepython_pipe_name, 0o644)
		except OSError:
			pass
		try:
			os.mkfifo(fromepython_pipe_name, 0o644)
		except OSError:
			pass
		command_to_exec="sudo /home/xilinx/epython/epython-microblaze -fullpython "+("-interactive " if interactive else "") +epythonfile_name+" 2>&1"
		popen = subprocess.Popen(command_to_exec, shell=True, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
		t1=Thread(target=executeOnCoProcessor)
		t2=Thread(target=pollScheduler)
		t1.setDaemon(True)
		t2.setDaemon(True)
		t1.start()
		t2.start()
		pingEpython()
		ePythonFunctionTable=getExportableFunctionTable()
		number_of_cores=numcores()
		thisCore=coreid()
		activeCores=[False]*number_of_cores
		activeCores[thisCore]=True

if (not interactivePython):
	with open(sys.argv[0], 'rU') as f:
		content = f.readlines()
	initialise(content)
else:
	initialise("", True)
