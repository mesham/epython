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
#include "misc.h"

struct hostHeapNodes {
    char* ptr;
    struct hostHeapNodes *next, *prev;
};

volatile struct hostHeapNodes ** rootHeapNode;
volatile unsigned char **sharedComm, **syncValues;
volatile struct shared_basic * basicState;
volatile int total_threads, hostCoresBasePid;
pthread_mutex_t barrier_mutex;
volatile int * flip_barrier_array, * flop_barrier_array;

#ifdef HOST_STANDALONE
volatile unsigned int * pb;
#endif

static struct value_defn getInputFromUser(int);
static struct value_defn getInputFromUserWithString(struct value_defn, int);
static void displayToUser(struct value_defn, int);
static void garbageCollect(int, struct symbol_node*, int);
static int getTypeOfInput(char*);
static struct value_defn performGetInputFromUser(char*, int);
static void sendDataToDeviceCore(struct value_defn, int, int, int);
static void sendDataToHostProcess(struct value_defn, int, char, int);
static struct value_defn recvDataFromDeviceCore(int, int, int);
static struct value_defn recvDataFromHostProcess(int, int);
static struct value_defn sendRecvDataWithDeviceCore(struct value_defn, int, int, int);
static struct value_defn sendRecvDataWithHostProcess(struct value_defn, int, int);
static void syncWithDevice();
static char removehostHeapNode(char*, int);
static struct hostHeapNodes * findHeapNode(char*, int);
static char isMemoryAddressFound(char*, int, struct symbol_node*);
static struct value_defn performMathsOp(int, struct value_defn);
static struct value_defn test_or_wait_for_sent_message(int, char, int);

/**
 * Initiates the host communication data, this is called once (i.e. not by each thread) and will
 * set up the state & memory for each thread to use
 */
void initHostCommunicationData(int total_number_threads, struct shared_basic * parallelBasicState, int ahostCoresBasePid) {
	int i, j;
	basicState=parallelBasicState;
	rootHeapNode=(volatile struct hostHeapNodes **) malloc(sizeof(struct hostHeapNodes*)*total_number_threads);
	sharedComm=(volatile unsigned char**) malloc(sizeof(unsigned char*)*total_number_threads);
	syncValues=(volatile unsigned char**) malloc(sizeof(unsigned char*)*total_number_threads);
	for (i=0;i<total_number_threads;i++) {
        rootHeapNode[i]=NULL;
		sharedComm[i]=(unsigned char*) malloc(total_number_threads*6);
		syncValues[i]=(unsigned char*) malloc(total_number_threads);
		for (j=0;j<total_number_threads;j++) {
			syncValues[i][j]=0;
			sharedComm[i][j*6+5]=0;
		}
	}
	pthread_mutex_init(&barrier_mutex, NULL);
	flip_barrier_array=(int*) malloc(sizeof(int) * total_number_threads);
	flop_barrier_array=(int*) malloc(sizeof(int) * total_number_threads);
	for (i=0; i<total_threads; i++) {
        flip_barrier_array[i] = flop_barrier_array[i] =0;
    }
	total_threads=total_number_threads;
	hostCoresBasePid=ahostCoresBasePid;
}

