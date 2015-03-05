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
#include "main.h"
#include "basictokens.h"
#include "interpreter.h"
#include <e-lib.h>

static unsigned int localDataEntries=0, sharedDataEntries=0;
static char communication_data[6];

static int slength(char*);
static int copyStringToSharedMemoryAndSetLocation(char*,int);
static void waitOnAllRecvFromAllCores();
static struct value_defn doGetInputFromUser();
static int stringCmp(char*, char*);

/**
 * Displays a message to the user and waits for the host to have done this
 */
void displayToUser(struct value_defn value) {
	int length;
	sharedData->core_ctrl[myId].data[0]=value.type;
	if (value.type == STRING_TYPE) {
		char * v;
		cpy(&v, &value.data, sizeof(char*));
		length=copyStringToSharedMemoryAndSetLocation(v, 1);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[1], value.data, 4);
	}
	sharedData->core_ctrl[myId].core_command=1;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	if (value.type == STRING_TYPE) sharedDataEntries-=length; // Clears up the temporary memory used
}

/**
 * Checks two strings for equality
 */
int checkStringEquality(struct value_defn str1, struct value_defn str2) {
	char *c_str1, *c_str2;
	cpy(&c_str1, &str1.data, sizeof(char*));
	cpy(&c_str2, &str2.data, sizeof(char*));
	return stringCmp(c_str1, c_str2);
}

/**
 * Requests input from the host with a string to display
 */
struct value_defn getInputFromUserWithString(struct value_defn toDisplay) {
	if (toDisplay.type != STRING_TYPE) raiseError("Can only display strings with input statement");
	sharedData->core_ctrl[myId].data[0]=toDisplay.type;
	if (toDisplay.type == STRING_TYPE) {
		char * v;
		cpy(&v, &toDisplay.data, sizeof(char*));
		copyStringToSharedMemoryAndSetLocation(v, 1);
	}
	return doGetInputFromUser();
}

/**
 * Requests input from the host (no string to display)
 */
struct value_defn getInputFromUser() {
	sharedData->core_ctrl[myId].data[0]=0;
	return doGetInputFromUser();
}

/**
 * Does the copying required to get input from the host, waits until this is ready and then sets the
 * type and data correctly
 */
static struct value_defn doGetInputFromUser() {
	struct value_defn v;
	cpy(&sharedData->core_ctrl[myId].data[6], &sharedDataEntries, sizeof(unsigned int));
	sharedData->core_ctrl[myId].core_command=2;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	v.type=sharedData->core_ctrl[myId].data[0];
	if (v.type==STRING_TYPE) {
		char * strPtr=sharedData->core_ctrl[myId].shared_data_start + sharedDataEntries;
		cpy(&v.data, &strPtr, sizeof(char*));
		sharedDataEntries+=slength(strPtr)+1;
	} else {
		cpy(v.data, &sharedData->core_ctrl[myId].data[1], 4);
	}
	return v;
}

/**
 * Requests the host to perform some maths operation and blocks on this
 */
struct value_defn performMathsOp(unsigned short operation, struct value_defn value) {
	struct value_defn v;
	if (operation != RANDOM_MATHS_OP) {
		sharedData->core_ctrl[myId].data[0]=value.type;
		cpy(&sharedData->core_ctrl[myId].data[1], value.data, 4);
	}

	sharedData->core_ctrl[myId].core_command=1000+(unsigned int) operation;

	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	v.type=sharedData->core_ctrl[myId].data[0];
	cpy(v.data, &sharedData->core_ctrl[myId].data[1], 4);
	return v;
}

/**
 * String concatenation performed on the host (and any needed data transformations)
 */
struct value_defn performStringConcatenation(struct value_defn v1, struct value_defn v2) {
	struct value_defn v;
	v.type=STRING_TYPE;

