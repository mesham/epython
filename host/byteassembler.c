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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include "memorymanager.h"
#include "basictokens.h"
#include "byteassembler.h"

#define RECURSION_VAR_DEPTH 10

/*
 * Node for holding a specific scope information - the variables that belong to
 * this scope. These are arranged in a stack, and the stack searched downwards for
 * a variable. Therefore when we enter a scope block it is stack push and when we leave
 * stack pop
 */
struct scope_info {
	struct variable_node * variables;
	struct scope_info * next;
};

/*
 * Information about a specific variable, mapping it to a unique ID that will be
 * represented in the symbol table
 */
struct variable_node {
	char * name;
	unsigned short id;
	struct variable_node * next;
};

// The current for line, this is is used in conjunction with GOTO to code for repetition
int currentForLine=-1;
int currentSymbolTableId, isFnRecursive;
char * currentFunctionName=NULL;

static unsigned short current_var_id=1; // Current variable id (unique for each unique variable)
static struct scope_info * scope=NULL; // Scope stack
struct function_call_tree_node *currentCall=NULL; // The current function call tree state

static unsigned short addVariable(char*);
static unsigned short findVariable(struct variable_node*,  char*);
static int areStringsEqualIgnoreCase(char*, char*);
static unsigned short getVariableId(char*, int);
static struct memorycontainer* createExpression(unsigned char, struct memorycontainer*, struct memorycontainer*);
static struct memorycontainer* createUnaryGeneralMathsExpression(struct memorycontainer*, unsigned char);
static struct memorycontainer* appendLetIfNoAliasStatement(char *, struct memorycontainer*);

/**
 * Function entry, used for tracking recursive functions and the call tree
 */
void enterFunction(char* fn_name) {
	currentSymbolTableId=current_var_id;
	isFnRecursive=0;
	currentFunctionName=(char*) malloc(strlen(fn_name) + 1);
	strcpy(currentFunctionName, fn_name);
	struct function_call_tree_node * newFunctionCallNode=(struct function_call_tree_node*) malloc(sizeof(struct function_call_tree_node));
	newFunctionCallNode->number_of_calls=0;
	currentCall=newFunctionCallNode;
}

/**
 * Gets the total number of entries in the symbol table
 */
unsigned short getNumberEntriesInSymbolTable() {
	return current_var_id + (getNumberSymbolTableEntriesForRecursion()*(RECURSION_VAR_DEPTH-1));
}

/**
 * Sets the total number of entries in the symbol table
 */
void setNumberEntriesInSymbolTable(unsigned short e) {
	current_var_id=e;
}

/**
 * Appends and returns a reduction statement
 */
struct memorycontainer* appendReductionStatement(unsigned char op, struct memorycontainer* expression,  char* identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short) + sizeof(unsigned char)*2+ expression->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, REDUCTION_TOKEN, position);
	position=appendStatement(memoryContainer, op, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, expression, position);
	return memoryContainer;
}

/**
 * Appends and returns a broadcast statement
 */
struct memorycontainer* appendBcastStatement(struct memorycontainer* expression, struct memorycontainer* source,  char* identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short) + sizeof(unsigned char) + source->length+ expression->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, BCAST_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, expression, position);
	position=appendMemory(memoryContainer, source, position);
	return memoryContainer;
}

/**
 * Appends and returns a P2P receive statement
 */
struct memorycontainer* appendRecvStatement(char* identifier, struct memorycontainer* source) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)+sizeof(unsigned char)+ source->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, RECV_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, source, position);
	return memoryContainer;
}

/**
 * Appends and returns a P2P send statement
 */
struct memorycontainer* appendSendStatement(struct memorycontainer* toSendExpression, struct memorycontainer* target) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char) + toSendExpression->length+target->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, SEND_TOKEN, position);
	position=appendMemory(memoryContainer, toSendExpression, position);
	position=appendMemory(memoryContainer, target, position);
	return memoryContainer;
}

/**
 * Appends a sendrecv statement, which combined both p2p operations with one synchronisation
 */
