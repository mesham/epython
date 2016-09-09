/*
Illustration of P2P blocking send and receives from for 0 to core 1.
To run: epython p2pcomm.py
*/

import parallel

if coreid()==0:
  send(20, 1)
elif coreid()==1:
  print "Got value "+str(recv(0))+" from core 0"
