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
#define NULL ((void *)0)
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
static unsigned int handleGoto(char*, unsigned int, unsigned int, int);
static unsigned int handleFnCall(char*, unsigned int, unsigned int*, unsigned int, char, int);
static unsigned int handleLet(char*, unsigned int, unsigned int, char, int);
static unsigned int handleIf(char*, unsigned int, unsigned int, int);
static unsigned int handleFor(char*, unsigned int, unsigned int, int);
static unsigned int handleNative(char *, unsigned int, unsigned int, struct value_defn*, int);
static unsigned int handleAlias(char *, unsigned int, unsigned int, int);
static int getArrayAccessorIndex(struct symbol_node*, char*, unsigned int*, unsigned int, int);
static struct symbol_node* getVariableSymbol(unsigned short, unsigned char, int, int);
static int getSymbolTableEntryId(int);
static void clearVariablesToLevel(unsigned char, int);
static struct value_defn getExpressionValue(char*, unsigned int*, unsigned int, int);
static int determine_logical_expression(char*, unsigned int*,  unsigned int, int);
static struct value_defn computeExpressionResult(unsigned char, char*, unsigned int*, unsigned int, int);
#else
struct value_defn processAssembledCode(char*, unsigned int, unsigned int);
static unsigned int handleGoto(char*, unsigned int, unsigned int);
static unsigned int handleFnCall(char*, unsigned int, unsigned int*, unsigned int, char);
static unsigned int handleLet(char*, unsigned int, unsigned int, char);
static unsigned int handleIf(char*, unsigned int, unsigned int);
static unsigned int handleFor(char*, unsigned int, unsigned int);
static unsigned int handleNative(char *, unsigned int, unsigned int, struct value_defn*);
static unsigned int handleAlias(char *, unsigned int, unsigned int);
static int getArrayAccessorIndex(struct symbol_node*, char*, unsigned int*, unsigned int);
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
int getInt(void*);
float getFloat(void*);

