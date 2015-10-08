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
#include <pthread.h>

#include "functions.h"
#include "basictokens.h"
#include "interpreter.h"
#include "host-functions.h"
#include "device-support.h"

volatile unsigned char **sharedComm, **syncValues;
volatile struct shared_basic * basicState;
int total_threads, sync_counter;
pthread_mutex_t barrier_mutex;

#ifdef HOST_STANDALONE
volatile unsigned int * pb;
#endif

static int getTypeOfInput(char*);
static struct value_defn performGetInputFromUser(char*, int);
static void sendDataToDeviceCore(struct value_defn, int, int, int);
static void sendDataToHostProcess(struct value_defn, int, int);
static struct value_defn recvDataFromDeviceCore(int, int, int);
static struct value_defn recvDataFromHostProcess(int, int);
static struct value_defn sendRecvDataWithDeviceCore(struct value_defn, int, int, int);
static struct value_defn sendRecvDataWithHostProcess(struct value_defn, int, int);
static void syncWithDevice();

/**
 * Initiates the host communication data, this is called once (i.e. not by each thread) and will
 * set up the state & memory for each thread to use
 */
void initHostCommunicationData(int total_number_threads, struct shared_basic * parallelBasicState) {
	int i, j;
	basicState=parallelBasicState;
	sharedComm=(volatile unsigned char**) malloc(sizeof(unsigned char*)*total_number_threads);
	syncValues=(volatile unsigned char**) malloc(sizeof(unsigned char*)*total_number_threads);
	for (i=0;i<total_number_threads;i++) {
		sharedComm[i]=(unsigned char*) malloc(total_number_threads*6);
		syncValues[i]=(unsigned char*) malloc(total_number_threads);
		for (j=0;j<total_number_threads;j++) {
			syncValues[i][j]=0;
			sharedComm[i][j*6+5]=0;
		}
	}
	pthread_mutex_init(&barrier_mutex, NULL);
	total_threads=total_number_threads;
	sync_counter=0;
}

/**
 * Called when running on the host, will display to the user
 */
void displayToUser(struct value_defn value, int threadId) {
	if (value.type == INT_TYPE) {
		printf("[host %d] %d\n", threadId, *((int*) value.data));
	} else if (value.type == REAL_TYPE) {
		printf("[host %d] %f\n", threadId, *((float*) value.data));
	} else if (value.type == BOOLEAN_TYPE) {
		printf("[host %d] %s\n", threadId, *((int*) value.data) > 0 ? "true" : "false");
	} else if (value.type == STRING_TYPE) {
		char *c;
		cpy(&c, &value.data, sizeof(char*));
		printf("[host %d] %s\n", threadId, c);
	}
}

/**
 * Called when running on the host, will check for string equality
 */
int checkStringEquality(struct value_defn str1, struct value_defn str2) {
	char *c_str1, *c_str2;
	cpy(&c_str1, &str1.data, sizeof(char*));
	cpy(&c_str2, &str2.data, sizeof(char*));
	return strcmp(c_str1, c_str2) == 0;
}

/**
 * Called when running on the host, will get input from user displaying a message string
 */
struct value_defn getInputFromUserWithString(struct value_defn toDisplay, int threadId) {
	if (toDisplay.type != STRING_TYPE) raiseError("Can only display strings with input statement");
	char *c;
	cpy(&c, &toDisplay.data, sizeof(char*));
	return performGetInputFromUser(c, threadId);
}

/**
 * Called when running on the host, will get input from the user
 */
struct value_defn getInputFromUser(int threadId) {
	return performGetInputFromUser(NULL, threadId);
}

/**
 * Actually gets the input from the user and puts this in the appropriate data area
 */
