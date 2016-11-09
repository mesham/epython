import parallel
import taskfarm
import util
from math import pow
from random import random

rounds=10
initTaskFarm(0)

if (coreid()==0):
	piVal=0.0
	j=0
	while j<rounds:
		for i in range(1,numcores()-1):
			execFunction(i, simulateDarts, 1000)
		for i in range(1,numcores()-1):
			piVal+=waitFunctionFinish(i)
		j+=1
	
	print (piVal/rounds)/(numcores()-1)
	shutdownTaskFarm()
else:
	worker()

def simulateDarts(num_darts):
	score=0.0
	j=1
	while j<=num_darts:
		x=random()
		y=random()

		if (pow(x,2) + pow(y,2) < 1.0): score+=1			
		j+=1
	return 4.0 * (score/num_darts)
	