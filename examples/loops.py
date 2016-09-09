/*
Illustration of loops
To run: epython loops.py
*/

import util

for x in range(10):
  print "X="+str(x)

for x in range(105,115):
  print "X="+str(x)

list=[10,20,30,40,50,60]
for x in list:
  print "List item="+str(x)

i=10
while i<=20:
  print "I="+str(i)
  i+=1
