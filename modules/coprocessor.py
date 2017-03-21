import parallel
import taskfarm
import array

globalLookup=array(10)
globalLookupPoint=0

def registerGlobalVariable(a):
	globalLookup[globalLookupPoint]=id(a)
	globalLookupPoint+=1

@exportable
def copyToGlobal(gid, data):
	d=native rtl_dereference(globalLookup[gid])
	if (len(d) != len(data)):
		print "Error, data to write must equal the target data size"
		exit()
	elif(len(d) == 0):
		d=data
	else:
		i=0
		while i<len(d):
			d[i]=data[i]
			i+=1

@exportable
def copyFromGlobal(gid):
	return native rtl_dereference(globalLookup[gid])

initTaskFarm(16)