#ifdef HOST_INTERPRETER
void initThreadedAspectsForInterpreter(int total_number_threads, int baseHostPid, struct shared_basic * basicState) {
	stopInterpreter=(char*) malloc(total_number_threads);
	symbolTable=(struct symbol_node**) malloc(sizeof(struct symbol_node*) * total_number_threads);
	currentSymbolEntries=(int*) malloc(sizeof(int) * total_number_threads);
	localCoreId=(int*) malloc(sizeof(int) * total_number_threads);
	numActiveCores=(int*) malloc(sizeof(int) * total_number_threads);
	fnLevel=(unsigned char*) malloc(sizeof(unsigned char) * total_number_threads);
	initHostCommunicationData(total_number_threads, basicState, baseHostPid);
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
	empty.type=NONE_TYPE;
	empty.dtype=SCALAR;
	unsigned int i, fnAddr;
	for (i=currentPoint;i<length;) {
		unsigned char command=getUChar(&assembled[i]);
		i+=sizeof(unsigned char);
		if (command == LET_TOKEN) i=handleLet(assembled, i, length, 0, threadId);
		if (command == LETNOALIAS_TOKEN) i=handleLet(assembled, i, length, 1, threadId);
		if (command == STOP_TOKEN) return empty;
		if (command == IF_TOKEN) i=handleIf(assembled, i, length, threadId);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i, length, threadId);
		if (command == FOR_TOKEN) i=handleFor(assembled, i, length, threadId);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i, length, threadId);
		if (command == FNCALL_TOKEN || command == FNCALL_BY_VAR_TOKEN) {
			i=handleFnCall(assembled, i, &fnAddr, length, command == FNCALL_BY_VAR_TOKEN ? 1:0, threadId);
			fnLevel[threadId]++;
			processAssembledCode(assembled, fnAddr, length, threadId);
			clearVariablesToLevel(fnLevel[threadId], threadId);
			fnLevel[threadId]--;
		}
		if (command == NATIVE_TOKEN) i=handleNative(assembled, i, length, NULL, threadId);
		if (command == ALIAS_TOKEN) i=handleAlias(assembled, i, length, threadId);
		if (command == RETURN_TOKEN) return empty;
		if (command == RETURN_EXP_TOKEN) {
			return getExpressionValue(assembled, &i, length, threadId);
		}
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
	empty.type=NONE_TYPE;
	empty.dtype=SCALAR;
	unsigned int i, fnAddr;
	for (i=currentPoint;i<length;) {
		unsigned char command=getUChar(&assembled[i]);
		i+=sizeof(unsigned char);
		if (command == LET_TOKEN) i=handleLet(assembled, i, length, 0);
		if (command == LETNOALIAS_TOKEN) i=handleLet(assembled, i, length, 1);
		if (command == STOP_TOKEN) return empty;
		if (command == IF_TOKEN) i=handleIf(assembled, i, length);
		if (command == IFELSE_TOKEN) i=handleIf(assembled, i, length);
		if (command == FOR_TOKEN) i=handleFor(assembled, i, length);
		if (command == GOTO_TOKEN) i=handleGoto(assembled, i, length);
		if (command == FNCALL_TOKEN || command == FNCALL_BY_VAR_TOKEN) {
			i=handleFnCall(assembled, i, &fnAddr, length, command == FNCALL_BY_VAR_TOKEN ? 1:0);
			fnLevel++;
			processAssembledCode(assembled, fnAddr, length);
			clearVariablesToLevel(fnLevel);
			fnLevel--;
		}
		if (command == NATIVE_TOKEN) i=handleNative(assembled, i, length, NULL);
		if (command == ALIAS_TOKEN) i=handleAlias(assembled, i, length);
		if (command == RETURN_TOKEN) return empty;
		if (command == RETURN_EXP_TOKEN) {
			return getExpressionValue(assembled, &i, length);
		}
		if (stopInterpreter) return empty;
	}
	return empty;
}
#endif

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

#ifdef HOST_INTERPRETER
static unsigned int handleNative(char * assembled, unsigned int currentPoint, unsigned int length, struct value_defn * returnValue, int threadId) {
#else
static unsigned int handleNative(char * assembled, unsigned int currentPoint, unsigned int length, struct value_defn * returnValue) {
#endif
    unsigned char fnCode=getUChar(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned char);
	unsigned short numArgs=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);

    struct value_defn toPassValues[numArgs];
	int i;
	for (i=0;i<numArgs;i++) {
#ifdef HOST_INTERPRETER
        toPassValues[i]=getExpressionValue(assembled, &currentPoint, length, threadId);
#else
        toPassValues[i]=getExpressionValue(assembled, &currentPoint, length);
#endif
	}
	if (returnValue != NULL) {
#ifdef HOST_INTERPRETER
        callNativeFunction(returnValue, fnCode, numArgs, toPassValues, numActiveCores[threadId], localCoreId[threadId], currentSymbolEntries[threadId], symbolTable[threadId], threadId);
#else
        callNativeFunction(returnValue, fnCode, numArgs, toPassValues, numActiveCores, localCoreId, currentSymbolEntries, symbolTable);
#endif
	} else {
	    struct value_defn dummy;
#ifdef HOST_INTERPRETER
        callNativeFunction(&dummy, fnCode, numArgs, toPassValues, numActiveCores[threadId], localCoreId[threadId], currentSymbolEntries[threadId], symbolTable[threadId], threadId);
#else
        callNativeFunction(&dummy, fnCode, numArgs, toPassValues, numActiveCores, localCoreId, currentSymbolEntries, symbolTable);
#endif
	}
	return currentPoint;
}

/**
 * Calls some function and stores the call point in the function call stack for returning from this function
 */
