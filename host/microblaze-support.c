/*
 * Copyright (c) 2018, Nick Brown
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

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "libxlnk_cma.h"
#include "microblaze-support.h"
#include "interpreter.h"
#include "misc.h"
#include "memorymanager.h"
#include "configuration.h"

#define PROGRAM_NAME "epython-microblaze.bin"
#define ADDRESS_BASE 0x40000000
#define ADDRESS_RANGE 65536
#define SHARED_MEMORY_SIZE 1024*1024*32
#define SYMBOL_TABLE_EXTRA 2
#define MAILBOX_START 0xA000

struct gpio_state {
  int index, direction; // direction is 0 for out and 1 for everything else (specifically in)
  char * filename;
};

struct mmio_state {
  char * buffer;
  int file_handle;
  unsigned int length, address_base, virt_base, virt_offset;
};

struct timeval tval_before[TOTAL_CORES];
struct gpio_state * reset_pin, * interupt_pin;
struct mmio_state * microblaze_memory;
char * shared_buffer;
int totalActive;
static short active[TOTAL_CORES];
volatile unsigned int * pb;

void _xlnk_reset();
static void allocateSharedBuffer(void);
static void initialiseMicroblaze(void);
static void initialiseCores(struct shared_basic*, int, struct interpreterconfiguration*);
static void checkStatusFlagsOfCore(struct shared_basic*, struct interpreterconfiguration*, int);
static void startApplicableCores(struct shared_basic*, struct interpreterconfiguration*);
static void displayCoreMessage(int, struct core_ctrl*);
static void inputCoreMessage(int, struct core_ctrl*);
static int getTypeOfInput(char*);
static void performMathsOp(struct core_ctrl*);
static void raiseError(int, struct core_ctrl*);
static void stringConcatenate(int, struct core_ctrl*);
static void deactivateCore(struct interpreterconfiguration*, int);
static void placeByteCode(struct shared_basic*, int);
static void place_ePythonVMOnMicroblaze(char*);
static struct mmio_state * createMMIO(unsigned int, unsigned int);
static void closeMMIO(struct mmio_state*);
static void writeMMIO(struct mmio_state*, unsigned int, void*, unsigned int);
static void readMMIO(struct mmio_state*, unsigned int, void*, unsigned int);
static struct gpio_state * openGPIO(int, char*);
static void writeGPIO(struct gpio_state*, int);
static int readGPIO(struct gpio_state*);
static void closeGPIO(struct gpio_state*);
static void timeval_subtract(struct timeval*, struct timeval*,  struct timeval*);
static char * allocateChunkInSharedHeapMemory(size_t, struct core_ctrl *);

struct shared_basic * loadCodeOntoMicroblaze(struct interpreterconfiguration* configuration) {
  allocateSharedBuffer();
  struct shared_basic * basicCode=(void*) shared_buffer;
  int codeOnCore=0;

  basicCode->length=getMemoryFilledSize();
  if (configuration->forceCodeOnCore) {
		codeOnCore=1;
	} else if (configuration->forceCodeOnShared) {
		codeOnCore=0;
	} else {
		codeOnCore=basicCode->length <= CORE_CODE_MAX_SIZE;
		if (!codeOnCore) {
			printf("Warning: Your code size of %d bytes exceeds the %d byte limit for placement on cores so storing in shared memory\n", basicCode->length, CORE_CODE_MAX_SIZE);
		}
	}
	basicCode->symbol_size=getNumberEntriesInSymbolTable();
	basicCode->allInSharedMemory=configuration->forceDataOnShared;
	basicCode->codeOnCores=codeOnCore==1;
	basicCode->num_procs=configuration->coreProcs+configuration->hostProcs;
	basicCode->baseHostPid=configuration->coreProcs;

  initialiseCores(basicCode, codeOnCore, configuration);
	placeByteCode(basicCode, codeOnCore);
	initialiseMicroblaze();
	startApplicableCores(basicCode, configuration);

	pb=(unsigned int*) malloc(sizeof(unsigned int) * TOTAL_CORES);
	int i;
	for (i=0;i<TOTAL_CORES;i++) {
		pb[i]=1;
	}

  return basicCode;
}

void monitorMicroblaze(struct shared_basic * basicState, struct interpreterconfiguration * configuration) {
  int i;
	while (totalActive > 0) {
		for (i=0;i<TOTAL_CORES;i++) {
			if (active[i]) {
				checkStatusFlagsOfCore(basicState, configuration, i);
			}
		}
	}
}

void finaliseMicroblaze(void) {
  cma_free(shared_buffer);
  closeMMIO(microblaze_memory);
  closeGPIO(reset_pin);
  closeGPIO(interupt_pin);
}

/**
 * Checks whether the core has sent some command to the host and actions this command if so
 */
