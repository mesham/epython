def randint(a, b):
	return (native rtl_math(14) % (b-a)) + a

def randrange(a):
    return native rtl_math(14) % a

def random():
    return native rtl_math(14) % 20000 / 20001.0
