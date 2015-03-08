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
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h>
#include <math.h>

#include "e-hal.h"
#include "e-loader.h"
#include "basictokens.h"
#include "memorymanager.h"
#include "byteassembler.h"
#include "interpreter.h"
#include "device-support.h"
#include "configuration.h"
#include "shared.h"

struct timeval tval_before[TOTAL_CORES];
extern e_platform_t e_platform;
e_mem_t management_DRAM;
e_epiphany_t epiphany;
static short active[TOTAL_CORES];
int totalActive;

static void initialiseCores(struct shared_basic*, int, struct ebasicconfiguration*);
static void loadBinaryInterpreterOntoCores(char, char*);
static void placeBasicCode(struct shared_basic*, int, char*);
static void checkStatusFlagsOfCore(struct shared_basic*, struct ebasicconfiguration*, int, unsigned int*);
static void deactivateCore(struct ebasicconfiguration*, int);
static void startApplicableCores(struct shared_basic*, struct ebasicconfiguration*);
static void timeval_subtract(struct timeval*, struct timeval*,  struct timeval*);
static void displayCoreMessage(int, struct core_ctrl*);
static void raiseError(int, struct core_ctrl*);
static void stringConcatenate(int, struct core_ctrl*);
static void inputCoreMessage(int, struct core_ctrl*);
static void performMathsOp(struct core_ctrl*);
static int getTypeOfInput(char*);
static char* getEpiphanyExecutableFile(void);
static int doesFileExist(char*);

/**
 * Loads up the code onto the appropriate Epiphany cores, sets up the state (BASIC bytecode, symbol table, data area etc)
 * and then starts the cores running
 */
struct shared_basic * loadCodeOntoEpiphany(struct ebasicconfiguration* configuration) {
	struct shared_basic * basicCode;
	int result, codeOnCore=0;
	e_set_host_verbosity(H_D0);
	result = e_init(NULL);
	if (result == E_ERR) fprintf(stderr, "Error on initialisation\n");
	result = e_reset_system();
	if (result == E_ERR) fprintf(stderr, "Error on system reset\n");
	result = e_open(&epiphany, 0, 0, e_platform.chip[0].rows, e_platform.chip[0].cols);
	if (result != E_OK) fprintf(stderr, "Error opening Epiphany\n");

	result = e_alloc(&management_DRAM, EXTERNAL_MEM_ABSOLUTE_START, SHARED_DATA_SIZE);
	if (result == E_ERR) fprintf(stderr, "Error allocating memory\n");

	basicCode=(void*) management_DRAM.base;
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

	initialiseCores(basicCode, codeOnCore, configuration);
	placeBasicCode(basicCode, codeOnCore, configuration->intentActive);
	startApplicableCores(basicCode, configuration);

	return basicCode;
}

/**
 * Finalises the cores and shuts then down
 */
void finaliseCores(void) {
	if (e_close(&epiphany)) {
		fprintf(stderr, "\nERROR: Can't close connection to Epiphany device!\n\n");
		exit(1);
	}
	if (e_free(&management_DRAM)) {
		fprintf(stderr, "\nERROR: Can't release Epiphany DRAM!\n\n");
		exit(1);
	}

	e_finalize();
}

/**
 * The host acts as a monitor, responding to core communications for host actions (such as IO, some maths etc..)
 */
void monitorCores(struct shared_basic * basicState, struct ebasicconfiguration* configuration) {
	int i;
	unsigned int pb[TOTAL_CORES];
	for (i=0;i<TOTAL_CORES;i++) {
		pb[i]=1;
	}
	while (totalActive > 0) {
		for (i=0;i<TOTAL_CORES;i++) {
			if (active[i]) {
				checkStatusFlagsOfCore(basicState, configuration, i, pb);
			}
		}
	}
}

/**
 * Checks whether the core has sent some command to the host and actions this command if so
 */
