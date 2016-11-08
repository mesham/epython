from util import *
from parallel import *
from random import randrange
from array import len, array

ln=25
N=ln * numcores()
x=[0]*ln
other=[0]*ln
i=0
while i < ln:
  x[i]=randrange(1000)
  i+=1

k=0
while k <= numcores()-1:
  oddSort(x)
  partner=0
  if (k%2 == 0):
    if (coreid() % 2 == 0):
      partner=coreid()+1
    else:
      partner=coreid()-1
  else:
    if (coreid()%2 == 0):
      partner=coreid()-1
    else:
      partner=coreid()+1
  if (partner >= 0 and partner < numcores()):
    other=sendrecv(x, partner, ln)
    if coreid() < partner:
      swap_values(other, x)
    else:
      swap_values(x, other)
  k+=1

for j in range(numcores()-1):
  if (j==coreid()):
    for i in range(ln-1):
      print x[i]
  sync()

def swap_values(a, b):
  searching=true
  while searching:
    searching=false
    min_index=get_min_index(a)
    max_index=get_max_index(b)
    if (a[min_index] < b[max_index]):
      temp=a[min_index]
      a[min_index]=b[max_index]
      b[max_index]=temp
      searching=true

def get_min_index(a):
  v=0
  j=-1
  i=0
  while i <= len(a)-1:
    if (j == -1 or v > a[i]):
      v=a[i]
      j=i
    i+=1
  return j

def get_max_index(a):
  v=0
  j=-1
  i=0
  while i <= len(a)-1:
    if (j == -1 or v < a[i]):
      v=a[i]
      j=i
    i+=1
  return j