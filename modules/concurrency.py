def expose(data, pid):
	global_ref=native rtl_global_reference(id(data))
	native rtl_send(global_ref,pid)

def access(src):
	ref=native rtl_recv(src)
	return native rtl_dereference(ref)