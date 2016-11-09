import taskfarm

initTaskFarm(0)

if (coreid() == 0):
	execFunction(1, exampleFn, 35)		
	arr=[0]*10
	i=0
	while i<len(arr):
		arr[i]=i
		i+=1
	execFunction(2, addValuesFn, arr, 100)	
	print waitFunctionFinish(1)
	arr=waitFunctionFinish(2)
	for i in arr:
		print i
	shutdownTaskFarm()
else:
	worker()


def exampleFn(a):
	print "Running exampleFn with input "+a
	return a+10

def addValuesFn(a, b):
	i=0
	print "Running addValuesFn with array length "+len(a)+" adding on "+b
	while i<len(a):
		a[i]=a[i]+b
		i+=1
	return a