def send(data, pid, n=none):
	if (n is none):
		native rtl_send(data,pid)
	else:
		i=0
		while i<n:
			d=data[i]
			native rtl_send(d,pid)
			i=i+1

def recv(pid, n=none):
	if (n is none):
		return native rtl_recv(pid)
	else:
		dim retV[n]
		i=0
		while i<n:
			retV[i]=native rtl_recv(pid)
			i=i+1
		return retV

def sendrecv(data, pid, n=none):
	if (n is none):
		return native rtl_sendrecv(data, pid)
	else:
		dim retV[n]
		i=0
		while i<n:
			d=data[i]
			retV[i]=native rtl_sendrecv(d, pid)
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
	native rtl_sync()

def coreid():
	return epy_i_coreid

def numcores():
	return epy_i_numcores

def ishost():
	return native rtl_ishost()

def isdevice():
	return native rtl_isdevice()
