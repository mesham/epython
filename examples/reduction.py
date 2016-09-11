/*
Illustration of global reduction across all cores, here we find the maximum random number - can also do min, sum and prod
To run: epython reduction.py
*/

from parallel import *

a=reduce(random%100, "max")
print "The highest random number is "+str(a)
