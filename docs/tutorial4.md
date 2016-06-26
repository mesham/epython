#Pipelines on the Epiphany
In the previous tutorial (available [here](tutorial3.md)) we looked at splitting a problem up geometrically. Driven by the decomposition of the data, different parts of the problem ran on different Epiphany cores with these cores often needing to communuicate when a neighbouring value held on another core was required. 

Whilst geometric decomposition is a very common approach, not all problems are suited to being split around the geometry of the data and instead this tutorial we will look at splitting up a problem based upon the flow of data, known as a pipeline, 

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

###Pipeline
A core represents a stage of a pipeline and here data flows into the first stage, some processing is performed on it and a resulting value flows into the next stage, which performs processing and passes it onto the next stage etc.. Once data has been sent from one stage to the next then that stage is ready to receive some more data and start processing that. 
<img src="https://raw.githubusercontent.com/mesham/epython/master/docs/pipeline.jpg">

This is illustrated in the diagram, in a pipeline data only flows one way (here from left to right) and at each stage the data is refined, from its initial "raw" value to the final "finished" value. Ideally you want all stages in the pipeline to be busy, when your program starts it takes some time to fill up the pipeline and at the end the pipeline drains.

###ePython pipeline
Based upon a large set of numbers, we want to know the percentage of numbers that are contiguous, i.e. where the same numeric value lies one after another. This leads to a pipeline with four stages:
<ol>
<li>Decides the number of data elements (chosen randomly) for each for that specific sequence.</li>
<li>Based upon the number of elements will generate random numbers for each of these.</li>
<li>Sorts the number sequence</li>
<li>Progresses through the sequence and counts the number of contiguous elements, the percentage of which is output</li>
</ol>

The input to the entire pipeline is the number of sequences to work on and the output of the pipeline is the percentage of contiguous numbers in that set.

```python
import parallel
import util

dim data[510]

if (coreid()==0):
  pipelineStageOne(100)
elif (coreid()==1):
  pipelineStageTwo()
elif (coreid()==2):
  pipelineStageThree()
elif (coreid()==3):
  pipelineStageFour()

def pipelineStageOne(num_items):
  for i in range(num_items):
    num=random % 500 + 5
    send(num, coreid()+1)
  send(-1,coreid()+1)

def pipelineStageTwo():
  num=0
  while num >= 0:
    num=recv(coreid()-1)
    if num > 0:
      i=0
      while i < num:
        data[i]=random % 10
        i+=1
    send(num, coreid()+1)
    if num > 0: send(data, coreid()+1, num)

def pipelineStageThree():
  num=0
  while num >=0:
    num=recv(coreid()-1)
    if num > 0:
      data=recv(coreid()-1, num)
      odd_even_sort(data, num)
    send(num, coreid()+1)
    if num > 0: send(data, coreid()+1, num)
    
def pipelineStageFour():
  num=0
  num_contig=0.0
  total_num=0
  while num >=0:
    num=recv(coreid()-1)
    if num > 0:
      total_num+=num
      data=recv(coreid()-1, num)
      cnum=data[0]
      ccount=1
      i=0
      while i < num:
        if (data[i] == cnum):
          ccount+=1
        else:
          num_contig+=ccount
          cnum=data[i]
          ccount=0
        i+=1
    chance=(num_contig/total_num)*100
    print chance+"% of numbers were contiguous"
```

**This is an illustration of the code, the executable version is <a href="https://github.com/mesham/epython/blob/master/examples/pipeline.py">here</a>**

Based upon its core ID, a core will execute the appropriate function, waiting for data and once it has received this will process it and send the results onto the next stage. The *odd_even_sort* function (not shown here, but in the executable version) will perform an odd-even sort on the number sequence. It can be seen that at the end of the pipeline, stage one will send the value *-1* to stage two, which will then send it along to the next stage and quit. This action is repeated for the other stages and this is known a sentinal or poison pill, which will shut the pipeline down.

So we now have a pipeline, passing data between the cores and each stage operates on this data. However there is a problem, namely that the amount of work per pipeline stage is very uneven. For instance stage 1 will progress very quickly, whereas stage 3 (the sorting stage) will take much longer and fast stages will be held up by the slower stages. Bear in mind though, that our current pipeline is only using 4 of the Epiphany cores, and we have 12 idle cores.... so can we take advantage of these to help address this problem?