static void checkStatusFlagsOfCore(struct shared_basic * basicState, struct interpreterconfiguration* configuration, int coreId) {
	char updateCoreWithComplete=0;
	if (basicState->core_ctrl[coreId].core_busy == 0) {
		if (basicState->core_ctrl[coreId].core_run == 0) {
			deactivateCore(configuration, coreId);
		} else if (basicState->core_ctrl[coreId].core_command == 1) {
			displayCoreMessage(coreId, &basicState->core_ctrl[coreId]);
			updateCoreWithComplete=1;
		} else if (basicState->core_ctrl[coreId].core_command == 2) {
			inputCoreMessage(coreId, &basicState->core_ctrl[coreId]);
			updateCoreWithComplete=1;
		} else if (basicState->core_ctrl[coreId].core_command == 3) {
			raiseError(coreId, &basicState->core_ctrl[coreId]);
			updateCoreWithComplete=1;
		} else if (basicState->core_ctrl[coreId].core_command == 4) {
			stringConcatenate(coreId, &basicState->core_ctrl[coreId]);
			updateCoreWithComplete=1;
		} else if (basicState->core_ctrl[coreId].core_command >= 1000) {
			performMathsOp(&basicState->core_ctrl[coreId]);
			updateCoreWithComplete=1;
		}
		if (updateCoreWithComplete) {
			basicState->core_ctrl[coreId].core_command=0;
			basicState->core_ctrl[coreId].core_busy=++pb[coreId];
		}
	}
}

/**
 * Concatenates two strings, or a string and integer/real together with necessary conversions
 */
static void __attribute__((optimize("O0"))) stringConcatenate(int coreId, struct core_ctrl * core) {
	char * newString, *str1, *str2;
	unsigned int relativeLocation;
	if (core->data[0]==STRING_TYPE && core->data[5]==STRING_TYPE) {
        memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		str1=core->host_shared_data_start+relativeLocation;

		memcpy(&relativeLocation, &core->data[6], sizeof(unsigned int));
		str2=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str1)+strlen(str2)+1;
		newString=(char*) malloc(totalLen);
		sprintf(newString,"%s%s", str1, str2);
	} else if (core->data[0]==STRING_TYPE) {
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		str1=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str1)+21;
		newString=(char*) malloc(totalLen);
		if (((core->data[5] >> 7) & 1) == 1) {
			int v;
			memcpy(&v, &core->data[6], sizeof(int));
			sprintf(newString,"%s0x%x", str1, v);
		} else if (core->data[5]==INT_TYPE) {
			int d;
			memcpy(&d, &core->data[6], sizeof(int));
			sprintf(newString,"%s%d", str1, d);
		} else if (core->data[5]==BOOLEAN_TYPE) {
			int d;
			memcpy(&d, &core->data[6], sizeof(int));
			sprintf(newString,"%s%s", str1, d > 0?"true":"false");
		} else if (core->data[5]==NONE_TYPE) {
			sprintf(newString, "%sNONE", str1);
		} else if (core->data[5]==REAL_TYPE) {
			float f;
			memcpy(&f, &core->data[6], sizeof(float));
			sprintf(newString,"%s%f", str1, f);
		}
	} else {
		memcpy(&relativeLocation, &core->data[6], sizeof(unsigned int));
		str2=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str2)+21;
		newString=(char*) malloc(totalLen);
		if (((core->data[0] >> 7) & 1) == 1) {
			int v;
			memcpy(&v, &core->data[1], sizeof(int));
			sprintf(newString,"0x%x%s", v, str2);
		} else if (core->data[0]==INT_TYPE) {
			int d;
			memcpy(&d, &core->data[1], sizeof(int));
			sprintf(newString,"%d%s", d, str2);
		} else if (core->data[0]==BOOLEAN_TYPE) {
			int d;
			memcpy(&d, &core->data[1], sizeof(int));
			sprintf(newString,"%s%s", d > 0?"true":"false", str2);
		} else if (core->data[0]==NONE_TYPE) {
			sprintf(newString, "NONE%s", str2);
		} else if (core->data[0]==REAL_TYPE) {
			float f;
			memcpy(&f, &core->data[1], sizeof(float));
			sprintf(newString,"%f%s", f, str2);
		}
	}
	char * target=allocateChunkInSharedHeapMemory(strlen(newString) + 1, core);
	strcpy(target, newString);
	relativeLocation=target-core->host_shared_data_start;
	memcpy(&core->data[11], &relativeLocation, sizeof(unsigned int));
	free(newString);
}

