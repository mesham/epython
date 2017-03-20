import parallel
import taskfarm

globalLookup=[0]*10
globalLookupPoint=0

def registerGlobalVariable(a):
	globalLookup[globalLookupPoint]=id(a)
	globalLookupPoint+=1

@exportable
def copyToGlobal(gid, data):
	d=native rtl_dereference(globalLookup[gid])
	d=data

@exportable
def copyFromGlobal(gid):
	return None

initTaskFarm(16)