###Splitting the pipeline
What we are going to do here is keep stage 1 unique (i.e. on core 0), but then duplicate stages 2, 3 and 4 across all the remaining cores. This is known as a non-linear pipeline and it will look like the diagram here:
<img src="https://raw.githubusercontent.com/mesham/epython/master/docs/split_pipeline.jpg">

Importantly all cores are busy and we have further parallelised the problem, as now not only will each of the four stages operate in parallel, but also multiple cores will be performing the exact same stage work.

```python
.....
if (coreid()==0):
  pipelineStageOne(100)
else:
  if (coreid() % 3 == 1):
    pipelineStageTwo()
  elif (coreid() % 3 == 2):
    pipelineStageThree()
  else:
    pipelineStageFour()

def pipelineStageOne(num_items):
  matchingpid=1
  for i in range(num_items):
    num=random % 500 + 5
    send(num, matchingpid)
    matchingpid+=3
    if matchingpid > 13: matchingpid=1
  for i in range(1,13,3):
    send(-1,i)

.....
```

**This is an illustration of the code, the executable version is <a href="https://github.com/mesham/epython/blob/master/examples/split_pipeline.py">here</a>**

You can see that the code is very similar but core 1 is just maintaining a matching core ID, *matchingpid* which is sends to next.

Time both versions (using the *-t* command line argument), you should see that this split pipeline is far quicker to run than the initial pipeline version.

### Parallelising a stage
The sorting stage of the pipeline is the most expensive, so instead of splitting the pipeline  we could keep with 4 simple stages but just parallelise the sorting stage. Therefore 1 core will execute stages one, two and four and the rest (13 cores) will execute stage three.

```python
.....

if (coreid()==0):
  pipelineStageOne(10)
elif (coreid()==1):
  pipelineStageTwo()
elif (coreid() >= 2 and coreid() <= 14):
  pipelineStageThree()
elif (coreid()==15):
  pipelineStageFour()

.....

def pipelineStageTwo():
  num=0
  while num >= 0:
    num=recv(coreid()-1)
    j=2
    while j<=14:
      if num > 0:
        i=0
        while i < num/13:
          data[i]=random % 1000
          i+=1
        send(num/13, j)
        send(data, j, num/13)
      else:
        send(-1, j)
      j+=1

def pipelineStageThree():
  num=0
  while num >=0:
    num=recv(1)
    if num > 0:
      data=recv(1, num)
      parallel_odd_even_sort(num)
    send(num, 15)
    if num > 0: send(data, 15, num)
    
def pipelineStageFour():
  dim rdata[100]
  num=0
  num_contig=0.0
  total_num=0
  while num >=0:
    i=2
    while i<=14:
      num=recv(i)
      if (num > 0):
        rdata=recv(i, num)
        j=num*i
        while j<num*(i+1):
          data[j]=rdata[j - (num*i)]
          j+=1
      i+=1
    if num > 0:
      .....
    chance=(num_contig/total_num)*100
    print chance+"% of numbers were contiguous"
```

**This is an illustration of the code, the executable version is <a href="https://github.com/mesham/epython/blob/master/examples/parallel_pipeline.py">here</a>**

This approach is a bit more complex as, instead of filling in the entire number sequence and passing it along, stage two will complete each subsequence needed for the different cores working on stage three. Stage three cores then receive the data, executes the *parallel_odd_even_sort* function and send their values onto stage four which assemble them and perform the calculation.

###Summary
In this tutorial we have looked at pipelines, where the parallelism is oriented around the data flow and as it flows through the pipeline's stages the data is refined until we get a final value. This approach is suited to many problems, and some that you might not nescesarily expect (such as <a href="https://en.wikipedia.org/wiki/Instruction_pipelining">CPU instruction pipelines</a>.) Due to the fast interconnect between the Epiphany cores this approach of streaming data between them is potentially very advantageous - but as we have seen you want each stage to be busy at all times, and if your stages have different amounts of computation then additional options need to be considered.

More information about pipelines can be found <a href="http://parlab.eecs.berkeley.edu/wiki/_media/patterns/pipeline-v1.pdf" here</a>