void callNativeFunction(struct value_defn * value, unsigned char fnIdentifier, int numArgs, struct value_defn* parameters,
                                       int numActiveCores, int localCoreId, int currentSymbolEntries, struct symbol_node* symbolTable, int threadId) {
    if (fnIdentifier==NATIVE_FN_RTL_ISHOST || fnIdentifier==NATIVE_FN_RTL_ISDEVICE) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        value->type=BOOLEAN_TYPE;
        value->dtype=SCALAR;
        int v=fnIdentifier==NATIVE_FN_RTL_ISHOST ? 1 : 0;
        cpy(value->data, &v, sizeof(int));
    } else if (fnIdentifier==NATIVE_FN_RTL_ISDEVICE) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        value->type=BOOLEAN_TYPE;
        value->dtype=SCALAR;
        int v=0;
        cpy(value->data, &v, sizeof(int));
    } else if (fnIdentifier==NATIVE_FN_RTL_PRINT) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        displayToUser(parameters[0], threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_NUMDIMS) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        int intNDims=0;
        if (parameters[0].dtype == ARRAY) {
            char * ptr;
            cpy(&ptr, parameters[0].data, sizeof(char*));
            unsigned char num_dims;
            cpy(&num_dims, ptr, sizeof(unsigned char));
            num_dims=num_dims & 0xF;
            intNDims=(int) num_dims;
        }
        value->type=INT_TYPE;
        value->dtype=SCALAR;
		cpy(value->data, &intNDims, sizeof(int));
    } else if (fnIdentifier==NATIVE_FN_RTL_DSIZE) {
        if (numArgs != 2) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        int dimSize=0;
        if (parameters[0].dtype == ARRAY) {
            int lookupIndex=getInt(parameters[1].data);
            char * ptr;
            cpy(&ptr, parameters[0].data, sizeof(char*));
            unsigned char num_dims;
            cpy(&num_dims, ptr, sizeof(unsigned char));
            num_dims=num_dims & 0xF;
            if (lookupIndex < num_dims) {
                cpy(&dimSize, &ptr[(lookupIndex * sizeof(int)) + sizeof(unsigned char)], sizeof(int));
            }
        }
        value->type=INT_TYPE;
        value->dtype=SCALAR;
		cpy(value->data, &dimSize, sizeof(int));
    } else if (fnIdentifier==NATIVE_FN_RTL_INPUT) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=getInputFromUser(threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_INPUTPRINT) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=getInputFromUserWithString(parameters[0], threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_SYNC) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        syncCores(1, threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_GC) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        garbageCollect(currentSymbolEntries, symbolTable, threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_FREE) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        char * ptr;
        cpy(&ptr, parameters[0].data, sizeof(char*));
        freeMemoryInHeap(ptr, threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_SEND || fnIdentifier==NATIVE_FN_RTL_SEND_NB) {
        if (numArgs != 2) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        sendData(parameters[0], getInt(parameters[1].data), fnIdentifier==NATIVE_FN_RTL_SEND ? 1 : 0, threadId, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_RECV) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=recvData(getInt(parameters[0].data), threadId, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_PROBE_FOR_MESSAGE) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=probeForMessage(getInt(parameters[0].data), threadId, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_TEST_FOR_SEND || fnIdentifier==NATIVE_FN_RTL_WAIT_FOR_SEND) {
        if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=test_or_wait_for_sent_message(getInt(parameters[0].data), fnIdentifier==NATIVE_FN_RTL_WAIT_FOR_SEND ? 1 : 0, threadId);
    } else if (fnIdentifier==NATIVE_FN_RTL_SENDRECV) {
        if (numArgs != 2) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=sendRecvData(parameters[0], getInt(parameters[1].data), threadId, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_BCAST) {
        if (numArgs != 2) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=bcastData(parameters[0], getInt(parameters[1].data), threadId, numActiveCores, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_NUMCORES || fnIdentifier==NATIVE_FN_RTL_COREID) {
        if (numArgs != 0) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        value->type=INT_TYPE;
		value->dtype=SCALAR;
        if (fnIdentifier==NATIVE_FN_RTL_NUMCORES) cpy(value->data, &numActiveCores, sizeof(int));
        if (fnIdentifier==NATIVE_FN_RTL_COREID) cpy(value->data, &localCoreId, sizeof(int));
    } else if (fnIdentifier==NATIVE_FN_RTL_REDUCE) {
        if (numArgs != 2) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        *value=reduceData(parameters[0], getInt(parameters[1].data), threadId, numActiveCores, hostCoresBasePid);
    } else if (fnIdentifier==NATIVE_FN_RTL_ALLOCARRAY || fnIdentifier==NATIVE_FN_RTL_ALLOCSHAREDARRAY) {
        int totalDataSize=1, i;
        for (i=0;i<numArgs;i++) {
            totalDataSize*=getInt(parameters[i].data);
        }
        char * address=getHeapMemory(sizeof(unsigned char) + (sizeof(int)*(totalDataSize+numArgs)),
                                     fnIdentifier==NATIVE_FN_RTL_ALLOCSHAREDARRAY, threadId);
        value->type=INT_TYPE;
        value->dtype=ARRAY;
        cpy(value->data, &address, sizeof(char*));

        unsigned char num_dims=numArgs & 0xF;
        cpy(address, &num_dims, sizeof(unsigned char));
        address+=sizeof(unsigned char);
        for (i=0;i<numArgs;i++) {
            cpy(address, parameters[i].data, sizeof(int));
            address+=sizeof(int);
        }
    } else if (fnIdentifier==NATIVE_FN_RTL_MATH) {
        if (numArgs == 2) {
            *value=performMathsOp(getInt(parameters[0].data), parameters[1]);
        } else if (numArgs == 1) {
            *value=performMathsOp(getInt(parameters[0].data), *value);
        } else {
            raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
        }
    } else if (fnIdentifier==NATIVE_FN_RTL_GLOBAL_REFERENCE) {
		if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
		value->type=parameters[0].type;
		value->dtype=parameters[0].dtype;
		cpy(value->data, parameters[0].data, sizeof(char*));
    } else if (fnIdentifier==NATIVE_FN_RTL_DEREFERENCE) {
		if (numArgs != 1) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
		value->type=parameters[0].type & 0x1F;
		value->dtype=(parameters[0].type >> 5 & 0x3) + 2;
		cpy(value->data, parameters[0].data, sizeof(char*));
    } else {
        raiseError(ERR_UNKNOWN_NATIVE_COMMAND);
    }
};

/**
 * Called when running on the host, will display to the user
 */
static void displayToUser(struct value_defn value, int threadId) {
	if (((value.type >> 7) & 1) == 1) {
		char* y;
        memcpy(&y, value.data, sizeof(char*));
        char t=value.type & 0x1F;
        char dt=value.type >> 5 & 0x3;
		printf("[host %d] %p points to %s %s\n", threadId, y,
				t==0 ? "integer" : t==1 ? "floating point" : t==2 ? "boolean" : t==3 ? "none" : t==4 ? "function" : "unknown", dt==0 ? "scalar" : "array");
	} else if (value.type == INT_TYPE) {
        int v;
        cpy(&v, value.data, sizeof(int));
		printf("[host %d] %d\n", threadId, v);
	} else if (value.type == REAL_TYPE) {
	    float f;
	    cpy(&f, value.data, sizeof(float));
		printf("[host %d] %f\n", threadId, f);
	} else if (value.type == BOOLEAN_TYPE) {
	    int v;
        cpy(&v, value.data, sizeof(int));
		printf("[host %d] %s\n", threadId, v > 0 ? "true" : "false");
	} else if (value.type == NONE_TYPE) {
		printf("[host %d] NONE\n", threadId);
	} else if (value.type == STRING_TYPE) {
		char *c;
		cpy(&c, &value.data, sizeof(char*));
		printf("[host %d] %s\n", threadId, c);
	}
	fflush(stdout);
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
static struct value_defn getInputFromUserWithString(struct value_defn toDisplay, int threadId) {
	if (toDisplay.type != STRING_TYPE) raiseError(ERR_ONLY_DISPLAY_STR_WITH_INPUT);
	char *c;
	cpy(&c, &toDisplay.data, sizeof(char*));
	return performGetInputFromUser(c, threadId);
}

/**
 * Called when running on the host, will get input from the user
 */
static struct value_defn getInputFromUser(int threadId) {
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
	errorCheck(scanf("%[^\n]", inputvalue), "Getting user input");
	int inputType=getTypeOfInput(inputvalue);
	if (inputType==INT_TYPE) {
		v.type=INT_TYPE;
		int ival=atoi(inputvalue);
		cpy(v.data, &ival, sizeof(int));
	} else if (inputType==REAL_TYPE) {
		v.type=REAL_TYPE;
		float fval=atof(inputvalue);
		cpy(v.data, &fval, sizeof(float));
	} else {
		v.type=STRING_TYPE;
		char * newString=getHeapMemory(strlen(inputvalue)+1, 0, threadId);
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
struct value_defn performStringConcatenation(struct value_defn v1, struct value_defn v2, int threadId) {
	struct value_defn result;
	result.type=STRING_TYPE;
	result.dtype=SCALAR;
	if (v1.type==STRING_TYPE && v2.type==STRING_TYPE) {
		char *str1, *str2;
		cpy(&str1, &v1.data, sizeof(char*));
		cpy(&str2, &v2.data, sizeof(char*));
		int totalLen=strlen(str1)+strlen(str2)+1;
		char * newString=getHeapMemory(totalLen, 0, threadId);
		sprintf(newString,"%s%s", str1, str2);
		cpy(&result.data, &newString, sizeof(char*));
	} else if (v1.type==STRING_TYPE) {
		char *str1;
		cpy(&str1, &v1.data, sizeof(char*));
		int totalLen=strlen(str1)+21;
		char * newString=getHeapMemory(totalLen, 0, threadId);
		if (((v2.type >> 7) & 1) == 1) {
			char* v;
			cpy(&v, v2.data, sizeof(char*));
			sprintf(newString,"%s%p", str1, v);
		} else if (v2.type==INT_TYPE) {
			int int_v;
			cpy(&int_v, v2.data, sizeof(int));
			sprintf(newString,"%s%d", str1, int_v);
		} else if (v2.type==BOOLEAN_TYPE) {
			int int_v;
			cpy(&int_v, v2.data, sizeof(int));
			sprintf(newString,"%s%s", str1, int_v > 0?"true":"false");
		} else if (v2.type==NONE_TYPE) {
			sprintf(newString,"%sNONE", str1);
		} else if (v2.type==REAL_TYPE) {
			float f;
			cpy(&f, v2.data, sizeof(float));
			sprintf(newString,"%s%f", str1, f);
		}
		cpy(&result.data, &newString, sizeof(char*));
	} else {
		char *str2;
		cpy(&str2, &v2.data, sizeof(char*));
		int totalLen=strlen(str2)+21;
		char * newString=getHeapMemory(totalLen, 0, threadId);
		if (((v1.type >> 7) & 1) == 1) {
			char* v;
			cpy(&v, v2.data, sizeof(char*));
			sprintf(newString,"%p%s", v, str2);
		} else if (v1.type==INT_TYPE) {
			int int_v;
			cpy(&int_v, v1.data, sizeof(int));
			sprintf(newString,"%d%s", int_v, str2);
		} else if (v1.type==BOOLEAN_TYPE) {
			int int_v;
			cpy(&int_v, v1.data, sizeof(int));
			sprintf(newString,"%s%s", int_v > 0?"true":"false", str2);
		} else if (v1.type==NONE_TYPE) {
			sprintf(newString,"NONE%s", str2);
		} else if (v1.type==REAL_TYPE) {
			float f;
			cpy(&f, v1.data, sizeof(float));
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

static void garbageCollect(int currentSymbolEntries, struct symbol_node* symbolTable, int threadId) {
    volatile struct hostHeapNodes * head=rootHeapNode[threadId];
    char * ptr;
    while (head != NULL) {
        ptr=head->ptr;
        head=head->next;
        if (!isMemoryAddressFound(ptr, currentSymbolEntries, symbolTable)) {
            removehostHeapNode(ptr, threadId);
        }
    }
}

static char isMemoryAddressFound(char * address, int currentSymbolEntries, struct symbol_node* symbolTable) {
    int i;
    char * ptr;
    for (i=0;i<=currentSymbolEntries;i++) {
        if (symbolTable[i].state==ALLOCATED && (symbolTable[i].value.dtype==ARRAY || symbolTable[i].value.type==STRING_TYPE)) {
            cpy(&ptr, symbolTable[i].value.data, sizeof(char*));
            if (address == ptr) return 1;
        }
    }
    return 0;
}

/**
 * Called when running on the host, will get the memory address to store some array into
 */
char* getHeapMemory(int size, char shared, int threadId) {
    char * ptr=(char*) malloc(size);
    struct hostHeapNodes * newNode=(struct hostHeapNodes*) malloc(sizeof(struct hostHeapNodes));
    newNode->ptr=ptr;
    newNode->next=(struct hostHeapNodes *) rootHeapNode[threadId];
    newNode->prev=NULL;
    rootHeapNode[threadId]=newNode;
	return ptr;
}

static char removehostHeapNode(char* ptr, int threadId) {
    struct hostHeapNodes * toDelete=findHeapNode(ptr, threadId);
    if (toDelete != NULL) {
        if (toDelete->next != NULL) toDelete->next->prev=toDelete->prev;
        if (toDelete->prev != NULL) toDelete->prev->next=toDelete->next;
        if (rootHeapNode[threadId] == toDelete) rootHeapNode[threadId]=toDelete->next;
        free(toDelete);
        return 1;
    }
    return 0;
}

static struct hostHeapNodes * findHeapNode(char* ptr, int threadId) {
    volatile struct hostHeapNodes * head=rootHeapNode[threadId];
    while (head != NULL) {
        if (head->ptr == ptr) return (struct hostHeapNodes *) head;
        head=head->next;
    }
    return NULL;
}

char* getStackMemory(int size, char shared) {
	return (char*) malloc(size);
}

void freeMemoryInHeap(void* addr, int threadId) {
    char * address=(char*) addr;
    if (removehostHeapNode(address, threadId)) {
        free(address);
    } else {
        raiseError(ERR_FREE_ON_NON_HEAP);
    }
}

void clearFreedStackFrames(char* targetPointer) {
	// No operation here (allow stack to leak on host)
}

__attribute__((optimize("O0")))
struct value_defn sendRecvData(struct value_defn to_send, int target, int threadId, int hostCoresBasePid) {
	if (to_send.type == STRING_TYPE) raiseError(ERR_ONLY_SEND_INT_AND_REAL);
	if (target >= (int) basicState->num_procs) raiseError(ERR_SENDRECV_WITH_UNKNOWN_CORE);
	if (target < hostCoresBasePid) {
		return sendRecvDataWithDeviceCore(to_send, target, threadId, hostCoresBasePid);
	} else {
		return sendRecvDataWithHostProcess(to_send, target-hostCoresBasePid, threadId);
	}
}

__attribute__((optimize("O0")))
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
 __attribute__((optimize("O0")))
static struct value_defn sendRecvDataWithHostProcess(struct value_defn to_send, int target, int threadId) {
	struct value_defn receivedData;
	if (to_send.type == STRING_TYPE) raiseError(ERR_ONLY_SEND_INT_AND_REAL);
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
 __attribute__((optimize("O0")))
void sendData(struct value_defn to_send, int target, char blocking, int threadId, int hostCoresBasePid) {
	if (to_send.type == STRING_TYPE) raiseError(ERR_ONLY_SEND_INT_AND_REAL);
	if (target >= (int) basicState->num_procs) raiseError(ERR_SEND_TO_UNKNOWN_CORE);
	if (target < hostCoresBasePid) {
        if (!blocking) raiseError(ERR_NBSEND_NOT_SUPPORTED);
		sendDataToDeviceCore(to_send, target, threadId, hostCoresBasePid);
	} else {
		sendDataToHostProcess(to_send, target-hostCoresBasePid, blocking, threadId);
	}
}

__attribute__((optimize("O0")))
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

__attribute__((optimize("O0")))
static void sendDataToHostProcess(struct value_defn to_send, int target, char blocking, int threadId) {
	volatile unsigned char communication_data[6];
	communication_data[0]=to_send.type;
	cpy(&communication_data[1], to_send.data, 4);
	syncValues[threadId][target]=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
	communication_data[5]=syncValues[threadId][target];
	char * remoteMemory=(char*) sharedComm[target] + (threadId*6);
	cpy(remoteMemory, communication_data, 6);
	syncValues[threadId][target]=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
	if (blocking) {
        while (communication_data[5] != syncValues[threadId][target]) {
            cpy(communication_data, remoteMemory, 6);
        }
	}
}

__attribute__((optimize("O0")))
static struct value_defn test_or_wait_for_sent_message(int target, char is_wait, int threadId) {
    struct value_defn toreturn;
    toreturn.type=BOOLEAN_TYPE;
    toreturn.dtype=SCALAR;
    if (target >= (int) basicState->num_procs) raiseError(ERR_SEND_TO_UNKNOWN_CORE);
	if (target < hostCoresBasePid) {
        raiseError(ERR_PROBE_NOT_SUPPORTED);
	} else {
	    int boolVal;
        volatile unsigned char communication_data[6];
        char * remoteMemory=(char*) sharedComm[target] + (threadId*6);
        cpy(communication_data, remoteMemory, 6);
        if (is_wait) {
            while (communication_data[5] != syncValues[threadId][target]) {
                cpy(communication_data, remoteMemory, 6);
            }
            boolVal=1;
        } else {
            boolVal=communication_data[5] == syncValues[threadId][target];
        }
        cpy(toreturn.data, &boolVal, sizeof(int));
	}
	return toreturn;
}

/**
 * Called when running on the host, the function for broadcasting data between processes
 */
 __attribute__((optimize("O0")))
struct value_defn bcastData(struct value_defn to_send, int source, int threadId, int totalProcesses, int hostCoresBasePid) {
	if (threadId==source-hostCoresBasePid) {
		int i;
		for (i=0;i<totalProcesses;i++) {
			if (i == threadId) continue;
			sendData(to_send, i, 1, threadId, hostCoresBasePid);
		}
		return to_send;
	} else {
		return recvData(source, threadId, hostCoresBasePid);
	}
}

/**
 * Called when running on the host, the function for reducing data between processes
 */
 __attribute__((optimize("O0")))
struct value_defn reduceData(struct value_defn to_send, int rop, int threadId, int numberProcesses, int hostCoresBasePid) {
	struct value_defn returnValue, retrieved;
	int i, intV=0, tempInt=0;
	float floatV=0, tempFloat=0;
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
			if (rop==0) intV+=tempInt;
			if (rop==1 && tempInt < intV) intV=tempInt;
			if (rop==2 && tempInt > intV) intV=tempInt;
			if (rop==3) intV*=tempInt;
		} else {
			cpy(&tempFloat, retrieved.data, sizeof(float));
			if (rop==0) floatV+=tempFloat;
			if (rop==1 && tempFloat < floatV) floatV=tempFloat;
			if (rop==2 && tempFloat > floatV) floatV=tempFloat;
			if (rop==3) floatV*=tempFloat;
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

__attribute__((optimize("O0")))
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
 __attribute__((optimize("O0")))
void syncCores(int global, int threadId) {
	if (global && threadId==0 && basicState->baseHostPid > 0) {
		// Some cores are active
		syncWithDevice();
	}
	if (threadId == basicState->baseHostPid) {
		int i;
		pthread_mutex_lock(&barrier_mutex);
		flip_barrier_array[threadId] = 1;
		pthread_mutex_unlock(&barrier_mutex);
		// poll on all slots
		for (i=0; i<total_threads; i++) {
			while (flip_barrier_array[i] != 1) {};
		}
		pthread_mutex_lock(&barrier_mutex);
		for (i=0; i<total_threads; i++) {
			flip_barrier_array[i] = 0;
		}
		// set remote slots
		for (i=0; i<total_threads; i++) {
			flop_barrier_array[i] = 1;
		}
		pthread_mutex_unlock(&barrier_mutex);
	} else {
	    pthread_mutex_lock(&barrier_mutex);
		flip_barrier_array[threadId] = 1;
		pthread_mutex_unlock(&barrier_mutex);
		while (flop_barrier_array[threadId] != 1) {};
		pthread_mutex_lock(&barrier_mutex);
		flop_barrier_array[threadId] = 0;
		pthread_mutex_unlock(&barrier_mutex);
	}
}

/**
 * Called when running on the host, this raises an error
 */
void raiseError(unsigned char errorCode) {
    char* errorMessage=translateErrorCodeToMessage(errorCode);
	if (errorMessage != NULL) {
        fprintf(stderr, "Error from host virtual core: %s\n", errorMessage);
        free(errorMessage);
	}
	exit(0);
}

 __attribute__((optimize("O0")))
 struct value_defn probeForMessage(int target, int threadId, int hostCoresBasePid) {
    struct value_defn toreturn;
    toreturn.type=BOOLEAN_TYPE;
    toreturn.dtype=SCALAR;
    if (target >= (int) basicState->num_procs) raiseError(ERR_RECV_FROM_UNKNOWN_CORE);
	if (target < hostCoresBasePid) {
        int boolVal=basicState->core_ctrl[target].core_command == 5;
		cpy(toreturn.data, &boolVal, sizeof(int));
	} else {
	    volatile unsigned char communication_data[6];
        cpy(communication_data, sharedComm[threadId] + (target*6), 6);
        unsigned char sV=syncValues[threadId][target]==255 ? 0 : syncValues[threadId][target]+1;
        int boolVal=communication_data[5] == sV;
		cpy(toreturn.data, &boolVal, sizeof(int));
	}
	return toreturn;
 }

/**
 * Called when running on the host, the function for receiving data between processes
 */
 __attribute__((optimize("O0")))
struct value_defn recvData(int source, int threadId, int hostCoresBasePid) {
	if (source >= (int) basicState->num_procs) raiseError(ERR_RECV_FROM_UNKNOWN_CORE);
	if (source < hostCoresBasePid) {
		return recvDataFromDeviceCore(source, threadId, hostCoresBasePid);
	} else {
		return recvDataFromHostProcess(source-hostCoresBasePid, threadId);
	}
}

__attribute__((optimize("O0")))
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

__attribute__((optimize("O0")))
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
static struct value_defn performMathsOp(int operation, struct value_defn value) {
	struct value_defn result;
	result.dtype=SCALAR;
	if (operation== RANDOM_MATHS_OP) {
		result.type=INT_TYPE;
		int r=rand();
		cpy(result.data, &r, sizeof(int));
	} else {
		float fvalue=0, r=0;
		int ivalue;
		if (value.type==REAL_TYPE) {
            cpy(&fvalue, value.data, sizeof(float));
		} else if (value.type==INT_TYPE) {
		    cpy(&ivalue, value.data, sizeof(int));
		    fvalue=(float) ivalue;
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

/**
 * Helper method to get an integer from data (needed as casting to integer directly requires 4 byte alignment which we
 * do not want to enforce as it wastes memory.)
 */
int getInt(void* data) {
	int v;
	cpy(&v, data, sizeof(int));
	return v;
}

/**
 * Helper method to get a float from data (needed as casting to integer directly requires 4 byte alignment which we
 * do not want to enforce as it wastes memory.)
 */
float getFloat(void* data) {
	float v;
	cpy(&v, data, sizeof(float));
	return v;
}
