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

// This is set at the end of parsing to be the entire byte code representation of the users BASIC program
struct memorycontainer* assembledMemory=NULL;
// This is the function list
struct functionListNode* functionListHead=NULL;

static unsigned short findLocationOfLineNumber(struct lineDefinition*, int);
static unsigned short findLocationOfFunctionName(struct lineDefinition*, char*);

/**
 * Compiles the memory by going through and resolving relative links (i.e. gotos) and adds a stop at the end
 */
void compileMemory(struct memorycontainer* memory) {
	struct memorycontainer* stopStatement=appendStopStatement();
	if (memory != NULL) {
		struct memorycontainer* compiledMem=concatenateMemory(memory, stopStatement);
		struct functionListNode * fnHead=functionListHead;
		while (fnHead != NULL) {
			compiledMem=concatenateMemory(compiledMem, fnHead->fn->contents);
			fnHead=fnHead->next;
		}
		struct lineDefinition * root=compiledMem->lineDefns, *r2;
		while (root != NULL) {
			if (root->type==1) {
				unsigned short lineLocation=findLocationOfLineNumber(compiledMem->lineDefns, root->linenumber);
				memcpy(&compiledMem->data[root->currentpoint], &lineLocation, sizeof(unsigned short));
			} else if (root->type==3){
				unsigned short lineLocation=findLocationOfFunctionName(compiledMem->lineDefns, root->name);
				memcpy(&compiledMem->data[root->currentpoint], &lineLocation, sizeof(unsigned short));
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
 * Adds a function to the function list which are all combined in the compile memory function
 */
void addFunction(struct functionDefinition* functionDefintion) {
	struct functionListNode * node=(struct functionListNode*) malloc(sizeof(struct functionListNode));
	node->fn=functionDefintion;
	node->next=functionListHead;
	functionListHead=node;
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
static unsigned short findLocationOfFunctionName(struct lineDefinition * root, char * functionName) {
	while (root != NULL) {
		if (root->type==2 && strcmp(root->name, functionName) == 0) return (unsigned short) root->currentpoint;
		root=root->next;
	}
	fprintf(stderr, "Can not find function name %s\n", functionName);
	exit(0);
}

/**
 * Sets a line number in the memory to be the current (highest level) point
 */
void setLineNumber(struct memorycontainer* memory, int lineNumber) {
	struct lineDefinition * defn = (struct lineDefinition*) malloc(sizeof(struct lineDefinition));
	defn->linenumber=lineNumber;
	defn->currentpoint=0;
	defn->type=0;
	defn->next=memory->lineDefns;
	memory->lineDefns=defn;
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
	memcpy(memoryContainer->data, m1->data, m1->length);
	memcpy(&memoryContainer->data[m1->length], m2->data, m2->length);
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

/**
 * Appends a statement to some memory and returns the new current location (for next entry)
 */
unsigned int appendStatement(struct memorycontainer* memory, unsigned short command, unsigned int position) {
	memcpy(&memory->data[position], &command, sizeof(short));
	position+=sizeof(short);
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
