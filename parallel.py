def send(data, pid):
	epy_i_send data to pid

def recv(pid):
	retV=0
	epy_i_recv retV from pid
	return retV

def sendrecv(data, pid):
	retV=0
	epy_i_sendrecv data tofrom pid into retV
	return retV

def bcast(data, root):
	retV=0
	epy_i_bcast data from root into retV
	return retV

def reduce(data, operator):
	retV=0
	if operator=="sum":
		epy_i_reduce sum data into retV
	if operator=="min":
		epy_i_reduce min data into retV
	if operator=="max":
		epy_i_reduce max data into retV
	if operator=="prod":
		epy_i_reduce prod data into retV
	return retV

def sync():
	epy_i_sync

def coreid():
	return epy_i_coreid

def numcores():
	return epy_i_numcores

def ishost():
	if epy_i_ishost:
		return true
	else:
		return false

def isdevice():
	if epy_i_isdevice:
		return true
	else:
		return false