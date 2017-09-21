from epython import *
import array
import math

data=None
data_p1=None
define_on_device(data)
define_on_device(data_p1)

MAX_ITS=10000

@offload
def initialise(global_size):
  num_local=global_size/(numcores()-1)
  if num_local * (numcores()-1) != global_size:
    if (coreid() < global_size-num_local*(numcores()-1)): num_local+=1
  data=[0.0]*(num_local+2)
  data_p1=[0.0]*(num_local+2)
  if coreid()==0: data[0]=1.0
  if coreid()==numcores()-2: data[num_local+1]=10.0

@offload
def calc_residual():
  tmpnorm=0.0
  i=1
  while i<=len(data)-2:
    tmpnorm=tmpnorm+(data[i]*2-data[i-1]-data[i+1])^2
    i+=1
  return tmpnorm

@offload
def jacobi_iteration():
  if (coreid() > 0): data[0]=sendrecv(data[1], coreid()-1)
  if (coreid() < numcores()-2): data[len(data)-1]=sendrecv(data[len(data)-2], coreid()+1)
  i=1
  while i<=len(data)-2:
    data_p1[i]=0.5* (data[i-1] + data[i+1])
    i+=1
  # Swap data around for next iteration
  i=1
  while i<=len(data)-2:
    data[i]=data_p1[i]
    i+=1

initialise(100)
a=calc_residual()
bnorm=math.sqrt(sum(a))

norm=1.0
it=0

while norm > 1e-4:
  jacobi_iteration()
  rn=calc_residual()
  norm=math.sqrt(sum(rn))/bnorm
  it+=1
  if it%50 == 0 : print "Rnorm is "+str(norm)+" after "+str(it)+" iterations"