#ifdef HOST_INTERPRETER
static unsigned int handleFnCall(char * assembled, unsigned int currentPoint, unsigned int * functionAddress, unsigned int length, char calledByVar, int threadId) {
#else
static unsigned int handleFnCall(char * assembled, unsigned int currentPoint, unsigned int * functionAddress, unsigned int length, char calledByVar) {
#endif
	unsigned short fnAddress;
	if (calledByVar) {
#ifdef HOST_INTERPRETER
        struct symbol_node* callVar=getVariableSymbol(getUShort(&assembled[currentPoint]), fnLevel[threadId], threadId, 1);
#else
        struct symbol_node* callVar=getVariableSymbol(getUShort(&assembled[currentPoint]), fnLevel, 1);
#endif
        if (callVar->value.type != FN_ADDR_TYPE) raiseError(ERR_FNCALL_VAR_NOT_CONTAINING_FN_PTR);
        char *ptr;
        cpy(&ptr, callVar->value.data, sizeof(char*));
        fnAddress=getUShort(ptr);
	} else {
        fnAddress=getUShort(&assembled[currentPoint]);
	}
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
	int singleSize, arrSize=1, i, headersize;
	unsigned char numDims;
	cpy(&ptr, expressionVal.data, sizeof(char*));
	cpy(&numDims, ptr, sizeof(unsigned char));
	numDims=numDims & 0xF;
	for (i=0;i<numDims;i++) {
        cpy(&singleSize, &ptr[1+(i*sizeof(unsigned int))], sizeof(unsigned int));
        arrSize*=singleSize;
	}
	headersize=sizeof(unsigned char) + (sizeof(unsigned int) * numDims);
	struct value_defn varVal=getVariableValue(incrementVarSymbol, -1);
	int incrementVal=getInt(varVal.data);
	if (incrementVal < arrSize) {
		struct value_defn nextElement;
		nextElement.type=expressionVal.type;
		cpy(&nextElement.data, ptr+((incrementVal*sizeof(int)) + headersize), sizeof(int));
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

#ifdef HOST_INTERPRETER
static unsigned int handleAlias(char * assembled, unsigned int currentPoint, unsigned int length, int threadId) {
#else
static unsigned int handleAlias(char * assembled, unsigned int currentPoint, unsigned int length) {
#endif
	unsigned short tgtVarId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* tgtVariableSymbol=getVariableSymbol(tgtVarId, fnLevel[threadId], threadId, 1);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length, threadId);
#else
	struct symbol_node* tgtVariableSymbol=getVariableSymbol(tgtVarId, fnLevel, 1);
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length);
#endif
	int symbolVal=getInt(value.data);
	tgtVariableSymbol->state=ALIAS;
	tgtVariableSymbol->alias=(unsigned char) symbolVal;
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
	unsigned char identifierType=getUChar(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned char);
	unsigned short varId=getUShort(&assembled[currentPoint]);
	currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel[threadId], threadId, 1);
	int targetIndex=-1;
	if (identifierType==ARRAYACCESS_TOKEN) {
		targetIndex=getArrayAccessorIndex(variableSymbol, assembled, &currentPoint, length, threadId);
	}
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length, threadId);
	if (restrictNoAlias && getVariableSymbol(varId, fnLevel[threadId], threadId, 0)->state==ALIAS) return currentPoint;
#else
	struct symbol_node* variableSymbol=getVariableSymbol(varId, fnLevel, 1);
	int targetIndex=-1;
	if (identifierType==ARRAYACCESS_TOKEN) {
		targetIndex=getArrayAccessorIndex(variableSymbol, assembled, &currentPoint, length);
	}
	struct value_defn value=getExpressionValue(assembled, &currentPoint, length);
	if (restrictNoAlias && getVariableSymbol(varId, fnLevel, 0)->state==ALIAS) return currentPoint;
#endif
	variableSymbol->value.type=value.type;
	// Set the dtype if this is not an array (otherwise it can overwrite an array type with scalar, and array access will always be predefined so should be fine
	if (identifierType!=ARRAYACCESS_TOKEN) variableSymbol->value.dtype=value.dtype;
	if (value.dtype == ARRAY || value.dtype > 1) {
		cpy(variableSymbol->value.data, value.data, sizeof(char*));
	} else if (value.type == STRING_TYPE) {
		cpy(&variableSymbol->value.data, &value.data, sizeof(char*));
	} else {
		char * ptr;
		cpy(&ptr, variableSymbol->value.data, sizeof(char*));
		if (ptr == 0) {
			ptr=getStackMemory(sizeof(int), 0);
			cpy(variableSymbol->value.data, &ptr, sizeof(char*));
			cpy(ptr, value.data, sizeof(char*));
		} else {
			setVariableValue(variableSymbol, value, targetIndex);
		}
	}
	if (variableSymbol->value.dtype > 1) variableSymbol->value.dtype-=2;
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
	} else if (expressionId == NOT_TOKEN) {
#ifdef HOST_INTERPRETER
		struct value_defn expression=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		struct value_defn expression=getExpressionValue(assembled, currentPoint, length);
#endif
		int value=getInt(expression.data);
		if (value > 0) return 0;
		return 1;
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
			cpy(&ptr1, expression1.data, sizeof(char*));
			cpy(&ptr2, expression2.data, sizeof(char*));
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
				raiseError(ERR_STR_ONLYTEST_EQ);
			}
		} else if (expression1.type == expression2.type && expression1.type == NONE_TYPE) {
			if (expressionId == EQ_TOKEN || expressionId == IS_TOKEN) {
				return 1;
			} else if (expressionId == NEQ_TOKEN) {
				return 0;
			} else {
				raiseError(ERR_NONE_ONLYTEST_EQ);
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
            int targetIndex=getArrayAccessorIndex(variableSymbol, assembled, currentPoint, length, threadId);
#else
			int targetIndex=getArrayAccessorIndex(variableSymbol, assembled, currentPoint, length);
#endif
			value=getVariableValue(variableSymbol, targetIndex);
		}
		if (value.type == BOOLEAN_TYPE) {
			return getInt(value.data) > 0;
		}
		return 0;
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
	} else if (expressionId ==FN_ADDR_TOKEN) {
        value.type=FN_ADDR_TYPE;
		value.dtype=SCALAR;
		cpy(value.data, &assembled[*currentPoint], sizeof(unsigned short));
		*currentPoint+=sizeof(unsigned short);
	} else if (expressionId == LET_TOKEN) {
#ifdef HOST_INTERPRETER
		*currentPoint=handleLet(assembled, *currentPoint, length, 0, threadId);
		value=getExpressionValue(assembled, currentPoint, length, threadId);
#else
		*currentPoint=handleLet(assembled, *currentPoint, length, 0);
		value=getExpressionValue(assembled, currentPoint, length);
#endif
	} else if (expressionId == ARRAY_TOKEN) {
		int i, j, repetitionMultiplier=1, numItems=getInt(&assembled[*currentPoint]), totalSize=numItems;
		*currentPoint+=sizeof(int);
		unsigned char hasRepetition=getUChar(&assembled[*currentPoint]), ndims=1;
		*currentPoint+=sizeof(unsigned char);
		if (hasRepetition) {
#ifdef HOST_INTERPRETER
			struct value_defn repetitionV=getExpressionValue(assembled, currentPoint, length, threadId);
#else
			struct value_defn repetitionV=getExpressionValue(assembled, currentPoint, length);
#endif
            cpy(&repetitionMultiplier, repetitionV.data, sizeof(int));
            totalSize*=repetitionMultiplier;
		}
#ifdef HOST_INTERPRETER
        char * address=getHeapMemory(sizeof(unsigned char) + (sizeof(int)*(totalSize+1)), 0, threadId);
#else
        char * address=getHeapMemory(sizeof(unsigned char) + (sizeof(int)*(totalSize+1)), 0, currentSymbolEntries, symbolTable);
#endif
		cpy(value.data, &address, sizeof(char*));
		ndims=ndims | (1 << 4);
		cpy(address, &ndims, sizeof(unsigned char));
		address+=sizeof(unsigned char);
		cpy(address, &totalSize, sizeof(int));
		unsigned int prevCP=*currentPoint;
		for (j=0;j<repetitionMultiplier;j++) {
        *currentPoint=prevCP;
            for (i=0;i<numItems;i++) {
#ifdef HOST_INTERPRETER
                struct value_defn itemV=getExpressionValue(assembled, currentPoint, length, threadId);
#else
                struct value_defn itemV=getExpressionValue(assembled, currentPoint, length);
#endif
            cpy(address+((i+(j*numItems)+1) * sizeof(int)), itemV.data, sizeof(int));
            value.type=itemV.type;
            }
		}
		value.dtype=ARRAY;
	} else if (expressionId == FNCALL_TOKEN || expressionId == FNCALL_BY_VAR_TOKEN) {
#ifdef HOST_INTERPRETER
		unsigned int fnAddr;
		*currentPoint=handleFnCall(assembled, *currentPoint, &fnAddr, length, expressionId == FNCALL_BY_VAR_TOKEN ? 1:0, threadId);
		fnLevel[threadId]++;
		value=processAssembledCode(assembled, fnAddr, length, threadId);
		clearVariablesToLevel(fnLevel[threadId], threadId);
		fnLevel[threadId]--;
#else
		unsigned int fnAddr;
		*currentPoint=handleFnCall(assembled, *currentPoint, &fnAddr, length, expressionId == FNCALL_BY_VAR_TOKEN ? 1:0);
		fnLevel++;
		value=processAssembledCode(assembled, fnAddr, length);
		clearVariablesToLevel(fnLevel);
		fnLevel--;
#endif
    } else if (expressionId == NATIVE_TOKEN) {
#ifdef HOST_INTERPRETER
        *currentPoint=handleNative(assembled, *currentPoint, length, &value, threadId);
#else
        *currentPoint=handleNative(assembled, *currentPoint, length, &value);
#endif
	} else if (expressionId == SYMBOL_TOKEN) {
		unsigned short variable_id=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel[threadId], threadId, 1);
