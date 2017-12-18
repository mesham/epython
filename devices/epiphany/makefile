CC=e-gcc
CFLAGS=-I ../../interpreter -Os -fno-exceptions -freg-struct-return -fno-default-inline
LDFLAGS=-T linker.ldf -Wl,--gc-sections

all: clean epython-epiphany.elf
epython-device.elf: main.o epiphany-runtime.o ../../interpreter/interpreter.o
bins = epython-epiphany.elf

.PHONE: check

%.o : %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(bins) :
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -le-lib
	e-objcopy --srec-forceS3 --output-target srec epython-epiphany.elf epython-epiphany.srec

clean:
	$(RM) -f -v $(bins) *.yy.[ch] *.tab.[ch] *.o *.d *.output ../../interpreter/*.o

-include *.d