struct memorycontainer* appendSendRecvStatement(struct memorycontainer* toSendExpression, struct memorycontainer* target, char* identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)+sizeof(unsigned char) + toSendExpression->length+target->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, SENDRECV_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, toSendExpression, position);
	position=appendMemory(memoryContainer, target, position);
	return memoryContainer;
}

/**
 * Appends and returns the declaration of an array into shared (parallella) memory
 */
struct memorycontainer* appendDeclareSharedArray( char* identifier, struct memorycontainer* exp1) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)+sizeof(unsigned char) + exp1->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, DIMSHAREDARRAY_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, exp1, position);
	return memoryContainer;
}

/**
 * Appends and returns the declaration of an array into default (often core local) memory statement
 */
struct memorycontainer* appendDeclareArray( char* identifier, struct memorycontainer* exp1) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)+sizeof(unsigned char) + exp1->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, DIMARRAY_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, exp1, position);
	return memoryContainer;
}

/**
 * Appends and returns an input statement
 */
struct memorycontainer* appendInputStatement( char * identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short) + sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, INPUT_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	return memoryContainer;
}

/**
 * Appends and returns an input statement that displays a user message
 */
struct memorycontainer* appendInputStringStatement(struct memorycontainer* toDisplay,  char* identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short) +sizeof(unsigned char)+ toDisplay->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, INPUT_STRING_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	appendMemory(memoryContainer, toDisplay, position);
	return memoryContainer;
}

/**
 * Appends and returns a call function, this is added as a placeholder and then resolved at the end to point to the absolute byte code location
 * which is needed as the function might appear at any point
 */
struct memorycontainer* appendCallFunctionStatement(char* functionName, struct stack_t* args) {
	if (currentFunctionName != NULL && strcmp(currentFunctionName, functionName) == 0) isFnRecursive=1;

	struct memorycontainer* assignmentContainer=NULL;
	unsigned short numArgs=(unsigned short) getStackSize(args);
	char * varname=(char*) malloc(strlen(functionName)+5);
	int i;
	for (i=0;i<numArgs;i++) {
		struct memorycontainer* expression=getExpressionAt(args, i);
		unsigned char command=((unsigned char*) expression->data)[0];
		if (command != IDENTIFIER_TOKEN) {
			sprintf(varname,"%s#%d", functionName, i);
			if (assignmentContainer == NULL) {
				assignmentContainer=appendLetStatement(varname, getExpressionAt(args, i));
			} else {
				assignmentContainer=concatenateMemory(assignmentContainer, appendLetStatement(varname, getExpressionAt(args, i)));
			}
		}
	}
	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)*(2+numArgs)+sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);

	defn->next=NULL;
	defn->type=3;
	defn->name=(char*) malloc(strlen(functionName)+1);
	strcpy(defn->name, functionName);
	defn->currentpoint=sizeof(unsigned char);

	memoryContainer->lineDefns=defn;

	unsigned int position=0;

	position=appendStatement(memoryContainer, FNCALL_TOKEN, position);
	position+=sizeof(unsigned short);
	position=appendVariable(memoryContainer, numArgs, position);

	for (i=0;i<numArgs;i++) {
		struct memorycontainer* expression=getExpressionAt(args, i);
		unsigned char command=((unsigned char*) expression->data)[0];
		if (command == IDENTIFIER_TOKEN) {
			unsigned short varId=*((unsigned short*) (&((char*) expression->data)[1]));
			position=appendVariable(memoryContainer, varId, position);
		} else {
			sprintf(varname,"%s#%d", functionName, i);
			position=appendVariable(memoryContainer, getVariableId(varname, 0), position);
		}
	}
	clearStack(args);
	free(varname);
	if (currentCall==NULL) {
		mainCodeCallTree.calledFunctions[mainCodeCallTree.number_of_calls]=(char*)malloc(strlen(functionName)+1);
		strcpy(mainCodeCallTree.calledFunctions[mainCodeCallTree.number_of_calls++], functionName);
	} else {
		currentCall->calledFunctions[currentCall->number_of_calls]=(char*)malloc(strlen(functionName)+1);
		strcpy(currentCall->calledFunctions[currentCall->number_of_calls++], functionName);
	}
	if (assignmentContainer != NULL) {
		return concatenateMemory(assignmentContainer, memoryContainer);
	} else {
		return memoryContainer;
	}
}

