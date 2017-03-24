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

#define NATIVE_RTL_ISHOST_STR "rtl_ishost"
#define NATIVE_RTL_ISDEVICE_STR "rtl_isdevice"
#define NATIVE_RTL_PRINT_STR "rtl_print"
#define NATIVE_RTL_NUMDIMS_STR "rtl_numdims"
#define NATIVE_RTL_DSIZE_STR "rtl_dsize"
#define NATIVE_RTL_INPUT_STR "rtl_input"
#define NATIVE_RTL_INPUTPRINT_STR "rtl_inputprint"
#define NATIVE_RTL_SYNC_STR "rtl_sync"
#define NATIVE_RTL_GC_STR "rtl_gc"
#define NATIVE_RTL_FREE_STR "rtl_free"
#define NATIVE_RTL_SEND_STR "rtl_send"
#define NATIVE_RTL_RECV_STR "rtl_recv"
#define NATIVE_RTL_SENDRECV_STR "rtl_sendrecv"
#define NATIVE_RTL_BCAST_STR "rtl_bcast"
#define NATIVE_RTL_NUMCORES_STR "rtl_numcores"
#define NATIVE_RTL_COREID_STR "rtl_coreid"
#define NATIVE_RTL_REDUCE_STR "rtl_reduce"
#define NATIVE_RTL_ALLOCATEARRAY_STR "rtl_allocatearray"
#define NATIVE_RTL_ALLOCATESHAREDARRAY_STR "rtl_allocatesharedarray"
#define NATIVE_RTL_MATH_STR "rtl_math"
#define NATIVE_RTL_PROBE_FOR_MESSAGE_STR "rtl_probe"
#define NATIVE_RTL_TEST_FOR_SEND_STR "rtl_test_for_send"
#define NATIVE_RTL_WAIT_FOR_SEND_STR "rtl_wait_for_send"
#define NATIVE_RTL_SEND_NB_STR "rtl_send_nonblocking"
#define NATIVE_RTL_GLOBAL_REFRENCE_STR "rtl_global_reference"
#define NATIVE_RTL_DEREFRENCE_STR "rtl_dereference"
#define NATIVE_RTL_FLATTEN_STR "rtl_flatten"
#define NATIVE_RTL_ARRAY_COPY_STR "rtl_arraycopy"

extern int line_num;
extern char * fn_decorator;

// Used for tracking gotos and line numberings (which are resolved once the byte code is assembled)
struct lineDefinition {
	char type;
	char * name;
	int linenumber, currentpoint;
	struct lineDefinition * next;
};

// Tree node for the current function call and the main entry point
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
struct memorycontainer* appendCallFunctionStatement(char*, struct stack_t*);
struct memorycontainer* appendNativeCallFunctionStatement(char*, struct stack_t*, struct memorycontainer*);
struct memorycontainer* appendReferenceStatement(char*);
struct memorycontainer* appendGotoStatement(int);
struct memorycontainer* appendWhileStatement(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendForStatement(char *, struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendIfStatement(struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendIfElseStatement(struct memorycontainer*, struct memorycontainer*, struct memorycontainer*);
struct memorycontainer* appendArraySetStatement(char*, struct stack_t*, struct memorycontainer*);
struct memorycontainer* appendLetStatement(char*, struct memorycontainer*);
struct memorycontainer* appendLetWithOperatorStatement(char*, struct memorycontainer*, unsigned char);
struct memorycontainer* appendReturnStatement(void);
struct memorycontainer* appendReturnStatementWithExpression(struct memorycontainer*);
struct memorycontainer* appendStopStatement(void);
struct memorycontainer* appendPassStatement(void);
struct memorycontainer* createStringExpression(char*);
struct memorycontainer* createRealExpression(float);
struct memorycontainer* createIntegerExpression(int);
struct memorycontainer* createBooleanExpression(int);
struct memorycontainer* createArrayExpression(struct stack_t*, struct memorycontainer*);
struct memorycontainer* createNoneExpression(void);
struct memorycontainer* createIdentifierExpression(char*);
struct memorycontainer* createIdentifierArrayAccessExpression(char*, struct stack_t*);
struct memorycontainer* createNumberExpression(float);
struct memorycontainer* createNotExpression(struct memorycontainer*);
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
void addVariableIfNeeded(char*);
void enterScope(void);
void leaveScope(void);
#endif /* BYTEASSEMBLER_H_ */
