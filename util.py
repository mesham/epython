def range(a,b):
	dim r[(b-a)+1]
	i=a
	while i<=b:
		r[i-a]=i
		i=i+1
	return r

def xrange(a,b):
	return range(a,b)