/**
 * Appends and returns a goto, this is added as a placeholder and then resolved at the end to point to the absolute byte code location
 * which is needed as we might be jumping forward and have not yet encountered the line label
 */
struct memorycontainer* appendGotoStatement(int lineNumber) {
	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned short)+sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);

	defn->next=NULL;
	defn->type=1;
	defn->linenumber=lineNumber;
	defn->currentpoint=sizeof(unsigned char);

	memoryContainer->lineDefns=defn;
	appendStatement(memoryContainer, GOTO_TOKEN, 0);
	return memoryContainer;
}

/**
 * Appends and returns a for iteration. This puts in the assignment of the initial value to the variable, the normal stuff and then
 * termination check at each iteration along with jumping to next iteration if applicable
 */
struct memorycontainer* appendForStatement(char * identifier, struct memorycontainer* exp, struct memorycontainer* block) {
	struct memorycontainer* initialLet=appendLetStatement("epy_i_ctr", createIntegerExpression(0));
	struct memorycontainer* variantLet=appendLetStatement(identifier, createIntegerExpression(0));
	struct memorycontainer* incrementLet=appendLetStatement("epy_i_ctr", createAddExpression(createIdentifierExpression("epy_i_ctr"), createIntegerExpression(1)));

	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)*2+sizeof(unsigned short) * 4 + exp->length + (block != NULL ? block->length : 0) +
			initialLet->length + variantLet->length + incrementLet->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	struct memorycontainer* combinedBlock=block != NULL ? concatenateMemory(block, incrementLet) : incrementLet;

	unsigned int position=0;

	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=0;
	defn->linenumber=currentForLine;
	defn->currentpoint=initialLet->length;
	memoryContainer->lineDefns=defn;

	position=appendMemory(memoryContainer, initialLet, position);
	position=appendMemory(memoryContainer, variantLet, position);
	position=appendStatement(memoryContainer, FOR_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId("epy_i_ctr", 0), position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 0), position);
	position=appendMemory(memoryContainer, exp, position);
	unsigned short length=(unsigned short) combinedBlock->length;
	memcpy(&memoryContainer->data[position], &length, sizeof(unsigned short));
	position+=sizeof(unsigned short);
	position=appendMemory(memoryContainer, combinedBlock, position);
	position=appendStatement(memoryContainer, GOTO_TOKEN, position);
	defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=1;
	defn->linenumber=currentForLine;
	defn->currentpoint=position;
	memoryContainer->lineDefns=defn;
	currentForLine--;
	return memoryContainer;
}

/**
 * Appends in a do while statement, which assembles down to an if statement with jump at the end of the block
 * to retest the condition and either do another iteration or not
 */
struct memorycontainer* appendWhileStatement(struct memorycontainer* expression, struct memorycontainer* block) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) * 3 + expression->length + (block != NULL ? block->length : 0);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, IF_TOKEN, position);
	position=appendMemory(memoryContainer, expression, position);
	if (block != NULL) {
		unsigned short blockLen=(unsigned short) block->length + 4;
		memcpy(&memoryContainer->data[position], &blockLen, sizeof(unsigned short));
		position+=sizeof(unsigned short);
		position=appendMemory(memoryContainer, block, position);
	} else {
		unsigned short blockLen=4;
		memcpy(&memoryContainer->data[position], &blockLen, sizeof(unsigned short));
		position+=sizeof(unsigned short);
	}
	position=appendStatement(memoryContainer, GOTO_TOKEN, position);

	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=0;
	defn->linenumber=currentForLine;
	defn->currentpoint=0;
	memoryContainer->lineDefns=defn;

	defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=1;
	defn->linenumber=currentForLine;
	defn->currentpoint=position;
	memoryContainer->lineDefns=defn;

	currentForLine--;
	return memoryContainer;
}

