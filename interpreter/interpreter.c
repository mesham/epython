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

#ifdef HOST_INTERPRETER
// Whether we should stop the interpreter or not (due to error raised)
char * stopInterpreter;
// The symbol table
static struct symbol_node ** symbolTable;
// Number of entries currently in the symbol table
static int * currentSymbolEntries;
// The absolute ID of the local core
static int * localCoreId;
// Number of active cores
static int * numActiveCores;
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
#endif

#ifdef HOST_INTERPRETER
static int handleInput(char*, int, int);
static int handleInputWithString(char*, int, int);
static int handleGoto(char*, int, int);
static int handlePrint(char*, int, int);
static int handleDimArray(char*, int, char, int);
static int handleLet(char*, int, int);
static int handleArraySet(char*, int, int);
static int handleIf(char*, int, int);
static int handleFor(char*, int, int);
static int handleSend(char*, int, int);
static int handleRecv(char*, int, int);
static int handleRecvToArray(char*, int, int);
static int handleSendRecv(char*, int, int);
static int handleSendRecvArray(char*, int, int);
static int handleBcast(char*, int, int);
static int handleReduction(char*, int, int);
static int handleSync(char*, int, int);
static struct symbol_node* getVariableSymbol(unsigned short, int);
static struct value_defn getExpressionValue(char*, int*, int);
static int determine_logical_expression(char*, int*, int);
static struct value_defn computeExpressionResult(unsigned short, char*, int*, int);
#else
static int handleInput(char*, int);
static int handleInputWithString(char*, int);
static int handleGoto(char*, int);
static int handlePrint(char*, int);
static int handleDimArray(char*, int, char);
static int handleLet(char*, int);
static int handleArraySet(char*, int);
static int handleIf(char*, int);
static int handleFor(char*, int);
static int handleSend(char*, int);
static int handleRecv(char*, int);
static int handleRecvToArray(char*, int);
static int handleSendRecv(char*, int);
static int handleSendRecvArray(char*, int);
static int handleBcast(char*, int);
static int handleReduction(char*, int);
static int handleSync(char*, int);
static struct symbol_node* getVariableSymbol(unsigned short);
static struct value_defn getExpressionValue(char*, int*);
static int determine_logical_expression(char*, int*);
static struct value_defn computeExpressionResult(unsigned short, char*, int*);
#endif
static unsigned short getUShort(void*);
static int getInt(void*);
static float getFloat(void*);

#ifdef HOST_INTERPRETER
void initThreadedAspectsForInterpreter(int total_number_threads) {
	stopInterpreter=(char*) malloc(total_number_threads);
	symbolTable=(struct symbol_node**) malloc(sizeof(struct symbol_node*) * total_number_threads);
	currentSymbolEntries=(int*) malloc(sizeof(int) * total_number_threads);
	localCoreId=(int*) malloc(sizeof(int) * total_number_threads);
	numActiveCores=(int*) malloc(sizeof(int) * total_number_threads);
	initHostCommunicationData(total_number_threads);
}
#endif

#ifdef HOST_INTERPRETER
/**
 * Entry function which will process the assembled code and perform the required actions
 */
