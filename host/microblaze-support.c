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
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
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

#define OVERLAY_TCL_FILE "/opt/python3.6/lib/python3.6/site-packages/pynq/overlays/base/base.tcl"
#define PROGRAM_NAME "epython-microblaze.bin"
#define GPIO_DIR "/sys/class/gpio"

#define RESET_PIN_CONFIG_KEY_PMODA "mb_iop_pmoda_reset"
#define RESET_PIN_CONFIG_KEY_PMODB "mb_iop_pmodb_reset"
#define RESET_PIN_CONFIG_KEY_ARDUINO "mb_iop_arduino_reset"

#define INTERUPT_PIN_CONFIG_KEY_PMODA "mb_iop_pmoda_intr_ack"
#define INTERUPT_PIN_CONFIG_KEY_PMODB "mb_iop_pmodb_intr_ack"
#define INTERUPT_PIN_CONFIG_KEY_ARDUINO "mb_iop_arduino_intr_ack"

#define MICROBLAZE_MEMORY_CONFIG_KEY_PMODA "iop_pmoda/mb_bram_ctrl"
#define MICROBLAZE_MEMORY_CONFIG_KEY_PMODB "iop_pmodb/mb_bram_ctrl"
#define MICROBLAZE_MEMORY_CONFIG_KEY_ARDUINO "iop_arduino/mb_bram_ctrl"

#define SHARED_MEMORY_SIZE 1024*1024*6
#define SYMBOL_TABLE_EXTRA 2
#define GPIO_MIN_USER_PIN 54
#define MAILBOX_START 0xB800

static int max_cores=3;
static char * core_program_names[3] = {PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME};
static char * core_reset_pin_keys[3] = {RESET_PIN_CONFIG_KEY_PMODA, RESET_PIN_CONFIG_KEY_PMODB, RESET_PIN_CONFIG_KEY_ARDUINO};
static char * core_interupt_pin_keys[3] = {INTERUPT_PIN_CONFIG_KEY_PMODA, INTERUPT_PIN_CONFIG_KEY_PMODB, INTERUPT_PIN_CONFIG_KEY_ARDUINO};
static char * core_mb_memory_keys[3] = {MICROBLAZE_MEMORY_CONFIG_KEY_PMODA, MICROBLAZE_MEMORY_CONFIG_KEY_PMODB, MICROBLAZE_MEMORY_CONFIG_KEY_ARDUINO};

struct gpio_state {
  int index, direction; // direction is 0 for out and 1 for everything else (specifically in)
  char * filename;
};

struct mmio_state {
  char * buffer;
  int file_handle;
  unsigned int length, address_base, virt_base, virt_offset;
};

struct config_gpio_node {
  int index;
  char * name;
  struct config_gpio_node * next;
};

struct config_memory_node {
  unsigned int address, range;
  char * name;
  struct config_memory_node * next;
};

struct timeval tval_before[TOTAL_CORES];
struct gpio_state ** reset_pins, ** interupt_pins;
struct mmio_state ** microblaze_memories;
int num_initialised_microblazes;
char * shared_buffer;
int totalActive;
static short active[TOTAL_CORES];
volatile unsigned int * pb;
struct config_gpio_node * head_gpio_config = NULL;
struct config_memory_node * head_memory_config=NULL;

void _xlnk_reset();
static void allocateSharedBuffer(void);
static void initialiseMicroblaze(int);
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
static void place_ePythonVMOnMicroblaze(char*, struct mmio_state*);
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
static int parseConfiguration(char *);
static void cleanConfigurationRecords();
static struct config_gpio_node* findGPIOConfigRecord(char*);
static struct config_memory_node* findMemoryConfigRecord(char*);
static char *trim(char *);
static int getBaseGPIONumber(char*);

struct shared_basic * loadCodeOntoMicroblaze(struct interpreterconfiguration* configuration) {
  if (parseConfiguration(OVERLAY_TCL_FILE) == -1) {
    fprintf(stderr, "Error opening overlay TCL file %s\n", OVERLAY_TCL_FILE);
    exit(EXIT_FAILURE);
  }
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

	reset_pins=(struct gpio_state **) malloc(sizeof(struct gpio_state *) * configuration->coreProcs);
	interupt_pins=(struct gpio_state **) malloc(sizeof(struct gpio_state *) * configuration->coreProcs);
  microblaze_memories=(struct mmio_state **) malloc(sizeof(struct mmio_state *) * configuration->coreProcs);
  num_initialised_microblazes=configuration->coreProcs;

