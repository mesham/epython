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
	@mv device/epython-device.elf .

clean: 
	@cd interpreter; rm -f *.o *.d
	@cd host; $(MAKE) clean
	@cd device; $(MAKE) clean

install:
	@cp epython-host epython-device.srec epython-device.elf /usr/bin
	@cp epython.sh /usr/bin/epython
	@mkdir -p /usr/include/epython
	@cp -R modules /usr/include/epython/.
	@echo 'export PYTHONPATH=$$PYTHONPATH:/usr/include/epython/modules:$(shell pwd)' >> ~/.bashrc
	@echo "ePython installed, start a new bash session by executing bash before running ePython"

uninstall:
	@rm /usr/bin/epython-host
	@rm /usr/bin/epython-device.srec
	@rm /usr/bin/epython-device.elf
	@rm /usr/bin/epython
	@rm /usr/include/parallel.py
	@rm /usr/include/util.py
