/*
Illustrates control flow, you can limit the cores run with the -c argument
i.e. epython controlflow.py will run on all cores
i.e. epython -c 1 controlflow.py will run on core 1 only
i.e. epython -c 1,2,3,4,9 controlflow.py will run on cores 1,2,3,4 and 9
i.e. epython -c 1:7 controlflow.py will run on cores 1 to 7 inclusive
*/


from parallel import *

if coreid()==0 or coreid()==1:
  print "Core id is 0 or 1"
elif coreid()==2:
  print "Core id is 2"
else:
  print "Core id is not 0, 1 or 2"