static struct value_defn performGetInputFromUser(char * toDisplay, int threadId) {
	struct value_defn v;
	v.dtype=SCALAR;
	char inputvalue[1000];
	if (toDisplay != NULL) {
		printf("[host %d] %s", threadId, toDisplay);
	} else {
		printf("host %d> ", threadId);
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
 * Called when running on the host, concatenates two strings (or a string with integer/real)
 */
struct value_defn performStringConcatenation(struct value_defn v1, struct value_defn v2) {
	struct value_defn result;
	result.type=STRING_TYPE;
	result.dtype=SCALAR;
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
			int int_v=*((int*) v2.data);
			sprintf(newString,"%s%d", str1, int_v);
		} else if (v2.type==BOOLEAN_TYPE) {
			int int_v=*((int*) v2.data);
			sprintf(newString,"%s%s", str1, int_v > 0?"true":"false");
		} else if (v2.type==REAL_TYPE) {
			float f=*((float*) v2.data);
			sprintf(newString,"%s%f", str1, f);
		}
		cpy(&result.data, &newString, sizeof(char*));
	} else {
		char *str2;
		cpy(&str2, &v2.data, sizeof(char*));
		int totalLen=strlen(str2)+21;
		char * newString=(char*) malloc(totalLen);
		if (v1.type==INT_TYPE) {
			int int_v=*((int*) v1.data);
			sprintf(newString,"%d%s", int_v, str2);
		} else if (v2.type==BOOLEAN_TYPE) {
			int int_v=*((int*) v1.data);
			sprintf(newString,"%s%s", int_v > 0?"true":"false", str2);
		} else if (v2.type==REAL_TYPE) {
			float f=*((float*) v1.data);
			sprintf(newString,"%f%s", f, str2);
		}
		cpy(&result.data, &newString, sizeof(char*));
	}
	return result;
}

/**
 * Called when running on the host, initialises the symbol table
 */
struct symbol_node* initialiseSymbolTable(int numberSymbols) {
	return (struct symbol_node*) malloc(sizeof(struct symbol_node) * numberSymbols);
}

/**
 * Called when running on the host, will get the memory address to store some array into
 */
int* getArrayAddress(int size, char shared) {
	return (int*) malloc(sizeof(int) * size);
}

struct value_defn sendRecvData(struct value_defn to_send, int target, int threadId, int hostCoresBasePid) {
	if (to_send.type == STRING_TYPE) raiseError("Can only send integers and reals between cores");
	if (target >= (int) basicState->num_procs) raiseError("Attempting to sendrecv with non-existent process");
	if (target < hostCoresBasePid) {
		return sendRecvDataWithDeviceCore(to_send, target, threadId, hostCoresBasePid);
	} else {
		return sendRecvDataWithHostProcess(to_send, target-hostCoresBasePid, threadId);
	}
}

static struct value_defn sendRecvDataWithDeviceCore(struct value_defn to_send, int target, int threadId, int hostCoresBasePid) {
	struct value_defn receivedData;
	int issuedProcess=threadId+hostCoresBasePid-1;
	while (issuedProcess != threadId+hostCoresBasePid) {
		while (basicState->core_ctrl[target].core_command != 7) { }
		memcpy(&issuedProcess, (void*) &basicState->core_ctrl[target].data, 4);
		if (issuedProcess == threadId+hostCoresBasePid) {
			basicState->core_ctrl[target].data[11]=to_send.type;
			memcpy((void*) &basicState->core_ctrl[target].data[12], to_send.data, 4);
			basicState->core_ctrl[target].core_command=0;
			basicState->core_ctrl[target].core_busy=++pb[target];
			receivedData.type=basicState->core_ctrl[target].data[5];
			memcpy(receivedData.data, (void*) &basicState->core_ctrl[target].data[6], 4);
		}
	}
	receivedData.dtype=SCALAR;
	return receivedData;
}

/**
 * Called when running on the host, the function for sending and receiving data between processes
 */