static char * allocateChunkInSharedHeapMemory(size_t size, struct core_ctrl * core) {
  unsigned char chunkInUse;
  unsigned int chunkLength, splitChunkLength;
  char * heapPtr=core->host_shared_data_start;

  size_t headersize=sizeof(unsigned char) + sizeof(unsigned int);
  size_t lenStride=sizeof(unsigned int);
  while (1==1) {
    memcpy(&chunkLength, heapPtr, sizeof(unsigned int));
    memcpy(&chunkInUse, &heapPtr[lenStride], sizeof(unsigned char));
    if (!chunkInUse && chunkLength >= (size + headersize)) {
      char * splitChunk=(char*) (heapPtr + ((chunkLength + headersize) - (size + headersize)));
      splitChunkLength=chunkLength - size - headersize;
      memcpy(heapPtr, &chunkLength, sizeof(unsigned int));
      chunkLength=size;
      cpy(splitChunk, &chunkLength, sizeof(unsigned int));
      chunkInUse=1;
      cpy(&splitChunk[lenStride], &chunkInUse, sizeof(unsigned char));
      return heapPtr + headersize;
    } else {
      heapPtr+=chunkLength + headersize;
      if (heapPtr  >= core->host_shared_data_start + SHARED_HEAP_DATA_AREA_PER_CORE) {
        break;
      }
    }
  }
  return NULL;
}

/**
 * The core has raised an error
 */
static void raiseError(int coreId, struct core_ctrl * core) {
  unsigned char errorCode;
  memcpy(&errorCode, &core->data[1], sizeof(unsigned char));
  char* errorMessage=translateErrorCodeToMessage(errorCode);
  if (errorMessage != NULL) {
    fprintf(stderr, "Error from core %d: %s\n", coreId, errorMessage);
    free(errorMessage);
  }
}

/**
 * Displays a message from the core
 */
static void __attribute__((optimize("O0"))) displayCoreMessage(int coreId, struct core_ctrl * core) {
	if (((core->data[0] >> 7) & 1) == 1) {
		int y;
    memcpy(&y, &(core->data[1]), sizeof(int));
    char t=core->data[0] & 0x1F;
    char dt=core->data[0] >> 5 & 0x3;
		printf("[device %d] 0x%x points to %s %s\n", coreId, y,
    t==0 ? "integer" : t==1 ? "floating point" : t==2 ? "boolean" : t==3 ? "none" : t==4 ? "function" : "unknown", dt==0 ? "scalar" : "array");
	} else if (core->data[0] == 0) {
		int y;
    memcpy(&y, &(core->data[1]), sizeof(int));
		printf("[device %d] %d\n", coreId, y);
	} else if (core->data[0] == 1) {
		float y;
    memcpy(&y, &(core->data[1]), sizeof(float));
		printf("[device %d] %f\n", coreId, y);
	} else if (core->data[0] == 3) {
		int y;
    memcpy(&y, &(core->data[1]), sizeof(int));
		printf("[device %d] %s\n", coreId, y> 0 ? "true" : "false");
	} else if (core->data[0] == 4) {
		printf("[device %d] NONE\n", coreId);
	} else if (core->data[0] == 2) {
		unsigned int relativeLocation;
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		char * message=core->host_shared_data_start+relativeLocation;
		printf("[device %d] %s\n", coreId, message);
	}
	fflush(stdout);
}

/**
 * Inputs a message from the user, with some optional displayed message.
 */