	sharedData->core_ctrl[myId].data[0]=v1.type;
	if (v1.type == STRING_TYPE) {
		char * v;
		cpy(&v, &v1.data, sizeof(char*));
		copyStringToSharedMemoryAndSetLocation(v, 1);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[1], v1.data, 4);
	}
	sharedData->core_ctrl[myId].data[5]=v2.type;
	if (v2.type == STRING_TYPE) {
		char * v;
		cpy(&v, &v2.data, sizeof(char*));
		copyStringToSharedMemoryAndSetLocation(v, 6);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[6], v2.data, 4);
	}
	sharedData->core_ctrl[myId].data[10]=STRING_TYPE;
	cpy(&sharedData->core_ctrl[myId].data[11], &sharedDataEntries, sizeof(unsigned int));

	sharedData->core_ctrl[myId].core_command=4;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }

	v.type=STRING_TYPE;
	char * strPtr=sharedData->core_ctrl[myId].shared_data_start + sharedDataEntries;
	cpy(&v.data, &strPtr, sizeof(char*));
	sharedDataEntries+=slength(strPtr)+1;
	return v;
}

/**
 * Raises an error to the host and quits
 */
void raiseError(char * error) {
	stopInterpreter=1;
	sharedData->core_ctrl[myId].core_command=3;
	sharedData->core_ctrl[myId].data[0]=STRING_TYPE;

	copyStringToSharedMemoryAndSetLocation(error, 1);
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
}

/**
 * Initialises the symbol table in core memory
 */
struct symbol_node* initialiseSymbolTable(int numberSymbols) {
	return (void*) sharedData->core_ctrl[myId].symbol_table;
}

/**
 * Gets the address of an array either from core or shared data and updates the required location flag to point past this
 */
int* getArrayAddress(int size, char isShared) {
	if (sharedData->allInSharedMemory || isShared) {
		int * dS= (int*) sharedData->core_ctrl[myId].shared_data_start + sharedDataEntries;
		sharedDataEntries+=size*4;
		return dS;
	} else {
		int * dS= (int*) sharedData->core_ctrl[myId].data_start + localDataEntries;
		localDataEntries+=size*4;
		if ((int) (sharedData->core_ctrl[myId].data_start + localDataEntries) >= 0x8000) {
			raiseError("Out of core memory, allocate in shared memory instead");
		}
		return dS;
	}
}

/**
 * Sends data to some other core and blocks on this being received
 */
void sendData(struct value_defn to_send, int target) {
	if (!sharedData->core_ctrl[target].active) {
		raiseError("Attempting to send to inactive core");
	} else {
		communication_data[0]=to_send.type;
		cpy(&communication_data[1], to_send.data, 4);
		communication_data[5]=1;
		int row=target/e_group_config.group_cols;
		int col=target-(row*e_group_config.group_cols);
		e_write(&e_group_config, communication_data, row, col, sharedData->core_ctrl[myId].postbox_start + (myId*6), 6);
		while (communication_data[5] == 1) {
			e_read(&e_group_config, communication_data, row, col, sharedData->core_ctrl[myId].postbox_start + (myId*6), 6);
		}
	}
}

/**
 * Gets some data from another core (blocking operation)
 */
struct value_defn recvData(int source) {
	struct value_defn to_recv;
	if (!sharedData->core_ctrl[source].active) {
		raiseError("Attempting to receive from inactive core");
	} else {
		cpy(communication_data, sharedData->core_ctrl[myId].postbox_start + (source*6), 6);
		while (communication_data[5] != 1) {
			cpy(communication_data, sharedData->core_ctrl[myId].postbox_start + (source*6), 6);
		}
		communication_data[5]=0;
		cpy(sharedData->core_ctrl[myId].postbox_start + (source*6), communication_data, 6);
		to_recv.type=communication_data[0];
		cpy(to_recv.data, &communication_data[1], 4);
	}
	return to_recv;
}

/**
 * Synchronises all cores
 */
void syncCores(void) {
	char data;
	int i, row, col;
	for (i=0;i<16;i++) {
		if (i == myId || !sharedData->core_ctrl[i].active) continue;
		row=i/e_group_config.group_cols;
		col=i-(row*e_group_config.group_cols);
		data=1;
		e_write(&e_group_config, &data, row, col, sharedData->core_ctrl[i].postbox_start + (myId*6)+5, 1);
	}
	waitOnAllRecvFromAllCores();
	data=0;
	for (i=0;i<16;i++) {
		cpy(sharedData->core_ctrl[myId].postbox_start + (i*6)+5, &data, 1);
	}
}

