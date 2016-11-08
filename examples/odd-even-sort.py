/*
Simple odd-even sort
*/

from util import *
from random import randrange
from array import len, array

x=array(100)
for i in range(99):
	x[i]=randrange(100)

sorted=false
while not sorted:
	sorted=true
	i=0
	while i<len(x):
		if x[i] > x[i+1]:
			temp= x[i]
			x[i]=x[i+1]
			x[i+1] = temp
			sorted=false
		i+=2
	i=1
	while i<len(x)-1:
		if x[i] > x[i+1]:
			temp= x[i]
			x[i]=x[i+1]
			x[i+1] = temp
			sorted=false
		i+=2

for i in x:
	print i