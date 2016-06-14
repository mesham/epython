def range(a,b=none,c=none):
	i_a=a
	i_b=b
	i_c=c
	if (b is none):
		i_b=a
		i_a=0
	if (c is none):
		i_c=1
	dim r[((i_b-i_a)/i_c)+1]
	i=i_a
	j=0
	while i<=i_b:
		r[j]=i
		if (c is none):
			i+=1
		else:
			i=i+c
		j=j+1
	return r

def xrange(a,b):
	return range(a,b)