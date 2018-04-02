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
#include "microblaze-shared.h"

#define NULL 0
typedef unsigned int size_t; // Microblaze is 32 bit hence we can get away with this

volatile static unsigned int sharedStackEntries=0, localStackEntries=0;
volatile static unsigned char communication_data[6];

static void sendData(struct value_defn, int, char);
static struct value_defn recvData(int);
static struct value_defn sendRecvData(struct value_defn, int);
static struct value_defn bcastData(struct value_defn, int, int);
static struct value_defn reduceData(struct value_defn, int, int);
static struct value_defn getInputFromUser(void);
static struct value_defn getInputFromUserWithString(struct value_defn, int, struct symbol_node*);
static void displayToUser(struct value_defn, int, struct symbol_node*);
static void garbageCollect(int, struct symbol_node*);
static void sendDataToDeviceCore(struct value_defn, int, char);
static void sendDataToHostProcess(struct value_defn, int);
static struct value_defn recvDataFromHostProcess(int);
static struct value_defn recvDataFromDeviceCore(int);
static struct value_defn sendRecvDataWithHostProcess(struct value_defn, int);
static struct value_defn sendRecvDataWithDeviceCore(struct value_defn, int);
static char* copyStringToSharedMemoryAndSetLocation(char*, int, int, struct symbol_node*);
static struct value_defn doGetInputFromUser();
static int stringCmp(char*, char*);
static void consolidateHeapChunks(char);
static char * allocateChunkInHeapMemory(int, char);
static char isMemoryAddressFound(char*, int, struct symbol_node*);
static void performGC(int, struct symbol_node*, char);
static struct value_defn performMathsOp(int, struct value_defn);
static int getLargestCoreId(int);
static struct value_defn probeForMessage(int);
static struct value_defn test_or_wait_for_sent_message(int, char);