/**
 * Broadcasts data, if this is the source then send it, all cores return the data (even the source)
 */
struct value_defn bcastData(struct value_defn to_send, int source) {
	if (myId==source) {
		int i;
		for (i=0;i<16;i++) {
			if (i == myId || !sharedData->core_ctrl[i].active) continue;
			sendData(to_send, i);
		}
		return to_send;
	} else {
		return recvData(source);
	}
}

/**
 * Reduction of data amongst the cores with some operator
 */
struct value_defn reduceData(struct value_defn to_send, unsigned short operator) {
	struct value_defn returnValue, retrieved;
	int i, intV, tempInt;
	float floatV, tempFloat;
	if (to_send.type==INT_TYPE) {
		cpy(&intV, to_send.data, sizeof(int));
	} else {
		cpy(&floatV, to_send.data, sizeof(int));
	}
	for (i=0;i<16;i++) {
		if (i == myId || !sharedData->core_ctrl[i].active) continue;
		if (i < myId) {
			sendData(to_send, i);
			retrieved=recvData(i);
		} else {
			retrieved=recvData(i);
			sendData(to_send, i);
		}
		if (to_send.type==INT_TYPE) {
			cpy(&tempInt, retrieved.data, sizeof(int));
			if (operator==0) intV+=tempInt;
			if (operator==1 && tempInt < intV) intV=tempInt;
			if (operator==2 && tempInt > intV) intV=tempInt;
			if (operator==3) intV*=tempInt;
		} else {
			cpy(&tempFloat, retrieved.data, sizeof(float));
			if (operator==0) floatV+=tempFloat;
			if (operator==1 && tempFloat < floatV) floatV=tempFloat;
			if (operator==2 && tempFloat > floatV) floatV=tempFloat;
			if (operator==3) floatV*=tempFloat;
		}
	}
	returnValue.type=to_send.type;
	if (to_send.type==INT_TYPE) {
		cpy(returnValue.data, &intV, sizeof(int));
	} else {
		cpy(returnValue.data, &floatV, sizeof(float));
	}
	return returnValue;
}

/**
 * Copies an amount of data from one core to another
 */
void cpy(void* to, void * from, unsigned int size) {
	unsigned int i;
	char *cto=(char*) to, *cfrom=(char*) from;
	for (i=0;i<size;i++) {
		cto[i]=cfrom[i];
	}
}

/**
 * Awaits the receiving of data from all cores
 */
static void waitOnAllRecvFromAllCores() {
	int i, completed=0;
	char data;
	while (!completed) {
		completed=1;
		for (i=0;i<16;i++) {
			if (i == myId || !sharedData->core_ctrl[i].active) continue;
			cpy(&data, sharedData->core_ctrl[myId].postbox_start + (i*6)+5, 1);
			if (!data) completed=0;
		}
	}
}

/**
 * Copies some string into shared memory and sets the location in the data core area
 */
static int copyStringToSharedMemoryAndSetLocation(char * string, int start) {
	int len=slength(string)+1;
	char* ptr=sharedData->core_ctrl[myId].shared_data_start + sharedDataEntries;
	cpy(ptr, string, len);
	cpy(&sharedData->core_ctrl[myId].data[start], &sharedDataEntries, sizeof(unsigned int));
	sharedDataEntries+=len;
	return len;
}

/**
 * Gets the length of a string
 */
static int slength(char * v) {
	int i=0;
	while (v[i]!='\0') i++;
	return i;
}

/**
 * Compares two strings together
 */
static int stringCmp(char * str1, char * str2) {
	int len1=slength(str1);
	int len2=slength(str2);
	if (len1 != len2) return 0;
	int i;
	for (i=0;i<len1;i++) {
		if (str1[i] != str2[i]) return 0;
	}
	return 1;
}
