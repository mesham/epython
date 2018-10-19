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
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include "stack.h"
#include "ctype.h"

#include "configuration.h"
#include "interpreter.h"
#include "memorymanager.h"
#include "byteassembler.h"
#include "python_interoperability.h"
#include "misc.h"
#include "preprocessor.h"

#if defined(EPIPHANY_TARGET)
#include "epiphany-shared.h"
#include "epiphany-support.h"
#elif defined(MICROBLAZE_TARGET)
#include "microblaze-support.h"
#include "microblaze-shared.h"
#elif defined(HOST_STANDALONE)
#include "host-shared.h"
#endif

// Wrapper for the context which is passed into a thread
struct hostRunningThreadWrapper {
	char * assembledCode;
	unsigned int memoryFilledSize;
	unsigned short entriesInSymbolTable;
	int hostThreadId, numberProcesses, hostStartPoint;
};

struct monitorThreadWrapper {
	struct interpreterconfiguration* configuration;
	struct shared_basic * deviceState;
};

struct fullPythonInteractivityThreadWrapper {
    struct interpreterconfiguration* configuration;
    struct shared_basic * deviceState;
    pthread_t* emanagementThread;
};

struct included_source_files {
    char * fileName;
    struct included_source_files * next;
};

#define TEXTUAL_BASIC_SIZE_STRIDE 5000

extern int yyparse();
extern int yy_scan_string(const char*);
extern void initThreadedAspectsForInterpreter(int, int, struct shared_basic*);

struct stack_t indent_stack, filenameStack, lineNumberStack;
struct included_source_files * included_src_root=NULL;

static void displayParsedBasicInfo(void);
void writeOutByteCode(char*);
void loadByteCode(char*);
static void runCodeOnHost(struct interpreterconfiguration*, struct shared_basic*);
static void * runSpecificHostProcess(void*);
static void* runCodeForFullPythonInteractivity(void*);
#ifdef EPIPHANY_TARGET
static void* runCodeOnEpiphany(void*);
#endif

#ifdef MICROBLAZE_TARGET
static void* runCodeOnMicroblaze(void*);
#endif

/*
 * Host program entry point, bootstraps reading configuration, lexing & parsing (if applicable) and running the code
 */