void processAssembledCode(char * assembled, unsigned int length, unsigned short numberSymbols,
		int coreId, int numberActiveCores, int threadId) {
	stopInterpreter[threadId]=0;
	currentSymbolEntries[threadId]=0;
	localCoreId[threadId]=coreId;
	numActiveCores[threadId]=numberActiveCores;
	symbolTable[threadId]=initialiseSymbolTable(numberSymbols);
	unsigned int i;
	for (i=0;i<length;) {
		unsigned short command=getUShort(&assembled[i]);
		i+=sizeof(unsigned short);
		if (command == LET_TOKEN) i=handleLet(assembled, i, threadId);
		if (command == ARRAYSET_TOKEN) i=handleArraySet(assembled, i, threadId);
		if (command == DIMARRAY_TOKEN) i=handleDimArray(assembled, i, 0, threadId);
		if (command == DIMSHAREDARRAY_TOKEN) i=handleDimArray(assembled, i, 1, threadId);
		if (command == PRINT_TOKEN) i=handlePrint(assembled, i, threadId);
		if (command == STOP_TOKEN) return;
		if (command == SYNC_TOKEN) i=handleSync(assembled, i, threadId);
		if (command == IF_TOKEN) i=handleIf(assembled, i, threadId);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i, threadId);
		if (command == FOR_TOKEN) i=handleFor(assembled, i, threadId);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i, threadId);
		if (command == INPUT_TOKEN) i=handleInput(assembled, i, threadId);
		if (command == INPUT_STRING_TOKEN) i=handleInputWithString(assembled, i, threadId);
		if (command == SEND_TOKEN) i=handleSend(assembled, i, threadId);
		if (command == RECV_TOKEN) i=handleRecv(assembled, i, threadId);
		if (command == RECVTOARRAY_TOKEN) i=handleRecvToArray(assembled, i, threadId);
		if (command == SENDRECV_TOKEN) i=handleSendRecv(assembled, i, threadId);
		if (command == SENDRECVARRAY_TOKEN) i=handleSendRecvArray(assembled, i, threadId);
		if (command == BCAST_TOKEN) i=handleBcast(assembled, i, threadId);
		if (command == REDUCTION_TOKEN) i=handleReduction(assembled, i, threadId);
		if (stopInterpreter[threadId]) return;
	}
}
#else
/**
 * Entry function which will process the assembled code and perform the required actions
 */
void processAssembledCode(char * assembled, unsigned int length, unsigned short numberSymbols,
		int coreId, int numberActiveCores) {
	stopInterpreter=0;
	currentSymbolEntries=0;
	localCoreId=coreId;
	numActiveCores=numberActiveCores;
	symbolTable=initialiseSymbolTable(numberSymbols);
	unsigned int i;
	for (i=0;i<length;) {
		unsigned short command=getUShort(&assembled[i]);
		i+=sizeof(unsigned short);
		if (command == LET_TOKEN) i=handleLet(assembled, i);
		if (command == ARRAYSET_TOKEN) i=handleArraySet(assembled, i);
		if (command == DIMARRAY_TOKEN) i=handleDimArray(assembled, i, 0);
		if (command == DIMSHAREDARRAY_TOKEN) i=handleDimArray(assembled, i, 1);
		if (command == PRINT_TOKEN) i=handlePrint(assembled, i);
		if (command == STOP_TOKEN) return;
		if (command == SYNC_TOKEN) i=handleSync(assembled, i);
		if (command == IF_TOKEN) i=handleIf(assembled, i);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i);
		if (command == FOR_TOKEN) i=handleFor(assembled, i);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i);
		if (command == INPUT_TOKEN) i=handleInput(assembled, i);
		if (command == INPUT_STRING_TOKEN) i=handleInputWithString(assembled, i);
		if (command == SEND_TOKEN) i=handleSend(assembled, i);
		if (command == RECV_TOKEN) i=handleRecv(assembled, i);
		if (command == RECVTOARRAY_TOKEN) i=handleRecvToArray(assembled, i);
		if (command == SENDRECV_TOKEN) i=handleSendRecv(assembled, i);
		if (command == SENDRECVARRAY_TOKEN) i=handleSendRecvArray(assembled, i);
		if (command == BCAST_TOKEN) i=handleBcast(assembled, i);
		if (command == REDUCTION_TOKEN) i=handleReduction(assembled, i);
		if (stopInterpreter) return;
	}
}
#endif

/**
 * Synchronisation between the cores
 */
#ifdef HOST_INTERPRETER
static int handleSync(char * assembled, int currentPoint, int threadId) {
#else
static int handleSync(char * assembled, int currentPoint) {
#endif
	syncCores();
	return currentPoint;
}

/**
 * Sending of data from one core to another
 */
#ifdef HOST_INTERPRETER
static int handleSend(char * assembled, int currentPoint, int threadId) {
	struct value_defn to_send_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, threadId);
	sendData(to_send_expression, getInt(target_expression.data), threadId);
#else
static int handleSend(char * assembled, int currentPoint) {
	struct value_defn to_send_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint);
	sendData(to_send_expression, getInt(target_expression.data));
#endif
	return currentPoint;
}

