from util import *
from parallel import *

ln=25
N=ln * numcores()
dim x[ln]
dim other[ln]
for i in range(ln-1):
	x[i]=random%100

for i in range(numcores()-1):
	bubblesort(x)
	partner=0
	if (i%2 == 0):
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

def bubblesort(d):
	i=0
	while i<len(d):
		j=0
		while j<len(d):
			if d[j] > d[i]:
				temp=d[i]
				d[i]=d[j]
				d[j]=temp
			j=j+1
		i=i+1

def get_min_index(a):
	v=0
	j=-1
	for i in range(len(a)-1):
		if (j == -1 or v > a[i]): 
			v=a[i]
			j=i
	return j

def get_max_index(a):
	v=0
	j=-1
	for i in range(len(a)-1):
		if (j == -1 or v < a[i]): 
			v=a[i]
			j=i
	return j