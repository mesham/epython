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

microblaze: clean microblaze-device-build
	@cd host; $(MAKE) epython MICROBLAZE=1
	@mv host/epython-host epython-microblaze

microblaze-full: clean microblaze-device-build
	@cd host; $(MAKE) full MICROBLAZE=1
	@mv host/epython-host epython-microblaze

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

microblaze-device-build:
	@cd devices/microblaze; $(MAKE)
	@mv devices/microblaze/epython-microblaze.bin .

clean: 
	@cd interpreter; rm -f *.o *.d
	@cd host; $(MAKE) clean
	@cd devices/epiphany; $(MAKE) clean

install:
	@mkdir -p $(DESTDIR)$(bindir)
	@cp epython-microblaze epython-microblaze.bin $(DESTDIR)$(bindir)
	@cp epython.sh $(DESTDIR)$(bindir)/epython
	@mkdir -p $(DESTDIR)$(includedir)/epython
	@cp -R modules $(DESTDIR)$(includedir)/epython/.
	@echo 'export EPYTHONPATH=$$EPYTHONPATH:$(includedir)/epython/modules:$(shell pwd)' >> ~/.bashrc
	@echo 'export PYTHONPATH=$$PYTHONPATH:$(includedir)/epython/modules/fullpython' >> ~/.bashrc
	@ln -s $(DESTDIR)$(includedir)/epython/modules/fullpython/epython.py /root/.ipython/epython.py
	@echo "ePython installed, start a new bash session by executing bash before running ePython"

uninstall:
	@rm $(DESTDIR)$(bindir)/epython-microblaze
	@rm $(DESTDIR)$(bindir)/epython-microblaze.bin
	@rm $(DESTDIR)$(bindir)/epython
	@rm -Rf $(DESTDIR)$(includedir)/epython
	@rm /root/.ipython/epython.py
