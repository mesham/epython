#Parallel messaging with the Epiphany

In this tutorial we are going to explore the parallel capabilities of the Epiphany and develop some parallel codes which take advantage of the fact that we have multiple cores available. The techniques we will be discussing here are the same as those used by HPC programmers to write large scale parallel codes on modern supercomputers.

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

###Point to point communications

In parallel programming, one of the fundamental activities is sending a message from one core to another. Open up a text editor and enter the following code before saving it as *p2p.py*

```python
import parallel

if coreid()==0:
  send(20, 1)
elif coreid()==1:
  print "Got value "+recv(0)+" from core 0"
```

Now issue *epython p2p.py* and core 1 will display that it received the value *20* from core 0. The parallel functions of ePython (in this case *coreid*, *send*, *recv*) are located in the parallel module, therefore before writing any parallel codes in ePython you need to import this as per line 1. At line 4 core 0 will send the value 20 to core 1 - here we supply the value 20 directly but a variable or return value from a function could also be used, and at line 6 core 1 will receive this value from core 0. These send and receive communication calls are blocking, which means that the core will not continue until it has either fully sent or fully received the value. This is something you need to be aware of, as if there is no matching communication call then the core will block and wait forever - for instance edit line 4 and instead of sending to core 1 send to core 2 (the second argument to the *send* function.) Now rerun the code, you will see that the code does not terminate (you can force quit by pressing ctrl and c) because now core 0 is sending to core 2, but core 2 has not issued a receive and core 1 is attempting receiving from core 0 but there is no message being sent to core 1. If you edit line 5 and change the core id from 1 to 2 then this will ensure communications match and fix the issue.

This first example has illustrated two very important concepts, firstly point to point communications and secondly accessing a core's ID (via *coreid*) and selectively executing some code on that core only based upon its id. 

###Broadcasting values

The point to point communications that we have just seen only involve 2 cores for each communication call, the sender and the receiver. Collective communications involve all cores and the first example of this we are going to see is the broadcast, where we broadcast a value from one core (commonly called the root) to every other core. 

```python
import parallel

a=bcast(numcores(), 0)
print "The number from core 0 is "+a
```

In this example the root (core 0) will broadcast the number of cores (determined by the *numcores* function) to every other core including itself, and each core will display this value. The provided value to the function (in this case the number of cores) is only relevant on the root and is ignored by every other core. You can specify the number of Epiphany cores to run on via the *-d* command line argument, for instance, if this is called *bcast.py* then executing *epython -d 5 bcast.py* will run on 5 cores of the Epiphany and your code will report this number. Currently each core executes line 4 and displays the message, based upon what we have already looked at in this tutorial modify the code so that only core 3 prints out the message.

```python
import parallel
from random import randrange

rootcore=2
a=0
if coreid()==rootcore:
  a=bcast(randrange(100), rootcore)
else:
  a=bcast(none, rootcore)
print "The random number from core "+rootcore+" is "+a
```

This code example illustrates a more common format followed by the broadcast, where only the root core (in this case core 2) has some value (in this case a random number between 0 and 100) which it then broadcasts amongst the other cores. On every non root core the input value to the broadcast is ignored, so every other core either provides a dummy value as the value to the broadcast or *none*, which is Python's way of representing the absence of a value. The way this example is written, by modifying the value of the rootcore variable at line 3 you will change the root core for this broadcast call.

###Reducing values

As well as broadcasting values from one process to all others, it is often useful to combine values held on every core together in order to determine a final result. For instance, one might wish to find the maximum value held by each core, or add all the values together. This is known as a reduction, where each core will supply a value and operation to perform, and the final result available on each core is the reduction of these individual values.

```python
import parallel
from random import randrange

a=reduce(randrange(100), "max")
print "The highest random number is "+a
```

In this code each core is generating a random number (using the *random* function, and %100 takes the modulo to 100, hence the number will always be between 0 and 100), and by using the *reduce* call with the *max* argument, the communication function determines the maximum random number that was generated by any core, which is then available to every core in the a variable. One of four operators can be used, *max*, *min*, *sum* and *prod*. By editing the code and changing the operator then you will see the difference this makes to the reported value.

###Synchronisation

