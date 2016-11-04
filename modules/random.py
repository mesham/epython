def randint(a, b):
	return (native rtl_random() % (b-a)) + a

def randrange(a):
    return native rtl_random() % a

def random():
    return native rtl_random() % 20000 / 20001.0
