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

epiphany: clean epiphany-device-build
	@cd host; $(MAKE) epython EPIPHANY=1
	@mv host/epython-host .

epiphany-full: clean epiphany-device-build
	@cd host; $(MAKE) full EPIPHANY=1
	@mv host/epython-host .
	
epiphany-device-build:	
	@cd devices/epiphany; $(MAKE)
	@mv devices/epiphany/epython-epiphany.srec .
	@mv devices/epiphany/epython-epiphany.elf .

clean: 
	@cd interpreter; rm -f *.o *.d
	@cd host; $(MAKE) clean
	@cd devices/epiphany; $(MAKE) clean

install:
	@mkdir -p $(DESTDIR)$(bindir)
	@cp epython-host epython-epiphany.srec epython-epiphany.elf $(DESTDIR)$(bindir)
	@cp epython.sh $(DESTDIR)$(bindir)/epython
	@mkdir -p $(DESTDIR)$(includedir)/epython
	@cp -R modules $(DESTDIR)$(includedir)/epython/.
	@echo 'export EPYTHONPATH=$$EPYTHONPATH:$(includedir)/epython/modules:$(shell pwd)' >> ~/.bashrc
	@echo 'export PYTHONPATH=$$PYTHONPATH:$(includedir)/epython/modules/fullpython' >> ~/.bashrc
	@echo "ePython installed, start a new bash session by executing bash before running ePython"

uninstall:
	@rm $(DESTDIR)$(bindir)/epython-host
	@rm $(DESTDIR)$(bindir)/epython-epiphany.srec
	@rm $(DESTDIR)$(bindir)/epython-epiphany.elf
	@rm $(DESTDIR)$(bindir)/epython
	@rm $(DESTDIR)$(includedir)/epython/modules/*.py
