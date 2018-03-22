CC=mb-gcc
CFLAGS=-I . -I ../../interpreter -Os -fno-exceptions -freg-struct-return -fno-default-inline -DMICROBLAZE_TARGET
LDFLAGS=

all: clean epython-microblaze.elf
epython-microblaze.elf: main.o microblaze-runtime.o ../../interpreter/interpreter.o
bins = epython-microblaze.elf

.PHONE: check

%.o : %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(bins) :
	$(CC) $(LDFLAGS) -o $@ $^ 
	mb-objcopy -O binary epython-microblaze.elf epython-microblaze.bin

clean:
	$(RM) -f -v $(bins) *.yy.[ch] *.tab.[ch] *.o *.d *.output ../../interpreter/*.o

-include *.d
