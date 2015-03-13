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
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "functions.h"
#include "basictokens.h"
#include "interpreter.h"

static int getTypeOfInput(char*);
static struct value_defn performGetInputFromUser(char*);

/**
 * Called when running in host standalone mode, will display to the user
 */
void displayToUser(struct value_defn value) {
	if (value.type == INT_TYPE) {
		printf("%d\n", *((int*) value.data));
	} else if (value.type == REAL_TYPE) {
		printf("%f\n", *((float*) value.data));
	} else if (value.type == STRING_TYPE) {
		char *c;
		cpy(&c, &value.data, sizeof(char*));
		printf("%s\n", c);
	}
}

/**
 * Called when running in host standalone mode, will check for string equality
 */
int checkStringEquality(struct value_defn str1, struct value_defn str2) {
	char *c_str1, *c_str2;
	cpy(&c_str1, &str1.data, sizeof(char*));
	cpy(&c_str2, &str2.data, sizeof(char*));
	return strcmp(c_str1, c_str2) == 0;
}

/**
 * Called when running in host standalone mode, will get input from user displaying a message string
 */
struct value_defn getInputFromUserWithString(struct value_defn toDisplay) {
	if (toDisplay.type != STRING_TYPE) raiseError("Can only display strings with input statement");
	char *c;
	cpy(&c, &toDisplay.data, sizeof(char*));
	return performGetInputFromUser(c);
}

/**
 * Called when running in host standalone mode, will get input from the user
 */
struct value_defn getInputFromUser() {
	return performGetInputFromUser(NULL);
}

/**
 * Actually gets the input from the user and puts this in the appropriate data area
 */
static struct value_defn performGetInputFromUser(char * toDisplay) {
	struct value_defn v;
	char inputvalue[1000];
	if (toDisplay != NULL) {
		printf("%s", toDisplay);
	} else {
		printf("> ");
	}
	scanf("%[^\n]", inputvalue);
	int inputType=getTypeOfInput(inputvalue);
	if (inputType==INT_TYPE) {
		v.type=INT_TYPE;
		*((int*) v.data)=atoi(inputvalue);
	} else if (inputType==REAL_TYPE) {
		v.type=REAL_TYPE;
		*((float*) v.data)=atof(inputvalue);
	} else {
		v.type=STRING_TYPE;
		char * newString=(char*) malloc(strlen(inputvalue)+1);
		strcpy(newString, inputvalue);
		cpy(&v.data, &newString, sizeof(char*));
	}
	return v;
}

/**
 * Gets the type of input (integer, real, string) that the user entered
 */
static int getTypeOfInput(char * input) {
	unsigned int i;
	char allNumbers=1, hasDecimal=0;
	for (i=0;i<strlen(input);i++) {
		if (!isdigit(input[i])) {
			if (input[i] == '.') {
				hasDecimal=1;
			} else {
				allNumbers=0;
			}
		}
	}
	if (allNumbers && !hasDecimal) return INT_TYPE;
	if (allNumbers && hasDecimal) return REAL_TYPE;
	return STRING_TYPE;
}

/**
 * Called when running in host standalone mode, contatenates two strings (or a string with integer/real)
 */
struct value_defn performStringConcatenation(struct value_defn v1, struct value_defn v2) {
	struct value_defn result;
	result.type=STRING_TYPE;
	if (v1.type==STRING_TYPE && v2.type==STRING_TYPE) {
		char *str1, *str2;
		cpy(&str1, &v1.data, sizeof(char*));
		cpy(&str2, &v2.data, sizeof(char*));
		int totalLen=strlen(str1)+strlen(str2)+1;
		char * newString=(char*) malloc(totalLen);
		sprintf(newString,"%s%s", str1, str2);
		cpy(&result.data, &newString, sizeof(char*));
	} else if (v1.type==STRING_TYPE) {
		char *str1;
		cpy(&str1, &v1.data, sizeof(char*));
		int totalLen=strlen(str1)+21;
		char * newString=(char*) malloc(totalLen);
		if (v2.type==INT_TYPE) {
			sprintf(newString,"%s%d", str1, *((int*) v2.data));
		} else if (v2.type==REAL_TYPE) {
			sprintf(newString,"%s%f", str1, *((float*) v2.data));
		}
		cpy(&result.data, &newString, sizeof(char*));
	} else {
		char *str2;
		cpy(&str2, &v2.data, sizeof(char*));
		int totalLen=strlen(str2)+21;
		char * newString=(char*) malloc(totalLen);
		if (v1.type==INT_TYPE) {
			sprintf(newString,"%d%s", *((int*) v1.data), str2);
		} else if (v2.type==REAL_TYPE) {
			sprintf(newString,"%f%s", *((float*) v1.data), str2);
		}
		cpy(&result.data, &newString, sizeof(char*));
	}
	return result;
}

