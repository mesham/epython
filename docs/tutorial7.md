# Epiphany as an accelerator: managing device data

In ([tutorial 6](tutorial6.md)) we looked at using the *offload* decorator on functions (or kernels) to execute them on Epiphany cores. So far we have assumed that data is copied in (via function arguments) for each kernel execution and then copied back to the host (via the return value) once code has finished executing on the Epiphany. Transfering data from host to device and back again is actually really expensive - in the world of GPUs you need to be really careful that the cost of data transfer does not outweigh the computational benefits of the accelertor. 

In addition to offloading functions, it is also possible to define and manage what we call device resident data - i.e. variables that are allocated on each Epiphany core and stay in memory between kernels runs.

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

**Important:** Unlike some other ePython tutorials, all the code snipets here are to be executed under the CPython interpreter (using the *python* command.)

### Defining device resident data

The *epython* module contains a function, *define_on_device* which will define any variable with its current state on each Epiphany core. For instance in the code snippet below the variable *a* has been declared on the host to be an array of size 10. This is then declared on each Epiphany core and each core has its own, private, copy of this variable. These copies are entirely independent and for instance there is nothing stopping the programmer changing the structure or values of the arrays on some of the cores or the host. Once you have defined some data on the Epiphanies these variables are entirely indepdent from each other, for instance changes to variable *a* on Epiphany core 0 will have no impact on any other cores or the host copy of the data.

```python
from epython import offload, define_on_device, copy_from_device

a=[0]*10

define_on_device(a)

@offload
def updateA(i):
  from parallel import coreid
  a[i]=i * coreid()

for i in range(10):
  updateA(i)

print copy_from_device("a")
```

In this code snippet the host is launching the *updateA* kernel on each Epiphany core 10 times. For each kernel launch the array index is passed in and the Epiphany core will set that location in its copy of variable *a* to be *i* multiplied by the ID of the core. Most importantly you can see that variable *a* stays resident on the Epiphany cores between calls of the kernel, so we don't need to pay the penalty of copying this variable to and from the cores on every kernel launch.

At the end of the code the *copy_from_device* is issued on the host to copy the device resident data held in variable *a* on every core back to the host. The host then displays this - it will display 16 arrays each of size 10 elements as there are 16 copies (one per core) of this data. 

You can see with the *copy_from_device* function, we are refering to the variable *a* by a string of its name (i.e. *"a"* rather than *a*.)

### Updating data on the device from the host

The code snippet in this section below illustrates the *copy_to_device* function, where again we define the variable *a* on all Epiphany cores as well as the host. This is first updated on each core to be the value *19* by the call to the *updateA* kernel. Then we copy the value 99 into *a* held on each Epiphany core and overwrite the previous value *19*) with this.

```python
from epython import offload, define_on_device, copy_to_device, copy_from_device

a=23

define_on_device(a)

@offload
def updateA():
  a=19

print copy_from_device("a")
updateA()
print copy_from_device("a")
copy_to_device("a", 99)
print copy_from_device("a")
```

We have illustrated this with single valued variable (scalars), but these functions can equally be used for arrays too. Copying data from the host to the device can be useful as a code progresses. This might be updated values from the host after it has done some more processing, or alternatively it might be a general *scratch* space you reuse between kernel calls and the host is copying in some input data for a series of kernel calls it is about to launch on the cores.

### Data transfer onto a subset of cores

Exactly the same with kernels, we can use additional arguments to these data transfer functions to run them in an asynchronous, non-blocking, manner and/or perform data transfer on a subset of the cores. The code snippet below is very similar to the previous one, but on line 10 we are only copying values of *a* held on cores 7 and 8 back - so the list that is displayed is of size 2 rather than 16. At line 13 we are only changing the value of *a* to be 99 on cores 1, 5 and 9, all other cores retain the existing value of *19*.

