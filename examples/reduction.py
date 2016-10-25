/*
Illustration of global reduction across all cores, here we find the maximum random number - can also do min, sum and prod
To run: epython reduction.py
*/

from parallel import *
from random import randrange

a=reduce(randrange(100), "max")
print "The highest random number is "+str(a)
