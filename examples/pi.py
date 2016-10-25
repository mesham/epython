/*
The dartboard method to find PI which is an example of a Monte Carlo method. Apart from the reduction at the end it is embarasingly
parallel.
*/

from parallel import *
from random import random
from math import pow

darts=100
rounds=10
mypi=0.0

if coreid()==0: print "Using "+numcores()+" cores to estimate PI, this might take a few moments....."
i=1
while i<=rounds:
  score=0.0
  j=1
  while j<=darts:
    x=random()
    y=random()

    if (pow(x,2) + pow(y,2) < 1.0):
      score+=1
    j+=1
  mypi=mypi+4.0 * (score/darts)
  i+=1
mypi=reduce(mypi, "sum")
if coreid()==0: print "Value of PI="+str((mypi/rounds)/numcores())