void callNativeFunction(struct value_defn * value, unsigned char fnIdentifier, int numArgs, struct value_defn* parameters,
                                       int numActiveCores, int localCoreId, int currentSymbolEntries, struct symbol_node* symbolTable) {
  unsigned char expectedArgs=(fnIdentifier & 0b11100000) >> 5;
  fnIdentifier=fnIdentifier & 0b00011111;
  if (expectedArgs < 7 && numArgs != (int) expectedArgs) raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
	if (fnIdentifier==NATIVE_FN_RTL_ISHOST || fnIdentifier==NATIVE_FN_RTL_ISDEVICE) {
		value->type=BOOLEAN_TYPE;
		value->dtype=SCALAR;
		int v=fnIdentifier==NATIVE_FN_RTL_ISHOST ? 0 : 1;
		cpy(value->data, &v, sizeof(int));
	} else if (fnIdentifier==NATIVE_FN_RTL_PRINT) {
		displayToUser(parameters[0], currentSymbolEntries, symbolTable);
	} else if (fnIdentifier==NATIVE_FN_RTL_NUMDIMS) {
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
		*value=getInputFromUser();
	} else if (fnIdentifier==NATIVE_FN_RTL_INPUTPRINT) {
		*value=getInputFromUserWithString(parameters[0], currentSymbolEntries, symbolTable);
	} else if (fnIdentifier==NATIVE_FN_RTL_SYNC) {
		syncCores(1);
	} else if (fnIdentifier==NATIVE_FN_RTL_GC) {
		garbageCollect(currentSymbolEntries, symbolTable);
	} else if (fnIdentifier==NATIVE_FN_RTL_FREE) {
		char * ptr;
		cpy(&ptr, parameters[0].data, sizeof(char*));
		freeMemoryInHeap(ptr);
	} else if (fnIdentifier==NATIVE_FN_RTL_SEND || fnIdentifier==NATIVE_FN_RTL_SEND_NB) {
		sendData(parameters[0], getInt(parameters[1].data), fnIdentifier==NATIVE_FN_RTL_SEND ? 1 : 0);
	} else if (fnIdentifier==NATIVE_FN_RTL_RECV) {
		*value=recvData(getInt(parameters[0].data));
	} else if (fnIdentifier==NATIVE_FN_RTL_SENDRECV) {
		*value=sendRecvData(parameters[0], getInt(parameters[1].data));
	} else if (fnIdentifier==NATIVE_FN_RTL_TEST_FOR_SEND || fnIdentifier==NATIVE_FN_RTL_WAIT_FOR_SEND) {
		*value=test_or_wait_for_sent_message(getInt(parameters[0].data), fnIdentifier==NATIVE_FN_RTL_WAIT_FOR_SEND ? 1 : 0);
	} else if (fnIdentifier==NATIVE_FN_RTL_BCAST) {
		*value=bcastData(parameters[0], getInt(parameters[1].data), numActiveCores);
	} else if (fnIdentifier==NATIVE_FN_RTL_PROBE_FOR_MESSAGE) {
		*value=probeForMessage(getInt(parameters[0].data));
	} else if (fnIdentifier==NATIVE_FN_RTL_NUMCORES || fnIdentifier==NATIVE_FN_RTL_COREID) {
		value->type=INT_TYPE;
		value->dtype=SCALAR;
		if (fnIdentifier==NATIVE_FN_RTL_NUMCORES) cpy(value->data, &numActiveCores, sizeof(int));
		if (fnIdentifier==NATIVE_FN_RTL_COREID) cpy(value->data, &localCoreId, sizeof(int));
	} else if (fnIdentifier==NATIVE_FN_RTL_REDUCE) {
		*value=reduceData(parameters[0], getInt(parameters[1].data), numActiveCores);
	} else if (fnIdentifier==NATIVE_FN_RTL_ALLOCARRAY || fnIdentifier==NATIVE_FN_RTL_ALLOCSHAREDARRAY) {
		int totalDataSize=1, i;
		for (i=0;i<numArgs;i++) {
			totalDataSize*=getInt(parameters[i].data);
		}
		char * address=getHeapMemory(sizeof(unsigned char) + (sizeof(int)*(totalDataSize+numArgs)),
																	fnIdentifier==NATIVE_FN_RTL_ALLOCSHAREDARRAY, currentSymbolEntries, symbolTable);
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
	} else if (fnIdentifier==NATIVE_FN_RTL_FLATTEN) {
		int intNDims=0, i;
		char * ptr;
		if (parameters[0].dtype == ARRAY) {
			cpy(&ptr, parameters[0].data, sizeof(char*));
			unsigned char num_dims;
			cpy(&num_dims, ptr, sizeof(unsigned char));
			num_dims=num_dims & 0xF;
			intNDims=(int) num_dims;

			if (intNDims > 1) {
				int blank=1;
				for (i=1;i<intNDims;i++) {
					cpy(&ptr[(i * sizeof(int)) + sizeof(unsigned char)], &blank, sizeof(int));
				}
			}
			int newSize=getInt(parameters[1].data);
			cpy(&ptr[sizeof(unsigned char)], &newSize, sizeof(int));
		}
	} else if (fnIdentifier==NATIVE_FN_RTL_ARRAYCOPY) {
		char * tgtptr, *srcptr;
		int tgtDims, srcDims, len;
		cpy(&tgtptr, parameters[0].data, sizeof(char*));
		cpy(&srcptr, parameters[1].data, sizeof(char*));
		tgtDims=getInt(parameters[2].data);
		srcDims=getInt(parameters[3].data);
		len=getInt(parameters[4].data);
		cpy(&tgtptr[sizeof(unsigned char)+(tgtDims*sizeof(int))], &srcptr[sizeof(unsigned char)+(srcDims*sizeof(int))], sizeof(int) * len);
	} else if (fnIdentifier==NATIVE_FN_RTL_MATH) {
		if (numArgs == 2) {
			*value=performMathsOp(getInt(parameters[0].data), parameters[1]);
		} else if (numArgs == 1) {
			*value=performMathsOp(getInt(parameters[0].data), *value);
		} else {
			raiseError(ERR_INCORRECT_NUM_NATIVE_PARAMS);
		}
	} else if (fnIdentifier==NATIVE_FN_RTL_GLOBAL_REFERENCE) {
		value->type=parameters[0].type;
		value->dtype=parameters[0].dtype;
		char * ptr;
		cpy(&ptr, parameters[0].data, sizeof(char*));
		// TODO - need to go from MB address space to another space
		//int row=localCoreId/e_group_config.group_cols;
		//int col=localCoreId-(row*e_group_config.group_cols);
		char * remoteMemory=NULL; //(char*) e_get_global_address(row, col, ptr);
		cpy(value->data, &remoteMemory, sizeof(char*));
	} else if (fnIdentifier==NATIVE_FN_RTL_DEREFERENCE) {
		value->type=parameters[0].type & 0x1F;
		value->dtype=(parameters[0].type >> 5 & 0x3) + 2;
		cpy(value->data, parameters[0].data, sizeof(char*));
	} else {
        raiseError(ERR_UNKNOWN_NATIVE_COMMAND);
	}
};