  initialiseCores(basicCode, codeOnCore, configuration);
	placeByteCode(basicCode, codeOnCore);
	int i;
	for (i=0;i<configuration->coreProcs;i++) {
	  initialiseMicroblaze(i);
	}
	cleanConfigurationRecords();
	startApplicableCores(basicCode, configuration);

	pb=(unsigned int*) malloc(sizeof(unsigned int) * TOTAL_CORES);
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
  int i;
  for (i=0;i<num_initialised_microblazes;i++) {
    closeMMIO(microblaze_memories[i]);
    closeGPIO(reset_pins[i]);
    closeGPIO(interupt_pins[i]);
  }
  free(microblaze_memories);
  free(reset_pins);
  free(interupt_pins);
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
static void __attribute__((optimize("O0"))) performMathsOp(struct core_ctrl * core) {
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

static void initialiseMicroblaze(int core_index) {
  struct config_gpio_node * reset_pin_config=findGPIOConfigRecord(core_reset_pin_keys[core_index]);
  if (reset_pin_config == NULL) {
    fprintf(stderr, "Can not find reset pin with name %s in TCL file\n", core_reset_pin_keys[core_index]);
    exit(EXIT_FAILURE);
  }
  struct config_gpio_node * interupt_pin_config=findGPIOConfigRecord(core_interupt_pin_keys[core_index]);
  if (interupt_pin_config == NULL) {
    fprintf(stderr, "Can not find interupt pin with name %s in TCL file\n", core_interupt_pin_keys[core_index]);
    exit(EXIT_FAILURE);
  }

  int chipId=getBaseGPIONumber(GPIO_DIR);
  if (chipId == -1) {
    fprintf(stderr, "Can not find a GPIO chip id in directory %s\n", GPIO_DIR);
    exit(EXIT_FAILURE);
  }

  struct config_memory_node * microblaze_memory_config=findMemoryConfigRecord(core_mb_memory_keys[core_index]);
  if (microblaze_memory_config == NULL) {
    fprintf(stderr, "Can not find memory configuration entry %s in TCL file\n", core_mb_memory_keys[core_index]);
    exit(EXIT_FAILURE);
  }

  reset_pins[core_index]=openGPIO(reset_pin_config->index + chipId + GPIO_MIN_USER_PIN, "out");
  interupt_pins[core_index]=openGPIO(interupt_pin_config->index + chipId + GPIO_MIN_USER_PIN, "out");

  microblaze_memories[core_index]=createMMIO(microblaze_memory_config->address, microblaze_memory_config->range);

  writeGPIO(reset_pins[core_index], 1); // Reset Microblaze

  // Set up boostrapper mailbox, this is telling the MB what ID it is and the address of the shared memory
  writeMMIO(microblaze_memories[core_index], MAILBOX_START, &core_index, 4); // The core ID
  // Copy the physical address of shared memory onto the Microblaze so it can access it
  unsigned int physical_address=cma_get_phy_addr((void*) shared_buffer);
  writeMMIO(microblaze_memories[core_index], MAILBOX_START+4, &physical_address, 4);

  place_ePythonVMOnMicroblaze(core_program_names[core_index], microblaze_memories[core_index]);
  writeGPIO(reset_pins[core_index], 0); // Run code on Microblaze
  // Clear the interupt
  writeGPIO(interupt_pins[core_index], 1);
  writeGPIO(interupt_pins[core_index], 0);
}

static void place_ePythonVMOnMicroblaze(char * exec_name, struct mmio_state * microblaze_memory) {
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
  char * postbox_starting_mem_address=((char*) basicState) + (sizeof(struct shared_basic) + 1024);
	unsigned int i, j;
	char allActive=1;
	for (i=0;i<TOTAL_CORES;i++) {
		for (j=0;j<15;j++) basicState->core_ctrl[i].data[j]=0;
		basicState->core_ctrl[i].core_run=0;
		basicState->core_ctrl[i].core_busy=0;
		basicState->core_ctrl[i].core_command=0;
		basicState->core_ctrl[i].symbol_table=(void*) CORE_DATA_START;
		basicState->core_ctrl[i].postbox_start=postbox_starting_mem_address + (i * 100);

		if (!configuration->forceDataOnShared) {
			// If on core then store after the symbol table and code
			basicState->core_ctrl[i].stack_start=(void*) (CORE_DATA_START+(basicState->symbol_size*(sizeof(struct symbol_node)+SYMBOL_TABLE_EXTRA))+(codeOnCore?basicState->length:0));
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
  unsigned int page_size=sysconf(_SC_PAGESIZE);
  if (SHARED_MEMORY_SIZE >= page_size*cma_pages_available()) {
    // If we haven't got enough shared memory then first reset the link which should free up any previously allocated but not freed memory
    _xlnk_reset();
    // Now recheck how much shared memory there is and error if we don't have enough available
    if (SHARED_MEMORY_SIZE >= page_size*cma_pages_available()) {
      fprintf(stderr, "Unable to allocate shared memory as %d bytes is needed but only %d bytes available\n", SHARED_MEMORY_SIZE, page_size*cma_pages_available());
      exit(EXIT_FAILURE);
    }
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

static void cleanConfigurationRecords() {
  struct config_gpio_node * n=head_gpio_config, *p;
	while (n != NULL) {
		free(n->name);
		p=n;
		n=n->next;
		free(p);
	}
	head_gpio_config=NULL;

	struct config_memory_node * n2=head_memory_config, *p2;
	while (n2 != NULL) {
		free(n2->name);
		p2=n2;
		n2=n2->next;
		free(p2);
	}
	head_memory_config=NULL;
}

static struct config_gpio_node * findGPIOConfigRecord(char * name) {
  struct config_gpio_node * n=head_gpio_config;
	while (n != NULL) {
		if (strcmp(n->name, name) == 0) return n;
		n=n->next;
	}
	return NULL;
}

static struct config_memory_node * findMemoryConfigRecord(char * name) {
  struct config_memory_node * n=head_memory_config;
	while (n != NULL) {
		if (strcmp(n->name, name) == 0) return n;
		n=n->next;
	}
	return NULL;
}

static int parseConfiguration(char * filename) {
  int port_number=-1;
  int in_property=0, i;
  char line_buffer[500];
  FILE * f=fopen(filename, "r");
  if (f == NULL) return -1;
  while (fgets(line_buffer, 500, f) != NULL)  {
    char * location;
    if (in_property && (location = strstr(line_buffer, "CONFIG.DIN_FROM {")) != NULL) {
      char * endBrace=strstr(line_buffer, "}");
      endBrace[0]='\0';
      port_number=atoi(&location[17]);
    } else if ((location=strstr(line_buffer, "set_property -dict [")) != NULL) {
      in_property=1;
    } else if (in_property && (location=strstr(line_buffer, "] $")) != NULL) {
      char * propertyname=&location[3];
      propertyname=trim(propertyname);
      in_property=0;
      struct config_gpio_node *n=(struct config_gpio_node *) malloc(sizeof(struct config_gpio_node));
      n->next=head_gpio_config;
      n->index=port_number;
      n->name=(char*) malloc(strlen(propertyname)+1);
      strcpy(n->name, propertyname);
      head_gpio_config=n;
    } else if (!in_property && strstr(line_buffer, "create_bd_addr_seg") != NULL && strstr(line_buffer, "[get_bd_addr_spaces ps7_0/Data]") != NULL){
      struct config_memory_node * n = (struct config_memory_node*) malloc(sizeof(struct config_memory_node));
      n->next=head_memory_config;
      char * data_start=trim(line_buffer);
      char * token = strtok(data_start, " ");
      for (i=0;i<2;i++) {
        if (token == NULL) break;
        token = strtok(NULL, " ");
      }
      if (token != NULL) n->range=(int)strtol(token, NULL, 0);
      for (i=0;i<2;i++) {
	      if (token == NULL) break;
	      token = strtok(NULL, " ");
	    }
	    if (token != NULL) n->address=(int)strtol(token, NULL, 0);
	    for (i=0;i<4;i++) {
	      if (token == NULL) break;
	      token = strtok(NULL, " ");
	    }
	    if (token != NULL) {
        char * r=strchr(token, '/');
        if (r != NULL) {
          r=strchr(&r[1], '/');
          if (r != NULL) {
            r[0]='\0';
            n->name=(char*) malloc(strlen(token)+1);
            strcpy(n->name, token);
          }
        }
	    }
	    head_memory_config=n;
    }
  }
  fclose(f);
  return 0;
}

static char *trim(char *str) {
  char *end;
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;
  if (*str == 0)  return str;
  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  // Write new null terminator
  *(end+1) = 0;
  return str;
}

static int getBaseGPIONumber(char * searchDir) {
  int id_number=-1;
  struct dirent *dir;
  struct stat path_stat;
  DIR * d = opendir(searchDir);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      stat(dir->d_name, &path_stat);
        if (S_ISDIR(path_stat.st_mode)) {
        char * location=strstr(dir->d_name, "gpiochip");
        if (location != NULL) {
          id_number=atoi(&location[8]);
          break;
        }
      }
    }
    closedir(d);
  }
  return id_number;
}
