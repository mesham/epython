all: epiphany

standalone: clean
	@cd host; $(MAKE) epython STANDALONE=1
	@mv host/epython-host .

standalone-full: clean
	@cd host; $(MAKE) full STANDALONE=1
	@mv host/epython-host .

epiphany: clean host-build device-build

full: clean host-full device-build

host-build:
	@cd host; $(MAKE) epython
	@mv host/epython-host .

host-full:
	@cd host; $(MAKE) full
	@mv host/epython-host .
	
device-build:	
	@cd device; $(MAKE)
	@mv device/epython-device.srec .

clean: 
	@cd interpreter; rm -f *.o *.d
	@cd host; $(MAKE) clean
	@cd device; $(MAKE) clean

install:
	@cp epython-host epython-device.srec /usr/bin
	@cp epython.sh /usr/bin/epython
	@cp parallel.py /usr/include
	@cp util.py /usr/include
	@echo 'export PYTHONPATH=$$PYTHONPATH:/usr/include:$(shell pwd)' >> ~/.bashrc
	@echo "ePython installed, start a new bash session by executing bash before running ePython"

uninstall:
	@rm /usr/bin/epython-host
	@rm /usr/bin/epython
	@rm /usr/include/parallel.py
	@rm /usr/include/util.py