/**
 * Appends and returns a conditional, this is without an else statement so sets that to be zero
 */
struct memorycontainer* appendIfStatement(struct memorycontainer* expressionContainer, struct memorycontainer* thenBlock) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) + expressionContainer->length +
			(thenBlock != NULL ? thenBlock->length : 0);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, IF_TOKEN, position);
	position=appendMemory(memoryContainer, expressionContainer, position);
	if (thenBlock != NULL) {
		unsigned short len=(unsigned short) thenBlock->length;
		memcpy(&memoryContainer->data[position], &len, sizeof(unsigned short));
		position+=sizeof(unsigned short);
		position=appendMemory(memoryContainer, thenBlock, position);
	} else {
		unsigned short emptyLen=0;
		memcpy(&memoryContainer->data[position], &emptyLen, sizeof(unsigned short));
	}
	return memoryContainer;
}

/**
 * Appends and returns a conditional with else statement, a bit more complex as have to jump after the then block to the end of the
 * else block
 */
struct memorycontainer* appendIfElseStatement(struct memorycontainer* expressionContainer, struct memorycontainer* thenBlock,
		struct memorycontainer* elseBlock) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)*2+sizeof(unsigned short)*2 + expressionContainer->length +
			(thenBlock != NULL ? thenBlock->length : 0) + (elseBlock != NULL ? elseBlock->length : 0);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, IFELSE_TOKEN, position);
	position=appendMemory(memoryContainer, expressionContainer, position);

	unsigned short combinedThenGotoLength=(unsigned short) (thenBlock != NULL ? thenBlock->length : 0)+3;	// add for goto and line num
	memcpy(&memoryContainer->data[position], &combinedThenGotoLength, sizeof(unsigned short));
	position+=sizeof(unsigned short);

	if (thenBlock != NULL) {
		position=appendMemory(memoryContainer, thenBlock, position);
	}
	position=appendStatement(memoryContainer, GOTO_TOKEN, position);
	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=1;
	defn->linenumber=currentForLine;
	defn->currentpoint=position;
	memoryContainer->lineDefns=defn;
	position+=sizeof(unsigned short);
	if (elseBlock != NULL) position=appendMemory(memoryContainer, elseBlock, position);

	defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=memoryContainer->lineDefns;
	defn->type=0;
	defn->linenumber=currentForLine;
	defn->currentpoint=position;
	memoryContainer->lineDefns=defn;

	currentForLine--;
	return memoryContainer;
}

void appendArgument(char* argName) {
	getVariableId(argName, 1);
}

/**
 * Appends a new function statement to the function list which is held by the memory manager.
 * This also appends a return statement to the end of the function body and registers
 * the current goto point as the function name
 */
