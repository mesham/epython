/*
 * Copyright (c) 2015, Nick Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#if defined(EPIPHANY_TARGET)
#include "epiphany-shared.h"
#elif defined(MICROBLAZE_TARGET)
#include "microblaze-shared.h"
#elif defined(HOST_STANDALONE)
#include "host-shared.h"
#endif

#define INT_TYPE 0
#define REAL_TYPE 1
#define STRING_TYPE 2
#define BOOLEAN_TYPE 3
#define NONE_TYPE 4
#define FN_ADDR_TYPE 5

#define INT_PTR_TYPE 100
#define REAL_PTR_TYPE 101
#define STRING_PTR_TYPE 102
#define BOOLEAN_PTR_TYPE 103
#define NONE_PTR_TYPE 104
#define FN_ADDR_PTR_TYPE 105

#define SCALAR 0
#define ARRAY 1

#define UNALLOCATED 1
#define ALLOCATED 2
#define ALIAS 3

// The value in a symbol table; its type and data (which is integer/real or pointer to string
// or array.) In host mode this is 8 bytes as often pointers are 64bit, but on Epiphany only 4 byte as 32 bit pointers
struct value_defn {
	char type, dtype;
#if defined(HOST_STANDALONE)
	char data[8];
#elif defined(EPIPHANY_TARGET)
	char data[4];
#elif defined(MICROBLAZE_TARGET)
  char data[4];
#endif
};

// A node in the symbol table - its id and value
struct symbol_node {
	unsigned short id, alias;
	unsigned char state, level;
	struct value_defn value __attribute__((aligned(8)));
};

#if defined(HOST_INTERPRETER)
extern volatile char * stopInterpreter;
void runIntepreter(char*, unsigned int, unsigned short, int, int, int);
void initThreadedAspectsForInterpreter(int, int, struct shared_basic*);
#elif defined(EPIPHANY_TARGET)
extern char stopInterpreter;
void runIntepreter(char*, unsigned int, unsigned short, int, int, int);
#endif
#endif /* INTERPRETER_H_ */
