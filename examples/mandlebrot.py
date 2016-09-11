/*
Simple mandlbrot example, based on a version by Mike Bell
*/

from parallel import *
from util import *

outstr=""

x=-2.0
y=-1.0 + (coreid()*0.125)

i=0
while i<=66:
  re = x
  im = y
  j=0
  while j<=20:
    re_next = re*re - im*im + x
    im = 2*re*im + y
    re=re_next
    j+=1
  if re*re + im*im < 4:
    outstr = outstr+"#"
  else:
    outstr = outstr+" "
  x+=0.05
  i+=1

for i in range(16):
  if coreid()==i:
    print outstr
  sync()

