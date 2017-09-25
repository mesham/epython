# Installing and getting to grips with ePython

Programming the Epiphany chip is actually very simple, and in this walk through we will be using an Epiphany version the Python programming language (ePython) as our technology. Using ePython you can go from being a complete novice to writing and running your own code on the Epiphany co-processor in 60 seconds. This walk through is intended as an introductory guide, and we will initially discuss installation & configuration of ePython, before looking at some code examples which you can then modify to further explore the concepts.

### Installing ePython
ePython, our version of Python, is open source and available at GitHub. You only need to complete these install commands once, once ePython is installed it can be used as many times as you like. Log into your Parallella board as usual and issue the command

```
git clone https://github.com/mesham/epython.git
```

This will copy ePython onto your machine and a directory called epython will have been created. Next we are going to build this by issuing the make command, from the top level directory (the one you issued the git clone into) issue the following two commands:

```
cd epython
make
```

The build process takes around 20-30 seconds and once complete you will be returned to the bash prompt. The next (and last) step is to install ePython to a central location by issuing the two commands below. You will be promoted for your user's password with the first command. The second command (bash) starts a new bash terminal which has the python paths correctly set and every time bash starts from now on it will be correctly configured for ePython.

```
sudo make install
bash
```

Congratulations! You have installed ePython and are ready to start programming! 

### Let's get coding!

Open a text editor and enter the following code, then save this file as hello.py

```python
print "Hello world"
```

Now issue *epython hello.py* and each Epiphany core will display the message "Hello world", along with the ID of that specific core. Well done - you have just run your first program on the Epiphany co-processor, so let's start exploring some more! The *parallel* package provides a number of functions which are useful for parallel codes. We are going to look at the *coreid* and *numcores* functions. Using the text editor, put the following code into your source file *hello.py* and reissue *epython hello.py*

```python
import parallel
print "Hello world from core "+coreid()+" out of "+numcores()+" cores"
```

Line one will import the parallel functions (of which *coreid* and *numcores* are members.) Line two then displays a similar message from each core as the first example, but also includes the ID of each core and total number of cores in the output. We don't have to use all Epiphany cores, one can set the number of cores via the *-d* command line argument, for instance *epython -d 5 hello.py* will only run over five Epiphany cores (you should not select a number greater than the number of physical cores.)

### You're doing great, let's look at something a bit more advanced

We have been printing out information about the cores, but we can also use this in other ways too. The first code example in this section will display an even or odd message depending upon the core's id.

```python
import parallel
if coreid() % 2 == 0:
  print "Even core"
else:
  print "Odd core"
```

Now we are going to put this all together and produce a slightly more complex example. In the following code the first core will request a number from the user (this can be an integer or float.) The *bcast* function is then called (part of the parallel package) to broadcast this number from the root process (in this case 0, the second argument to the *bcast* call) to all other cores. Each core then displays the number it has just received.

```python
import parallel
a=0
if coreid()==0:
  a=input("Enter a number: ")
a=bcast(a,0)
print "Number is "+a
```

This is an example of a collective communication, where each process collectively works together to produce some final value. Collective communications form a major corner stone of parallel programming and broadcasting values between processes (or Epiphany cores in this case) is a fundamental aspect of many parallel codes running on modern supercomputers. This topic is covered in more depth in the second tutorial.

### Summary

In this walk through we have installed Epiphany Python and then run a few simple, introductory examples to illustrate running codes on the Epiphany co-processor. We have just scratched the surface here and as you can probably imagine, there is far more to explore. ePython comes with complete documentation (doc folder) along with a number of code examples which you can play with.
