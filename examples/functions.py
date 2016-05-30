/*
Illustration of defining functions, note how in anotherfn we provide default values incase the user does not specify them
To run: epython functions.py
*/

def fn(a,b):
  print a+b

def anotherfn(a=10, b=20):
  return a+b


fn(1,2)
fn("hello ", "world")

print anotherfn()
print anotherfn(2)
print anotherfn(2,4)