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

#ifndef BYTEASSEMBLER_H_
#define BYTEASSEMBLER_H_

#include <stddef.h>
#include "stack.h"

extern int line_num;

// Used for tracking gotos and line numberings (which are resolved once the byte code is assembled)
struct lineDefinition {
	char type;
	char * name;
	int linenumber, currentpoint;
	struct lineDefinition * next;
};

struct function_call_tree_node {
	int number_of_calls;
	char* calledFunctions[256];
};

// A memory container, containing some bytecode, the length of the code and line definitions that relate to it
struct memorycontainer {
	unsigned int length;
	char * data;
	struct lineDefinition * lineDefns;
};

// A function definition, containing the function memory and the name of the function
struct functionDefinition {
	char * name;
	struct memorycontainer * contents;
	int numberEntriesInSymbolTable, recursive, number_of_fn_calls, called;
	char ** functionCalls;
};

void enterFunction(char*);
unsigned short getNumberEntriesInSymbolTable(void);
void setNumberEntriesInSymbolTable(unsigned short);
void appendNewFunctionStatement(char*, struct stack_t*, struct memorycontainer*);
void appendArgument(char*);
struct memorycontainer* appendReductionStatement(unsigned char, struct memorycontainer*, char*);
struct memorycontainer* appendBcastStatement(struct memorycontainer*, struct memorycontainer*, char*);
struct memorycontainer* appendRecvStatement(char*, struct memorycontainer*);
struct memorycontainer* appendSendStatement(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendSendRecvStatement(struct memorycontainer*, struct memorycontainer*, char*);
struct memorycontainer* appendDeclareArray(char*, struct memorycontainer*);
struct memorycontainer* appendDeclareSharedArray(char*, struct memorycontainer*);
struct memorycontainer* appendInputStatement(char*);
struct memorycontainer* appendInputStringStatement(struct memorycontainer*, char*);
struct memorycontainer* appendCallFunctionStatement(char*, struct stack_t*);
struct memorycontainer* appendGotoStatement(int);
struct memorycontainer* appendWhileStatement(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendForStatement(char *, struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendIfStatement(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendIfElseStatement(struct memorycontainer*, struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendArraySetStatement(char*, struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendLetStatement(char*, struct memorycontainer*);
struct memorycontainer* appendLetWithOperatorStatement(char*, struct memorycontainer*, unsigned char);
struct memorycontainer* appendReturnStatement(void);
struct memorycontainer* appendReturnStatementWithExpression(struct memorycontainer*);
struct memorycontainer* appendPrintStatement(struct memorycontainer*);
struct memorycontainer* appendStopStatement(void);
struct memorycontainer* appendSyncStatement(void);
struct memorycontainer* createStringExpression(char*);
struct memorycontainer* createRealExpression(float);
struct memorycontainer* createCoreIdExpression(void);
struct memorycontainer* createNumCoresExpression(void);
struct memorycontainer* createRandomExpression(void);
struct memorycontainer* createIntegerExpression(int);
struct memorycontainer* createBooleanExpression(int);
struct memorycontainer* createArrayExpression(struct stack_t*);
struct memorycontainer* createNoneExpression(void);
struct memorycontainer* createIdentifierExpression(char*);
struct memorycontainer* createIdentifierArrayAccessExpression(char*, struct memorycontainer*);
struct memorycontainer* createNumberExpression(float);
struct memorycontainer* createIsHostExpression(void);
struct memorycontainer* createIsDeviceExpression(void);
struct memorycontainer* createOrExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createAndExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createEqExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createIsExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createNeqExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createGtExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createLtExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createGeqExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createLeqExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createAddExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createSubExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createMulExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createDivExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createFloorDivExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createModExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createPowExpression(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* createSqrtExpression(struct memorycontainer*);
struct memorycontainer* createSinExpression(struct memorycontainer*);
struct memorycontainer* createCosExpression(struct memorycontainer*);
struct memorycontainer* createTanExpression(struct memorycontainer*);
struct memorycontainer* createASinExpression(struct memorycontainer*);
struct memorycontainer* createACosExpression(struct memorycontainer*);
struct memorycontainer* createATanExpression(struct memorycontainer*);
struct memorycontainer* createSinHExpression(struct memorycontainer*);
struct memorycontainer* createCosHExpression(struct memorycontainer*);
struct memorycontainer* createTanHExpression(struct memorycontainer*);
struct memorycontainer* createFloorExpression(struct memorycontainer*);
struct memorycontainer* createCeilExpression(struct memorycontainer*);
struct memorycontainer* createLogExpression(struct memorycontainer*);
struct memorycontainer* createLog10Expression(struct memorycontainer*);
struct memorycontainer* createLenExpression(struct memorycontainer*);
void addVariableIfNeeded(char*);
void enterScope(void);
void leaveScope(void);
#endif /* BYTEASSEMBLER_H_ */
