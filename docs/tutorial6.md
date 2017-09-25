# Offloading kernels from Python to the Epiphany

The latest version of ePython makes it possible to take existing Python code and offload specific functions (we tend to call them kernels) to the Epiphany cores. This is really viewing the Epiphany as an accelerator, where codes run on the host (the Parallella) and specific computationally intensive kernels are then offloaded to the accelerator for execution. The good news is that, using ePython, it is super easy to do this!

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

**Important:** Unlike some other ePython tutorials, all the code snipets here are to be executed under the CPython interpreter (using the *python* command.)

### Offloading a Python function

To offload a Python function onto the Epiphany we first need to import the *epython* module, in the code example below we do this at line one. Next we simply need to decorate each function to be offloaded with the *@offload* decorator. If you run this in any Python interpreter on the Parallella (via the *python* command) then you will see each Epiphany core displays the *Hello World* message and a list of size 16 is displayed, each element with the value of 30.

```python
from epython import offload

@offload
def helloworld(a,b):
  print "Hello World"
  return a+b

print helloworld(10, 20)
```

If you comment out line three (the *offload* decorator) and re-run then a single *Hello World* and 30 value is displayed. Without the decorator then the *helloworld* function runs on the Parallella only (what we call the host.) When we offload a function to the Epiphany behind the scenes it will copy your code and function arguments to the Epiphany cores. Once the function has completed then each core will send its return value back (if there is one) to the Parallella host. In this example the return value is 30 (10 plus 20) and the function call provides 16 of these values - one from each Epiphany core.

### Non-blocking asynchronous kernel launches

The previous example was blocking, where execution in Python on the host will stop and wait for the kernel to run to completion on the Epiphany before continuing. We don't always want this, instead it can sometimes be nice to launch kernels on the Epiphany, then whilst these run go and do something else before grabbing the results sometime later.

```python
from epython import offload

@offload(async=True)
def helloworld(a,b):
  print "Hello World"
  return a+b

handler=helloworld(10, 20)
print handler.wait()
```

In the code example above we have added the argument *async=True* to the *offload* decorator, which tells ePython to launch this function in an asynchronous, non-blocking, manner. Instead of returning the values directly from the function call (at line 8) a handler is returned which can be used to track function execution. At line 9 we are telling Python to wait upon handler completion, which will return the actual returned values from each kernel on the Epiphanies. It is also possible to use the *wait_any* call to wait for any return value (and potentially use this whilst other cores complete) as well as the *test* call which will return whether at least one kernel has completed and made its return value is available.

What if you launch multiple kernels without waiting for previous ones to complete? That's absolutely fine as ePython contains a scheduler which will queue up kernel launches until the Epiphany cores are free to execute them.

### Running on a subset of the Epiphany cores

Up until this point we have executed our kernel on all the Epiphany cores, but often you want to limit to a subset of the cores instead. Using arguments to the *offload* directive we can instruct ePython how many and/or what cores to run on.

```python
from epython import offload

@offload(auto=4)
def helloworld(a,b):
  print "Hello World"
  return a+b

print helloworld(10, 20)
```

In this example we have added the *auto* argment to the *offload* directive, this tells ePython to run over 4 cores - but you don't care which cores these are so to best select exactly which cores to run over (i.e. idle cores.) Instead of *auto* you can use *target*, for instance *target=[1,5,8]* which will explicitly run the kernel only on cores 1, 5 and 8.

```python
from epython import offload

@offload
def helloworld(a,b):
  print "Hello World"
  return a+b

h=helloworld(10, 20, target=[9, 10], async=True)
print h.wait()
```

In the example above we have done things slightly differently - this *helloworld* function will execute asynchronously and on Epiphany cores 9 and 10 only. But we have instructed ePython to do this by arguments to the function call rather than arguments to the *offload* decorator. This provides additional flexibility, you can think of arguments to the specific function call as overriding the options provided to the decorator. For instance here by default *helloworld* will run on all cores in a blocking manner due to the arguments (or lack thereof) to the *offload* decorator. However we have overridden the behaviour just for this one specific kernel launch to execute asynchronously only on Epiphany cores 9 and 10.

### Short cuts for offload arguments

Remembering the offload arguments for common calls can be a bit of a pain - hence we have also introduced the *offload_multiple* and *offload_single* decorators. These can be thought of exactly the same as the *offload* directive, but set up some pre-defined behaviour. The *offload_multiple* decorator will launch kernels in an asynchronous, non-blocking manner, on a subset of cores (the number given by the *cores* argument.) The *offload_single* decorator will launch the kernel in an asynchronous, non-blocking, manner on any single Epiphany core.

```python
from epython import offload_multiple, offload_single, waitAll

@offload_multiple(cores=8)
def adder(a,b):
  return a+b

@offload_single
def subtractor(a,b):
  return a-b


h1=adder(10,20)
h2=subtractor(10,20)
print waitAll(h1,h2)
```

In this code snippet we have two functions, an *adder* function that will run over 8 Epiphany cores and a *substractor* function that will run only on one Epiphany core. These are both launched and the *waitAll* ePython call is issued to wait for all provided handlers to complete which also returns the kernel values from the Epiphany.

### Putting it all together to find PI

Back in ([tutorial 2](tutorial2.md)) we ran a code directly on the Epiphany cores through ePython to find the value of PI using the dartboard method. We can modify this code to instead be executed from CPython, with the computational kernel offloaded to the Epiphany cores.

```python
from epython import offload

@offload
def findPI(darts, rounds):
  from random import random
  from math import pow
  mypi=0.0
  i=1
  while i<=rounds:
    score=0.0
    j=1
    while j<=darts:
      x=random()
      y=random()
      if (pow(x,2) + pow(y,2) < 1.0):
        score+=1
      j+=1
    mypi=mypi+4.0 * (score/darts)
    i+=1
  return mypi

pi=sum(findPI(100,10))
print "Value of PI is "+str((pi/10)/16)
```

In this code the *findPI* function will run on each Epiphany core - you can see that we are also importing specific module functions in this kernel too to provide us with *random* from the *random* module and the *pow* function from the *math* module (lines 5 and 6.) As an exercise, if you comment out the offload directive (line 3) and replace the last two lines with *print findPI(100,10)/10* then this will run on the host (the Parallella) in CPython only.

### Summary

In this tutorial we have looked at offloading specific functions (we often call then kernels) in an existing Python code onto the Epiphany. This is really useful, not least because ePython only supports a subset of the Python language - so being able to offload the computational kernels whilst keeping everything else unchanged on the host can make things far easier.

However this is not quite the full story! What kills performance is copying data to and from an accelerator (i.e. arguments to and return values from the Epiphany kernels.) In the next tutorial we will look at other, data focused, calls to allow us to declare accelerator resident data which kernels can then use without having to copy that data to and from the Epiphany continually.
