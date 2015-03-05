CFLAGS := -Wall -Wextra -Wno-unused-parameter -Wmissing-prototypes -ansi -std=c99 -I ../interpreter
OBJECTS := lexer.o parser.o main.o memorymanager.o byteassembler.o configuration.o

ifeq ($(STANDALONE),1)
CFLAGS+= -DHOST_STANDALONE
OBJECTS+= ../interpreter/interpreter.o host-functions.o
LIBS=-lm
else
CFLAGS+= -I../ -I ${EPIPHANY_HOME}/tools/host/include -D__HOST__ -Dasm=__asm__ -Drestrict=
OBJECTS+=device-support.o
CC=arm-linux-gnueabihf-gcc
LDFLAGS=-L ${EPIPHANY_HOME}/tools/host/lib
LIBS=-le-hal -lrt -lm
ifneq (,$(wildcard ${EPIPHANY_HOME}/tools/host/lib/libe-loader.so))
    LIBS+=-le-loader
endif
endif

YFLAGS := -d
LFLAGS :=

ebasic: $(OBJECTS)
	$(CC) $(LDFLAGS) -o ebasic-host $(OBJECTS) $(LIBS)

full: lexer parser ebasic

.PHONE: check

%.o : %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

lexer:
	$(LEX) $(LFLAGS) -o lexer.c ebasic.l

parser:
	$(YACC) $(YFLAGS) -o parser.c ebasic.y

clean:
	$(RM) -f -v $(bins) *.yy.[ch] *.tab.[ch] *.o *.d *.output

-include *.d
