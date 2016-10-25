/*
Illustration of arrays, getting a random number and printing values out. Dim will pop the array in core local memory, you can specify shared memory via sdim
To run: epython arrays.py
*/

from random import randrange

dim a[100]
i=0
while i<100:
  a[i]=i
  i+=1
r=randrange(100)
print "Random index is "+str(r)+" value is "+str(a[r])
