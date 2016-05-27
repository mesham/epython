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

#include "functions.h"
#include "interpreter.h"
#include "basictokens.h"
#ifdef HOST_INTERPRETER
#include <stdlib.h>
#include "../host/host-functions.h"
#endif

#define MAX_CALL_STACK_DEPTH 10

#ifdef HOST_INTERPRETER
// Whether we should stop the interpreter or not (due to error raised)
volatile char * stopInterpreter;
// The symbol table
static struct symbol_node ** symbolTable;
// Number of entries currently in the symbol table
static volatile int * currentSymbolEntries;
// The absolute ID of the local core
static volatile int * localCoreId;
// Number of active cores
static volatile int * numActiveCores;
// Function call level
unsigned volatile char * fnLevel;
#else
// Whether we should stop the interpreter or not (due to error raised)
char stopInterpreter;
// The symbol table
static struct symbol_node * symbolTable;
// Number of entries currently in the symbol table
static int currentSymbolEntries;
// The absolute ID of the local core
static int localCoreId;
// Number of active cores
static int numActiveCores;
// Function call level
unsigned char fnLevel;
#endif

static int hostCoresBasePid;

#ifdef HOST_INTERPRETER
struct value_defn processAssembledCode(char*, unsigned int, unsigned int, int);
static unsigned int handleInput(char*, unsigned int, unsigned int, int);
static unsigned int handleInputWithString(char*, unsigned int, unsigned int, int);
static unsigned int handleGoto(char*, unsigned int, unsigned int, int);
static unsigned int handleFnCall(char*, unsigned int, unsigned int*, unsigned int, int);
static unsigned int handlePrint(char*, unsigned int, unsigned int, int);
static unsigned int handleDimArray(char*, unsigned int, char, unsigned int, int);
static unsigned int handleLet(char*, unsigned int, unsigned int, char, int);
static unsigned int handleArraySet(char*, unsigned int, unsigned int, int);
static unsigned int handleIf(char*, unsigned int, unsigned int, int);
static unsigned int handleFor(char*, unsigned int, unsigned int, int);
static unsigned int handleSend(char*, unsigned int, unsigned int, int);
static unsigned int handleRecv(char*, unsigned int, unsigned int, int);
static unsigned int handleSendRecv(char*, unsigned int, unsigned int, int);
static unsigned int handleBcast(char*, unsigned int, unsigned int, int);
static unsigned int handleReduction(char*, unsigned int, unsigned int, int);
static unsigned int handleSync(char*, unsigned int, unsigned int, int);
static struct symbol_node* getVariableSymbol(unsigned short, unsigned char, int, int);
static int getSymbolTableEntryId(int);
static void clearVariablesToLevel(unsigned char, int);
static struct value_defn getExpressionValue(char*, unsigned int*, unsigned int, int);
static int determine_logical_expression(char*, unsigned int*,  unsigned int, int);
static struct value_defn computeExpressionResult(unsigned char, char*, unsigned int*, unsigned int, int);
#else
struct value_defn processAssembledCode(char*, unsigned int, unsigned int);
static unsigned int handleInput(char*, unsigned int, unsigned int);
static unsigned int handleInputWithString(char*, unsigned int, unsigned int);
static unsigned int handleGoto(char*, unsigned int, unsigned int);
static unsigned int handleFnCall(char*, unsigned int, unsigned int*, unsigned int);
static unsigned int handlePrint(char*, unsigned int, unsigned int);
static unsigned int handleDimArray(char*, unsigned int, char, unsigned int);
static unsigned int handleLet(char*, unsigned int, unsigned int, char);
static unsigned int handleArraySet(char*, unsigned int, unsigned int);
static unsigned int handleIf(char*, unsigned int, unsigned int);
static unsigned int handleFor(char*, unsigned int, unsigned int);
static unsigned int handleSend(char*, unsigned int, unsigned int);
static unsigned int handleRecv(char*, unsigned int, unsigned int);
static unsigned int handleSendRecv(char*, unsigned int, unsigned int);
static unsigned int handleBcast(char*, unsigned int, unsigned int);
static unsigned int handleReduction(char*, unsigned int, unsigned int);
static unsigned int handleSync(char*, unsigned int, unsigned int);
static struct symbol_node* getVariableSymbol(unsigned short, unsigned char, int);
static int getSymbolTableEntryId(void);
static void clearVariablesToLevel(unsigned char);
static struct value_defn getExpressionValue(char*, unsigned int*, unsigned int);
static int determine_logical_expression(char*, unsigned int*, unsigned int);
static struct value_defn computeExpressionResult(unsigned char, char*, unsigned int*, unsigned int);
#endif
void setVariableValue(struct symbol_node*, struct value_defn, int);
struct value_defn getVariableValue(struct symbol_node*, int);
static unsigned short getUShort(void*);
static unsigned char getUChar(void*);
static int getInt(void*);
static float getFloat(void*);

#ifdef HOST_INTERPRETER
void initThreadedAspectsForInterpreter(int total_number_threads, int baseHostPid, struct shared_basic * basicState) {
	stopInterpreter=(char*) malloc(total_number_threads);
	symbolTable=(struct symbol_node**) malloc(sizeof(struct symbol_node*) * total_number_threads);
	currentSymbolEntries=(int*) malloc(sizeof(int) * total_number_threads);
	localCoreId=(int*) malloc(sizeof(int) * total_number_threads);
	numActiveCores=(int*) malloc(sizeof(int) * total_number_threads);
	fnLevel=(unsigned char*) malloc(sizeof(unsigned char) * total_number_threads);
	initHostCommunicationData(total_number_threads, basicState);
	hostCoresBasePid=baseHostPid;
}
#endif

