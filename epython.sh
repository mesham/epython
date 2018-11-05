#!/bin/bash

export EPYTHONPATH=$EPYTHONPATH:`pwd`:/usr/include/epython/modules

FILE=epython-microblaze

if [ -f $FILE ]
then
FILE=./epython-microblaze
else
FILE=/usr/bin/epython-microblaze
fi

sudo $FILE "$@"
