/*
Illustration of broadcasting a value from one core (0 here) to each other and displaying the result
To run: epython broadcast.py
*/

import parallel
a=bcast(random%100, 0)
print "The random number from core 0 is "+a
