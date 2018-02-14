CC=mb-gcc
MB_BASE_DIR=/home/xilinx/pynq/lib/arduino/bsp_iop_arduino
CFLAGS=-I . -I ../../interpreter -Os -fno-exceptions -freg-struct-return -fno-default-inline -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -DMICROBLAZE_TARGET
LDFLAGS=-Wl,-T -Wl,$(MB_BASE_DIR)/lscript.ld -L$(MB_BASE_DIR)/iop_arduino_mb/lib -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax

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
