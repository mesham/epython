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

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "interpreter.h"

/*
 * These functions are implemented by the device and host to support running in normal parallel core
 * Epiphany mode, and also standalone host mode only which is useful for interpreter development/testing
 */

#ifdef HOST_INTERPRETER
void callNativeFunction(struct value_defn*, unsigned char, int, struct value_defn*,int,int,int,struct symbol_node*,int);
char* getHeapMemory(int,char,int);
void freeMemoryInHeap(void*,int);
void syncCores(int, int);
struct value_defn performStringConcatenation(struct value_defn, struct value_defn, int);
#else
void callNativeFunction(struct value_defn*, unsigned char, int, struct value_defn*, int, int, int, struct symbol_node*);
char* getHeapMemory(int,char,int,struct symbol_node*);
void freeMemoryInHeap(void*);
void syncCores(int);
struct value_defn performStringConcatenation(struct value_defn, struct value_defn, int, struct symbol_node*);
#endif
int checkStringEquality(struct value_defn, struct value_defn);
struct symbol_node* initialiseSymbolTable(int);
char* getStackMemory(int,char);
char* getGlobalReference(char*);
void clearFreedStackFrames(char*);
void cpy(volatile void*, volatile void *, unsigned int);
void raiseError(unsigned char);
int slength(char*);
int getInt(void*);
float getFloat(void*);

#endif /* FUNCTIONS_H_ */
