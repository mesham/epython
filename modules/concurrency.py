def expose(data, pid):
	native rtl_send(id(data),pid)

def access(src):
	ref=native rtl_recv(src)
	return deref(ref)