/*
Simple odd-even sort
*/

from util import *
from random import randrange

dim x[100]
for i in range(99):
	x[i]=randrange(100)

sorted=false
while not sorted:
	sorted=true
	for i in range(0, len(x)-1, 2):
		if x[i] > x[i+1]:
			temp= x[i]
			x[i]=x[i+1]
			x[i+1] = temp
			sorted=false
	for i in range(1, len(x)-2, 2):
		if x[i] > x[i+1]:
			temp= x[i]
			x[i]=x[i+1]
			x[i+1] = temp
			sorted=false

for i in range(99):
	print x[i]