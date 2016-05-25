def range(a,b=none):
	i_a=a
	i_b=b
	if (b is none):
		i_b=a
		i_a=0
	dim r[(i_b-i_a)+1]
	i=i_a
	while i<=i_b:
		r[i-i_a]=i
		i+=1
	return r

def xrange(a,b):
	return range(a,b)