/**
 * Displays a message to the user and waits for the host to have done this
 */
static void displayToUser(struct value_defn value, int currentSymbolEntries, struct symbol_node* symbolTable) {
	sharedData->core_ctrl[myId].data[0]=value.type;
	char* tempStr=NULL;
	if (value.type == STRING_TYPE) {
		char * v;
		cpy(&v, &value.data, sizeof(char*));
		tempStr=copyStringToSharedMemoryAndSetLocation(v, 1, currentSymbolEntries, symbolTable);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[1], value.data, 4);
	}
	sharedData->core_ctrl[myId].core_command=1;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	if (tempStr != NULL) freeMemoryInHeap(tempStr); // Clears up the temporary memory used
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
static struct value_defn getInputFromUserWithString(struct value_defn toDisplay, int currentSymbolEntries, struct symbol_node* symbolTable) {
	if (toDisplay.type != STRING_TYPE) raiseError(ERR_ONLY_DISPLAY_STR_WITH_INPUT);
	sharedData->core_ctrl[myId].data[0]=toDisplay.type;
	char * msg=NULL;
	if (toDisplay.type == STRING_TYPE) {
		char * v;
		cpy(&v, &toDisplay.data, sizeof(char*));
		msg=copyStringToSharedMemoryAndSetLocation(v, 1, currentSymbolEntries, symbolTable);
	}
	struct value_defn inputValue=doGetInputFromUser();
	if (msg != NULL) freeMemoryInHeap(msg);
	return inputValue;
}

/**
 * Requests input from the host (no string to display)
 */
static struct value_defn getInputFromUser() {
	sharedData->core_ctrl[myId].data[0]=0;
	return doGetInputFromUser();
}

/**
 * Does the copying required to get input from the host, waits until this is ready and then sets the
 * type and data correctly
 */
static struct value_defn doGetInputFromUser() {
	struct value_defn v;
	v.dtype=SCALAR;
	sharedData->core_ctrl[myId].core_command=2;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	v.type=sharedData->core_ctrl[myId].data[0];
	if (v.type==STRING_TYPE) {
        unsigned int relativeLocation;
        cpy(&relativeLocation, &sharedData->core_ctrl[myId].data[1], sizeof(unsigned int));
        char * ptr=sharedData->core_ctrl[myId].shared_heap_start + relativeLocation;
		cpy(&v.data, &ptr, sizeof(char*));
	} else {
		cpy(v.data, &sharedData->core_ctrl[myId].data[1], 4);
	}
	return v;
}

/**
 * Requests the host to perform some maths operation and blocks on this
 */
static struct value_defn performMathsOp(int operation, struct value_defn value) {
	struct value_defn v;
	if (operation != 14) {
        // This is random maths operation, just constant here to reduce executable size
		sharedData->core_ctrl[myId].data[0]=value.type;
		cpy(&sharedData->core_ctrl[myId].data[1], value.data, 4);
	}

	sharedData->core_ctrl[myId].core_command=1000+operation;

	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	v.type=sharedData->core_ctrl[myId].data[0];
	cpy(v.data, &sharedData->core_ctrl[myId].data[1], 4);
	v.dtype=SCALAR;
	return v;
}

/**
 * String concatenation performed on the host (and any needed data transformations)
 */
