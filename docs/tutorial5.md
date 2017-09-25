# Python task farms on the Epiphany
Splitting problems up into tasks and running these concurrently over a number of cores is a popular approach to parallelism. In recent year this has becoming more and more popular and is seen as one of the ways in which parallel codes might be written for future machines with very large numbers of processing cores. In this tutorial we are going to look at this task approach and using ePython it is very simple to send tasks around between the Epiphany cores.

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

### Remote procedure calls
Remote Procedure Calls (RPC) is where a core will call a function to execute on another core, providing the arguments to that function and then obtaining any results from its execution. In Python functions are known as *first class*, which means that they can be refered to like any other value and even communicated between the Epiphany cores.

```python
import parallel

if (coreid()==0):
	send(functionToRun, 1)
	send(50, 1)
	print recv(1)
elif (coreid()==1):
	op=recv(0)
	arg=recv(0)
	returnVal=op(arg)
	send(returnVal, 0)

def functionToRun(a):
	print "Running on core 1 "+a
	return a+10
```

In this code core 0 there is a function called *functionToRun*, which takes one argument and returns a value. Core 0 will send this function over to core 1, along with the argument and then await a message back from core 1 which it will then display. Core 1 receives the function (*op*), then receives the argument from core 0 to run this with (into *arg*), it then executes the function and sends back the returned value to core 0.

In this approach we can communicate any functions, any number of arguments and send returned values back from any cores. However there is a problem with how we have written this, namely the fact that for core 0 this is blocking, i.e. it sits idle and waits for the returned value whilst the function is being executed on core 1. This isn't ideal and not particularly parallel because there might be other functions which core 0 wants to execute on other cores.

### The taskfarm module
We have seen so far that sending functions around is a nice way of executing them on other cores, but if these are possibly going to produce results and send them back we don't want to be stalling and waiting for the results. ePython comes with the *taskfarm* module which provides a way of farming tasks out to other cores and avoiding this issue of blocking for results. So now we are going to rewrite the first example but instead using functions from the *taskfarm* module:

```python
import parallel
import taskfarm

initTaskFarm(0)

if (coreid()==0):
	execFunction(1, functionToRun, 50)
	if (testFunctionFinish(1)):
		print "The function has executed"
	else:
		print "The function is still running"
	print waitFunctionFinish(1)
	shutdownTaskFarm()
else:
	worker()

def functionToRun(a):
	print "Running on core 1 "+a
	return a+10
```

The first function call *initTaskFarm* will initialise the task farm and the argument determines which core is the "master", i.e. which will instruct other cores to execute what functions. Every core which is not the master (in this case every core whose id is not 0) will call the *worker* function, which waits for either functions to execute (and then executes them) or for the task farm to shut down. Core 0 then calls *execFunction* which instructs the task farm to execute the *functionToRun* function on core 1 (the first argument) with the value of *50*. This *execFunction* call is non-blocking, this means  that it will return as soon as the required data has been communicated to core 1 rather than when core 1 has finished executing the function itself. It is possible to determine the progress of a remotely running function on a core via the *testFunctionFinish* call and the *waitFunctionFinish* will wait for function completion on a core and return any returned values from that function. The *testFunctionFinish* function just returns true or false (representing whether the remote function has finished executing) so if you use this test, even if this call returns true, then you will still need to call *waitFunctionFinish* to retrieve a returned value. The *shutdownTaskFarm* is called from the master to command the worker cores to shutdown once they have finished running any current functions.

As an exercise extend thsi example to run multiple functions over multiple worker cores (hint, if you get stuck then have a look at the [task_farm_example.py] (../examples/task_farm_example.py) which illustrates how to do this.

### Master worker
<img src="https://raw.githubusercontent.com/mesham/epython/master/docs/masterworker.png" width=300 align="right">
In the previous section we used the terminology of "master" and "worker", this is a common approach in parallelism where one core (in this case that with the ID provided to the *initTaskFarm* function) is a master, dishing out work to all other other cores which are workers. You can see this in the diagram to the right, where the master sends out tasks and data to the workers which then execute these and send back any results and inform the master they have completed (and hence can accept another task.) Many parallel problems can be split up into this approach of master and worker, we have rewritten the estimation of PI via Monte Carlo example of ([tutorial 2](tutorial2.md)) to instead use tasks, the *taskfarm* module and this general parallelisation strategy of master-worker.

```python
import parallel
import taskfarm
import util
from math import pow
from random import random

initTaskFarm(0)

if (coreid()==0):
	piVal=0.0
	for i in range(1,numcores()-1):
		execFunction(i, simulateDarts, 1000)
	for i in range(1,numcores()-1):
		piVal+=waitFunctionFinish(i)
	
	print piVal/(numcores()-1)
	shutdownTaskFarm()
else:
	worker()

def simulateDarts(num_darts):
	score=0.0
	j=1
	while j<=num_darts:
		x=random()
		y=random()

		if (pow(x,2) + pow(y,2) < 1.0): score+=1			
		j+=1
	return 4.0 * (score/num_darts)
```

In the code core 0 is the master, this then remotely executes the *simulateDarts* function on every other core concurrently (as remember *execFunction* is non-blocking), and then when each function is executing it will block for each remote function to complete in tern (via the *waitFunctionFinish* function) and add the returned value to the running total of PI which is then divided to deduce the final value. 

For reasons of simplicity for the example we are just executing the *simulateDarts* function once on each worker core, if you look at the PI example of ([tutorial 2](tutorial2.md)) in more detail you will see that this works in rounds. As an exercise extend the example to include these rounds so there are multiple function calls on each core. Once you have got a simple version of this working then instead of waiting for every function in each round to complete before moving onto the next round, consider how you might use the *testFunctionFinish* to poll all workers and simply re-assign more work (i.e. calls to the *simulateDarts* function) as they become idle.

### Summary
In this tutorial we have look at the concepts of tasks, remote procedure calls, task farms and master worker. It is often possible to rewrite many existing parallel codes in terms of distinct tasks which can be executed concurrently and this can form an alternative approach to parallelism. Whilst, for simplicity, we have focused on running a single task many times over all the cores (homogeneous), it is easy to see how one can provide additional functions and run tasks heterogeneously, i.e. very different tasks on different Epiphany cores. This can work well for some work loads and the tasks themselves can become quite complex and irregular, for instance involving communications.
