all: epiphany

standalone: clean
	@cd host; $(MAKE) ebasic STANDALONE=1
	@mv host/ebasic-host .

standalone-full: clean
	@cd host; $(MAKE) full STANDALONE=1
	@mv host/ebasic-host .

epiphany: clean host-build device-build

full: clean host-full device-build

host-build:
	@cd host; $(MAKE) ebasic
	@mv host/ebasic-host .

host-full:
	@cd host; $(MAKE) full
	@mv host/ebasic-host .
	
device-build:	
	@cd device; $(MAKE)
	@mv device/ebasic-device.srec .

clean: 
	@cd interpreter; rm -f *.o *.d
	@cd host; $(MAKE) clean
	@cd device; $(MAKE) clean

install:
	cp ebasic-host ebasic-device.srec /usr/bin
	cp ebasic.sh /usr/bin/ebasic
