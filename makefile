prefix ?= /usr
bindir = $(prefix)/bin
includedir = $(prefix)/include

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
	@mkdir -p $(DESTDIR)$(bindir)
	@cp epython-host epython-device.srec epython-device.elf $(DESTDIR)$(bindir)
	@cp epython.sh $(DESTDIR)$(bindir)/epython
	@mkdir -p $(DESTDIR)$(includedir)/epython
	@cp -R modules $(DESTDIR)$(includedir)/epython/.
	@echo 'export EPYTHONPATH=$$EPYTHONPATH:$(includedir)/epython/modules:$(shell pwd)' >> ~/.bashrc
	@echo 'export PYTHONPATH=$$PYTHONPATH:$(includedir)/epython/modules/fullpython:$(shell pwd)' >> ~/.bashrc
	@echo "ePython installed, start a new bash session by executing bash before running ePython"

uninstall:
	@rm $(DESTDIR)$(bindir)/epython-host
	@rm $(DESTDIR)$(bindir)/epython-device.srec
	@rm $(DESTDIR)$(bindir)/epython-device.elf
	@rm $(DESTDIR)$(bindir)/epython
	@rm $(DESTDIR)$(includedir)/epython/modules/*.py