/**
 * Called when running in host standalone mode, initialises the symbol table
 */
struct symbol_node* initialiseSymbolTable(int numberSymbols) {
	return (struct symbol_node*) malloc(sizeof(struct symbol_node) * numberSymbols);
}

/**
 * Called when running in host standalone mode, will get the memory address to store some array into
 */
int* getArrayAddress(int size, char shared) {
	return (int*) malloc(sizeof(int) * size);
}

/**
 * Called when running in host standalone mode, the function for sending and receiving data between cores,
 * this is empty (dummy) as in standalone mode it is on the host only.
 */
struct value_defn sendRecvData(struct value_defn to_send, int target) {
	struct value_defn dummy;
	return dummy;
}

/**
 * Called when running in host standalone mode, the function for sending data between cores, this is empty (dummy)
 * as in standalone mode it is on the host only (could be extended to use threading in future if so wished.)
 */
void sendData(struct value_defn to_send, int target) {

}

/**
 * Called when running in host standalone mode, the function for broadcasting data between cores, this is empty (dummy)
 * as in standalone mode it is on the host only (could be extended to use threading in future if so wished.)
 */
struct value_defn bcastData(struct value_defn to_send, int source) {
	struct value_defn dummy;
	return dummy;
}

/**
 * Called when running in host standalone mode, the function for reducing data between cores, this is empty (dummy)
 * as in standalone mode it is on the host only (could be extended to use threading in future if so wished.)
 */
struct value_defn reduceData(struct value_defn to_send, unsigned short operator) {
	struct value_defn dummy;
	return dummy;
}

/**
 * Called when running in host standalone mode, the function for synchronising cores, this is empty (dummy)
 * as in standalone mode it is on the host only (could be extended to use threading in future if so wished.)
 */
void syncCores(void) {

}

/**
 * Called when running in host standalone mode, this raises an error
 */
void raiseError(char * error) {
	fprintf(stderr, "%s\n", error);
	exit(0);
}

/**
 * Called when running in host standalone mode, the function for receiving data between cores, this is empty (dummy)
 * as in standalone mode it is on the host only (could be extended to use threading in future if so wished.)
 */
struct value_defn recvData(int source) {
	struct value_defn dummy;
	return dummy;
}

/**
 * Called when running in host standalone mode, this performs some maths operation
 */
struct value_defn performMathsOp(unsigned short operation, struct value_defn value) {
	struct value_defn result;
	if (operation== RANDOM_MATHS_OP) {
		result.type=INT_TYPE;
		int r=rand();
		cpy(result.data, &r, sizeof(int));
	} else {
		float fvalue, r;
		if (value.type==REAL_TYPE) {
			fvalue=*((float*) value.data);
		} else if (value.type==INT_TYPE) {
			fvalue=(float) *((int*) value.data);
		}
		result.type=REAL_TYPE;
		if (operation==SQRT_MATHS_OP) r=sqrtf(fvalue);
		if (operation==SIN_MATHS_OP) r=sinf(fvalue);
		if (operation==COS_MATHS_OP) r=cosf(fvalue);
		if (operation==TAN_MATHS_OP) r=tanf(fvalue);
		if (operation==ASIN_MATHS_OP) r=asinf(fvalue);
		if (operation==ACOS_MATHS_OP) r=acosf(fvalue);
		if (operation==ATAN_MATHS_OP) r=atanf(fvalue);
		if (operation==SINH_MATHS_OP) r=sinhf(fvalue);
		if (operation==COSH_MATHS_OP) r=coshf(fvalue);
		if (operation==TANH_MATHS_OP) r=tanhf(fvalue);
		if (operation==FLOOR_MATHS_OP) r=floorf(fvalue);
		if (operation==CEIL_MATHS_OP) r=ceilf(fvalue);
		if (operation==LOG_MATHS_OP) r=logf(fvalue);
		if (operation==LOG10_MATHS_OP) r=log10f(fvalue);
		cpy(result.data, &r, sizeof(float));
	}
	return result;
}

void cpy(volatile void* to, volatile void * from, unsigned int size) {
	unsigned int i;
	char *cto=(char*) to, *cfrom=(char*) from;
	for (i=0;i<size;i++) {
		cto[i]=cfrom[i];
	}
}

int slength(char * v) {
	return strlen(v);
}