#ifdef HOST_INTERPRETER
void runIntepreter(char * assembled, unsigned int length, unsigned short numberSymbols,
		int coreId, int numberActiveCores, int threadId) {
	stopInterpreter[threadId]=0;
	currentSymbolEntries[threadId]=-1;
	fnLevel[threadId]=0;
	localCoreId[threadId]=coreId;
	numActiveCores[threadId]=numberActiveCores;
	symbolTable[threadId]=initialiseSymbolTable(numberSymbols);
	processAssembledCode(assembled, 0, length, threadId);
}

#else
void runIntepreter(char * assembled, unsigned int length, unsigned short numberSymbols,
		int coreId, int numberActiveCores, int baseHostPid) {
	stopInterpreter=0;
	currentSymbolEntries=-1;
	fnLevel=0;
	localCoreId=coreId;
	numActiveCores=numberActiveCores;
	symbolTable=initialiseSymbolTable(numberSymbols);
	hostCoresBasePid=baseHostPid;
	processAssembledCode(assembled, 0, length);
}
#endif

#ifdef HOST_INTERPRETER
/**
 * Entry function which will process the assembled code and perform the required actions
 */
struct value_defn processAssembledCode(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
	struct value_defn empty;
	unsigned int i, fnAddr;
	for (i=currentPoint;i<length;) {
		unsigned char command=getUChar(&assembled[i]);
		i+=sizeof(unsigned char);
		if (command == LET_TOKEN) i=handleLet(assembled, i, length, 0, threadId);
		if (command == LETNOALIAS_TOKEN) i=handleLet(assembled, i, length, 1, threadId);
		if (command == ARRAYSET_TOKEN) i=handleArraySet(assembled, i, length, threadId);
		if (command == DIMARRAY_TOKEN) i=handleDimArray(assembled, i, 0, length, threadId);
		if (command == DIMSHAREDARRAY_TOKEN) i=handleDimArray(assembled, i, 1, length, threadId);
		if (command == PRINT_TOKEN) i=handlePrint(assembled, i, length, threadId);
		if (command == STOP_TOKEN) return empty;
		if (command == SYNC_TOKEN) i=handleSync(assembled, i, length, threadId);
		if (command == IF_TOKEN) i=handleIf(assembled, i, length, threadId);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i, length, threadId);
		if (command == FOR_TOKEN) i=handleFor(assembled, i, length, threadId);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i, length, threadId);
		if (command == FNCALL_TOKEN) {
			i=handleFnCall(assembled, i, &fnAddr, length, threadId);
			fnLevel[threadId]++;
			processAssembledCode(assembled, fnAddr, length, threadId);
			clearVariablesToLevel(fnLevel[threadId], threadId);
			fnLevel[threadId]--;
		}
		if (command == RETURN_TOKEN) return empty;
		if (command == RETURN_EXP_TOKEN) {
			return getExpressionValue(assembled, &i, length, threadId);
		}
		if (command == INPUT_TOKEN) i=handleInput(assembled, i, length, threadId);
		if (command == INPUT_STRING_TOKEN) i=handleInputWithString(assembled, i, length, threadId);
		if (command == SEND_TOKEN) i=handleSend(assembled, i, length, threadId);
		if (command == RECV_TOKEN) i=handleRecv(assembled, i, length, threadId);
		if (command == SENDRECV_TOKEN) i=handleSendRecv(assembled, i, length, threadId);
		if (command == BCAST_TOKEN) i=handleBcast(assembled, i, length, threadId);
		if (command == REDUCTION_TOKEN) i=handleReduction(assembled, i, length, threadId);
		if (stopInterpreter[threadId]) return empty;
	}
	return empty;
}
#else
/**
 * Entry function which will process the assembled code and perform the required actions
 */
struct value_defn processAssembledCode(char * assembled, unsigned int currentPoint, unsigned int length) {
	struct value_defn empty;
	unsigned int i, fnAddr;
	for (i=currentPoint;i<length;) {
		unsigned char command=getUChar(&assembled[i]);
		i+=sizeof(unsigned char);
		if (command == LET_TOKEN) i=handleLet(assembled, i, length, 0);
		if (command == LETNOALIAS_TOKEN) i=handleLet(assembled, i, length, 1);
		if (command == ARRAYSET_TOKEN) i=handleArraySet(assembled, i, length);
		if (command == DIMARRAY_TOKEN) i=handleDimArray(assembled, i, 0, length);
		if (command == DIMSHAREDARRAY_TOKEN) i=handleDimArray(assembled, i, 1, length);
		if (command == PRINT_TOKEN) i=handlePrint(assembled, i, length);
		if (command == STOP_TOKEN) return empty;
		if (command == SYNC_TOKEN) i=handleSync(assembled, i, length);
		if (command == IF_TOKEN) i=handleIf(assembled, i, length);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i, length);
		if (command == FOR_TOKEN) i=handleFor(assembled, i, length);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i, length);
		if (command == FNCALL_TOKEN) {
			i=handleFnCall(assembled, i, &fnAddr, length);
			fnLevel++;
			processAssembledCode(assembled, fnAddr, length);
			clearVariablesToLevel(fnLevel);
			fnLevel--;
		}
		if (command == RETURN_TOKEN) return empty;
		if (command == RETURN_EXP_TOKEN) {
			return getExpressionValue(assembled, &i, length);
		}
		if (command == INPUT_TOKEN) i=handleInput(assembled, i, length);
		if (command == INPUT_STRING_TOKEN) i=handleInputWithString(assembled, i, length);
		if (command == SEND_TOKEN) i=handleSend(assembled, i, length);
		if (command == RECV_TOKEN) i=handleRecv(assembled, i, length);
		if (command == SENDRECV_TOKEN) i=handleSendRecv(assembled, i, length);
		if (command == BCAST_TOKEN) i=handleBcast(assembled, i, length);
		if (command == REDUCTION_TOKEN) i=handleReduction(assembled, i, length);
		if (stopInterpreter) return empty;
	}
	return empty;
}
#endif