int main (int argc, char *argv[]) {
	srand((unsigned) time(NULL) * getpid());
	struct interpreterconfiguration* configuration=readConfiguration(argc, argv);
	if (configuration->filename != NULL) {
		char * contents = getSourceFileContents(configuration->filename);
		if (configuration->displayPPCode) printf("%s\n", contents);
		doParse(contents);
	} else if (configuration->loadByteFilename != NULL) {
		loadByteCode(configuration->loadByteFilename);
	} else if (configuration->pipedInContents != NULL) {
		if (configuration->displayPPCode) printf("%s\n", configuration->pipedInContents);
		doParse(configuration->pipedInContents);
	}
	if (configuration->displayStats) displayParsedBasicInfo();
	if (configuration->compiledByteFilename != NULL) {
		writeOutByteCode(configuration->compiledByteFilename);
	} else {
#if defined(EPIPHANY_TARGET)
		pthread_t epiphany_management_thread, fullPythonInteractivityThread;
		struct shared_basic * deviceState=loadCodeOntoEpiphany(configuration);
		struct monitorThreadWrapper * w = (struct monitorThreadWrapper*) malloc(sizeof(struct monitorThreadWrapper));
		w->configuration=configuration;
		w->deviceState=deviceState;
		pthread_create(&epiphany_management_thread, NULL, runCodeOnEpiphany, (void*)w);
		if (configuration->fullPythonHost) {
			struct fullPythonInteractivityThreadWrapper * wrapperForInteract=(struct fullPythonInteractivityThreadWrapper *) malloc(sizeof(struct fullPythonInteractivityThreadWrapper));
			wrapperForInteract->configuration=configuration;
			wrapperForInteract->deviceState=deviceState;
			wrapperForInteract->emanagementThread=&epiphany_management_thread;
			pthread_create(&fullPythonInteractivityThread, NULL, runCodeForFullPythonInteractivity, (void*) wrapperForInteract);
		}
		runCodeOnHost(configuration, deviceState);
#elif defined(MICROBLAZE_TARGET)
    pthread_t microblaze_management_thread, fullPythonInteractivityThread;
    struct shared_basic * deviceState=loadCodeOntoMicroblaze(configuration);
    struct monitorThreadWrapper * w = (struct monitorThreadWrapper*) malloc(sizeof(struct monitorThreadWrapper));
		w->configuration=configuration;
		w->deviceState=deviceState;
		pthread_create(&microblaze_management_thread, NULL, runCodeOnMicroblaze, (void*)w);
		if (configuration->fullPythonHost) {
			struct fullPythonInteractivityThreadWrapper * wrapperForInteract=(struct fullPythonInteractivityThreadWrapper *) malloc(sizeof(struct fullPythonInteractivityThreadWrapper));
			wrapperForInteract->configuration=configuration;
			wrapperForInteract->deviceState=deviceState;
			wrapperForInteract->emanagementThread=&microblaze_management_thread;
			pthread_create(&fullPythonInteractivityThread, NULL, runCodeForFullPythonInteractivity, (void*) wrapperForInteract);
		}
		runCodeOnHost(configuration, deviceState);
#elif defined(HOST_STANDALONE)
		pthread_t fullPythonInteractivityThread;
		struct shared_basic * standAloneState=(struct shared_basic*) malloc(sizeof(struct shared_basic));
		standAloneState->symbol_size=getNumberEntriesInSymbolTable();
		standAloneState->num_procs=configuration->coreProcs+configuration->hostProcs;
		standAloneState->baseHostPid=configuration->coreProcs;
		if (configuration->fullPythonHost) {
			struct fullPythonInteractivityThreadWrapper * wrapperForInteract=(struct fullPythonInteractivityThreadWrapper *) malloc(sizeof(struct fullPythonInteractivityThreadWrapper));
			wrapperForInteract->configuration=configuration;
			wrapperForInteract->deviceState=standAloneState;
			wrapperForInteract->emanagementThread=NULL;
			pthread_create(&fullPythonInteractivityThread, NULL, runCodeForFullPythonInteractivity, (void*) wrapperForInteract);
		}
		runCodeOnHost(configuration, standAloneState);
#endif
		pthread_exit(NULL);
#ifdef EPIPHANY_TARGET
		finaliseCores();
#elif defined(MICROBLAZE_TARGET)
    finaliseMicroblaze();
#endif
	}
	free(configuration->intentActive);
	free(configuration);
	return 0;
}

#ifdef EPIPHANY_TARGET
/*
 * Runs the code on the Epiphany cores, acts as a monitor whilst it is running and then finalises the cores afterwards
 */
static void* runCodeOnEpiphany(void * raw_wrapper) {
	struct monitorThreadWrapper * wrapper=(struct monitorThreadWrapper*) raw_wrapper;
	monitorCores(wrapper->deviceState, wrapper->configuration);
	return NULL;
}
#endif

#ifdef MICROBLAZE_TARGET
static void* runCodeOnMicroblaze(void * raw_wrapper) {
  struct monitorThreadWrapper * wrapper=(struct monitorThreadWrapper*) raw_wrapper;
  monitorMicroblaze(wrapper->deviceState, wrapper->configuration);
  return NULL;
}
#endif

/**
* Runs the full python interactivity monitor (host virtual core id = 0) in a thread
*/
static void* runCodeForFullPythonInteractivity(void * raw_wrapper) {
    struct fullPythonInteractivityThreadWrapper * wrapperForInteract=(struct fullPythonInteractivityThreadWrapper*) raw_wrapper;
    runFullPythonInteractivityOnHost(wrapperForInteract->configuration, wrapperForInteract->deviceState, wrapperForInteract->emanagementThread,
                                     wrapperForInteract->configuration->hostProcs > 1);
    return NULL;
}

/**
 * Runs the code on the host if compiled in standalone mode (helpful for development)
 */
