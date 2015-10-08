def range(a,b=none):
	if (b is none):
		b=a
		a=0
	dim r[(b-a)+1]
	i=a
	while i<=b:
		r[i-a]=i
		i+=1
	return r

def xrange(a,b):
	return range(a,b)