#else
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel, 1);
#endif
		value.dtype=SCALAR;
		value.type=INT_TYPE;
		cpy(value.data, &variableSymbol->id, sizeof(int));
	} else if (expressionId == REFERENCE_TOKEN) {
		unsigned short variable_id=getUShort(&assembled[*currentPoint]);
		*currentPoint+=sizeof(unsigned short);
#ifdef HOST_INTERPRETER
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel[threadId], threadId, 1);
#else
		struct symbol_node* variableSymbol=getVariableSymbol(variable_id, fnLevel, 1);
#endif
		value.dtype=SCALAR;
		value.type=variableSymbol->value.type;
		value.type|=1 << 7;
		value.type|=(variableSymbol->value.dtype & 1)<<5;
		value.type|=(variableSymbol->value.dtype >> 1 & 1)<<6;
		cpy(value.data, variableSymbol->value.data, sizeof(char*));
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
				cpy(value.data, variableSymbol->value.data, sizeof(char*));
			}
		} else if (expressionId == ARRAYACCESS_TOKEN) {
#ifdef HOST_INTERPRETER
			int targetIndex=getArrayAccessorIndex(variableSymbol, assembled, currentPoint, length, threadId);
#else
			int targetIndex=getArrayAccessorIndex(variableSymbol, assembled, currentPoint, length);
#endif
			value=getVariableValue(variableSymbol, targetIndex);
		}
	} else if (expressionId == ADD_TOKEN || expressionId == SUB_TOKEN || expressionId == MUL_TOKEN ||
			expressionId == DIV_TOKEN || expressionId == MOD_TOKEN || expressionId == POW_TOKEN) {
#ifdef HOST_INTERPRETER
		value=computeExpressionResult(expressionId, assembled, currentPoint, length, threadId);
#else
		value=computeExpressionResult(expressionId, assembled, currentPoint, length);
#endif
	} else if (expressionId == EQ_TOKEN || expressionId == NEQ_TOKEN || expressionId == GT_TOKEN || expressionId == GEQ_TOKEN ||
			expressionId == LT_TOKEN || expressionId == LEQ_TOKEN || expressionId == IS_TOKEN) {
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
#ifdef HOST_INTERPRETER
        return performStringConcatenation(v1, v2, threadId);
#else
        return performStringConcatenation(v1, v2, currentSymbolEntries, symbolTable);
#endif
		} else {
			raiseError(ERR_ONLY_ADDITION_STR);
		}
	}
	return value;
}