static void __attribute__((optimize("O0"))) inputCoreMessage(int coreId, struct core_ctrl * core) {
	char inputvalue[1000];
	unsigned int relativeLocation;
	if (core->data[0] == STRING_TYPE) {
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		char * message=core->host_shared_data_start+relativeLocation;
		printf("[device %d] %s", coreId, message);
	} else {
		printf("device %d> ", coreId);
	}
	errorCheck(scanf("%[^\n]", inputvalue), "Getting user input");
	int inputType=getTypeOfInput(inputvalue);
	// The following 2 lines cleans up the input so it is ready for the next input call
	int c;
	while ( (c = getchar()) != '\n' && c != EOF ) { }

	if (inputType==INT_TYPE) {
		core->data[0]=INT_TYPE;
		int iv=atoi(inputvalue);
		memcpy(&core->data[1], &iv, sizeof(int));
	} else if (inputType==REAL_TYPE) {
		core->data[0]=REAL_TYPE;
		float fv=atof(inputvalue);
		memcpy(&core->data[1], &fv, sizeof(float));
	} else {
		core->data[0]=STRING_TYPE;
		char * target=allocateChunkInSharedHeapMemory(strlen(inputvalue) + 1, core);
		strcpy(target, inputvalue);
		relativeLocation=target-core->host_shared_data_start;
		memcpy(&core->data[1], &relativeLocation, sizeof(unsigned int));
	}
}

/**
 * Determines the type of input from the user (is it an integer, real or string)
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
 * Performs some maths operation
 */
static void performMathsOp(struct core_ctrl * core) {
	if (core->core_command-1000 == RANDOM_MATHS_OP) {
		core->data[0]=INT_TYPE;
		int r=rand();
		memcpy(&core->data[1], &r, sizeof(int));
	} else {
		float fvalue=0.0, r=0.0;
		int ivalue;
		if (core->data[0]==REAL_TYPE) {
            memcpy(&fvalue, &core->data[1], sizeof(float));
		} else if (core->data[0]==INT_TYPE) {
		    memcpy(&ivalue, &core->data[1], sizeof(int));
		    fvalue=(float) ivalue;
		}
		if (core->core_command-1000 == SQRT_MATHS_OP) r=sqrtf(fvalue);
		if (core->core_command-1000 == SIN_MATHS_OP) r=sinf(fvalue);
		if (core->core_command-1000 == COS_MATHS_OP) r=cosf(fvalue);
		if (core->core_command-1000 == TAN_MATHS_OP) r=tanf(fvalue);
		if (core->core_command-1000 == ASIN_MATHS_OP) r=asinf(fvalue);
		if (core->core_command-1000 == ACOS_MATHS_OP) r=acosf(fvalue);
		if (core->core_command-1000 == ATAN_MATHS_OP) r=atanf(fvalue);
		if (core->core_command-1000 == SINH_MATHS_OP) r=sinhf(fvalue);
		if (core->core_command-1000 == COSH_MATHS_OP) r=coshf(fvalue);
		if (core->core_command-1000 == TANH_MATHS_OP) r=tanhf(fvalue);
		if (core->core_command-1000 == FLOOR_MATHS_OP) r=floorf(fvalue);
		if (core->core_command-1000 == CEIL_MATHS_OP) r=ceilf(fvalue);
		if (core->core_command-1000 == LOG_MATHS_OP) r=logf(fvalue);
		if (core->core_command-1000 == LOG10_MATHS_OP) r=log10f(fvalue);
		core->data[0]=REAL_TYPE;
		memcpy(&core->data[1], &r, sizeof(float));
	}
}

/**
 * Called when a core informs the host it has finished, optionally displays timing information
 */
