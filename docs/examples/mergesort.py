import util
import parallel

na=128
dim data[na]

if coreid()==0:
	populateData(data, na)
	sort(data, 0, na)
	displayData(data, na)
else:
	level=getlevel()
	pid=getparentId(level)
	dsize=na/(2^level)
	d=recv(pid, dsize)
	sort(d, level, dsize)
	send(d, coreid() - (2^(4-level)), dsize)
	
def sort(d, level, thissize):
	if level == 4:
		bubblesort(d, thissize)
	else:
		pivot=thissize/2
		cid=coreid() + (2^(3-level))
		send(d, cid, pivot)
		dim split[thissize-pivot]
		for x in range(pivot, thissize-1):
			split[x-pivot]=d[x]
		sort(split,level+1, thissize-pivot)
		ssplit=recv(cid, pivot)
		merge(d, split, ssplit, pivot, thissize)

def merge(target, split, ssplit, pivot, length):
	i=0
	pre_index=0
	post_index=0
	while i<length:
		if pre_index >= pivot:
			target[i]=ssplit[post_index]
			post_index=post_index+1
		elif post_index >=length-pivot:
			target[i]=split[pre_index]
			pre_index=pre_index+1
		elif split[pre_index] < ssplit[post_index]:
			target[i]=split[pre_index]
			pre_index=pre_index+1
		else:
			target[i]=ssplit[post_index]
			post_index=post_index+1
		i=i+1

def bubblesort(d,size):
	i=0
	while i<size:
		j=0
		while j<size:
			if d[j] > d[i]:
				temp=d[i]
				d[i]=d[j]
				d[j]=temp
			j=j+1
		i=i+1


def populateData(d, l):
	for x in range(l-1):
		d[x]=random%1000

def displayData(d, l):
	i=0
	while i<l:
		print d[i]
		i=i+1

def getlevel(level):
	i=0
	cc=numcores()
	while cc > 1:
		if isdivbyn(coreid(), cc):	return i
		cc=cc/2
		i=i+1
	return i

def getparentId(level):
	cc=numcores()
	for x in range(1,level):
		cc=cc/2
	return coreid()-cc

def isdivbyn(a,b):
	if (a/b)*b==a:
		return true
	else:
		return false
	