static void runCodeOnHost(struct interpreterconfiguration* configuration, struct shared_basic * basicState) {
	struct hostRunningThreadWrapper * threadWrappers=(struct hostRunningThreadWrapper *)
			malloc(sizeof(struct hostRunningThreadWrapper) * configuration->hostProcs);
	pthread_t threads[configuration->hostProcs];
	int i;
	char * assembledCode=getAssembledCode();
	unsigned int memoryFilledSize=getMemoryFilledSize();
	unsigned short entriesInSymbolTable=getNumberEntriesInSymbolTable();
	if (configuration->hostProcs > 0) initThreadedAspectsForInterpreter(configuration->hostProcs, configuration->coreProcs, basicState);
	for (i=(configuration->fullPythonHost ? 1 : 0);i<configuration->hostProcs;i++) {
		threadWrappers[i].assembledCode=assembledCode;
		threadWrappers[i].memoryFilledSize=memoryFilledSize;
		threadWrappers[i].entriesInSymbolTable=entriesInSymbolTable;
		threadWrappers[i].hostThreadId=i;
		threadWrappers[i].hostStartPoint=configuration->coreProcs;
		threadWrappers[i].numberProcesses=configuration->hostProcs + configuration->coreProcs;
		pthread_create(&threads[i], NULL, runSpecificHostProcess, (void*)&threadWrappers[i]);
	}
}

/**
 * Host thread entry point, which calls on to the interpreter
 */
static void * runSpecificHostProcess(void * rawThreadContext) {
	struct hostRunningThreadWrapper * threadContext= (struct hostRunningThreadWrapper*) rawThreadContext;
	runIntepreter(threadContext->assembledCode, threadContext->memoryFilledSize, threadContext->entriesInSymbolTable,
			threadContext->hostThreadId + threadContext->hostStartPoint, threadContext->numberProcesses, threadContext->hostThreadId);
	return NULL;
}

/**
 * Displays the parsed basic information, giving an idea of the size of the processed byte code, symbol table and memory free on each core
 */
static void displayParsedBasicInfo() {
	int memSize=getMemoryFilledSize();
	int symbolEntries=getNumberEntriesInSymbolTable();
#if defined(EPIPHANY_TARGET)
	printf("%d bytes for code, %lu bytes for symbol table (%d entries), %d bytes free\n",
			memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries, (0x8000-CORE_DATA_START)-(memSize+(symbolEntries*5)));
#elif defined(MICROBLAZE_TARGET)
  printf("%d bytes for code, %lu bytes for symbol table (%d entries), %d bytes free\n",
			memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries, (0x10000-CORE_DATA_START)-(memSize+(symbolEntries*5)));
#elif defined(HOST_STANDALONE)
	printf("%d bytes for code, %lu bytes for symbol table (%d entries)\n", memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries);
#endif
}

/**
 * Starts the interpreter from a byte code file
 */
void loadByteCode(char * loadByteFilename) {
	FILE * byteFile=fopen(loadByteFilename, "rb");
	if (byteFile != NULL) {
		unsigned int len;
		errorCheck(fread(&len, sizeof(unsigned int), 1, byteFile), "Memory filled size from byte code file");
		setMemoryFilledSize(len);
		unsigned short symbols;
		errorCheck(fread(&symbols, sizeof(unsigned short), 1, byteFile), "Number of symbols from byte code file");
		setNumberEntriesInSymbolTable(symbols);
		char * code=(char*) malloc(len);
		errorCheck(fread(code, sizeof(char), len, byteFile), "Byte code from file");
		setAssembledCode(code);
		fclose(byteFile);
	} else {
		fprintf(stderr, "Opening of byte code file '%s' failed, are you sure this file exists?\n", loadByteFilename);
		exit(0);
	}
}

/**
 * Writes out the byte code to a file
 */
void writeOutByteCode(char * compiledByteFilename) {
	FILE * byteFile=fopen(compiledByteFilename, "wb");
	if (byteFile != NULL) {
		unsigned int len=getMemoryFilledSize();
		fwrite(&len, sizeof(unsigned int), 1, byteFile);
		unsigned short symbols=getNumberEntriesInSymbolTable();
		fwrite(&symbols, sizeof(unsigned short), 1, byteFile);
		char * code=getAssembledCode();
		fwrite(code, sizeof(char), len, byteFile);
		fclose(byteFile);
	} else {
		fprintf(stderr, "Writing byte code to file '%s' failed\n", compiledByteFilename);
		exit(0);
	}
}
