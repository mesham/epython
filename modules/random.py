def randint(a, b):
	return (native random() % (b-a)) + a

def randrange(a):
    return native random() % a

def random():
    return native random() % 20000 / 20001.0
