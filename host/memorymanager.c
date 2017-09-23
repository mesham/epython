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

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "memorymanager.h"

// This is set at the end of parsing to be the entire byte code representation of the users Python program
struct memorycontainer* assembledMemory=NULL;
// This is the function list
struct functionListNode* functionListHead=NULL;
// Exportable view of the functions and their location in the byte code
struct exportableFunctionTableNode* exportableFunctionTable=NULL;
int numberExportableFunctionsInTable=0;

struct function_call_tree_node mainCodeCallTree;

static void determineUsedFunctions(void);
static void processUsedFunction(struct functionDefinition*);
static unsigned short findLocationOfLineNumber(struct lineDefinition*, int);
static unsigned short findLocationOfFunctionName(struct lineDefinition*, char*, int, int);
static struct functionDefinition* findFunctionDefinition(char*);
static int doesFunctionAlreadyExistInExportableTable(char*);

int getNumberOfSymbolEntriesNotUsed(void) {
    int ignoreSymbolEntries=0;
    struct functionListNode * fnHead=functionListHead;
    while (fnHead != NULL) {
        if (!fnHead->fn->called) ignoreSymbolEntries+=fnHead->fn->numberEntriesInSymbolTable;
        fnHead=fnHead->next;
    }
    return ignoreSymbolEntries;
}

/**
 * Compiles the memory by going through and resolving relative links (i.e. gotos) and adds a stop at the end
 */
void compileMemory(struct memorycontainer* memory) {
	int i;
	determineUsedFunctions();
	struct memorycontainer* stopStatement=appendStopStatement();
	if (memory != NULL) {
		struct memorycontainer* compiledMem=concatenateMemory(memory, stopStatement);
		struct functionListNode * fnHead=functionListHead;
		while (fnHead != NULL) {
			if (fnHead->fn->called) compiledMem=concatenateMemory(compiledMem, fnHead->fn->contents);
			if (fnHead->fn->functionCalls != NULL) {
				for (i=0;i<fnHead->fn->number_of_fn_calls;i++) {
					free(fnHead->fn->functionCalls[i]);
				}
				free(fnHead->fn->functionCalls);
			}
			fnHead=fnHead->next;
		}
		struct lineDefinition * root=compiledMem->lineDefns, *r2;
		while (root != NULL) {
			if (root->type==1) {
				unsigned short lineLocation=findLocationOfLineNumber(compiledMem->lineDefns, root->linenumber);
				memcpy(&compiledMem->data[root->currentpoint], &lineLocation, sizeof(unsigned short));
			} else if (root->type==3 || root->type==4 || root->type==2) {
				unsigned short lineLocation=findLocationOfFunctionName(compiledMem->lineDefns, root->name, root->linenumber, root->type==4);
				if (root->type==3 || root->type==4) {
					memcpy(&compiledMem->data[root->currentpoint], &lineLocation, sizeof(unsigned short));
				}
				if (!doesFunctionAlreadyExistInExportableTable(root->name)) {
					struct exportableFunctionTableNode* newExportableNode=(struct exportableFunctionTableNode*) malloc(sizeof(struct exportableFunctionTableNode));
					newExportableNode->functionLocation=lineLocation;
					newExportableNode->functionName=(char*) malloc(strlen(root->name)+1);
					strcpy(newExportableNode->functionName, root->name);
					newExportableNode->next=exportableFunctionTable;
					exportableFunctionTable=newExportableNode;
					numberExportableFunctionsInTable++;
				}
			}
			root=root->next;
		}
		// Clear up the memory used for these line definition nodes
		root=compiledMem->lineDefns;
		while (root != NULL) {
			r2=root->next;
			free(root);
			root=r2;
		}
		assembledMemory=compiledMem;
	} else {
		assembledMemory=stopStatement;
	}
}

/**
* Determines whether a specific function of a specific name already exists in the exportable global function table
*/
static int doesFunctionAlreadyExistInExportableTable(char* functionName) {
	struct exportableFunctionTableNode* root=exportableFunctionTable;
	while (root != NULL) {
		if (strcmp(root->functionName, functionName) == 0) return 1;
		root=root->next;
	}
	return 0;
}

/**
 * Determines the used (i.e. called by the code) functions, driven from the main function
 */
static void determineUsedFunctions(void) {
	int i;
	for (i=0;i<mainCodeCallTree.number_of_calls;i++) {
		struct functionDefinition* defn=findFunctionDefinition(mainCodeCallTree.calledFunctions[i]);
		if (defn != NULL) {
			if (!defn->called) processUsedFunction(defn);
		}
	}
}

/**
 * Marks the current function as used (i.e. called from code), if it has not already been processed will then
 * go and examine all the called functions from this
 */
static void processUsedFunction(struct functionDefinition* specificFunction) {
	specificFunction->called=1;
	if (specificFunction->functionCalls != NULL) {
		int i;
		for (i=0;i<specificFunction->number_of_fn_calls;i++) {
			struct functionDefinition* defn=findFunctionDefinition(specificFunction->functionCalls[i]);
			if (defn != NULL) {
				if (!defn->called) processUsedFunction(defn);
			}
		}
	}
}

/**
 * Adds a function to the function list which are all combined in the compile memory function
 */
void addFunction(struct functionDefinition* functionDefintion) {
	struct functionListNode * node=(struct functionListNode*) malloc(sizeof(struct functionListNode));
	node->fn=functionDefintion;
	node->next=functionListHead;
	functionListHead=node;
}