static void checkStatusFlagsOfCore(struct shared_basic * basicState, struct ebasicconfiguration* configuration, int coreId, unsigned int * pb) {
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
 * Called when a core informs the host it has finished, optionally displays timing information
 */
static void deactivateCore(struct ebasicconfiguration* configuration, int coreId) {
	if (configuration->displayTiming) {
		struct timeval tval_after, tval_result;
		gettimeofday(&tval_after, NULL);
		timeval_subtract(&tval_result, &tval_after, &tval_before[coreId]);
		printf("Core %d completed in %ld.%06ld seconds\n", coreId, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	}
	active[coreId]=0;
	totalActive--;
}

/**
 * Initialises the cores by setting up their data structures and loading the interpreter onto the cores
 */
static void initialiseCores(struct shared_basic * basicState, int codeOnCore, struct ebasicconfiguration* configuration) {
	unsigned int i;
	char allActive=1;
	for (i=0;i<TOTAL_CORES;i++) {
		basicState->core_ctrl[i].core_run=0;
		basicState->core_ctrl[i].core_busy=0;
		basicState->core_ctrl[i].core_command=0;
		basicState->core_ctrl[i].symbol_table=(void*) CORE_DATA_START;
		basicState->core_ctrl[i].postbox_start=(void*) (CORE_DATA_START+(basicState->symbol_size*sizeof(struct symbol_node))+(codeOnCore?basicState->length:0));
		if (!configuration->forceDataOnShared) {
			// If on core then store after the symbol table and code
			basicState->core_ctrl[i].data_start=basicState->core_ctrl[i].postbox_start+100;
		} else {
			basicState->core_ctrl[i].data_start=SHARED_DATA_AREA_START+(i*SHARED_DATA_AREA_PER_CORE)+(void*)management_DRAM.ephy_base;
		}
		basicState->core_ctrl[i].shared_data_start=SHARED_DATA_AREA_START+(i*SHARED_DATA_AREA_PER_CORE)+(void*)management_DRAM.ephy_base;
		basicState->core_ctrl[i].host_shared_data_start=SHARED_DATA_AREA_START+(i*SHARED_DATA_AREA_PER_CORE)+(void*) management_DRAM.base;
		active[i]=0;
		if (!configuration->intentActive[i]) allActive=0;
	}
	loadBinaryInterpreterOntoCores(allActive, configuration->intentActive);
}

/**
 * Physically loads the binary interpreter onto the cores
 */
static void loadBinaryInterpreterOntoCores(char allActive, char * intentActive) {
	unsigned int i;
	int result;
	char* binaryName=getEpiphanyExecutableFile();
	if (allActive && e_platform.chip[0].num_cores == TOTAL_CORES) {
		result = e_load_group(binaryName, &epiphany, 0, 0, epiphany.rows, epiphany.cols, E_TRUE);
		if (result != E_OK) fprintf(stderr, "Error loading Epiphany program\n");
	} else {
		for (i=0;i<TOTAL_CORES;i++) {
			if (intentActive[i]) {
				int row=i/epiphany.cols;
				result = e_load(binaryName, &epiphany, row, i-(row*epiphany.cols), E_TRUE);
				if (result != E_OK) fprintf(stderr, "Error loading Epiphany program onto core %d\n", i);
			}
		}
	}
}

static char* getEpiphanyExecutableFile() {
	if (doesFileExist(EPIPHANY_BINARY_FILE)) return EPIPHANY_BINARY_FILE;
	char * binLocation=(char*) malloc(strlen(EPIPHANY_BINARY_FILE) + strlen(BIN_PATH) + 1);
	sprintf(binLocation, "%s%s", BIN_PATH, EPIPHANY_BINARY_FILE);
	if (doesFileExist(binLocation)) return binLocation;
	fprintf(stderr, "Can not device binary '%s' in the local directory or binary (%s) directory\n",
			EPIPHANY_BINARY_FILE, BIN_PATH);
	exit(0);
}

static int doesFileExist(char * filename) {
	FILE * file = fopen(filename, "r");
	if (file != NULL) {
		fclose(file);
		return 1;
	}
	return 0;
}

/**
 * Places the bytecode representation of the users BASIC code onto the cores
 */
static void placeBasicCode(struct shared_basic * basicState, int codeOnCore, char * intentActive) {
	unsigned int i;
	if (!codeOnCore) {
		basicState->data=(void*) (SHARED_CODE_AREA_START+management_DRAM.base);
		basicState->edata=(void*) (SHARED_CODE_AREA_START+(void*)management_DRAM.ephy_base);
		memcpy(basicState->data, getAssembledCode(), basicState->length);
	} else {
		// Place code after symbol table (which is 5 bytes per entry)
		basicState->edata=(void*) CORE_DATA_START+(basicState->symbol_size*sizeof(struct symbol_node));
		for (i=0;i<TOTAL_CORES;i++) {
			if (intentActive[i]) {
				int row=i/epiphany.cols;
				e_write(&epiphany, row, i-(row*epiphany.cols), (off_t) basicState->edata, getAssembledCode(), basicState->length);
			}
		}
	}
}

/**
 * Starts up applicable cores and tracks which were initially active
 */
static void startApplicableCores(struct shared_basic * basicState, struct ebasicconfiguration* configuration) {
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
		if (core->data[0]==1) {
			fvalue=*((float*) &core->data[1]);
		} else if (core->data[0]==0) {
			fvalue=(float) *((int*) &core->data[1]);
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
 * Concatenates two strings, or a string and integer/real together with necessary conversions
 */
static void stringConcatenate(int coreId, struct core_ctrl * core) {
	char * newString;
	unsigned int relativeLocation;
	if (core->data[0]==STRING_TYPE && core->data[5]==STRING_TYPE) {
		char *str1, *str2;

		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		str1=core->host_shared_data_start+relativeLocation;

		memcpy(&relativeLocation, &core->data[6], sizeof(unsigned int));
		str2=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str1)+strlen(str2)+1;
		newString=(char*) malloc(totalLen);
		sprintf(newString,"%s%s", str1, str2);
	} else if (core->data[0]==STRING_TYPE) {
		char *str1;
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		str1=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str1)+21;
		newString=(char*) malloc(totalLen);
		if (core->data[5]==INT_TYPE) {
			int d=*((int*) &core->data[6]);
			sprintf(newString,"%s%d", str1, d);
		} else if (core->data[5]==REAL_TYPE) {
			float f=*((float*) &core->data[6]);
			sprintf(newString,"%s%f", str1, f);
		}
	} else {
		char *str2;
		memcpy(&relativeLocation, &core->data[6], sizeof(unsigned int));
		str2=core->host_shared_data_start+relativeLocation;

		int totalLen=strlen(str2)+21;
		newString=(char*) malloc(totalLen);
		if (core->data[0]==INT_TYPE) {
			int d=*((int*) &core->data[1]);
			sprintf(newString,"%d%s", d, str2);
		} else if (core->data[0]==REAL_TYPE) {
			float f=*((float*) &core->data[1]);
			sprintf(newString,"%f%s", f, str2);
		}
	}
	char * target;
	memcpy(&relativeLocation, &core->data[11], sizeof(unsigned int));
	target=core->host_shared_data_start+relativeLocation;
	strcpy(target, newString);
	free(newString);
}

/**
 * The core has raised an error
 */
static void raiseError(int coreId, struct core_ctrl * core) {
	unsigned int relativeLocation;
	char * errorMessage;
	memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
	errorMessage=core->host_shared_data_start+relativeLocation;
	fprintf(stderr, "Error from core %d: %s\n", coreId, errorMessage);
}

/**
 * Inputs a message from the user, with some optional displayed message.
 */
static void inputCoreMessage(int coreId, struct core_ctrl * core) {
	char inputvalue[1000];
	if (core->data[0] == STRING_TYPE) {
		unsigned int relativeLocation;
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		char * message=core->host_shared_data_start+relativeLocation;
		printf("[%d] %s", coreId, message);
	} else {
		printf("%d> ", coreId);
	}
	scanf("%[^\n]", inputvalue);
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
		unsigned int relativeLocation;
		memcpy(&relativeLocation, &core->data[6], sizeof(unsigned int));
		char * target=core->host_shared_data_start+relativeLocation;
		strcpy(target, inputvalue);
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
 * Displays a message from the core
 */
static void displayCoreMessage(int coreId, struct core_ctrl * core) {
	if (core->data[0] == 0) {
		int y=*((int*) &core->data[1]);
		printf("[%d] %d\n", coreId, y);
	} else if (core->data[0] == 1) {
		float y=*((float*) &core->data[1]);
		printf("[%d] %f\n", coreId, y);
	} else if (core->data[0] == 2) {
		unsigned int relativeLocation;
		memcpy(&relativeLocation, &core->data[1], sizeof(unsigned int));
		char * message=core->host_shared_data_start+relativeLocation;
		printf("[%d] %s\n", coreId, message);
	}
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
