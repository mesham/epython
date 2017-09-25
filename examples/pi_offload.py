from epython import offload

@offload
def findPI(darts, rounds):
  from random import random
  from math import pow

  mypi=0.0
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
  return mypi

pi=sum(findPI(100,10))
print "Value of PI is "+str((pi/10)/16)