/**
 * A reduction operation - collective communication between cores
 */
#ifdef HOST_INTERPRETER
static int handleReduction(char * assembled, int currentPoint, int threadId) {
#else
static int handleReduction(char * assembled, int currentPoint) {
#endif
	unsigned short reductionOperator=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, threadId);
	variableSymbol->value=reduceData(broadcast_expression, reductionOperator, threadId, numActiveCores[threadId]);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint);
	variableSymbol->value=reduceData(broadcast_expression, reductionOperator);
#endif
	return currentPoint;
}

/**
 * Broadcast collective communication
 */
#ifdef HOST_INTERPRETER
static int handleBcast(char * assembled, int currentPoint, int threadId) {
#else
static int handleBcast(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, threadId);
	variableSymbol->value=bcastData(broadcast_expression, getInt(source_expression.data), threadId, numActiveCores[threadId]);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn broadcast_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint);
	variableSymbol->value=bcastData(broadcast_expression, getInt(source_expression.data));
#endif
	return currentPoint;
}

/**
 * Receiving some data from another core
 */
#ifdef HOST_INTERPRETER
static int handleRecv(char * assembled, int currentPoint, int threadId) {
#else
static int handleRecv(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, threadId);
	variableSymbol->value=recvData(getInt(source_expression.data), threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint);
	variableSymbol->value=recvData(getInt(source_expression.data));
#endif
	return currentPoint;
}

/**
 * Receiving some data from another core and placing this into an array structure
 */
