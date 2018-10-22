import parallel
import array

_remoteFunctionCallState=array(numcores())
_masterTask=0
_running=True

def initTaskFarm(masterTask):
	_masterTask=masterTask
	if (coreid()==masterTask):
		_remoteFunctionCallState[masterTask]=false

def shutdownTaskFarm():
	i=0
	while i<numcores():
		if (i != _masterTask):
			waitFunctionFinish(i)
			send(-1, i)
		i+=1

def execFunction(pid, op, a=none, b=none, c=none, d=none, e=none):
	waitFunctionFinish(pid)
	_remoteFunctionCallState[pid]=true
	num_args=0
	if (!a is none): num_args+=1
	if (!b is none): num_args+=1
	if (!c is none): num_args+=1
	if (!d is none): num_args+=1
	if (!e is none): num_args+=1
	send(num_args, pid)
	send(op, pid)
	if (!a is none): sendArgument(pid, a)
	if (!b is none): sendArgument(pid, b)
	if (!c is none): sendArgument(pid, c)
	if (!d is none): sendArgument(pid, d)
	if (!e is none): sendArgument(pid, e)

def testFunctionFinish(pid):
	if (_remoteFunctionCallState[pid]):
		return probe(pid)
	return false

def waitFunctionFinish(pid):
	if (_remoteFunctionCallState[pid]):
		_remoteFunctionCallState[pid]=false
		recvCount=recv(pid)
		if (recvCount == -1):
			return none
		elif (recvCount == 0):
			return recv(pid)
		else:
			return recv(pid, recvCount)

def sendArgument(pid, arg):
	datalen=len(arg)
	send(datalen, pid)
	if (datalen > 0):
		send(arg, pid, datalen)
	else:
		send(arg, pid)

def stopTaskFarm():
	 _running=False

def worker():
	if (not _running): return
	num_args=recv(_masterTask)
	while num_args >= 0:
		op=recv(_masterTask)
		retVal=none
		if (num_args == 0): retVal=op()
		if (num_args == 1): retVal=op(recvArgument(_masterTask))
		if (num_args == 2): retVal=op(recvArgument(_masterTask), recvArgument(_masterTask))
		if (num_args == 3): retVal=op(recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask))
		if (num_args == 4): retVal=op(recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask))
		if (num_args == 5): retVal=op(recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask), recvArgument(_masterTask))
		if (retVal is none):
			send(-1, _masterTask)
		else:
			datalen=len(retVal)
			send(datalen, _masterTask)
			if (datalen==0):
				send(retVal, _masterTask)
			else:
				send(retVal, _masterTask, datalen)
		if (not _running): return
		num_args=recv(_masterTask)

def recvArgument(pid):
	length=recv(pid)
	if (length==0):
		return recv(pid)
	else:
		return recv(pid, length)
