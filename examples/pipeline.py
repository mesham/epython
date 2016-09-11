from parallel import *
from util import *

dim data[300]

if (coreid()==0):
	pipelineStageOne(10)
elif (coreid()==1):
	pipelineStageTwo()
elif (coreid()==2):
	pipelineStageThree()
elif (coreid()==3):
	pipelineStageFour()

def pipelineStageOne(num_items):
	for i in range(num_items):
		num=random % 295 + 5
		send(num, coreid()+1)
	send(-1,coreid()+1)

def pipelineStageTwo():
	num=0
	while num >= 0:
		num=recv(coreid()-1)
		if num > 0:
			i=0
			while i < num:
				data[i]=random % 1000
				i+=1
		send(num, coreid()+1)
		if num > 0: send(data, coreid()+1, num)

def pipelineStageThree():
	num=0
	while num >=0:
		num=recv(coreid()-1)
		if num > 0:
			data=recv(coreid()-1, num)
			odd_even_sort(num)
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

def odd_even_sort(l):
	sorted=false
	while not sorted:
		sorted=true
		i=0
		while i < l:
			if data[i] > data[i+1]:
				temp= data[i]
				data[i]=data[i+1]
				data[i+1] = temp
				sorted=false
			i+=2
		i=1
		while i < l-1:
			if data[i] > data[i+1]:
				temp= data[i]
				data[i]=data[i+1]
				data[i+1] = temp
				sorted=false
			i+=2
