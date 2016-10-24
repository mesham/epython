def send(data, pid, n=none):
	if (n is none):
		epy_i_send data to pid
	else:
		i=0
		while i<n:
			d=data[i]			
			epy_i_send d to pid
			i=i+1

def recv(pid, n=none):
	if (n is none):		
		retV=0
		epy_i_recv retV from pid
		return retV
	else:
		dim retV[n]
		i=0
		while i<n:
			v=0
			epy_i_recv v from pid
			retV[i]=v
			i=i+1
		return retV

def sendrecv(data, pid, n=none):
	if (n is none):
		retV=0
		epy_i_sendrecv data tofrom pid into retV
		return retV
	else:
		dim retV[n]
		i=0
		while i<n:
			v=0
			d=data[i]	
			epy_i_sendrecv d tofrom pid into v
			retV[i]=v
			i=i+1
		return retV

def bcast(data, root):
	retV=0
	epy_i_bcast data from root into retV
	return retV

def reduce(data, operator):
	retV=0
	if operator=="sum":
		epy_i_reduce epy_i_sum data into retV
	elif operator=="min":
		epy_i_reduce epy_i_min data into retV
	elif operator=="max":
		epy_i_reduce epy_i_max data into retV
	elif operator=="prod":
		epy_i_reduce epy_i_prod data into retV
	else:
		print "Operator "+operator+" not found"
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