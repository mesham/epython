# Offloading kernels from Python to the Epiphany

The latest version of ePython makes it possible to take existing Python code and offload specific functions (we tend to call them kernels) to the Epiphany cores. From a programming perspective this is very simple to do and get an example up and running which is what we will be looking at in this tutorial.

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

** Important: Unlike some other ePython tutorials, all the code snipets here are to be executed under the CPython interpreter (using the *python* command.) **

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
