CFLAGS := -O3 -DHOST_INTERPRETER -Wall -Wextra -Wno-unused-parameter -Wmissing-prototypes -std=c99 -I ../interpreter
OBJECTS := lexer.o parser.o main.o memorymanager.o byteassembler.o stack.o misc.o configuration.o ../interpreter/interpreter.o host-functions.o  python_interoperability.o preprocessor.o

LIBS=-lm -lpthread

ifeq ($(STANDALONE),1)
CFLAGS+= -DHOST_STANDALONE -I../devices/host
else ifeq ($(MICROBLAZE),1)
CFLAGS+= -DMICROBLAZE_TARGET  -I../devices/microblaze
OBJECTS+=microblaze-support.o
LIBS+=-lsds_lib -lrt
else ifeq ($(EPIPHANY),1)
CFLAGS+= -DEPIPHANY_TARGET -I../devices/epiphany -I ${EPIPHANY_HOME}/tools/host/include -D__HOST__ -Dasm=__asm__ -Drestrict=
OBJECTS+=epiphany-support.o
CC=arm-linux-gnueabihf-gcc
LDFLAGS=-L ${EPIPHANY_HOME}/tools/host/lib
LIBS+=-le-hal -lrt
ifneq (,$(wildcard ${EPIPHANY_HOME}/tools/host/lib/libe-loader.so))
    LIBS+=-le-loader
endif
endif

YFLAGS := -d
LFLAGS :=

epython: clean_interpreter $(OBJECTS)
	$(CC) $(LDFLAGS) -o epython-host $(OBJECTS) $(LIBS)

clean_interpreter:
	$(RM) ../interpreter/interpreter.o

full: lexer parser epython

.PHONE: check

%.o : %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

lexer:
	$(LEX) $(LFLAGS) -o lexer.c epython.l

parser:
	$(YACC) $(YFLAGS) -o parser.c epython.y

clean:
	$(RM) -f -v $(bins) *.yy.[ch] *.tab.[ch] *.o *.d *.output

-include *.d
