/*
Jacobi iteration to solve Laplace's equation for diffusion in one dimension
This illustrates distributing data amongst the cores, halo swapping and reductions
*/

import parallel

DATA_SIZE=100
MAX_ITS=10000

# Work out the amount of data to hold on this core
local_size=DATA_SIZE/numcores()
if local_size * numcores() != DATA_SIZE:
        if (coreid() < DATA_SIZE-local_size*numcores()): local_size=local_size+1

# Allocate the two arrays (two as this is Jacobi) we +2 to account for halos/boundary conditions
dim data[local_size+2]
dim data_p1[local_size+2]

# Set the initial conditions
i=0
while i<=local_size+1:
        data[i]=0.0
        i+=1

if coreid()==0: data[0]=1.0
if coreid()==numcores()-1: data[local_size+1]=10.0

# Compute the initial absolute residual
tmpnorm=0.0
i=1
while i<=local_size:
        tmpnorm=tmpnorm+(data[i]*2-data[i-1]-data[i+1])^2
        i+=1
tmpnorm=reduce(tmpnorm, "sum")
bnorm=sqrt(tmpnorm)

norm=1.0
its=0
while norm >= 1e-4 and its < MAX_ITS:
        # Halo swap to my left and right neighbours if I have them
        if (coreid() > 0): data[0]=sendrecv(data[1], coreid()-1)        
        if (coreid() < numcores()-1): data[local_size+1]=sendrecv(data[local_size], coreid()+1)

        # Calculate current residual
        tmpnorm=0.0
        i=1
        while i<=local_size:
                tmpnorm=tmpnorm+(data[i]*2-data[i-1]-data[i+1])^2
                i+=1
        tmpnorm=reduce(tmpnorm, "sum")
        norm=sqrt(tmpnorm)/bnorm

        if coreid()==0 and its%1000 == 0: print "RNorm is "+norm+" at "+its+" iterations"

        # Performs the Jacobi iteration for Laplace
        i=1
        while i<=local_size:
                data_p1[i]=0.5* (data[i-1] + data[i+1])
                i+=1
        # Swap data around for next iteration
        i=1
        while i<=local_size:
                data[i]=data_p1[i]
                i+=1
        its+=1

if coreid()==0: print "Completed in "+its+" iterations, RNorm="+norm