static struct functionDefinition* findFunctionDefinition(char * functionName) {
	struct functionListNode * node=functionListHead;
	while (node != NULL) {
		if (strcmp(node->fn->name, functionName) == 0) return node->fn;
		node=node->next;
	}
	return NULL;
}

int getNumberSymbolTableEntriesForRecursion(void) {
	int r=0;
	struct functionListNode * fnHead=functionListHead;
	while (fnHead != NULL) {
		if (fnHead->fn->recursive && fnHead->fn->called) r+=fnHead->fn->numberEntriesInSymbolTable;
		fnHead=fnHead->next;
	}
	return r;
}

/**
 * Given a line number will return the byte location of this in the memory
 */
static unsigned short findLocationOfLineNumber(struct lineDefinition * root, int lineNumber) {
	while (root != NULL) {
		if (root->type==0 && root->linenumber == lineNumber) return (unsigned short) root->currentpoint;
		root=root->next;
	}
	fprintf(stderr, "Can not find line %d in goto\n", lineNumber);
	exit(0);
}

/**
 * Finds the location of a function name and returns this or raises an error if the function is not found
 */
static unsigned short findLocationOfFunctionName(struct lineDefinition * root, char * functionName, int line_num_for_error, int isvarorfn) {
	while (root != NULL) {
		if (root->type==2 && strcmp(root->name, functionName) == 0) return (unsigned short) root->currentpoint;
		root=root->next;
	}
	if (isvarorfn) {
        fprintf(stderr, "Can not find variable or function '%s' in assignment at line number %d\n", functionName, line_num_for_error);
	} else {
        fprintf(stderr, "Can not find function '%s' in function call at line number %d\n", functionName, line_num_for_error);
	}
	exit(0);
}

/**
 * Concatenates two memory structures together and returns the result of this
 */
struct memorycontainer* concatenateMemory(struct memorycontainer* m1, struct memorycontainer* m2) {
	if (m1 == NULL) return m2;
	if (m2 == NULL) return m1;
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=m1->length + m2->length;
	memoryContainer->data=malloc(memoryContainer->length);
	memoryContainer->lineDefns=m1->lineDefns;
	if (m1->data != NULL && m1->length > 0) memcpy(memoryContainer->data, m1->data, m1->length);
	if (m2->data != NULL && m2->length > 0) memcpy(&memoryContainer->data[m1->length], m2->data, m2->length);
	struct lineDefinition * root=m2->lineDefns, *r2;
	while (root != NULL) {
		root->currentpoint+=m1->length;
		r2=root->next;
		root->next=memoryContainer->lineDefns;
		memoryContainer->lineDefns=root;
		root=r2;
	}
	// Free up the m1 and m2 memory
	free(m1->data);
	free(m1);
	free(m2->data);
	free(m2);
	return memoryContainer;
}

struct memorycontainer* cloneMemory(struct memorycontainer* m1) {
	struct memorycontainer* memoryContainer = (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	memoryContainer->length=m1->length;
	memoryContainer->data=malloc(memoryContainer->length);
	memoryContainer->lineDefns=m1->lineDefns;
	if (m1->data != NULL && m1->length > 0) memcpy(memoryContainer->data, m1->data, m1->length);
	return memoryContainer;
}

/**
 * Appends a statement to some memory and returns the new current location (for next entry)
 */
unsigned int appendStatement(struct memorycontainer* memory, unsigned char command, unsigned int position) {
	memcpy(&memory->data[position], &command, sizeof(unsigned char));
	position+=sizeof(unsigned char);
	return position;
}

/**
 * Appends a variable to some memory and returns the new current location (for next entry)
 */
unsigned int appendVariable(struct memorycontainer* memory, unsigned short variableid, unsigned int position) {
	memcpy(&memory->data[position], &variableid, sizeof(short));
	position+=sizeof(short);
	return position;
}

/**
 * Appends some memory to some other existing memory at a specific location
 */
unsigned int appendMemory(struct memorycontainer* memory, struct memorycontainer* statement, unsigned int position) {
	memcpy(&memory->data[position], statement->data, statement->length);

	struct lineDefinition * root=statement->lineDefns, *r2;
	while (root != NULL) {
		root->currentpoint+=position;
		r2=root->next;
		root->next=memory->lineDefns;
		memory->lineDefns=root;
		root=r2;
	}
	position+=statement->length;

	// Free up the statement memory
	free(statement->data);
	free(statement);
	return position;
}

/**
 * Gets the length of the assembled memory
 */
unsigned int getMemoryFilledSize() {
	if (assembledMemory == NULL) return 0;
	return assembledMemory->length;
}

/**
 * Sets the length of the assembled memory (when loading from bytecode file)
 */
void setMemoryFilledSize(unsigned int size) {
	if (assembledMemory == NULL) assembledMemory= (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	assembledMemory->length=size;
}

/**
 * Gets the bytecode in the assembled memory
 */
char * getAssembledCode() {
	if (assembledMemory == NULL) return NULL;
	return assembledMemory->data;
}

/**
 * Sets the code in the assembled memory (when loading from bytecode file)
 */
void setAssembledCode(char * a) {
	if (assembledMemory == NULL) assembledMemory= (struct memorycontainer*) malloc(sizeof(struct memorycontainer));
	assembledMemory->data=a;
}