/**
 * Retrieves the absolute array target index based upon the provided index expression(s) and dimensions of the array itself. Does some error checking
 * to ensure that the configured values do not exceed the size
 */
#ifdef HOST_INTERPRETER
static int getArrayAccessorIndex(struct symbol_node* variableSymbol, char * assembled, unsigned int * currentPoint, unsigned int length, int threadId) {
#else
static int getArrayAccessorIndex(struct symbol_node* variableSymbol, char * assembled, unsigned int * currentPoint, unsigned int length) {
#endif
    struct value_defn index;
    int i, j, runningWeight, spec_weight, num_weights, specificIndex=0, provIdx;
    unsigned int totSize=1;
    unsigned char num_dims=getUChar(&assembled[*currentPoint]), array_dims, needsExtension=0, allowedExtension;
    *currentPoint+=sizeof(unsigned char);

    char * arraymemory;
    cpy(&arraymemory, variableSymbol->value.data, sizeof(char*));
    cpy(&array_dims, arraymemory, sizeof(unsigned char));
    allowedExtension=(array_dims >> 4) & 1;
    array_dims=array_dims&0xF;
    arraymemory+=sizeof(unsigned char);

    if (num_dims > array_dims) raiseError(ERR_TOO_MANY_ARR_INDEX);

    for (i=0;i<num_dims;i++) {
        num_weights=array_dims-(i+1);
        runningWeight=1;
        for (j=num_weights;j>0;j--) {
            cpy(&spec_weight, &arraymemory[sizeof(int) * (array_dims-j)], sizeof(int));
            runningWeight*=spec_weight;
        }
#ifdef HOST_INTERPRETER
        index=getExpressionValue(assembled, currentPoint, length, threadId);
#else
        index=getExpressionValue(assembled, currentPoint, length);
#endif
        cpy(&spec_weight, &arraymemory[sizeof(int) * i], sizeof(int));
        totSize*=spec_weight;
        provIdx=getInt(index.data);
        if (provIdx < 0) {
            raiseError(ERR_NEG_ARR_INDEX);
        } else if (provIdx >= spec_weight) {
            if (!allowedExtension) raiseError(ERR_ARR_INDEX_EXCEED_SIZE);
            spec_weight=provIdx+1;
            cpy(&arraymemory[sizeof(int) * i], &spec_weight, sizeof(int));
            needsExtension=1;
        }
        specificIndex+=(runningWeight * provIdx);
    }
    if (needsExtension) {
        unsigned int newSize=1;
        for (i=0;i<num_dims;i++) {
            cpy(&spec_weight, &arraymemory[sizeof(int) * i], sizeof(int));
            newSize*=spec_weight;
        }
#ifdef HOST_INTERPRETER
        char * newmem=getHeapMemory((sizeof(int) * newSize) + (sizeof(int) * num_dims) + sizeof(unsigned char), 0, threadId);
#else
        char * newmem=getHeapMemory((sizeof(int) * newSize) + (sizeof(int) * num_dims) + sizeof(unsigned char), 0, currentSymbolEntries, symbolTable);
#endif
        arraymemory-=sizeof(unsigned char);
        cpy(newmem, arraymemory, (sizeof(int) * totSize) + (sizeof(int) * num_dims) + sizeof(unsigned char));
#ifdef HOST_INTERPRETER
        freeMemoryInHeap(arraymemory, threadId);
#else
        freeMemoryInHeap(arraymemory);
#endif
        cpy(variableSymbol->value.data, &newmem, sizeof(char*));
    }
    return specificIndex;
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
	char* zero=0;
#ifdef HOST_INTERPRETER
	int newEntryLocation=getSymbolTableEntryId(threadId);
	symbolTable[threadId][newEntryLocation].id=id;
	symbolTable[threadId][newEntryLocation].state=ALLOCATED;
	symbolTable[threadId][newEntryLocation].level=lvl;
	symbolTable[threadId][newEntryLocation].value.type=INT_TYPE;
	cpy(symbolTable[threadId][newEntryLocation].value.data, &zero, sizeof(char*));
	return &symbolTable[threadId][newEntryLocation];
#else
	int newEntryLocation=getSymbolTableEntryId();
	symbolTable[newEntryLocation].id=id;
	symbolTable[newEntryLocation].level=lvl;
	symbolTable[newEntryLocation].state=ALLOCATED;
	symbolTable[newEntryLocation].value.type=INT_TYPE;
	symbolTable[newEntryLocation].value.dtype=SCALAR;
	cpy(symbolTable[newEntryLocation].value.data, &zero, sizeof(char*));
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
 * Sets a variables value in memory as pointed to by symbol table
 */
void setVariableValue(struct symbol_node* variableSymbol, struct value_defn value, int index) {
	variableSymbol->value.type=value.type;
	if (value.type == STRING_TYPE) {
		cpy(&variableSymbol->value.data, &value.data, sizeof(char*));
	} else {
		char * ptr;
		cpy(&ptr, variableSymbol->value.data, sizeof(char*));
		if (ptr == 0) {
			ptr=getStackMemory(sizeof(int) * index, 0);
			cpy(variableSymbol->value.data, &ptr, sizeof(char*));
			cpy(ptr+((index+1) *4), value.data, sizeof(int));
		} else {
			cpy(&ptr, variableSymbol->value.data, sizeof(char*));
			if (variableSymbol->value.dtype == ARRAY) {
                unsigned char num_dims;
                cpy(&num_dims, ptr, sizeof(unsigned char));
                num_dims=num_dims & 0xF;
                ptr+=((index+num_dims)*sizeof(int)) + sizeof(unsigned char);
            } else {
                ptr+=(index+1)*sizeof(int);
            }
			cpy(ptr, value.data, sizeof(int));
		}
	}
}

/**
 * Retrieves a variable value from memory, which the symbol table points to
 */
struct value_defn getVariableValue(struct symbol_node* variableSymbol, int index) {
	struct value_defn val;
	val.type=variableSymbol->value.type;
	val.dtype=SCALAR;
	if (variableSymbol->value.type == STRING_TYPE) {
		cpy(&val.data, &variableSymbol->value.data, sizeof(int*));
	} else {
		char * ptr;
		cpy(&ptr, variableSymbol->value.data, sizeof(char*));
		if (variableSymbol->value.dtype == ARRAY) {
            unsigned char num_dims;
            cpy(&num_dims, ptr, sizeof(unsigned char));
            num_dims=num_dims & 0xF;
            ptr+=((index+num_dims)*sizeof(int)) + sizeof(unsigned char);
		} else {
		    ptr+=(index+1)*sizeof(int);
		}
		cpy(val.data, ptr, sizeof(char*));
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