It can be useful for all cores to stop and wait for every other core to reach a specific point in the code before proceeding, this is known as synchronisation (or a barrier) and available via the *sync* function.

```python
import parallel

print "Hello from core "+coreid()
sync()
print "After sync from core "+coreid()
```

In this example every core will display an initial message, then stop and wait for every other core before displaying its next message. By commenting out the sync call at line 5 you will remove this stop and wait, and some cores might race ahead of others. As a general note, whilst this barrier synchronisation can be useful (and is often seen in many HPC codes) it is generally considered bad practice because each core is idle whilst it is waiting for every other core, instead of continuing ahead and doing useful work.

###Putting it all together - a parallel code to estimate PI

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/fb/Darts_in_a_dartboard.jpg/283px-Darts_in_a_dartboard.jpg" width="250" align="left">
We are going to estimate the value of PI via the dartboard method, which is an example of a Monte Carlo method (https://en.wikipedia.org/wiki/Monte_Carlo_method.) Basically, imagine we have a dartboard mounted on a wooden backing and the dartboard fits perfectly within this wooden backing as per the diagram.

If the radius of the dartboard is one, then the area of the board will be PI, as the dartboard fits snugly on the wooden backing then the area of the wood is 4 (2 by 2.) Therefore this means the ratio of the area of the circle to that of the wood is pi/4. If we throw lots of darts at the board then randomly some will land on the board and some on the wooden backing, but by probability the ratio of the number landing on the dartboard vs the number that is thrown will be pi/4. 

Each Epiphany core will simulate the throwing of lots of darts at this dartboard, and by tracking the number which land on the board across all cores we can estimate PI. The more darts which are thrown, the more accurate our approximation of PI.

```python
import parallel
from random import random
from math import pow

darts=100
rounds=0
mypi=0.0

if coreid()==0:
  rounds=input("Enter the number of rounds: ")
  rounds=bcast(rounds, 0)
else:
  rounds=bcast(none, 0)
i=1
while i<=rounds:
  score=0.0
  j=1
  while j<=darts:
    x=random()
    y=random()

    if (pow(x,2) + pow(y,2) < 1.0):
      score=score+1
    j+=1
  mypi=mypi+4.0 * (score/darts)
  i+=1
mypi=reduce(mypi, "sum")
if coreid()==0: print "Value of PI="+(mypi/rounds)/numcores()
```

In this code each core works in rounds, throwing *darts* number of darts per round. Initially core 0 requests from the user the number of rounds to run (10 is a good starting number), which is then broadcast amongst the cores at lines 9 and 11. Remember the provided value to a broadcast collective is only relevant on the root core (in this case core 0) - you can see at line 9 that core 0 will broadcast the *rounds* value, which has been inputted by the user, and every other core at line 11 issues the broadcast call with the *none* value, which is Python's way of representing the absence of a value. What we call the computational kernel, the heart of what each core is actually doing, is at lines 13-24 which performs the Monte Carlo method and then at line 25 the values determined at each core are summed together and then displayed at line 26 by core 0. 

By increasing the number of rounds we increase the accuracy of the answer, but the cost is an increase in runtime. You can use the *-t* command line argument to display timing information for each core, for instance *epython -t pi.py*, run with 10, 50, 100 and 500 rounds and you will see the difference (be patient with 500 rounds it takes a few seconds!)

As a general note, we have two extremes when classifying parallelism; at one end tightly coupled problems where each core must very extensively communicate with other cores and at the other end embarrassingly parallel problems where very little (if any) communication is needed. Most HPC codes sit somewhere between these extremes and this example is towards the embarrassingly parallel side, because there are only 2 communications (the initial broadcast and final reduction) and importantly there are no communications required in the computational kernel, so each core can just get on with its computational task. Communications add overhead, so it is useful to understand where a parallel code sits on this scale to give an idea of likely performance and scalability.

###Summary

In this tutorial we have used ePython to introduce some of the basic building blocks of parallelism and shown how quick and easy it is to write parallel codes on the Epiphany. The PI example that we looked at is a simple illustration of a Monte Carlo method, many codes running on the latest supercomputers are based around Monte Carlo methods and more generally the ideas of core identification, point to point & collective communications form the basis of the majority of HPC codes.