void appendNewFunctionStatement(char* functionName, struct stack_t * args, struct memorycontainer* functionContents) {
	struct functionDefinition * fn=(struct functionDefinition*) malloc(sizeof(struct functionDefinition));
	fn->name=(char*) malloc(strlen(functionName) + 1);
	strcpy(fn->name, functionName);
	fn->called=0;

	unsigned short numberArgs=(unsigned short) getStackSize(args);
	struct memorycontainer* numberArgsContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	numberArgsContainer->length=sizeof(unsigned short) * (numberArgs + 1);
	numberArgsContainer->data=(char*) malloc(sizeof(unsigned short) * (numberArgs + 1));
	numberArgsContainer->lineDefns=NULL;

	((unsigned short *) numberArgsContainer->data)[0]=numberArgs;

	struct memorycontainer* assignmentContainer=NULL;

	int i;
	for (i=0;i<numberArgs;i++) {
		if (getTypeAt(args, i) == 2) {
			((unsigned short *) numberArgsContainer->data)[i+1]=getVariableId(getIdentifierAt(args, i), 1);
		} else {
			struct identifier_exp * idexp=getExpressionIdentifierAt(args, i);
			if (assignmentContainer == NULL) {
				assignmentContainer=appendLetIfNoAliasStatement(idexp->identifier, idexp->exp);
			} else {
				assignmentContainer=concatenateMemory(assignmentContainer, appendLetIfNoAliasStatement(idexp->identifier, idexp->exp));
			}
			((unsigned short *) numberArgsContainer->data)[i+1]=getVariableId(idexp->identifier, 1);
		}
	}

	clearStack(args);

	if (assignmentContainer != NULL) numberArgsContainer=concatenateMemory(numberArgsContainer, assignmentContainer);

	struct memorycontainer* completedFunction=concatenateMemory(concatenateMemory(numberArgsContainer, functionContents),
			appendReturnStatement());

	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->next=completedFunction->lineDefns;
	defn->type=2;
	defn->currentpoint=0;
	defn->name=(char*) malloc(strlen(functionName) + 1);
	strcpy(defn->name, functionName);
	completedFunction->lineDefns=defn;

	fn->contents=completedFunction;
	fn->numberEntriesInSymbolTable=current_var_id - currentSymbolTableId;
	fn->recursive=isFnRecursive;
	fn->number_of_fn_calls=currentCall->number_of_calls;
	if (currentCall->number_of_calls == 0) {
		fn->functionCalls=NULL;
	} else {
		fn->functionCalls=(char**) malloc(sizeof(char*) * currentCall->number_of_calls);
		memcpy(fn->functionCalls, currentCall->calledFunctions, sizeof(char*) * currentCall->number_of_calls);
	}
	free(currentFunctionName);
	currentFunctionName=NULL;
	currentCall=NULL;
	addFunction(fn);
}

/**
 * Appends and returns the setting of an array element (assignment) statement
 */
struct memorycontainer* appendArraySetStatement( char* identifier, struct memorycontainer* indexContainer,
		struct memorycontainer* expressionContainer) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) + indexContainer->length+ expressionContainer->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, ARRAYSET_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	position=appendMemory(memoryContainer, indexContainer, position);
	position=appendMemory(memoryContainer, expressionContainer, position);
	return memoryContainer;
}

struct memorycontainer* appendLetWithOperatorStatement(char * identifier, struct memorycontainer* expressionContainer, unsigned char operator) {
	unsigned char token;
	if (operator == 0) {
		token=ADD_TOKEN;
	} else if (operator == 1) {
		token=SUB_TOKEN;
	} else if (operator == 2) {
		token=MUL_TOKEN;
	} else if (operator == 3 || operator == 6) {
		token=DIV_TOKEN;
	} else if (operator == 4) {
		token=MOD_TOKEN;
	} else if (operator == 5) {
		token=POW_TOKEN;
	} else {
		fprintf(stderr, "Can not find operator with id of %c\n", operator);
	}
	struct memorycontainer* rhs=createExpression(token, createIdentifierExpression(identifier), expressionContainer);
	if (operator == 6) {
		// Floor
		rhs=createUnaryGeneralMathsExpression(rhs, FLOOR_MATHS_OP);
	}
	return appendLetStatement(identifier, rhs);
}

/**
 * Appends and returns a let statement which sets and declares scalars
 */
struct memorycontainer* appendLetStatement(char * identifier, struct memorycontainer* expressionContainer) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) + expressionContainer->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, LET_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	appendMemory(memoryContainer, expressionContainer, position);
	return memoryContainer;
}

static struct memorycontainer* appendLetIfNoAliasStatement(char * identifier, struct memorycontainer* expressionContainer) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) + expressionContainer->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;

	position=appendStatement(memoryContainer, LETNOALIAS_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	appendMemory(memoryContainer, expressionContainer, position);
	return memoryContainer;
}

/**
 * Appends and returns a print statement
 */
struct memorycontainer* appendPrintStatement(struct memorycontainer* expressionContainer) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+expressionContainer->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, PRINT_TOKEN, position);
	appendMemory(memoryContainer, expressionContainer, position);
	return memoryContainer;
}

struct memorycontainer* appendReturnStatementWithExpression(struct memorycontainer* expressionContainer) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+expressionContainer->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position=0;
	position=appendStatement(memoryContainer, RETURN_EXP_TOKEN, position);
	appendMemory(memoryContainer, expressionContainer, position);
	return memoryContainer;
}