struct value_defn performStringConcatenation(struct value_defn v1, struct value_defn v2, int currentSymbolEntries, struct symbol_node* symbolTable) {
	struct value_defn v;
	v.type=STRING_TYPE;
	v.dtype=SCALAR;

	sharedData->core_ctrl[myId].data[0]=v1.type;
	char * tmpStr1, * tmpStr2;
	if (v1.type == STRING_TYPE) {
		char * v;
		cpy(&v, &v1.data, sizeof(char*));
		tmpStr1=copyStringToSharedMemoryAndSetLocation(v, 1, currentSymbolEntries, symbolTable);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[1], v1.data, 4);
	}
	sharedData->core_ctrl[myId].data[5]=v2.type;
	if (v2.type == STRING_TYPE) {
		char * v;
		cpy(&v, &v2.data, sizeof(char*));
		tmpStr2=copyStringToSharedMemoryAndSetLocation(v, 6, currentSymbolEntries, symbolTable);
	} else {
		cpy(&sharedData->core_ctrl[myId].data[6], v2.data, 4);
	}
	sharedData->core_ctrl[myId].core_command=4;
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }

	v.type=STRING_TYPE;
	unsigned int relativeLocation;
    cpy(&relativeLocation, &sharedData->core_ctrl[myId].data[11], sizeof(unsigned int));
    char * ptr=sharedData->core_ctrl[myId].shared_heap_start + relativeLocation;
	cpy(&v.data, &ptr, sizeof(char*));
	if (tmpStr1 != NULL) freeMemoryInHeap(tmpStr1);
	if (tmpStr2 != NULL) freeMemoryInHeap(tmpStr2);
	return v;
}

/**
 * Raises an error to the host and quits
 */
void raiseError(unsigned char errorCode) {
	stopInterpreter=1;
	sharedData->core_ctrl[myId].core_command=3;
	sharedData->core_ctrl[myId].data[0]=NONE_TYPE;

    cpy(&sharedData->core_ctrl[myId].data[1], &errorCode, sizeof(unsigned char));
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
}

/**
 * Initialises the symbol table in core memory
 */
struct symbol_node* initialiseSymbolTable(int numberSymbols) {
    unsigned char heapInUse=0;
    unsigned short coreHeapChunkLength;
    unsigned int sharedHeapChunkLength;
    coreHeapChunkLength=LOCAL_CORE_MEMORY_MAP_TOP-((int) sharedData->core_ctrl[myId].heap_start)-(sizeof(unsigned short) + sizeof(unsigned char));
    sharedHeapChunkLength=SHARED_HEAP_DATA_AREA_PER_CORE-(sizeof(unsigned int) + sizeof(unsigned char));
    cpy(sharedData->core_ctrl[myId].heap_start, &coreHeapChunkLength, sizeof(unsigned short));
    cpy(&sharedData->core_ctrl[myId].heap_start[2], &heapInUse, sizeof(unsigned char));
    cpy(sharedData->core_ctrl[myId].shared_heap_start, &sharedHeapChunkLength, sizeof(unsigned int));
    cpy(&sharedData->core_ctrl[myId].shared_heap_start[4], &heapInUse, sizeof(unsigned char));

	return (void*) sharedData->core_ctrl[myId].symbol_table;
}

/**
 * Allocates some memory in the heap
 */
char* getHeapMemory(int size, char isShared, int currentSymbolEntries, struct symbol_node* symbolTable) {
	if (sharedData->allInSharedMemory || isShared) {
		char * dS=allocateChunkInHeapMemory(size, 1);
		if (dS == NULL) {
            if (currentSymbolEntries >= 0 && symbolTable != NULL) {
                performGC(currentSymbolEntries, symbolTable, 1);
                dS=allocateChunkInHeapMemory(size, 1);
            }
            if (dS == NULL) raiseError(ERR_OUT_OF_SHARED_HEAP_MEM);
		}
		return dS;
	} else {
		char * dS=allocateChunkInHeapMemory(size, 0);
		if (dS == NULL) {
            if (currentSymbolEntries >= 0 && symbolTable != NULL) {
                performGC(currentSymbolEntries, symbolTable, 0);
                dS=allocateChunkInHeapMemory(size, 0);
            }
            if (dS == NULL) {
                dS=allocateChunkInHeapMemory(size, 1);
                if (dS == NULL) {
                    if (currentSymbolEntries >= 0 && symbolTable != NULL) {
                        performGC(currentSymbolEntries, symbolTable, 1);
                        dS=allocateChunkInHeapMemory(size, 1);
                    }
                    if (dS == NULL) raiseError(ERR_OUT_OF_CORE_SHARED_HEAP_MEM);
                }
            }
		}
		return dS;
	}
}

