CC=e-gcc
CFLAGS=-I ../ -I ../interpreter -O1 -Os -fno-exceptions -freg-struct-return -fno-default-inline
LDFLAGS=-T ${EPIPHANY_HOME}/bsps/current/fast.ldf -Wl,--gc-sections

all: clean epython-device
epython-device: main.o device-functions.o ../interpreter/interpreter.o
bins = epython-device

.PHONE: check

%.o : %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(bins) :
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -le-lib
	e-objcopy --srec-forceS3 --output-target srec epython-device epython-device.srec

clean:
	$(RM) -f -v $(bins) *.yy.[ch] *.tab.[ch] *.o *.d *.output ../interpreter/*.o

-include *.d