/**
 * Appends a return statement
 */
struct memorycontainer* appendReturnStatement(void) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, RETURN_TOKEN, 0);
	return memoryContainer;
}

/**
 * Appends and returns a stop statement
 */
struct memorycontainer* appendStopStatement() {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, STOP_TOKEN, 0);
	return memoryContainer;
}

/**
 * Appends and returns a synchronisation statement
 */
struct memorycontainer* appendSyncStatement() {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, SYNC_TOKEN, 0);
	return memoryContainer;
}

/**
 * Creates an expression from a string
 */
struct memorycontainer* createStringExpression(char * string) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=strlen(string)-1+sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned char token=STRING_TOKEN;
	unsigned int location=0;
	memcpy(&memoryContainer->data[location], &token, sizeof(unsigned char));
	location+=sizeof(unsigned char);

	char * mstring=(char*) string;
	mstring[strlen(mstring)-1]='\0';
	strcpy(&memoryContainer->data[location], &mstring[1]);
	return memoryContainer;
}

/**
 * Creates a random (integer) expression for random numbers
 */
struct memorycontainer* createRandomExpression() {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, RANDOM_TOKEN, 0);
	return memoryContainer;
}

struct memorycontainer* createLenExpression(struct memorycontainer* expression) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char) + expression->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	unsigned int position;
	position=appendStatement(memoryContainer, LEN_TOKEN, 0);
	appendMemory(memoryContainer, expression, position);
	return memoryContainer;
}

/**
 * Creates a coreid (integer) expression for getting the ID of a core
 */
struct memorycontainer* createCoreIdExpression() {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, COREID_TOKEN, 0);
	return memoryContainer;
}

/**
 * Creates a number of cores (integer) expression for getting the number of active cores
 */
struct memorycontainer* createNumCoresExpression() {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, NUMCORES_TOKEN, 0);
	return memoryContainer;
}

/**
 * Creates an expression containing an integer
 */
struct memorycontainer* createIntegerExpression(int number) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(int) + sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int location=appendStatement(memoryContainer, INTEGER_TOKEN, 0);
	memcpy(&memoryContainer->data[location], &number, sizeof(int));
	return memoryContainer;
}

struct memorycontainer* createBooleanExpression(int booleanVal) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(int) + sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int location=appendStatement(memoryContainer, BOOLEAN_TOKEN, 0);
	memcpy(&memoryContainer->data[location], &booleanVal, sizeof(int));
	return memoryContainer;
}

struct memorycontainer* createArrayExpression(struct stack_t* arrayVals) {
	int lenOfArray=getStackSize(arrayVals);
	struct memorycontainer* expressionContainer=NULL;
	int i;
	for (i=0;i<lenOfArray;i++) {
		if (expressionContainer == NULL) {
			expressionContainer=getExpressionAt(arrayVals, i);
		} else {
			expressionContainer=concatenateMemory(expressionContainer, getExpressionAt(arrayVals, i));
		}
	}

	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char) + sizeof(int);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int location=appendStatement(memoryContainer, ARRAY_TOKEN, 0);
	memcpy(&memoryContainer->data[location], &lenOfArray, sizeof(int));

	return concatenateMemory(memoryContainer, expressionContainer);
}

struct memorycontainer* createNoneExpression(void) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, NONE_TOKEN, 0);
	return memoryContainer;
}

/**
 * Creates an expression wrapping a real number
 */
struct memorycontainer* createRealExpression(float number) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(float) + sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int location=appendStatement(memoryContainer, REAL_TOKEN, 0);
	memcpy(&memoryContainer->data[location], &number, sizeof(float));
	return memoryContainer;
}

/**
 * Creates an expression wrapping an identifier
 */
struct memorycontainer* createIdentifierExpression(char * identifier) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int location=appendStatement(memoryContainer, IDENTIFIER_TOKEN, 0);
	appendVariable(memoryContainer, getVariableId(identifier, 0), location);
	return memoryContainer;
}

/**
 * Creates an expression wrapping an identifier array access
 */
