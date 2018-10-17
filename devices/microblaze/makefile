CC=mb-gcc
MB_BASE_DIR=/home/xilinx/pynq/lib/pmod/bsp_iop_pmod
MB_LIB_DIR=iop_pmoda_mb/lib
CFLAGS=-I . -I ../../interpreter -I /home/xilinx/pynq/lib/pmod/bsp_iop_pmod/iop_pmoda_mb/include -Os -fno-exceptions -freg-struct-return -fno-default-inline -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -Wl,-gc-sections -DMICROBLAZE_TARGET
LDFLAGS=-Wl,-T -Wl,$(MB_BASE_DIR)/lscript.ld -L$(MB_BASE_DIR)/$(MB_LIB_DIR) -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -Wl,-gc-sections

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