static struct value_defn sendRecvDataWithHostProcess(struct value_defn to_send, int target, int threadId) {
	struct value_defn receivedData;
	if (to_send.type == STRING_TYPE) raiseError("Can only send integers and reals between cores");
	volatile unsigned char communication_data[6];
	communication_data[0]=to_send.type;
	cpy(&communication_data[1], to_send.data, 4);
	communication_data[5]=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
	char * remoteMemory=(char*) sharedComm[target] + (threadId*6);
	cpy(remoteMemory, communication_data, 6);
	receivedData=recvDataFromHostProcess(target, threadId);
	communication_data[5]=syncValues[threadId][target]==0 ? 255 : syncValues[threadId][target]-1;
	while (communication_data[5] != syncValues[threadId][target]) {
		cpy(communication_data, remoteMemory, 6);
	}
	receivedData.dtype=SCALAR;
	return receivedData;
}

/**
 * Called when running on the host, the function for sending data between processes
 */
void sendData(struct value_defn to_send, int target, int threadId, int hostCoresBasePid) {
	if (to_send.type == STRING_TYPE) raiseError("Can only send integers and reals between cores");
	if (target >= (int) basicState->num_procs) raiseError("Attempting to send to non-existent process");
	if (target < hostCoresBasePid) {
		sendDataToDeviceCore(to_send, target, threadId, hostCoresBasePid);
	} else {
		sendDataToHostProcess(to_send, target-hostCoresBasePid, threadId);
	}
}

static void sendDataToDeviceCore(struct value_defn to_send, int target, int threadId, int hostCoresBasePid) {
	int issuedProcess=threadId+hostCoresBasePid-1;
	while (issuedProcess != threadId+hostCoresBasePid) {
		while (basicState->core_ctrl[target].core_command != 6) { }
		memcpy(&issuedProcess, (void*) &basicState->core_ctrl[target].data, 4);
		if (issuedProcess == threadId+hostCoresBasePid) {
			basicState->core_ctrl[target].data[5]=to_send.type;
			memcpy((void*) &basicState->core_ctrl[target].data[6], to_send.data, 4);
			basicState->core_ctrl[target].core_command=0;
			basicState->core_ctrl[target].core_busy=++pb[target];
		}
	}
}

static void sendDataToHostProcess(struct value_defn to_send, int target, int threadId) {
	volatile unsigned char communication_data[6];
	communication_data[0]=to_send.type;
	cpy(&communication_data[1], to_send.data, 4);
	syncValues[threadId][target]=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
	communication_data[5]=syncValues[threadId][target];
	char * remoteMemory=(char*) sharedComm[target] + (threadId*6);
	cpy(remoteMemory, communication_data, 6);
	syncValues[threadId][target]=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
	while (communication_data[5] != syncValues[threadId][target]) {
		cpy(communication_data, remoteMemory, 6);
	}
}

/**
 * Called when running on the host, the function for broadcasting data between processes
 */
struct value_defn bcastData(struct value_defn to_send, int source, int threadId, int totalProcesses, int hostCoresBasePid) {
	if (threadId==source-hostCoresBasePid) {
		int i;
		for (i=0;i<totalProcesses;i++) {
			if (i == threadId) continue;
			sendData(to_send, i, threadId, hostCoresBasePid);
		}
		return to_send;
	} else {
		return recvData(source, threadId, hostCoresBasePid);
	}
}

/**
 * Called when running on the host, the function for reducing data between processes
 */
