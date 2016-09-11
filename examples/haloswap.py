/*
Illustrates one dimensional halo swapping from cores to the left and right
Note that there is no wrap around, therefore the left most value at core 0 and the right
most value at core 15 remains unchanged and is the core id.
*/

from parallel import *

DATA_SIZE=12
dim data[DATA_SIZE]

i=0
while i<DATA_SIZE:
        data[i]=coreid()
        i+=1

if (coreid() > 0):
        data[0]=sendrecv(coreid(), coreid()-1)

if (coreid() < 15):
        data[11]=sendrecv(coreid(), coreid()+1)

displaypid=bcast(random%16, 0)

if coreid()==displaypid:
        for i in data:
                print "Value is "+str(i)

