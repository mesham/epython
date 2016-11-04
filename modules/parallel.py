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
	return native rtl_bcast(data, root)

def reduce(data, operator):
	opVal=0
	if operator=="sum":
	    opVal=0
	elif operator=="min":
		opVal=1
	elif operator=="max":
		opVal=2
	elif operator=="prod":
		opVal=3
	else:
		print "Operator "+operator+" not found"
    return native rtl_reduce(data, opVal)

def sync():
	native rtl_sync()

def coreid():
	return native rtl_coreid()

def numcores():
	return native rtl_numcores()

def ishost():
	return native rtl_ishost()

def isdevice():
	return native rtl_isdevice()
