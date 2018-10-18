import parallel
import taskfarm
import array

globalLookup=array(10)
globalLookupPoint=0

def registerGlobalVariable(a):
	globalLookup[globalLookupPoint]=symbol(a)
	globalLookupPoint+=1

@exportable
def copyToGlobal(gid, data):
	srcdata=None
	alias(srcdata, globalLookup[gid])
	if (len(srcdata) != len(data)):
		print "Error, data to write must equal the target data size"
		quit()
	elif(len(srcdata) == 0):
		srcdata=data
	else:
		srcdata[0]=data[0]
		arraycopy(srcdata, data)

@exportable
def copyFromGlobal(gid):
	srcdata=None
	alias(srcdata, globalLookup[gid])
	return srcdata

@exportable
def stopCores():
	quit()

initTaskFarm(3)