struct value_defn reduceData(struct value_defn to_send, unsigned char operator, int threadId, int numberProcesses, int hostCoresBasePid) {
	struct value_defn returnValue, retrieved;
	int i, intV, tempInt;
	float floatV, tempFloat;
	if (to_send.type==INT_TYPE) {
		cpy(&intV, to_send.data, sizeof(int));
	} else {
		cpy(&floatV, to_send.data, sizeof(int));
	}
	syncCores(1, threadId);
	for (i=0;i<numberProcesses;i++) {
		if (i == threadId+hostCoresBasePid) continue;
		retrieved=sendRecvData(to_send, i, threadId, hostCoresBasePid);
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
	returnValue.dtype=SCALAR;
	if (to_send.type==INT_TYPE) {
		cpy(returnValue.data, &intV, sizeof(int));
	} else {
		cpy(returnValue.data, &floatV, sizeof(float));
	}
	return returnValue;
}

static void syncWithDevice() {
	int i;
	for (i=0;i<TOTAL_CORES;i++) {
		if (basicState->core_ctrl[i].active) {
			while (basicState->core_ctrl[i].core_command != 8) { }
			basicState->core_ctrl[i].core_command=0;
			basicState->core_ctrl[i].core_busy=++pb[i];
			return;
		}
	}
}

/**
 * Called when running on the host, the function for synchronising processes
 */
void syncCores(int global, int threadId) {
	if (global && threadId==0 && basicState->baseHostPid > 0) {
		// Some cores are active
		syncWithDevice();
	}
	pthread_mutex_lock(&barrier_mutex);
	if (sync_counter == total_threads) {
		sync_counter=1;
	} else {
		sync_counter++;
	}
	pthread_mutex_unlock(&barrier_mutex);
	while (sync_counter < total_threads) { }
}

/**
 * Called when running on the host, this raises an error
 */
void raiseError(char * error) {
	fprintf(stderr, "%s\n", error);
	exit(0);
}

/**
 * Called when running on the host, the function for receiving data between processes
 */
struct value_defn recvData(int source, int threadId, int hostCoresBasePid) {
	if (source >= (int) basicState->num_procs) raiseError("Attempting to receive from non-existent process");
	if (source < hostCoresBasePid) {
		return recvDataFromDeviceCore(source, threadId, hostCoresBasePid);
	} else {
		return recvDataFromHostProcess(source-hostCoresBasePid, threadId);
	}
}

static struct value_defn recvDataFromDeviceCore(int target, int threadId, int hostCoresBasePid) {
	struct value_defn to_recv;
	int issuedProcess=threadId+hostCoresBasePid-1;
	while (issuedProcess != threadId+hostCoresBasePid) {
		while (basicState->core_ctrl[target].core_command != 5) { }
		memcpy(&issuedProcess, (void*) &basicState->core_ctrl[target].data, 4);
		if (issuedProcess == threadId+hostCoresBasePid) {
			to_recv.type=basicState->core_ctrl[target].data[5];
			memcpy(to_recv.data, (void*) &basicState->core_ctrl[target].data[6], 4);
			basicState->core_ctrl[target].core_command=0;
			basicState->core_ctrl[target].core_busy=++pb[target];
		}
	}
	to_recv.dtype=SCALAR;
	return to_recv;
}

static struct value_defn recvDataFromHostProcess(int source, int threadId) {
	struct value_defn to_recv;
	volatile unsigned char communication_data[6];
	cpy(communication_data, sharedComm[threadId] + (source*6), 6);
	syncValues[threadId][source]=syncValues[threadId][source]==255 ? 0 : syncValues[threadId][source]+1;
	while (communication_data[5] != syncValues[threadId][source]) {
		cpy(communication_data, sharedComm[threadId] + (source*6), 6);
	}
	syncValues[threadId][source]=syncValues[threadId][source]==255 ? 0 : syncValues[threadId][source]+1;
	communication_data[5]=syncValues[threadId][source];
	cpy(sharedComm[threadId] + (source*6), communication_data, 6);
	to_recv.type=communication_data[0];
	cpy(to_recv.data, &communication_data[1], 4);
	to_recv.dtype=SCALAR;
	return to_recv;
}

/**
 * Called when running on the host, this performs some maths operation
 */
struct value_defn performMathsOp(unsigned short operation, struct value_defn value) {
	struct value_defn result;
	result.dtype=SCALAR;
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

/**
 * Copies data from one location to another
 */
void cpy(volatile void* to, volatile void * from, unsigned int size) {
	memcpy((void*) to, (void*) from, size);
}

/**
 * String length, returns the length of the string provided
 */
int slength(char * v) {
	return strlen(v);
}
