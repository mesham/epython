#Epiphany Python
This is an interpreter for Python which will run on the Epiphany chip and allows for common parallel activities such as communication and synchronisation. Full language documentation can be found in the docs folder. Example codes can be found in docs/examples

##Installation
Type make
If you wish to install it (into the bin directory) then sudo make install followed by starting a new bash session (execute bash at the command line.)

If you do not install it then you can still run epython from the current directory, as ./epython.sh but ensure that epython-device.elf is in the current directory when you run the interpreter. The epython.sh script will detect whether to run as sudo (earlier versions of the parallella OS) or not (later versions.)

In order to include files (required for parallel functions) you must either run your Python codes in the same directory as the executables (and the modules directory) and/or export the PYTHONPATH environment variable to point to the modules directory. When including files, by default ePython will search in the current directory, any subdirectory called modules and then the PYTHONPATH variable, which follows the same syntax as the PATH variable.

Issuing export export PYTHONPATH=$PYTHONPATH:`pwd` in the epython directory will set this to point to the current directory. You can also modify your ~/.bashrc file to contain a similiar command.

For more information about installing ePython refer [here](docs/tutorial1.md), for upgrading ePython refer [here](docs/installupgrade.md)

##Hello world
Create a file called hello, then put in the lines
print "Hello world"

save it, and execute epython hello (or ./epython.sh hello if you have not done make install.)

Each core will display the Hello world message to the screen along with their core id

For more information about first steps with ePython refer [here](docs/tutorial1.md), for more advanced ePython usage then follow the tutorials in the [docs directory](docs) which cover writing parallel Python code on the Epiphany.

##Troubleshooting

Often these are set by default, but if it complains that it can not find e-gcc or the libraries, then you will need to set these environment variables:

export PATH=/opt/adapteva/esdk/tools/e-gnu/bin:$PATH
export EPIPHANY_HOME=/opt/adapteva/esdk

(you might want to place this in your .bashrc file)

##64 cores

ePython has been developed and tested on a 16 core Epiphany machine, if you have a 64 core chip machine then it should work (still on 16 cores), and it should be trivial to edit the source and linker script to support the full 64 cores.

##Rebuilding the parser/lexer
To rebuild the parser and lexer too, then execute *make full*

##SREC and ELF

The device executable is built in both SREC and ELF format, as of 2016 the loading of SREC on the Epiphany is deprecated and will be removed from later SDK releases. You can choose which to load via the -elf and -srec command line arguments. ELF is the default for ePython, apart from very old Epiphany SDK versions which support SREC.
