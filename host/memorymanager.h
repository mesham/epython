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

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "byteassembler.h"

// Used to maintain a linked list of functions
struct functionListNode {
	struct functionDefinition * fn;
	struct functionListNode * next;
};

struct exportableFunctionTableNode {
    char * functionName;
    unsigned short functionLocation;
    struct exportableFunctionTableNode * next;
};

extern struct exportableFunctionTableNode* exportableFunctionTable;
extern int numberExportableFunctionsInTable;

int getNumberOfSymbolEntriesNotUsed(void);
void addFunction(struct functionDefinition*);
int getNumberSymbolTableEntriesForRecursion(void);
void compileMemory(struct memorycontainer*);
struct memorycontainer* concatenateMemory(struct memorycontainer*, struct memorycontainer*);
unsigned int appendStatement(struct memorycontainer*, unsigned char, unsigned int);
unsigned int appendMemory(struct memorycontainer*, struct memorycontainer*, unsigned int);
unsigned int appendVariable(struct memorycontainer*, unsigned short, unsigned int);
unsigned int getMemoryFilledSize(void);
void setMemoryFilledSize(unsigned int);
char * getAssembledCode(void);
void setAssembledCode(char*);

extern struct function_call_tree_node mainCodeCallTree;

#endif /* MEMORYMANAGER_H_ */
