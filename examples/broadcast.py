/*
Illustration of broadcasting a value from one core (0 here) to each other and displaying the result
To run: epython broadcast.py
*/

from parallel import *

a=bcast(random%100, 0)
print "The random number from core 0 is "+str(a)
