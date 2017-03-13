#!/usr/bin/python
import os
import sys
import functools
import thread
import atexit
import os.path
import subprocess

toepython_pipe_name="toepython"
fromepython_pipe_name="fromepython"
popen=None
ePythonFunctionTable=None
number_of_cores=0

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
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)

def send(data, pid, length=None, isFunctionPointer=False):
	if (isinstance(data, list)):
		length=len(data)
	if length is None:
		underlyingSend(data, pid, isFunctionPointer=isFunctionPointer)
	else:
		i=0
		while i<length:
			underlyingSend(data[i], pid, isFunctionPointer=isFunctionPointer)
			i+=1

def probe(pid):
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "12 "+str(pid)+"\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")
	return bool(items[2])

def underlyingRecv(pid):
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
	
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
	
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "3\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def coreid():
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "4\n")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def sync():
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
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
		return recv(coreId)
	else:
		return recv(coreId, length)

def testKernelCompletion(pid):
	return probe(pid)

def waitForKernelCompletion(pid):
	return receiveKernelReturnValue(pid)

def doPhysicalEpiphanyLaunch(pid, function_name, *args):
	send(len(args), pid)
	send(ePythonFunctionTable[function_name], pid, isFunctionPointer=True)		
	for arg in args:
		if isinstance(arg, list):
			send(len(arg), pid)
		else:
			send(0, pid)
		send(arg, pid)
	
def epiphany(test_func=None,async=False,target=None):
	if not test_func:
		return functools.partial(epiphany, async=async,target=target)
	@functools.wraps(test_func)
	def f(*args, **kwargs):
		global number_of_cores
		if target is None:
			pidtarget=range(1,number_of_cores)
		else:
			if isinstance(target, list):
				pidtarget=target
			else:
				pidtarget=[target]
		for pid in pidtarget:
			doPhysicalEpiphanyLaunch(pid, test_func.func_name, *args)
		if not async:
			if len(pidtarget) == 1:
				return receiveKernelReturnValue(pidtarget[0])
			else:
				returnVals=[]
				index=0
				for pid in pidtarget:
					returnVals[index]=receiveKernelReturnValue(pidtarget[0])
					index+=1				
	return f

def shutdownEpython():
	global popen
	send(-1,1)
	stopEpython()
	popen.wait()

def initialise():
	insideKernel=False
	firstAddition=False
	runningCoProcessor=False
	generatedCode="import coprocessor\n"
	with open(sys.argv[0], 'rU') as f:
		for line in f:
			if firstAddition and not line.startswith((' ', '\t')):
				insideKernel=False
			if insideKernel:
				generatedCode+=line
				firstAddition=True
			if "@epiphany" in line:
				runningCoProcessor=True
				insideKernel=True
				firstAddition=False
				generatedCode+="@exportable\n"
	if runningCoProcessor:
		global popen, ePythonFunctionTable, number_of_cores
		atexit.register(shutdownEpython)
		fo = open("pythonkernels.py", "wb")
		fo.write(generatedCode);
		fo.close()
		popen = subprocess.Popen("./epython-host -fullpython -h 1 pythonkernels.py", shell=True, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)	
		thread.start_new_thread(executeOnEpiphany,())
		pingEpython()
		ePythonFunctionTable=getExportableFunctionTable()
		number_of_cores=numcores()

initialise()