struct memorycontainer* createIdentifierArrayAccessExpression(char* identifier, struct memorycontainer* accessExpression) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)+sizeof(unsigned short) + accessExpression->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int position=0;
	position=appendStatement(memoryContainer, ARRAYACCESS_TOKEN, position);
	position=appendVariable(memoryContainer, getVariableId(identifier, 1), position);
	appendMemory(memoryContainer, accessExpression, position);

	return memoryContainer;
}

struct memorycontainer* createIsHostExpression(void) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, ISHOST_TOKEN, 0);
	return memoryContainer;
}

struct memorycontainer* createIsDeviceExpression(void) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	appendStatement(memoryContainer, ISDEVICE_TOKEN, 0);
	return memoryContainer;
}

struct memorycontainer* createOrExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(OR_TOKEN, expression1, expression2);
}

struct memorycontainer* createAndExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(AND_TOKEN, expression1, expression2);
}

struct memorycontainer* createEqExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(EQ_TOKEN, expression1, expression2);
}

struct memorycontainer* createIsExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(IS_TOKEN, expression1, expression2);
}

struct memorycontainer* createNeqExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(NEQ_TOKEN, expression1, expression2);
}

struct memorycontainer* createGtExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(GT_TOKEN, expression1, expression2);
}


struct memorycontainer* createLtExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(LT_TOKEN, expression1, expression2);
}


struct memorycontainer* createGeqExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(GEQ_TOKEN, expression1, expression2);
}


struct memorycontainer* createLeqExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(LEQ_TOKEN, expression1, expression2);
}

struct memorycontainer* createAddExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(ADD_TOKEN, expression1, expression2);
}

struct memorycontainer* createPowExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(POW_TOKEN, expression1, expression2);
}

struct memorycontainer* createSubExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(SUB_TOKEN, expression1, expression2);
}

struct memorycontainer* createMulExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(MUL_TOKEN, expression1, expression2);
}

struct memorycontainer* createDivExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(DIV_TOKEN, expression1, expression2);
}

struct memorycontainer* createFloorDivExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createUnaryGeneralMathsExpression(createExpression(DIV_TOKEN, expression1, expression2), FLOOR_MATHS_OP);
}

struct memorycontainer* createModExpression(struct memorycontainer* expression1, struct memorycontainer* expression2) {
	return createExpression(MOD_TOKEN, expression1, expression2);
}

struct memorycontainer* createSqrtExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, SQRT_MATHS_OP);
}

struct memorycontainer* createSinExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, SIN_MATHS_OP);
}

struct memorycontainer* createCosExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, COS_MATHS_OP);
}

struct memorycontainer* createTanExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, TAN_MATHS_OP);
}

struct memorycontainer* createASinExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, ASIN_MATHS_OP);
}

struct memorycontainer* createACosExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, ACOS_MATHS_OP);
}

struct memorycontainer* createATanExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, ATAN_MATHS_OP);
}

struct memorycontainer* createSinHExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, SINH_MATHS_OP);
}

struct memorycontainer* createCosHExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, COSH_MATHS_OP);
}

struct memorycontainer* createTanHExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, TANH_MATHS_OP);
}

struct memorycontainer* createFloorExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, FLOOR_MATHS_OP);
}

struct memorycontainer* createCeilExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, CEIL_MATHS_OP);
}

struct memorycontainer* createLogExpression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, LOG_MATHS_OP);
}

struct memorycontainer* createLog10Expression(struct memorycontainer* expression) {
	return createUnaryGeneralMathsExpression(expression, LOG10_MATHS_OP);
}

/**
 * Creates unary maths expression which is a operator (such as sin, cos etc) and some value
 */
static struct memorycontainer* createUnaryGeneralMathsExpression(struct memorycontainer* expression, unsigned char maths_op) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=sizeof(unsigned char)*2 + expression->length;
	memoryContainer->data=(char*) malloc(memoryContainer->length);
	memoryContainer->lineDefns=NULL;

	int position=0;

	position=appendStatement(memoryContainer, MATHS_TOKEN, position);
	position=appendStatement(memoryContainer, maths_op, position);
	appendMemory(memoryContainer, expression, position);
	return memoryContainer;
}

