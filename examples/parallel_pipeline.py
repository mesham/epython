import parallel
import util

dim data[300]

if (coreid()==0):
	pipelineStageOne(10)
elif (coreid()==1):
	pipelineStageTwo()
elif (coreid() >= 2 and coreid() <= 14):
	pipelineStageThree()
elif (coreid()==15):
	pipelineStageFour()

def pipelineStageOne(num_items):
	for i in range(num_items):
		num=random % 280 + 5
		num+=num % 13
		send(num, coreid()+1)
	send(-1,coreid()+1)

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
			num*=13
			total_num+=num
			cnum=data[0]
			ccount=0
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

def parallel_odd_even_sort(ln):
	dim other[ln]
	i=2
	while i <= 14:
		odd_even_sort(ln)
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
		if (partner >= 2 and partner <= 14):
			other=sendrecv(data, partner, ln)
			if coreid() < partner:
				swap_values(other, data)
			else:
				swap_values(data, other)
		i+=1

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
	while i < len(a):
		if (j == -1 or v > a[i]): 
			v=a[i]
			j=i
		i+=1
	return j

def get_max_index(a):
	v=0
	j=-1
	i=0
	while i < len(a):
		if (j == -1 or v < a[i]): 
			v=a[i]
			j=i
		i+=1
	return j

def odd_even_sort(l):
	sorted=false
	while not sorted:
		sorted=true
		i=0
		while i < l:
			if data[i] > data[i+1]:
				temp=data[i]
				data[i]=data[i+1]
				data[i+1]=temp
				sorted=false
			i+=2
		i=1
		while i < l-1:
			if data[i] > data[i+1]:
				temp=data[i]
				data[i]=data[i+1]
				data[i+1]=temp
				sorted=false
			i+=2