```python
from epython import offload, define_on_device, copy_to_device, copy_from_device

a=23

define_on_device(a)

@offload
def updateA():
  a=19

print copy_from_device("a", target=[7,8])
updateA()
print copy_from_device("a")
copy_to_device("a", 99, target=[1,5,9])
print copy_from_device("a")
```

### Asynchronous data transfer

So far the data transfer calls we have looked at have been used in a blocking manner. What I mean from this is that the host will stop and block until the data copy (either to or from) the Epiphany core(s) has completed before continuing. This can be really expensive and the host can be wasting time waiting for data transfers to complete rather than getting on with useful work. Of course sometimes you definately want this blocking behaviour, but equally other times it can be useful to kick off a data transfer and then go and do something else whilst this is in progress.

```python
from epython import offload, define_on_device, copy_to_device, copy_from_device
from random import random

a=[0]*100

define_on_device(a)

for i in range(100):
  a[i]=random()

h=copy_to_device("a", a, async=True, target=range(10))

@offload
def add(d1,d2):
  return d1+d2

somevalue=add(1,5, target=[11])
h.wait()

h=copy_from_device("a", target=[1], async=True)

print h.test()
print h.wait()
```

In the code snipet here we define an array of size 100 on each Epiphany core and then fill this up with random numbers on the host. The *copy_to_device* function is issued to update this on cores 0 to 9, but this is done asynchronously so that the call completes immediately without waiting for data to have been physically copied. At this point you MUST NOT update the host variable *a* (until the call has completed) as it is actively copying data in the background. Whilst the copying is on going, the *add* function is launched on core 11 and then we use *h.wait()* to wait on the handler *h* which is tracking the asynchronous data copying (at this point you can then change *a* on the device.)

Similarly at line 20 we asynchronously copy the data held in *a* from Epiphany core 0, completion is tested for at line 22 and waited on (and then displayed) at line 23. You can see that this feels very similar to the way we launch kernels asynchronously and on a subset of the Epiphany cores - this is no accident and actually behind the scenes it uses the exact same mechanism.

### Chaining data transfer and kernal launches

It is often useful to chain data transfers and kernel launches, so that you can asynchronously kick off all the aspects that need to run on the Epiphany (data transfers and kernel runs) at a single point, then go ahead and do other stuff on the host. Crticically when you do this you need to be confident that the data transfer will complete before the kernel executes. The good news is that in ePython the order of launch is guaranteed to be the order in which operations are scheduled, such that if *A*, *B* and *C* are scheduled to run on a specific Epiphany core then we guarantee that they will execute in that order.

```python
from epython import offload, define_on_device, copy_to_device, waitAll
from random import random

a=[0]*100

define_on_device(a)

for i in range(100):
  a[i]=random()
  
@offload(async=True)
def addAllA():
  i=0
  value=0
  while i < size(a):
    value+=a[i]
    i+=1
  return value

h1=copy_to_device("a", a, async=True, target=[1])
h2=addAllA(target=[0,1])
print waitAll(h1,h2)
```

The code snippet of this section illustates this concept, where an asynchronous data copy is started on core 1 (returning the handle *h1*.) Then the *addAllA* kernel is launched on cores 0 and 1 asynchronously and we wait for both handles at line 22. Due to the ordering of launch, ePython guarantees that the *addAllA* kernel will only execute on core 1 once the data transfer has completed to that core. There is no data transfer to core 0, so the kernel will launch immediately and return 0.

### Summary

In this tutorial we have looked at offloading parts of Python codes onto Epiphany cores in more detail. Carefully managing device resident data, often with asynchronous data copying, can provide significant performance benefits over simply copying all data on every kernel launch. For more information you can refer to the  <a href="https://github.com/mesham/epython/blob/dev/examples/jacobi_offload.py" target="_blank">Jacobi offload example</a> which uses device resident data. In this example you can see we launch the two kernels for every iteration which is quite slow (we are constantly launching kernels on the Epiphany cores rather than computation!) As an exercise modify the code so that it moves the iteration loop into the kernel, so that kernels only need to launched once for the entire run.
