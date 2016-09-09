/*
Illustration of printing, core id and conditional statements
To run: epython coreidentity.py
*/

import parallel

print "Hello world from core "+str(coreid())

if coreid()==5:
  print "Hello only from core "+str(coreid())