void freeMemoryInHeap(void * addr) {
    unsigned chunkInUse=0;
    char * address=(char*) addr;
    cpy(address-1, &chunkInUse, sizeof(unsigned char));
    consolidateHeapChunks((int) address > LOCAL_CORE_MEMORY_MAP_TOP);
}

static void garbageCollect(int currentSymbolEntries, struct symbol_node* symbolTable) {
    performGC(currentSymbolEntries, symbolTable, 0);
    performGC(currentSymbolEntries, symbolTable, 1);
}

static void performGC(int currentSymbolEntries, struct symbol_node* symbolTable, char inSharedMemory) {
    unsigned char chunkInUse, freedMem=0;
    unsigned short coreChunkLength;
    unsigned int chunkLength;
    char * heapPtr;

    size_t headersize, lenStride;
    if (inSharedMemory) {
        heapPtr=sharedData->core_ctrl[myId].shared_heap_start;
        headersize=sizeof(unsigned char) + sizeof(unsigned int);
        lenStride=sizeof(unsigned int);
    } else {
        heapPtr=sharedData->core_ctrl[myId].heap_start;
        headersize=sizeof(unsigned short) + sizeof(unsigned char);
        lenStride=sizeof(unsigned short);
    }
    while (1==1) {
        if (inSharedMemory) {
            cpy(&chunkLength, heapPtr, sizeof(unsigned int));
        } else {
            cpy(&coreChunkLength, heapPtr, sizeof(unsigned short));
            chunkLength=coreChunkLength;
        }
        cpy(&chunkInUse, &heapPtr[lenStride], sizeof(unsigned char));
        if (chunkInUse && !isMemoryAddressFound(&heapPtr[headersize], currentSymbolEntries, symbolTable)) {
            chunkInUse=0;
            cpy(&heapPtr[lenStride], &chunkInUse, sizeof(unsigned char));
            freedMem=1;
        }
        heapPtr+=chunkLength + headersize;
        if (inSharedMemory && heapPtr  >= sharedData->core_ctrl[myId].shared_heap_start + SHARED_HEAP_DATA_AREA_PER_CORE) {
            break;
        } else if ((int) heapPtr  >= LOCAL_CORE_MEMORY_MAP_TOP) {
            break;
        }
    }
    if (freedMem) consolidateHeapChunks(inSharedMemory);
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

static void consolidateHeapChunks(char inSharedMemory) {
    unsigned char chunkInUse;
    unsigned short coreChunkLength, nextCoreChunkLength;
    unsigned int chunkLength, nextChunkLength;
    size_t headersize, lenStride;
    char * heapPtr;
    if (inSharedMemory) {
        heapPtr=sharedData->core_ctrl[myId].shared_heap_start;
        headersize=sizeof(unsigned int) + sizeof(unsigned char);
        lenStride=sizeof(unsigned int);
    } else {
        heapPtr=sharedData->core_ctrl[myId].heap_start;
        headersize=sizeof(unsigned short) + sizeof(unsigned char);
        lenStride=sizeof(unsigned short);
    }
    while (1==1) {
        if (inSharedMemory) {
            cpy(&chunkLength, heapPtr, sizeof(unsigned int));
        } else {
            cpy(&coreChunkLength, heapPtr, sizeof(unsigned short));
            chunkLength=coreChunkLength;
        }
        cpy(&chunkInUse, &heapPtr[lenStride], sizeof(unsigned char));
        while (!chunkInUse) {
            if (inSharedMemory && heapPtr + chunkLength + headersize +lenStride >= sharedData->core_ctrl[myId].shared_heap_start + SHARED_HEAP_DATA_AREA_PER_CORE) {
                break;
            } else if ((int) heapPtr + chunkLength + headersize +lenStride >= LOCAL_CORE_MEMORY_MAP_TOP) {
                break;
            }
            cpy(&chunkInUse, &heapPtr[chunkLength + headersize +lenStride], sizeof(unsigned char));
            if (!chunkInUse) {
                if (inSharedMemory) {
                    cpy(&nextChunkLength, &heapPtr[chunkLength + headersize], sizeof(unsigned int));
                } else {
                    cpy(&nextCoreChunkLength, &heapPtr[chunkLength + headersize], sizeof(unsigned short));
                    nextChunkLength=nextCoreChunkLength;
                }
                chunkLength+=nextChunkLength+headersize;
                if (inSharedMemory) {
                    cpy(heapPtr, &chunkLength, sizeof(unsigned int));
                } else {
                    coreChunkLength=chunkLength;
                    cpy(heapPtr, &coreChunkLength, sizeof(unsigned short));
                }
            }
        }
        heapPtr+=chunkLength + headersize;
        if (inSharedMemory && heapPtr  >= sharedData->core_ctrl[myId].shared_heap_start + SHARED_HEAP_DATA_AREA_PER_CORE) {
            break;
        } else if ((int) heapPtr  >= LOCAL_CORE_MEMORY_MAP_TOP) {
            break;
        }
    }
}

static char * allocateChunkInHeapMemory(int size, char inSharedMemory) {
    unsigned char chunkInUse;
    unsigned short coreChunkLength;
    unsigned int chunkLength;
    char * heapPtr;

    size_t headersize, lenStride;
    if (inSharedMemory) {
        heapPtr=sharedData->core_ctrl[myId].shared_heap_start;
        headersize=sizeof(unsigned char) + sizeof(unsigned int);
        lenStride=sizeof(unsigned int);
    } else {
        heapPtr=sharedData->core_ctrl[myId].heap_start;
        headersize=sizeof(unsigned short) + sizeof(unsigned char);
        lenStride=sizeof(unsigned short);
    }
    while (1==1) {
        if (inSharedMemory) {
            cpy(&chunkLength, heapPtr, sizeof(unsigned int));
        } else {
            cpy(&coreChunkLength, heapPtr, sizeof(unsigned short));
            chunkLength=coreChunkLength;
        }
        cpy(&chunkInUse, &heapPtr[lenStride], sizeof(unsigned char));
        if (!chunkInUse && chunkLength >= (size + headersize)) {
            char * splitChunk=(char*) (heapPtr + ((chunkLength + headersize) - (size + headersize)));

            chunkLength=chunkLength - size - headersize;
            if (inSharedMemory) {
                cpy(heapPtr, &chunkLength, sizeof(unsigned int));
            } else {
                coreChunkLength=chunkLength;
                cpy(heapPtr, &coreChunkLength, sizeof(unsigned short));
            }

            chunkLength=size;
            if (inSharedMemory) {
                cpy(splitChunk, &chunkLength, sizeof(unsigned int));
            } else {
                coreChunkLength=chunkLength;
                cpy(splitChunk, &coreChunkLength, sizeof(unsigned short));
            }
            chunkInUse=1;
            cpy(&splitChunk[lenStride], &chunkInUse, sizeof(unsigned char));

            return splitChunk + headersize;
        } else {
            heapPtr+=chunkLength + headersize;
            if (inSharedMemory && heapPtr  >= sharedData->core_ctrl[myId].shared_heap_start + SHARED_HEAP_DATA_AREA_PER_CORE) {
                break;
            } else if ((int) heapPtr  >= LOCAL_CORE_MEMORY_MAP_TOP) {
                break;
            }
        }
    }
    return NULL;
}

/**
 * Allocates some memory in the stack
 */
char* getStackMemory(int size, char isShared) {
	if (sharedData->allInSharedMemory || isShared) {
			char * dS= (char*) (sharedData->core_ctrl[myId].shared_stack_start + sharedStackEntries);
			sharedStackEntries+=size;
			if (sharedStackEntries >= SHARED_STACK_DATA_AREA_PER_CORE) raiseError(ERR_OUT_OF_SHARED_STACK_MEM);
			return dS;
		} else {
			char * dS= (char*) (sharedData->core_ctrl[myId].stack_start + localStackEntries);
			localStackEntries+=size;
			if (localStackEntries >= LOCAL_CORE_STACK_SIZE) {
				dS= (char*) (sharedData->core_ctrl[myId].shared_stack_start + sharedStackEntries);
				sharedStackEntries+=size;
				if (sharedStackEntries >= SHARED_STACK_DATA_AREA_PER_CORE) raiseError(ERR_OUT_OF_CORE_SHARED_STACK_MEM);
			}
			return dS;
		}
}

/**
 * Removes items from the stack which are no longer needed (i.e. the reference has been removed due to the function returning.)
 */
void clearFreedStackFrames(char* targetPointer) {
	if (targetPointer >= sharedData->core_ctrl[myId].shared_stack_start) {
		sharedStackEntries=targetPointer-sharedData->core_ctrl[myId].shared_stack_start;
	} else {
		sharedStackEntries=0;
		localStackEntries=targetPointer-sharedData->core_ctrl[myId].stack_start;
	}
}

/**
 * Sends data to some other core and blocks on this being received
 */
static void sendData(struct value_defn to_send, int target, char blocking) {
	if (to_send.type == STRING_TYPE) raiseError(ERR_ONLY_SEND_INT_AND_REAL);
	if (target < getLargestCoreId(target)) {
		sendDataToDeviceCore(to_send, target, blocking);
	} else {
    if (!blocking) raiseError(ERR_NBSEND_NOT_SUPPORTED);
		sendDataToHostProcess(to_send, target);
	}
}

static void sendDataToHostProcess(struct value_defn to_send, int hostProcessTarget) {
	cpy(sharedData->core_ctrl[myId].data, &hostProcessTarget, 4);
	sharedData->core_ctrl[myId].data[5]=to_send.type;
	cpy(&sharedData->core_ctrl[myId].data[6], to_send.data, 4);
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_command=5;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
}

static void sendDataToDeviceCore(struct value_defn to_send, int target, char blocking) {
	// TODO
}

static struct value_defn test_or_wait_for_sent_message(int target, char is_wait) {
  // TODO
  struct value_defn toreturn;
  toreturn.type=BOOLEAN_TYPE;
  toreturn.dtype=SCALAR;
  raiseError(ERR_PROBE_NOT_SUPPORTED);
	return toreturn;
}

static int getLargestCoreId(int source) {
    int largestCoreId=sharedData->baseHostPid;
	if (source >= sharedData->num_procs) {
		if (source < TOTAL_CORES && sharedData->core_ctrl[source].active) {
			int i;
			for (i=0;i<TOTAL_CORES;i++) {
				if (sharedData->core_ctrl[i].active) largestCoreId=i+1;
			}
		} else {
			raiseError(ERR_RECV_FROM_UNKNOWN_CORE);
		}
	}
	return largestCoreId;
}

static struct value_defn probeForMessage(int source) {
  // TODO
  struct value_defn toreturn;
  toreturn.type=BOOLEAN_TYPE;
  toreturn.dtype=SCALAR;
	raiseError(ERR_PROBE_NOT_SUPPORTED);
	return toreturn;
}

static struct value_defn recvData(int source) {
	if (source < getLargestCoreId(source)) {
		return recvDataFromDeviceCore(source);
	} else {
		return recvDataFromHostProcess(source);
	}
}

static struct value_defn recvDataFromHostProcess(int hostSource) {
  struct value_defn to_recv;
	cpy(sharedData->core_ctrl[myId].data, &hostSource, 4);
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_command=6;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	to_recv.type=sharedData->core_ctrl[myId].data[5];
	cpy(to_recv.data, &sharedData->core_ctrl[myId].data[6], 4);
	to_recv.dtype=SCALAR;
	return to_recv;
}

/**
 * Gets some data from another core (blocking operation)
 */
static struct value_defn recvDataFromDeviceCore(int source) {
  // TODO
	struct value_defn to_recv;
	return to_recv;
}

/**
 * Combines the send and receive operations for a matching core. This is useful as it will block on the entire operation
 * rather than individual ones, so can greatly ease considerations of synchronisation. Basically it sends a message,
 * blocks on receive and then blocks on the initial send to form one overall block
 */
static struct value_defn sendRecvData(struct value_defn to_send, int target) {
	if (to_send.type == STRING_TYPE) raiseError(ERR_ONLY_SEND_INT_AND_REAL);
	if (target < getLargestCoreId(target)) {
		return sendRecvDataWithDeviceCore(to_send, target);
	} else {
		return sendRecvDataWithHostProcess(to_send, target);
	}
}

static struct value_defn sendRecvDataWithHostProcess(struct value_defn to_send, int hostProcessTarget) {
  struct value_defn receivedData;
	cpy(sharedData->core_ctrl[myId].data, &hostProcessTarget, 4);
	sharedData->core_ctrl[myId].data[5]=to_send.type;
	cpy(&sharedData->core_ctrl[myId].data[6], to_send.data, 4);
	unsigned int pb=sharedData->core_ctrl[myId].core_busy;
	sharedData->core_ctrl[myId].core_command=7;
	sharedData->core_ctrl[myId].core_busy=0;
	while (sharedData->core_ctrl[myId].core_busy==0 || sharedData->core_ctrl[myId].core_busy<=pb) { }
	receivedData.type=sharedData->core_ctrl[myId].data[11];
	cpy(receivedData.data, &sharedData->core_ctrl[myId].data[12], 4);
	receivedData.dtype=SCALAR;
	return receivedData;
}

static struct value_defn sendRecvDataWithDeviceCore(struct value_defn to_send, int target) {
  // TODO
	struct value_defn receivedData;
	return receivedData;
}

/**
 * Synchronises all cores
 */
void syncCores(int global) {
	// TODO
}

/**
 * Broadcasts data, if this is the source then send it, all cores return the data (even the source)
 */
static struct value_defn bcastData(struct value_defn to_send, int source, int totalProcesses) {
  if (myId==source) {
		int i, totalActioned=0;
		for (i=0;i<TOTAL_CORES && totalActioned<totalProcesses;i++) {
			if (sharedData->core_ctrl[i].active) {
				totalActioned++;
				if (i == myId) continue;
				sendData(to_send, i, 1);
			}
		}
		return to_send;
	} else {
		return recvData(source);
	}
}

/**
 * Reduction of data amongst the cores with some operator
 */
static struct value_defn reduceData(struct value_defn to_send, int rop, int totalProcesses) {
  struct value_defn returnValue, retrieved;
	int i, intV, tempInt, totalActioned=0;
	float floatV, tempFloat;
	if (to_send.type==INT_TYPE) {
		cpy(&intV, to_send.data, sizeof(int));
	} else {
		cpy(&floatV, to_send.data, sizeof(int));
	}
	for (i=0;i<TOTAL_CORES && totalActioned<totalProcesses;i++) {
		if (sharedData->core_ctrl[i].active) {
			totalActioned++;
			if (i == myId) continue;
			retrieved=sendRecvData(to_send, i);
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

/**
 * Copies an amount of data from one core to another
 */
void cpy(volatile void* to, volatile void * from, unsigned int size) {
	unsigned int i;
	char *cto=(char*) to, *cfrom=(char*) from;
	for (i=0;i<size;i++) {
		cto[i]=cfrom[i];
	}
}

/**
 * Copies some string into shared memory and sets the location in the data core area
 */
static char* copyStringToSharedMemoryAndSetLocation(char * string, int start, int currentSymbolEntries, struct symbol_node* symbolTable) {
	int len=slength(string)+1;
	char* ptr=getHeapMemory(len, 1, currentSymbolEntries, symbolTable);
	unsigned int relativeLocation;
	cpy(ptr, string, len);
	relativeLocation=ptr-sharedData->core_ctrl[myId].shared_heap_start;
	cpy(&sharedData->core_ctrl[myId].data[start], &relativeLocation, sizeof(unsigned int));
	return ptr;
}

/**
 * Gets the length of a string
 */
int slength(char * v) {
	int i=0;
	while (v[i]!='\0') i++;
	return i;
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