#ifdef HOST_INTERPRETER
static int handleRecvToArray(char * assembled, int currentPoint, int threadId) {
#else
static int handleRecvToArray(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn retrievedData=recvData(getInt(source_expression.data), threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint);
	struct value_defn source_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn retrievedData=recvData(getInt(source_expression.data));
#endif

	variableSymbol->value.type=retrievedData.type;
	char * ptr;
	cpy(&ptr, variableSymbol->value.data, sizeof(int*));
	cpy(ptr+(getInt(index.data) *4), retrievedData.data, 4);
	return currentPoint;
}

/**
 * Handles the sendrecv call, which does both P2P in one action with 1 synchronisation
 */
#ifdef HOST_INTERPRETER
static int handleSendRecv(char * assembled, int currentPoint, int threadId) {
#else
static int handleSendRecv(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, threadId);
	variableSymbol->value=sendRecvData(tosend_expression, getInt(target_expression.data), threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint);
	variableSymbol->value=sendRecvData(tosend_expression, getInt(target_expression.data));
#endif
	return currentPoint;
}

/**
 * Handles the sendrecv call into an array, which does both P2P in one action with 1 synchronisation
 */
#ifdef HOST_INTERPRETER
static int handleSendRecvArray(char * assembled, int currentPoint, int threadId) {
#else
static int handleSendRecvArray(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn retrievedData=sendRecvData(tosend_expression, getInt(target_expression.data), threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint);
	struct value_defn tosend_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn target_expression=getExpressionValue(assembled, &currentPoint);
	struct value_defn retrievedData=sendRecvData(tosend_expression, getInt(target_expression.data));
#endif

	variableSymbol->value.type=retrievedData.type;
	char * ptr;
	cpy(&ptr, variableSymbol->value.data, sizeof(int*));
	cpy(ptr+(getInt(index.data) *4), retrievedData.data, 4);
	return currentPoint;
}

/**
 * Goto some absolute location in the byte code
 */
#ifdef HOST_INTERPRETER
static int handleGoto(char * assembled, int currentPoint, int threadId) {
#else
static int handleGoto(char * assembled, int currentPoint) {
#endif
	return getUShort(&assembled[currentPoint]);
}

/**
 * Loop iteration
 */
#ifdef HOST_INTERPRETER
static int handleFor(char * assembled, int currentPoint, int threadId) {
#else
static int handleFor(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn to_expression=getExpressionValue(assembled, &currentPoint, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn to_expression=getExpressionValue(assembled, &currentPoint);
#endif
	unsigned short blockLen=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);

	if (getInt(variableSymbol->value.data) <= getInt(to_expression.data)) return currentPoint;
	currentPoint+=blockLen+sizeof(unsigned short)*2;
	return currentPoint;
}

/**
 * Conditional, with or without else block
 */
#ifdef HOST_INTERPRETER
static int handleIf(char * assembled, int currentPoint, int threadId) {
	int conditionalResult=determine_logical_expression(assembled, &currentPoint, threadId);
#else
static int handleIf(char * assembled, int currentPoint) {
	int conditionalResult=determine_logical_expression(assembled, &currentPoint);
#endif
	if (conditionalResult) return currentPoint+sizeof(unsigned short);
	unsigned short blockLen=getUShort(&assembled[currentPoint]);
	return currentPoint+sizeof(unsigned short)+blockLen;
}

/**
 * Input from user without string to display
 */
#ifdef HOST_INTERPRETER
static int handleInput(char * assembled, int currentPoint, int threadId) {
#else
static int handleInput(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
#endif
	variableSymbol->value=getInputFromUser();
	return currentPoint;
}

/**
 * Input from user with string to display
 */
#ifdef HOST_INTERPRETER
static int handleInputWithString(char * assembled, int currentPoint, int threadId) {
#else
static int handleInputWithString(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn string_display=getExpressionValue(assembled, &currentPoint, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn string_display=getExpressionValue(assembled, &currentPoint);
#endif
	variableSymbol->value=getInputFromUserWithString(string_display);
	return currentPoint;
}

/**
 * Print some value to the user
 */
#ifdef HOST_INTERPRETER
static int handlePrint(char * assembled, int currentPoint, int threadId) {
	struct value_defn result=getExpressionValue(assembled, &currentPoint, threadId);
#else
static int handlePrint(char * assembled, int currentPoint) {
	struct value_defn result=getExpressionValue(assembled, &currentPoint);
#endif
	displayToUser(result);
	return currentPoint;
}

/**
 * Declaration of an array and whether it is to be in default (core local) or shared memory
 */
#ifdef HOST_INTERPRETER
static int handleDimArray(char * assembled, int currentPoint, char inSharedMemory, int threadId) {
#else
static int handleDimArray(char * assembled, int currentPoint, char inSharedMemory) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn size=getExpressionValue(assembled, &currentPoint, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn size=getExpressionValue(assembled, &currentPoint);
#endif
	variableSymbol->value.type=INT_TYPE;
	int * address=getArrayAddress(getInt(size.data), inSharedMemory);
	cpy(variableSymbol->value.data, &address, sizeof(int*));
	return currentPoint;
}

/**
 * Set an individual element of an array
 */
#ifdef HOST_INTERPRETER
static int handleArraySet(char * assembled, int currentPoint, int threadId) {
#else
static int handleArraySet(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint, threadId);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	struct value_defn index=getExpressionValue(assembled, &currentPoint);
	struct value_defn value=getExpressionValue(assembled, &currentPoint);
#endif
	variableSymbol->value.type=value.type;
	char * ptr;
	cpy(&ptr, variableSymbol->value.data, sizeof(int*));
	cpy(ptr+(getInt(index.data) *4), value.data, 4);
	return currentPoint;
}

/**
 * Set a scalar value (held in the symbol table)
 */
#ifdef HOST_INTERPRETER
static int handleLet(char * assembled, int currentPoint, int threadId) {
#else
static int handleLet(char * assembled, int currentPoint) {
#endif
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, threadId);
	variableSymbol->value=getExpressionValue(assembled, &currentPoint, threadId);
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId);
	variableSymbol->value=getExpressionValue(assembled, &currentPoint);
#endif
	return currentPoint;
}

/**
 * Determines a logical expression based upon two operands and an operator
 */
#ifdef HOST_INTERPRETER
static int determine_logical_expression(char * assembled, int * currentPoint, int threadId) {
#else
static int determine_logical_expression(char * assembled, int * currentPoint) {
#endif
	unsigned short expressionId=getUShort(&assembled[*currentPoint]);
	*currentPoint+=sizeof(unsigned short);
	if (expressionId == AND_TOKEN || expressionId == OR_TOKEN) {
#ifdef HOST_INTERPRETER
		int s1=determine_logical_expression(assembled, currentPoint, threadId);
		int s2=determine_logical_expression(assembled, currentPoint, threadId);
#else
		int s1=determine_logical_expression(assembled, currentPoint);
		int s2=determine_logical_expression(assembled, currentPoint);
#endif
		if (expressionId == AND_TOKEN) return s1 && s2;
		if (expressionId == OR_TOKEN) return s1 || s2;
	} else if (expressionId == EQ_TOKEN || expressionId == NEQ_TOKEN || expressionId == GT_TOKEN || expressionId == GEQ_TOKEN ||
			expressionId == LT_TOKEN || expressionId == LEQ_TOKEN) {
#ifdef HOST_INTERPRETER
		struct value_defn expression1=getExpressionValue(assembled, currentPoint, threadId);
		struct value_defn expression2=getExpressionValue(assembled, currentPoint, threadId);
#else
		struct value_defn expression1=getExpressionValue(assembled, currentPoint);
		struct value_defn expression2=getExpressionValue(assembled, currentPoint);
#endif
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
			} else {
				raiseError("Can only test for equality with strings");
			}
		}
	}
	return 0;
}

/**
 * Gets the value of an expression, which is number, string, identifier or mathematical
 */
#ifdef HOST_INTERPRETER
static struct value_defn getExpressionValue(char * assembled, int * currentPoint, int threadId) {
#else
static struct value_defn getExpressionValue(char * assembled, int * currentPoint) {
#endif
	struct value_defn value;

	unsigned short expressionId=getUShort(&assembled[*currentPoint]);
	*currentPoint+=sizeof(unsigned short);
	if (expressionId == INTEGER_TOKEN) {
		value.type=INT_TYPE;
		cpy(value.data, &assembled[*currentPoint], sizeof(int));
		*currentPoint+=sizeof(int);
	} else if (expressionId == REAL_TOKEN) {
		value.type=REAL_TYPE;
		cpy(value.data, &assembled[*currentPoint], sizeof(float));
		*currentPoint+=sizeof(float);
	} else if (expressionId == STRING_TOKEN) {
		value.type=STRING_TYPE;
		char * strPtr=assembled + *currentPoint;
		cpy(&value.data, &strPtr, sizeof(char*));
		*currentPoint+=(slength(strPtr)+1);
	} else if (expressionId == COREID_TOKEN) {
		value.type=INT_TYPE;
#ifdef HOST_INTERPRETER
		cpy(value.data, &localCoreId[threadId], sizeof(int));
#else
		cpy(value.data, &localCoreId, sizeof(int));
#endif
	} else if (expressionId == NUMCORES_TOKEN) {
		value.type=INT_TYPE;
#ifdef HOST_INTERPRETER
		cpy(value.data, &numActiveCores[threadId], sizeof(int));
#else
		cpy(value.data, &numActiveCores, sizeof(int));
#endif
	} else if (expressionId == RANDOM_TOKEN) {
		value=performMathsOp(RANDOM_MATHS_OP, value);
	} else if (expressionId == MATHS_TOKEN) {
		unsigned short maths_op=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		value=performMathsOp(maths_op, getExpressionValue(assembled, currentPoint, threadId));
#else
		value=performMathsOp(maths_op, getExpressionValue(assembled, currentPoint));
#endif
	} else if (expressionId == IDENTIFIER_TOKEN || expressionId == ARRAYACCESS_TOKEN) {
		unsigned short variable_id=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, threadId);
#else
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id);
#endif
		value=variableSymbol->value;
		if (expressionId == ARRAYACCESS_TOKEN) {
#ifdef HOST_INTERPRETER
			struct value_defn index=getExpressionValue(assembled, currentPoint, threadId);
#else
			struct value_defn index=getExpressionValue(assembled, currentPoint);
#endif
			char * ptr;
			cpy(&ptr, variableSymbol->value.data, sizeof(int*));
			cpy(&value.data, ptr+(getInt(index.data) *4), sizeof(int));
		}
	} else if (expressionId == ADD_TOKEN || expressionId == SUB_TOKEN || expressionId == MUL_TOKEN ||
			expressionId == DIV_TOKEN || expressionId == MOD_TOKEN || expressionId == POW_TOKEN) {
#ifdef HOST_INTERPRETER
		value=computeExpressionResult(expressionId, assembled, currentPoint, threadId);
#else
		value=computeExpressionResult(expressionId, assembled, currentPoint);
#endif
	}
	return value;
}

/**
 * Computes the result of a simple mathematical expression, if one is a real and the other an integer
 * then raises to be a real
 */
#ifdef HOST_INTERPRETER
static struct value_defn computeExpressionResult(unsigned short operator, char * assembled, int * currentPoint, int threadId) {
#else
static struct value_defn computeExpressionResult(unsigned short operator, char * assembled, int * currentPoint) {
#endif
	struct value_defn value;
#ifdef HOST_INTERPRETER
	struct value_defn v1=getExpressionValue(assembled, currentPoint, threadId);
	struct value_defn v2=getExpressionValue(assembled, currentPoint, threadId);
#else
	struct value_defn v1=getExpressionValue(assembled, currentPoint);
	struct value_defn v2=getExpressionValue(assembled, currentPoint);
#endif
	value.type=v1.type==INT_TYPE && v2.type==INT_TYPE ? INT_TYPE : v1.type==STRING_TYPE || v2.type==STRING_TYPE ? STRING_TYPE : REAL_TYPE;
	if (value.type==INT_TYPE) {
		int i, value1=getInt(v1.data), value2=getInt(v2.data), result;
		if (operator==ADD_TOKEN) result=value1+value2;
		if (operator==SUB_TOKEN) result=value1-value2;
		if (operator==MUL_TOKEN) result=value1*value2;
		if (operator==DIV_TOKEN) result=value1/value2;
		if (operator==MOD_TOKEN) result=value1%value2;
		if (operator==POW_TOKEN) {
			result=value1;
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
				result=value1;
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
static struct symbol_node* getVariableSymbol(unsigned short id, int threadId) {
#else
static struct symbol_node* getVariableSymbol(unsigned short id) {
#endif
	int i;
#ifdef HOST_INTERPRETER
	for (i=0;i<currentSymbolEntries[threadId];i++) {
		if (symbolTable[threadId][i].id == id) return &(symbolTable[threadId])[i];
#else
	for (i=0;i<currentSymbolEntries;i++) {
		if (symbolTable[i].id == id) return &symbolTable[i];
#endif
	}
	int zero=0;
#ifdef HOST_INTERPRETER
	symbolTable[threadId][currentSymbolEntries[threadId]].id=id;
	symbolTable[threadId][currentSymbolEntries[threadId]].value.type=INT_TYPE;
	cpy(symbolTable[threadId][currentSymbolEntries[threadId]].value.data, &zero, sizeof(int));
	return &symbolTable[threadId][currentSymbolEntries[threadId]++];
#else
	symbolTable[currentSymbolEntries].id=id;
	symbolTable[currentSymbolEntries].value.type=INT_TYPE;
	cpy(symbolTable[currentSymbolEntries].value.data, &zero, sizeof(int));
	return &symbolTable[currentSymbolEntries++];
#endif
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
 * Helper method to get an unsigned short from data (needed as casting to integer directly requires 4 byte alignment
 * which we do not want to enforce as it wastes memory.)
 */
static unsigned short getUShort(void* data) {
	unsigned short v;
	cpy(&v, data, sizeof(unsigned short));
	return v;
}