/**
 * Enters a scope block, pushes a new scope store onto the stack
 */
void enterScope() {
	struct scope_info * newScope=(struct scope_info*) malloc(sizeof(struct scope_info));
	newScope->next=scope;
	newScope->variables=NULL;
	scope=newScope;
}

/**
 * Leaves a scope block, pops from the scope stack
 */
void leaveScope() {
	struct scope_info * oldScope=scope;
	scope=scope->next;
	struct variable_node * var=oldScope->variables, *nextVar;
	while (var!=NULL) {
		nextVar=var->next;
		free(var->name);
		free(var);
		var=nextVar;
	}
	free(oldScope);
}

/**
 * Creates an expression from two other expressions with some operator (such as add, equality test etc...)
 */
static struct memorycontainer* createExpression(unsigned char token, struct memorycontainer* expression1, struct memorycontainer* expression2) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=expression1->length + expression2->length + sizeof(unsigned char);
	memoryContainer->data=(char*) malloc(memoryContainer->length);

	unsigned int location=0;
	location=appendStatement(memoryContainer, token, location);
	memcpy(&memoryContainer->data[location], expression1->data, expression1->length);
	location+=expression1->length;
	memcpy(&memoryContainer->data[location], expression2->data, expression2->length);

	memoryContainer->lineDefns=expression1->lineDefns;
	struct lineDefinition * root=memoryContainer->lineDefns, *r2;
	while (root != NULL) {
		root->currentpoint+=sizeof(unsigned char);
		root=root->next;
	}
	root=expression2->lineDefns;
	while (root != NULL) {
		root->currentpoint+=expression1->length+sizeof(unsigned char);
		r2=root->next;
		root->next=memoryContainer->lineDefns;
		memoryContainer->lineDefns=root;
		root=r2;
	}

	// Free up the expression 1 and expression 2 memory
	free(expression1->data);
	free(expression1);
	free(expression2->data);
	free(expression2);
	return memoryContainer;
}

/**
 * Adds a variable to the symbol table if it is not already present
 */
void addVariableIfNeeded( char * name) {
	getVariableId(name, 1);
}

/**
 * Retrieves the ID of a variable from the symbol table, with a flag whether we are to allow adding the variable in
 * if it can not be found
 */
static unsigned short getVariableId(char * name, int allowAdd) {
	struct scope_info * scopeNode=scope;
	while (scopeNode != NULL) {
		unsigned short id=findVariable(scopeNode->variables, name);
		if (id >= 1) return id;
		scopeNode=scopeNode->next;
	}

	if (allowAdd) {
		return addVariable(name);
	} else {
		fprintf(stderr, "Can not find variable name %s at line %d, you must declare this before use\n", name, line_num);
		exit(0);
	}
}

/**
 * Finds a variable in a specific variable list or returns -1 for no variable found
 */
static unsigned short findVariable(struct variable_node * root,  char * name) {
	while (root != NULL) {
		if (areStringsEqualIgnoreCase(root->name, name)) return root->id;
		root=root->next;
	}
	return 0;
}

/**
 * Tests two strings for equality, ignoring the case - this is for case insensitive variable name matching
 */
static int areStringsEqualIgnoreCase(char * s1, char * s2) {
	size_t s1_len=strlen(s1), s2_len=strlen(s2), i;
	if (s1_len != s2_len) return 0;
	for (i=0;i<s1_len;i++) {
		if (tolower(s1[i]) != tolower(s2[i])) return 0;
	}
	return 1;
}

/**
 * Adds a variable to the variable list at the top of the scope stack, allocates the ID to be the next free one
 */
static unsigned short addVariable(char * name) {
	struct variable_node * newNode=(struct variable_node*) malloc(sizeof(struct variable_node));
	newNode->name=(char*) malloc(strlen(name) + 1);
	strcpy(newNode->name, name);
	newNode->id = current_var_id++;
	newNode->next=scope->variables;
	scope->variables=newNode;
	return newNode->id;
}
