/*
The dartboard method to find PI which is an example of a Monte Carlo method. Apart from the reduction at the end it is embarasingly
parallel.
*/

import parallel

darts=100
rounds=10
mypi=0.0

if coreid()==0: print "Using "+numcores()+" cores to estimate PI, this might take a few moments....."
i=1
while i<=rounds:
  score=0.0
  j=1
  while j<=darts:
    x=(random % 100000) / 100000.0
    y=(random % 100000) / 100000.0

    if x^2 + y^2 < 1.0:
      score=score+1
    j+=1
  mypi=mypi+4.0 * (score/darts)
  i+=1
mypi=reduce(mypi, "sum")
if coreid()==0: print "Value of PI="+(mypi/rounds)/numcores()