static void deactivateCore(struct interpreterconfiguration* configuration, int coreId) {
	if (configuration->displayTiming) {
		struct timeval tval_after, tval_result;
		gettimeofday(&tval_after, NULL);
		timeval_subtract(&tval_result, &tval_after, &tval_before[coreId]);
		printf("Core %d completed in %ld.%06ld seconds\n", coreId, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	}
	active[coreId]=0;
	totalActive--;
}

static void initialiseMicroblaze(void) {
  reset_pin=openGPIO(960, "out");
  interupt_pin=openGPIO(964, "out");
  microblaze_memory=createMMIO(ADDRESS_BASE, ADDRESS_RANGE);

  writeGPIO(reset_pin, 1); // Reset Microblaze

  // Set up boostrapper mailbox, this is telling the MB what ID it is and the address of the shared memory
  int myid_flag=0;
  writeMMIO(microblaze_memory, MAILBOX_START, &myid_flag, 4); // The id, this is 0 for now as only one MB
  // Copy the physical address of shared memory onto the Microblaze so it can access it
  unsigned int physical_address=cma_get_phy_addr((void*) shared_buffer);
  writeMMIO(microblaze_memory, MAILBOX_START+4, &physical_address, 4);

  place_ePythonVMOnMicroblaze(PROGRAM_NAME);
  writeGPIO(reset_pin, 0); // Run code on Microblaze
  // Clear the interupt
  writeGPIO(interupt_pin, 1);
  writeGPIO(interupt_pin, 0);
}

static void startApplicableCores(struct shared_basic * basicState, struct interpreterconfiguration* configuration) {
	unsigned int i;
	for (i=0;i<TOTAL_CORES;i++) {
		if (configuration->intentActive[i]) {
			if (configuration->displayTiming) gettimeofday(&tval_before[i], NULL);
			basicState->core_ctrl[i].core_run=1;
			basicState->core_ctrl[i].active=1;
			active[i]=1;
			totalActive++;
		} else {
			basicState->core_ctrl[i].active=0;
		}
	}
}

static void initialiseCores(struct shared_basic * basicState, int codeOnCore, struct interpreterconfiguration* configuration) {
  char * core_shared_mem_address=cma_get_phy_addr((void*) shared_buffer) | 0x20000000;
	unsigned int i, j;
	char allActive=1;
	for (i=0;i<TOTAL_CORES;i++) {
		for (j=0;j<15;j++) basicState->core_ctrl[i].data[j]=0;
		basicState->core_ctrl[i].core_run=0;
		basicState->core_ctrl[i].core_busy=0;
		basicState->core_ctrl[i].core_command=0;
		basicState->core_ctrl[i].symbol_table=(void*) CORE_DATA_START;
		basicState->core_ctrl[i].postbox_start=(void*) (CORE_DATA_START+(basicState->symbol_size*
				(sizeof(struct symbol_node)+SYMBOL_TABLE_EXTRA))+(codeOnCore?basicState->length:0));
		if (!configuration->forceDataOnShared) {
			// If on core then store after the symbol table and code
			basicState->core_ctrl[i].stack_start=basicState->core_ctrl[i].postbox_start+100;
			basicState->core_ctrl[i].heap_start=basicState->core_ctrl[i].stack_start+LOCAL_CORE_STACK_SIZE;
		} else {
			basicState->core_ctrl[i].stack_start=SHARED_DATA_AREA_START+(i*(SHARED_STACK_DATA_AREA_PER_CORE+SHARED_HEAP_DATA_AREA_PER_CORE))+(void*)core_shared_mem_address;
			basicState->core_ctrl[i].heap_start=basicState->core_ctrl[i].stack_start+SHARED_STACK_DATA_AREA_PER_CORE;
		}
		basicState->core_ctrl[i].shared_stack_start=SHARED_DATA_AREA_START+(i*(SHARED_STACK_DATA_AREA_PER_CORE+SHARED_HEAP_DATA_AREA_PER_CORE))+(void*)core_shared_mem_address;
		basicState->core_ctrl[i].shared_heap_start=basicState->core_ctrl[i].shared_stack_start+SHARED_STACK_DATA_AREA_PER_CORE;
		basicState->core_ctrl[i].host_shared_data_start=SHARED_DATA_AREA_START+SHARED_STACK_DATA_AREA_PER_CORE+(i*(SHARED_STACK_DATA_AREA_PER_CORE+SHARED_HEAP_DATA_AREA_PER_CORE))+(void*) shared_buffer;
		active[i]=0;
		if (!configuration->intentActive[i]) allActive=0;
	}
}

static void allocateSharedBuffer(void) {
  _xlnk_reset();  // Reset the link which should free up any previously allocated but not freed memory
  unsigned int page_size=sysconf(_SC_PAGESIZE);
  if (SHARED_MEMORY_SIZE >= page_size*cma_pages_available()) {
    fprintf(stderr, "Unable to allocate shared memory as %d bytes is needed but only %d bytes available\n", SHARED_MEMORY_SIZE, page_size*cma_pages_available());
    exit(EXIT_FAILURE);
  }
  shared_buffer=(char*) cma_alloc(SHARED_MEMORY_SIZE, 0);
  if (shared_buffer == 0) {
    fprintf(stderr, "Unable to allocate shared memory, allocator returned error\n");
    exit(EXIT_FAILURE);
  }
}

static void placeByteCode(struct shared_basic * basicState, int codeOnCore) {
  basicState->data=(void*) (shared_buffer+SHARED_CODE_AREA_START);
  basicState->esdata=(void*) ((cma_get_phy_addr((void*) shared_buffer) | 0x20000000) + SHARED_CODE_AREA_START);
  memcpy(basicState->data, getAssembledCode(), basicState->length);
  if (!codeOnCore) {
    basicState->edata=basicState->esdata;
  } else {
    // Place code after symbol table
    basicState->edata=(void*) CORE_DATA_START+(basicState->symbol_size*
        (sizeof(struct symbol_node)+SYMBOL_TABLE_EXTRA));
  }
}

static void place_ePythonVMOnMicroblaze(char * exec_name) {
  int handle=open(exec_name, O_RDONLY);
  struct stat st;
  fstat(handle, &st);
  int code_size = (int) (ceil(((double) st.st_size) / sysconf(_SC_PAGESIZE)) * sysconf(_SC_PAGESIZE));
  char * exec_buffer=(char*) malloc(code_size);
  read(handle, exec_buffer, code_size);
  writeMMIO(microblaze_memory, 0, exec_buffer, code_size);
  free(exec_buffer);
  close(handle);
}

static struct mmio_state * createMMIO(unsigned int address_base, unsigned int length) {
  struct mmio_state * state=(struct mmio_state *) malloc(sizeof(struct mmio_state));
  // Align the base address with the pages
  state->virt_base = address_base & ~(sysconf(_SC_PAGESIZE) - 1);
  state->virt_offset = address_base - state->virt_base;
  state->length=length;
  state->address_base=address_base;

  state->file_handle=open("/dev/mem", O_RDWR | O_SYNC);
  state->buffer=mmap(NULL, length+state->virt_offset, PROT_READ | PROT_WRITE, MAP_SHARED, state->file_handle, state->virt_base);
  return state;
}

static void closeMMIO(struct mmio_state * state) {
  close(state->file_handle);
  free(state);
}

static void writeMMIO(struct mmio_state * state, unsigned int offset, void * data, unsigned int size_data) {
  memcpy(&(state->buffer[offset]), data, size_data);
}

static void readMMIO(struct mmio_state * state, unsigned int offset, void * data, unsigned int size_data) {
  memcpy(data, &(state->buffer[offset]), size_data);
}

static struct gpio_state * openGPIO(int index, char * direction) {
  struct gpio_state * state = (struct gpio_state *) malloc(sizeof(struct gpio_state));
  state->index=index;
  state->direction=strcmp(direction, "out");

  char path[150];
  sprintf(path, "/sys/class/gpio/gpio%d", index);
  if (access(path, F_OK) == -1 ) {
   FILE * create_handle=fopen("/sys/class/gpio/export", "w");
   fprintf(create_handle, "%d", index);
   fclose(create_handle);
  }
  char f_name[150];
  sprintf(f_name,"%s/direction", path);
  FILE * handle=fopen(f_name, "w");
  fprintf(handle, "%s", direction);
  fclose(handle);

  state->filename=(char*) malloc(strlen(path) + 7);
  sprintf(state->filename,"%s/value", path);
  return state;
}

static void writeGPIO(struct gpio_state * state, int val) {
  FILE * file_handle=fopen(state->filename, state->direction==0 ? "w" : "r");
  fprintf(file_handle, "%d", val);
  fclose(file_handle);
}

static int readGPIO(struct gpio_state * state) {
  FILE * file_handle=fopen(state->filename, state->direction==0 ? "w" : "r");
  int val=fgetc(file_handle);
  fclose(file_handle);
  return val;
}

static void closeGPIO(struct gpio_state * state) {
  FILE * handle=fopen("/sys/class/gpio/unexport", "w");
  fprintf(handle, "%d", state->index);
  fclose(handle);
  free(state->filename);
  free(state);
}

/**
 * Helper timeval subtraction for core timing information
 */
static void timeval_subtract(struct timeval *result, struct timeval *x,  struct timeval *y) {
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
}