/**
 * Synchronisation between the cores
 */
#ifdef HOST_INTERPRETER
static unsigned int handleSync(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
	syncCores(1, threadId);
#else
static unsigned int handleSync(char * assembled, unsigned int currentPoint, unsigned int length) {
	syncCores(1);
#endif
	return currentPoint;
}

/**
 * Sending of data from one core to another
 */
#ifdef HOST_INTERPRETER
static unsigned int handleSend(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
	struct value_defn to_send_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	sendData(to_send_expression, getInt(target_expression.data), threadId, hostCoresBasePid);
#else
static unsigned int handleSend(char * assembled, unsigned int currentPoint, unsigned int length) {
	struct value_defn to_send_expression=getExpressionValue(assembled, &currentPoint, length);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, length);
	sendData(to_send_expression, getInt(target_expression.data));
#endif
	return currentPoint;
}

/**
 * A reduction operation - collective communication between cores
 */
#ifdef HOST_INTERPRETER
static unsigned int handleReduction(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleReduction(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned char reductionOperator=getUChar(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned char);
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	setVariableValue(variableSymbol, reduceData(broadcast_expression,
			reductionOperator, threadId, numActiveCores[threadId], hostCoresBasePid), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, length);
	setVariableValue(variableSymbol, reduceData(broadcast_expression, reductionOperator, numActiveCores), -1);
#endif
	return currentPoint;
}

/**
 * Broadcast collective communication
 */
#ifdef HOST_INTERPRETER
static unsigned int handleBcast(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleBcast(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	setVariableValue(variableSymbol, bcastData(broadcast_expression, getInt(source_expression.data),
			threadId, numActiveCores[threadId], hostCoresBasePid), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, length);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, length);
	setVariableValue(variableSymbol, bcastData(broadcast_expression, getInt(source_expression.data), numActiveCores), -1);
#endif
	return currentPoint;
}

/**
 * Receiving some data from another core
 */
#ifdef HOST_INTERPRETER
static unsigned int handleRecv(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleRecv(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	setVariableValue(variableSymbol, recvData(getInt(source_expression.data), threadId, hostCoresBasePid), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, length);
	setVariableValue(variableSymbol, recvData(getInt(source_expression.data)), -1);
#endif
	return currentPoint;
}

/**
 * Handles the sendrecv call, which does both P2P in one action with 1 synchronisation
 */
#ifdef HOST_INTERPRETER
static unsigned int handleSendRecv(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleSendRecv(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, length, threadId);
	setVariableValue(variableSymbol, sendRecvData(tosend_expression, getInt(target_expression.data), threadId, hostCoresBasePid), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint, length);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, length);
	setVariableValue(variableSymbol, sendRecvData(tosend_expression, getInt(target_expression.data)), -1);
#endif
	return currentPoint;
}

/**
 * Goto some absolute location in the byte code
 */
#ifdef HOST_INTERPRETER
static unsigned int handleGoto(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleGoto(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	return getUShort(&assembled[currentPoint]);
}

/**
 * Calls some function and stores the call point in the function call stack for returning from this function
 */
#ifdef HOST_INTERPRETER
static unsigned int handleFnCall(char * assembled, unsigned int currentPoint, unsigned int * functionAddress, unsigned int length, int threadId) {
#else
static unsigned int handleFnCall(char * assembled, unsigned int currentPoint, unsigned int * functionAddress, unsigned int length) {
#endif
	unsigned short fnAddress=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);

	unsigned short fnNumArgs=getUShort(&assembled[fnAddress]);
	fnAddress+=sizeof(unsigned short);

	unsigned short callerNumArgs=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
	struct symbol_node* srcSymbol, *targetSymbol;
	int i, numArgs;
	numArgs=fnNumArgs > callerNumArgs ? fnNumArgs : callerNumArgs;
	for (i=0;i<numArgs;i++) {
		if (i<callerNumArgs && i<fnNumArgs) {
#ifdef HOST_INTERPRETER
			srcSymbol=getVariableSymbol(getUShort(&assembled[currentPoint]), fnLevel[threadId], threadId, 0);
			targetSymbol=getVariableSymbol(getUShort(&assembled[fnAddress]), fnLevel[threadId]+1, threadId, 0);
#else
			srcSymbol=getVariableSymbol(getUShort(&assembled[currentPoint]), fnLevel, 0);
			targetSymbol=getVariableSymbol(getUShort(&assembled[fnAddress]), fnLevel+1, 0);
#endif
			targetSymbol->state=ALIAS;
			targetSymbol->alias=srcSymbol->id;
		}
		if (i<callerNumArgs) currentPoint+=sizeof(unsigned short);
		if (i<fnNumArgs) fnAddress+=sizeof(unsigned short);
	}
	*functionAddress=fnAddress;
	return currentPoint;
}

/**
 * Loop iteration
 */
#ifdef HOST_INTERPRETER
static unsigned int handleFor(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleFor(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short loopIncrementerId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
	unsigned short loopVariantId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* incrementVarSymbol=getVariableSymbol(loopIncrementerId, fnLevel[threadId], threadId, 1);
	struct symbol_node* variantVarSymbol=getVariableSymbol(loopVariantId, fnLevel[threadId], threadId, 1);
	struct value_defn expressionVal=getExpressionValue(assembled, &currentPoint, length, threadId);
#else
	struct symbol_node* incrementVarSymbol=getVariableSymbol(loopIncrementerId, fnLevel, 1);
	struct symbol_node* variantVarSymbol=getVariableSymbol(loopVariantId, fnLevel, 1);
	struct value_defn expressionVal=getExpressionValue(assembled, &currentPoint, length);
#endif
	unsigned short blockLen=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);

	char * ptr;
	int arrSize;
	cpy(&ptr, expressionVal.data, sizeof(int*));
	cpy(&arrSize, ptr, sizeof(int));
	struct value_defn varVal=getVariableValue(incrementVarSymbol, -1);
	int incrementVal=getInt(varVal.data);
	if (incrementVal < arrSize) {
		struct value_defn nextElement;
		nextElement.type=expressionVal.type;
		cpy(&nextElement.data, ptr+((incrementVal+1)*4), sizeof(int));
		setVariableValue(variantVarSymbol, nextElement, -1);
		return currentPoint;
	}
	currentPoint+=(blockLen+sizeof(unsigned short)+sizeof(unsigned char));
	return currentPoint;
}

/**
 * Conditional, with or without else block
 */
#ifdef HOST_INTERPRETER
static unsigned int handleIf(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
	int conditionalResult=determine_logical_expression(assembled, &currentPoint, length, threadId);
#else
static unsigned int handleIf(char * assembled, unsigned int currentPoint, unsigned int length) {
	int conditionalResult=determine_logical_expression(assembled, &currentPoint, length);
#endif
	if (conditionalResult) return currentPoint+sizeof(unsigned short);
	unsigned short blockLen=getUShort(&assembled[currentPoint]);
	return currentPoint+sizeof(unsigned short)+blockLen;
}

/**
 * Input from user without string to display
 */
#ifdef HOST_INTERPRETER
static unsigned int handleInput(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleInput(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	setVariableValue(variableSymbol, getInputFromUser(threadId), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	setVariableValue(variableSymbol, getInputFromUser(), -1);
#endif
	return currentPoint;
}

/**
 * Input from user with string to display
 */
#ifdef HOST_INTERPRETER
static unsigned int handleInputWithString(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleInputWithString(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn string_display=getExpressionValue(assembled, &currentPoint, length, threadId);
	setVariableValue(variableSymbol, getInputFromUserWithString(string_display, threadId), -1);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn string_display=getExpressionValue(assembled, &currentPoint, length);
	setVariableValue(variableSymbol, getInputFromUserWithString(string_display), -1);
#endif
	return currentPoint;
}

/**
 * Print some value to the user
 */
#ifdef HOST_INTERPRETER
static unsigned int handlePrint(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
	struct value_defn result=getExpressionValue(assembled, &currentPoint, length, threadId);
	displayToUser(result, threadId);
#else
static unsigned int handlePrint(char * assembled, unsigned int currentPoint, unsigned int length) {
	struct value_defn result=getExpressionValue(assembled, &currentPoint, length);
	displayToUser(result);
#endif
	return currentPoint;
}

/**
 * Declaration of an array and whether it is to be in default (core local) or shared memory
 */
#ifdef HOST_INTERPRETER
static unsigned int handleDimArray(char * assembled, unsigned int currentPoint, char inSharedMemory, unsigned int length, int threadId) {
#else
static unsigned int handleDimArray(char * assembled, unsigned int currentPoint, char inSharedMemory, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn size=getExpressionValue(assembled, &currentPoint, length, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn size=getExpressionValue(assembled, &currentPoint, length);
#endif
	variableSymbol->value.type=INT_TYPE;
	variableSymbol->value.dtype=ARRAY;
	int * address=getHeapMemory(sizeof(int)*(getInt(size.data)+1), inSharedMemory);
	cpy(variableSymbol->value.data, &address, sizeof(int*));
	cpy(address, size.data, sizeof(int));
	return currentPoint;
}

/**
 * Set an individual element of an array
 */
#ifdef HOST_INTERPRETER
static unsigned int handleArraySet(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleArraySet(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn index=getExpressionValue(assembled, &currentPoint, length, threadId);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn index=getExpressionValue(assembled, &currentPoint, length);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length);
#endif
	setVariableValue(variableSymbol, value, getInt(index.data));
	return currentPoint;
}

/**
 * Set a scalar value (held in the symbol table)
 */
#ifdef HOST_INTERPRETER
static unsigned int handleLet(char * assembled, unsigned int currentPoint, unsigned int length, char restrictNoAlias, int threadId) {
#else
static unsigned int handleLet(char * assembled, unsigned int currentPoint, unsigned int length, char restrictNoAlias) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length, threadId);
	if (restrictNoAlias && getVariableSymbol(varId, fnLevel[threadId], threadId, 0)->state==ALIAS) return currentPoint;
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length);
	if (restrictNoAlias && getVariableSymbol(varId, fnLevel, 0)->state==ALIAS) return currentPoint;
#endif
	variableSymbol->value.type=value.type;
	variableSymbol->value.dtype=value.dtype;
	if (value.dtype == ARRAY) {
		cpy(variableSymbol->value.data, value.data, sizeof(int*));
	} else if (value.type == STRING_TYPE) {
		cpy(&variableSymbol->value.data, &value.data, sizeof(int*));
	} else {
		int currentAddress=getInt(variableSymbol->value.data);
		if (currentAddress == 0) {
			int * address=getStackMemory(sizeof(int), 0);
			cpy(variableSymbol->value.data, &address, sizeof(int*));
			cpy(address, value.data, sizeof(int));
		} else {
			setVariableValue(variableSymbol, value, -1);
		}
	}
	return currentPoint;
}

/**
 * Determines a logical expression based upon two operands and an operator
 */
#ifdef HOST_INTERPRETER
static int determine_logical_expression(char * assembled, unsigned int * currentPoint, unsigned int length, int threadId) {
#else
static int determine_logical_expression(char * assembled, unsigned int * currentPoint, unsigned int length) {
#endif
	unsigned char expressionId=getUChar(&assembled[*currentPoint]);
	*currentPoint+=sizeof(unsigned char);
	if (expressionId == AND_TOKEN || expressionId == OR_TOKEN) {
#ifdef HOST_INTERPRETER
		int s1=determine_logical_expression(assembled, currentPoint, length, threadId);
		int s2=determine_logical_expression(assembled, currentPoint, length, threadId);
#else
		int s1=determine_logical_expression(assembled, currentPoint, length);
		int s2=determine_logical_expression(assembled, currentPoint, length);
#endif
		if (expressionId == AND_TOKEN) return s1 && s2;
		if (expressionId == OR_TOKEN) return s1 || s2;
	} else if (expressionId == EQ_TOKEN || expressionId == NEQ_TOKEN || expressionId == GT_TOKEN || expressionId == GEQ_TOKEN ||
			expressionId == LT_TOKEN || expressionId == LEQ_TOKEN || expressionId == IS_TOKEN) {
#ifdef HOST_INTERPRETER
		struct value_defn expression1=getExpressionValue(assembled, currentPoint, length, threadId);
		struct value_defn expression2=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		struct value_defn expression1=getExpressionValue(assembled, currentPoint, length);
		struct value_defn expression2=getExpressionValue(assembled, currentPoint, length);
#endif
		if (expressionId == IS_TOKEN) {
			if (expression1.type == NONE_TYPE && expression2.type == NONE_TYPE) return 1;
			if (expression1.type != expression2.type) return 0;
			char *ptr1, *ptr2;
			cpy(&ptr1, expression1.data, sizeof(int*));
			cpy(&ptr2, expression2.data, sizeof(int*));
			return ptr1 == ptr2;
		}
		if (expression1.type == expression2.type && expression1.type == INT_TYPE) {
			int value1=getInt(expression1.data);
			int value2=getInt(expression2.data);
			if (expressionId == EQ_TOKEN) return value1 == value2;
			if (expressionId == NEQ_TOKEN) return value1 != value2;
			if (expressionId == GT_TOKEN) return value1 > value2;
			if (expressionId == GEQ_TOKEN) return value1 >= value2;
			if (expressionId == LT_TOKEN) return value1 < value2;
			if (expressionId == LEQ_TOKEN) return value1 <= value2;
		} else if ((expression1.type == REAL_TYPE || expression1.type == INT_TYPE) &&
				(expression2.type == REAL_TYPE || expression2.type == INT_TYPE)) {
			float value1=getFloat(expression1.data);
			float value2=getFloat(expression2.data);
			if (expression1.type==INT_TYPE) value1=(float) getInt(expression1.data);
			if (expression2.type==INT_TYPE) value2=(float) getInt(expression2.data);
			if (expressionId == EQ_TOKEN) return value1 == value2;
			if (expressionId == NEQ_TOKEN) return value1 != value2;
			if (expressionId == GT_TOKEN) return value1 > value2;
			if (expressionId == GEQ_TOKEN) return value1 >= value2;
			if (expressionId == LT_TOKEN) return value1 < value2;
			if (expressionId == LEQ_TOKEN) return value1 <= value2;
		} else if (expression1.type == expression2.type && expression1.type == STRING_TYPE) {
			if (expressionId == EQ_TOKEN) {
				return checkStringEquality(expression1, expression2);
			} else if (expressionId == NEQ_TOKEN) {
				return !checkStringEquality(expression1, expression2);
			} else {
				raiseError("Can only test for equality with strings");
			}
		} else if (expression1.type == expression2.type && expression1.type == NONE_TYPE) {
			if (expressionId == EQ_TOKEN || expressionId == IS_TOKEN) {
				return 1;
			} else if (expressionId == NEQ_TOKEN) {
				return 0;
			} else {
				raiseError("Can only test for equality with none");
			}
		}
	} else if (expressionId == BOOLEAN_TOKEN) {
		struct value_defn value;
		cpy(value.data, &assembled[*currentPoint], sizeof(int));
		*currentPoint+=sizeof(int);
		return getInt(value.data) > 0;
	} else if (expressionId == IDENTIFIER_TOKEN || expressionId == ARRAYACCESS_TOKEN) {
		struct value_defn value;
		unsigned short variable_id=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel[threadId], threadId, 1);
#else
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel, 1);
#endif
		value=getVariableValue(variableSymbol, -1);
		if (expressionId == ARRAYACCESS_TOKEN) {
#ifdef HOST_INTERPRETER
			struct value_defn index=getExpressionValue(assembled, currentPoint, length, threadId);
#else
			struct value_defn index=getExpressionValue(assembled, currentPoint, length);
#endif
			value=getVariableValue(variableSymbol, getInt(index.data));
		}
		if (value.type == BOOLEAN_TYPE) {
			return getInt(value.data) > 0;
		}
		return 0;
	} else if (expressionId == ISHOST_TOKEN) {
#ifdef HOST_INTERPRETER
		return 1;
#else
		return 0;
#endif
	} else if (expressionId == ISDEVICE_TOKEN) {
#ifdef HOST_INTERPRETER
		return 0;
#else
		return 1;
#endif
	} else {
		*currentPoint-=sizeof(unsigned char);
		struct value_defn expValue;
#ifdef HOST_INTERPRETER
		expValue=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		expValue=getExpressionValue(assembled, currentPoint, length);
#endif
		if (expValue.type == BOOLEAN_TYPE || expValue.type == INT_TYPE) {
			return getInt(expValue.data) > 0;
		}
	}
	return 0;
}

/**
 * Gets the value of an expression, which is number, string, identifier or mathematical
 */
#ifdef HOST_INTERPRETER
static struct value_defn getExpressionValue(char * assembled, unsigned int * currentPoint, unsigned int length, int threadId) {
#else
static struct value_defn getExpressionValue(char * assembled, unsigned int * currentPoint, unsigned int length) {
#endif
	struct value_defn value;

	unsigned char expressionId=getUChar(&assembled[*currentPoint]);
	*currentPoint+=sizeof(unsigned char);
	if (expressionId == INTEGER_TOKEN) {
		value.type=INT_TYPE;
		value.dtype=SCALAR;
		cpy(value.data, &assembled[*currentPoint], sizeof(int));
		*currentPoint+=sizeof(int);
	} else if (expressionId == REAL_TOKEN) {
		value.type=REAL_TYPE;
		value.dtype=SCALAR;
		cpy(value.data, &assembled[*currentPoint], sizeof(float));
		*currentPoint+=sizeof(float);
	} else if (expressionId == BOOLEAN_TOKEN) {
		value.type=BOOLEAN_TYPE;
		value.dtype=SCALAR;
		cpy(value.data, &assembled[*currentPoint], sizeof(int));
		*currentPoint+=sizeof(int);
	} else if (expressionId == STRING_TOKEN) {
		value.type=STRING_TYPE;
		char * strPtr=assembled + *currentPoint;
		cpy(&value.data, &strPtr, sizeof(char*));
		*currentPoint+=(slength(strPtr)+1);
		value.dtype=SCALAR;
	} else if (expressionId == NONE_TOKEN) {
		value.type=NONE_TYPE;
		value.dtype=SCALAR;
	} else if (expressionId == COREID_TOKEN) {
		value.type=INT_TYPE;
		value.dtype=SCALAR;
#ifdef HOST_INTERPRETER
		cpy(value.data, &localCoreId[threadId], sizeof(int));
#else
		cpy(value.data, &localCoreId, sizeof(int));
#endif
	} else if (expressionId == NUMCORES_TOKEN) {
		value.type=INT_TYPE;
		value.dtype=SCALAR;
#ifdef HOST_INTERPRETER
		cpy(value.data, &numActiveCores[threadId], sizeof(int));
#else
		cpy(value.data, &numActiveCores, sizeof(int));
#endif
	} else if (expressionId == RANDOM_TOKEN) {
		value=performMathsOp(RANDOM_MATHS_OP, value);
		value.dtype=SCALAR;
	} else if (expressionId == LEN_TOKEN) {
#ifdef HOST_INTERPRETER
		value=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		value=getExpressionValue(assembled, currentPoint, length);
#endif
		value.type=INT_TYPE;
		value.dtype=SCALAR;
		char * ptr;
		cpy(&ptr, value.data, sizeof(int*));
		cpy(value.data, ptr, sizeof(int));
	} else if (expressionId == LET_TOKEN) {
#ifdef HOST_INTERPRETER
		*currentPoint=handleLet(assembled, *currentPoint, length, 0, threadId);
		value=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		*currentPoint=handleLet(assembled, *currentPoint, length, 0);
		value=getExpressionValue(assembled, currentPoint, length);
#endif
	} else if (expressionId == ARRAY_TOKEN) {
		int i, numItems=getInt(&assembled[*currentPoint]);
		*currentPoint+=sizeof(int);
		int * address=getHeapMemory(sizeof(int)*(numItems+1), 0);
		cpy(value.data, &address, sizeof(int*));
		cpy(address, &numItems, sizeof(int));
		for (i=0;i<numItems;i++) {
#ifdef HOST_INTERPRETER
			struct value_defn itemV=getExpressionValue(assembled, currentPoint, length, threadId);
#else
			struct value_defn itemV=getExpressionValue(assembled, currentPoint, length);
#endif
		cpy(address+(i+1), itemV.data, sizeof(int));
		value.type=itemV.type;
		}
		value.dtype=ARRAY;
	} else if (expressionId == FNCALL_TOKEN) {
#ifdef HOST_INTERPRETER
		unsigned int fnAddr;
		*currentPoint=handleFnCall(assembled, *currentPoint, &fnAddr, length, threadId);
		fnLevel[threadId]++;
		value=processAssembledCode(assembled, fnAddr, length, threadId);
		clearVariablesToLevel(fnLevel[threadId], threadId);
		fnLevel[threadId]--;
#else
		unsigned int fnAddr;
		*currentPoint=handleFnCall(assembled, *currentPoint, &fnAddr, length);
		fnLevel++;
		value=processAssembledCode(assembled, fnAddr, length);
		clearVariablesToLevel(fnLevel);
		fnLevel--;
#endif
	} else if (expressionId == MATHS_TOKEN) {
		unsigned char maths_op=getUChar(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned char);
#ifdef HOST_INTERPRETER
		value=performMathsOp(maths_op, getExpressionValue(assembled, currentPoint, length, threadId));
#else
		value=performMathsOp(maths_op, getExpressionValue(assembled, currentPoint, length));
#endif
		value.dtype=SCALAR;
	} else if (expressionId == IDENTIFIER_TOKEN || expressionId == ARRAYACCESS_TOKEN) {
		unsigned short variable_id=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel[threadId], threadId, 1);
#else
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel, 1);
#endif
		if (expressionId == IDENTIFIER_TOKEN) {
			if (variableSymbol->value.dtype==SCALAR) {
				value=getVariableValue(variableSymbol, -1);
			} else if (variableSymbol->value.dtype==ARRAY) {
				value.dtype=ARRAY;
				value.type=variableSymbol->value.type;
				cpy(value.data, variableSymbol->value.data, sizeof(int*));
			}
		} else if (expressionId == ARRAYACCESS_TOKEN) {
#ifdef HOST_INTERPRETER
			struct value_defn index=getExpressionValue(assembled, currentPoint, length, threadId);
#else
			struct value_defn index=getExpressionValue(assembled, currentPoint, length);
#endif
			value=getVariableValue(variableSymbol, getInt(index.data));
		}
	} else if (expressionId == ADD_TOKEN || expressionId == SUB_TOKEN || expressionId == MUL_TOKEN ||
			expressionId == DIV_TOKEN || expressionId == MOD_TOKEN || expressionId == POW_TOKEN) {
#ifdef HOST_INTERPRETER
		value=computeExpressionResult(expressionId, assembled, currentPoint, length, threadId);
#else
		value=computeExpressionResult(expressionId, assembled, currentPoint, length);
#endif
	} else if (expressionId == EQ_TOKEN || expressionId == NEQ_TOKEN || expressionId == GT_TOKEN || expressionId == GEQ_TOKEN ||
			expressionId == LT_TOKEN || expressionId == LEQ_TOKEN || expressionId == IS_TOKEN || expressionId == ISHOST_TOKEN ||
			expressionId == ISDEVICE_TOKEN) {
		*currentPoint-=sizeof(unsigned char);
#ifdef HOST_INTERPRETER
		int retVal=determine_logical_expression(assembled, currentPoint, length, threadId);
#else
		int retVal=determine_logical_expression(assembled, currentPoint, length);
#endif
		value.type=BOOLEAN_TYPE;
		value.dtype=SCALAR;
		cpy(value.data, &retVal, sizeof(int));
	}
	return value;
}

/**
 * Computes the result of a simple mathematical expression, if one is a real and the other an integer
 * then raises to be a real
 */
#ifdef HOST_INTERPRETER
static struct value_defn computeExpressionResult(unsigned char operator, char * assembled, unsigned int * currentPoint,
		unsigned int length, int threadId) {
#else
static struct value_defn computeExpressionResult(unsigned char operator, char * assembled, unsigned int * currentPoint,
		unsigned int length) {
#endif
	struct value_defn value;
#ifdef HOST_INTERPRETER
	struct value_defn v1=getExpressionValue(assembled, currentPoint, length, threadId);
	struct value_defn v2=getExpressionValue(assembled, currentPoint, length, threadId);
#else
	struct value_defn v1=getExpressionValue(assembled, currentPoint, length);
	struct value_defn v2=getExpressionValue(assembled, currentPoint, length);
#endif
	value.type=v1.type==INT_TYPE && v2.type==INT_TYPE ? INT_TYPE : v1.type==STRING_TYPE || v2.type==STRING_TYPE ? STRING_TYPE : REAL_TYPE;
	value.dtype=SCALAR;
	if (value.type==INT_TYPE) {
		int i, value1=getInt(v1.data), value2=getInt(v2.data), result;
		if (operator==ADD_TOKEN) result=value1+value2;
		if (operator==SUB_TOKEN) result=value1-value2;
		if (operator==MUL_TOKEN) result=value1*value2;
		if (operator==DIV_TOKEN) result=value1/value2;
		if (operator==MOD_TOKEN) result=value1%value2;
		if (operator==POW_TOKEN) {
			result=value2 == 0 ? 1 : value1;
			for (i=1;i<value2;i++) result=result*value1;
		}
		cpy(&value.data, &result, sizeof(int));
	} else if (value.type==REAL_TYPE) {
		float value1=getFloat(v1.data);
		float value2=getFloat(v2.data);
		float result;
		if (v1.type==INT_TYPE) value1=(float) getInt(v1.data);
		if (v2.type==INT_TYPE) {
			value2=(float) getInt(v2.data);
			if (operator == POW_TOKEN) {
				int i;
				result=value2 == 0 ? 1 : value1;
				for (i=1;i<(int) value2;i++) result=result*value1;
			}
		}
		if (operator == ADD_TOKEN) result=value1+value2;
		if (operator == SUB_TOKEN) result=value1-value2;
		if (operator == MUL_TOKEN) result=value1*value2;
		if (operator == DIV_TOKEN) result=value1/value2;
		cpy(&value.data, &result, sizeof(float));
	} else if (value.type==STRING_TYPE) {
		if (operator == ADD_TOKEN) {
			return performStringConcatenation(v1, v2);
		} else {
			raiseError("Can only perform addition with strings");
		}
	}
	return value;
}

/**
 * Retrieves the symbol entry of a variable based upon its id
 */
#ifdef HOST_INTERPRETER
static struct symbol_node* getVariableSymbol(unsigned short id, unsigned char lvl, int threadId, int followAlias) {
#else
static struct symbol_node* getVariableSymbol(unsigned short id, unsigned char lvl, int followAlias) {
#endif
	int i;
#ifdef HOST_INTERPRETER
	for (i=0;i<=currentSymbolEntries[threadId];i++) {
		if (symbolTable[threadId][i].id == id && symbolTable[threadId][i].state != UNALLOCATED && (symbolTable[threadId][i].level == 0 || symbolTable[threadId][i].level==lvl)) {
			if (followAlias && symbolTable[threadId][i].state == ALIAS) {
				return getVariableSymbol(symbolTable[threadId][i].alias, lvl-1, threadId, 1);
			} else {
				return &(symbolTable[threadId])[i];
			}
		}
#else
	for (i=0;i<=currentSymbolEntries;i++) {
		if (symbolTable[i].id == id && symbolTable[i].state != UNALLOCATED && (symbolTable[i].level == 0 || symbolTable[i].level==lvl)) {
			if (followAlias && symbolTable[i].state == ALIAS) {
				return getVariableSymbol(symbolTable[i].alias, lvl-1, 1);
			} else {
				return &symbolTable[i];
			}
		}
#endif
	}
	int zero=0;
#ifdef HOST_INTERPRETER
	int newEntryLocation=getSymbolTableEntryId(threadId);
	symbolTable[threadId][newEntryLocation].id=id;
	symbolTable[threadId][newEntryLocation].state=ALLOCATED;
	symbolTable[threadId][newEntryLocation].level=lvl;
	symbolTable[threadId][newEntryLocation].value.type=INT_TYPE;
	cpy(symbolTable[threadId][newEntryLocation].value.data, &zero, sizeof(int));
	return &symbolTable[threadId][newEntryLocation];
#else
	int newEntryLocation=getSymbolTableEntryId();
	symbolTable[newEntryLocation].id=id;
	symbolTable[newEntryLocation].level=lvl;
	symbolTable[newEntryLocation].state=ALLOCATED;
	symbolTable[newEntryLocation].value.type=INT_TYPE;
	symbolTable[newEntryLocation].value.dtype=SCALAR;
	cpy(symbolTable[newEntryLocation].value.data, &zero, sizeof(int));
	return &symbolTable[newEntryLocation];
#endif
}
#ifdef HOST_INTERPRETER
static int getSymbolTableEntryId(int threadId) {
#else
static int getSymbolTableEntryId(void) {
#endif
	int i;
#ifdef HOST_INTERPRETER
	for (i=0;i<=currentSymbolEntries[threadId];i++) {
			if (symbolTable[threadId][i].state == UNALLOCATED) return i;
	}
	return ++currentSymbolEntries[threadId];
#else
	for (i=0;i<=currentSymbolEntries;i++) {
		if (symbolTable[i].state == UNALLOCATED) return i;
	}
	return ++currentSymbolEntries;
#endif
}

#ifdef HOST_INTERPRETER
static void clearVariablesToLevel(unsigned char clearLevel, int threadId) {
#else
static void clearVariablesToLevel(unsigned char clearLevel) {
#endif
	int i;
	char * smallestMemoryAddress=0, *ptr;
#ifdef HOST_INTERPRETER
	for (i=0;i<=currentSymbolEntries[threadId];i++) {
		if (symbolTable[threadId][i].level >= clearLevel && symbolTable[threadId][i].state != UNALLOCATED) {
			symbolTable[threadId][i].state=UNALLOCATED;
			if (symbolTable[threadId][i].value.dtype==SCALAR && symbolTable[threadId][i].value.type != STRING_TYPE) {
				cpy(&ptr, symbolTable[threadId][i].value.data, sizeof(int*));
				if (ptr != 0 && (smallestMemoryAddress == 0 || smallestMemoryAddress > ptr)) smallestMemoryAddress=ptr;
			}
		}
	}
#else
	for (i=0;i<=currentSymbolEntries;i++) {
		if (symbolTable[i].level >= clearLevel && symbolTable[i].state != UNALLOCATED) {
			symbolTable[i].state=UNALLOCATED;
			if (symbolTable[i].value.dtype==SCALAR && symbolTable[i].value.type != STRING_TYPE) {
				cpy(&ptr, symbolTable[i].value.data, sizeof(char*));
				if (ptr != 0 && (smallestMemoryAddress == 0 || smallestMemoryAddress > ptr)) smallestMemoryAddress=ptr;
			}
		}
	}
#endif
	if (smallestMemoryAddress != 0) clearFreedStackFrames(smallestMemoryAddress);
}

/**
 * Helper method to get an integer from data (needed as casting to integer directly requires 4 byte alignment which we
 * do not want to enforce as it wastes memory.)
 */
static int getInt(void* data) {
	int v;
	cpy(&v, data, sizeof(int));
	return v;
}

/**
 * Helper method to get a float from data (needed as casting to integer directly requires 4 byte alignment which we
 * do not want to enforce as it wastes memory.)
 */
static float getFloat(void* data) {
	float v;
	cpy(&v, data, sizeof(float));
	return v;
}

/**
 * Sets a variables value in memory as pointed to by symbol table
 */
void setVariableValue(struct symbol_node* variableSymbol, struct value_defn value, int index) {
	variableSymbol->value.type=value.type;
	if (value.type == STRING_TYPE) {
		cpy(&variableSymbol->value.data, &value.data, sizeof(int*));
	} else {
		int currentAddress=getInt(variableSymbol->value.data);
		if (currentAddress == 0) {
			int * address=getStackMemory(sizeof(int) * index, 0);
			cpy(variableSymbol->value.data, &address, sizeof(int*));
			cpy(address+((index+1) *4), value.data, sizeof(int));
		} else {
			char * ptr;
			cpy(&ptr, variableSymbol->value.data, sizeof(int*));
			cpy(ptr+((index+1) *4), value.data, sizeof(int));
		}
	}
}

/**
 * Retrieves a variable value from memory, which the symbol table points to
 */
struct value_defn getVariableValue(struct symbol_node* variableSymbol, int index) {
	struct value_defn val;
	val.type=variableSymbol->value.type;
	val.dtype=variableSymbol->value.dtype;
	if (variableSymbol->value.type == STRING_TYPE) {
		cpy(&val.data, &variableSymbol->value.data, sizeof(int*));
	} else {
		char * ptr;
		cpy(&ptr, variableSymbol->value.data, sizeof(int*));
		ptr+=((index+1) *4);
		cpy(val.data, ptr, sizeof(int));
	}
	return val;
}

static unsigned char getUChar(void* data) {
	unsigned char v;
	cpy(&v, data, sizeof(unsigned char));
	return v;
}

/**
 * Helper method to get an unsigned short from data (needed as casting to integer directly requires 4 byte alignment
 * which we do not want to enforce as it wastes memory.)
 */
static unsigned short getUShort(void* data) {
	unsigned short v;
	cpy(&v, data, sizeof(unsigned short));
	return v;
}
