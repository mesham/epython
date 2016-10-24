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

#include "stack.h"
#include "ctype.h"

#include "configuration.h"
#include "interpreter.h"
#include "memorymanager.h"
#include "byteassembler.h"
#include "python_interoperability.h"
#ifndef HOST_STANDALONE
#include "shared.h"
#include "device-support.h"
#endif

// Wrapper for the context which is passed into a thread
struct hostRunningThreadWrapper {
	char * assembledCode;
	unsigned int memoryFilledSize;
	unsigned short entriesInSymbolTable;
	int hostThreadId, numberProcesses, hostStartPoint;
};

struct epiphanyMonitorThreadWrapper {
	struct interpreterconfiguration* configuration;
	struct shared_basic * deviceState;
};

#define TEXTUAL_BASIC_SIZE_STRIDE 5000

extern int yyparse();
extern int yy_scan_string(const char*);
extern void initThreadedAspectsForInterpreter(int, int, struct shared_basic*);

struct stack_t indent_stack, filenameStack, lineNumberStack;

static void doParse(char*);
static char * getSourceFileContents(char*);
static void displayParsedBasicInfo(void);
void writeOutByteCode(char*);
void loadByteCode(char*);
static char* getIncludeFileWithPath(char*);
static void runCodeOnHost(struct interpreterconfiguration*, struct shared_basic*);
static void * runSpecificHostProcess(void*);
#ifndef HOST_STANDALONE
static void* runCodeOnEpiphany(void*);
#endif

/*
 * Host program entry point, bootstraps reading configuration, lexing & parsing (if applicable) and running the code
 */
int main (int argc, char *argv[]) {
	srand(time(NULL));
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
#ifndef HOST_STANDALONE
		pthread_t epiphany_management_thread;
		struct shared_basic * deviceState=loadCodeOntoEpiphany(configuration);
		struct epiphanyMonitorThreadWrapper * w = (struct epiphanyMonitorThreadWrapper*) malloc(sizeof(struct epiphanyMonitorThreadWrapper));
		w->configuration=configuration;
		w->deviceState=deviceState;
		pthread_create(&epiphany_management_thread, NULL, runCodeOnEpiphany, (void*)w);
		if (configuration->fullPythonHost) {
			runFullPythonInteractivityOnHost(configuration, deviceState, &epiphany_management_thread);
		} else {
			runCodeOnHost(configuration, deviceState);
		}
#else
		struct shared_basic * standAloneState=(struct shared_basic*) malloc(sizeof(struct shared_basic));
		standAloneState->symbol_size=getNumberEntriesInSymbolTable();
		standAloneState->num_procs=configuration->coreProcs+configuration->hostProcs;
		standAloneState->baseHostPid=configuration->coreProcs;
		if (configuration->fullPythonHost) {
			runFullPythonInteractivityOnHost(configuration, standAloneState, NULL);
		} else {
			runCodeOnHost(configuration, standAloneState);
		}
#endif
		pthread_exit(NULL);
#ifndef HOST_STANDALONE
		finaliseCores();
#endif
	}
	free(configuration->intentActive);
	free(configuration);
	return 0;
}

/**
 * Calls out to do the lexing and parsing of the source code
 */
static void doParse(char * contents) {
	enterScope();
	initStack(&indent_stack);
	initStack(&filenameStack);
	initStack(&lineNumberStack);
	yy_scan_string(contents);
	yyparse();
}

#ifndef HOST_STANDALONE
/*
 * Runs the code on the Epiphany cores, acts as a monitor whilst it is running and then finalises the cores afterwards
 */
static void* runCodeOnEpiphany(void * raw_wrapper) {
	struct epiphanyMonitorThreadWrapper * wrapper=(struct epiphanyMonitorThreadWrapper*) raw_wrapper;
	monitorCores(wrapper->deviceState, wrapper->configuration);
	return NULL;
}
#endif



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
	for (i=0;i<configuration->hostProcs;i++) {
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
 * Given the name of a file will read it and return the char array containing the contents, an error
 * is reported along with program exit if the file cannot be read for whatever reason
 */
static char * getSourceFileContents(char * filename) {
	unsigned int contentsSize=TEXTUAL_BASIC_SIZE_STRIDE;
	char * contents=(char*) malloc(contentsSize);
	char buffer[1024];
	FILE * sourceCode=fopen(filename, "r");
	if (sourceCode != NULL) {
		sprintf(contents, "<<<%s\n", filename);
		while (fgets(buffer, 1024, sourceCode) != NULL) {
			if (strstr(buffer, "import") != NULL && buffer[0] != '#') {
				char * importPoint=strstr(buffer, "import");
				char * importPoint_from=strstr(buffer, "from");
				if (importPoint_from != NULL) {
					if (importPoint_from < importPoint) importPoint=importPoint_from;
				}
				int startIdx, idx=0, foundSpace=0;
				while (importPoint[idx] != '\0' && importPoint[idx] != '\n') {
					if (isspace(importPoint[idx]) && foundSpace==0) foundSpace=1;
					if (!isspace(importPoint[idx]) && foundSpace==1) {
						startIdx=idx;
						foundSpace=2;
					}
					if (isspace(importPoint[idx]) && foundSpace==2) break;
					idx++;
				}
				if (importPoint[idx-1]=='\n') importPoint[idx-1]='\0';
				importPoint[idx]='\0';
				char * newFilename=(char*) malloc(strlen(&importPoint[startIdx])+5);
				sprintf(newFilename, "%s.py", &importPoint[startIdx]);
				char* entirePathForFile=getIncludeFileWithPath(newFilename);
				if (entirePathForFile == NULL) {
					fprintf(stderr, "Opening of Python file '%s' failed, are you sure this file exists?\n", newFilename);
					exit(0);
				}
				char * importedContents=getSourceFileContents(entirePathForFile);
				free(newFilename);
				free(entirePathForFile);
				if (strlen(importedContents)+strlen(contents)+1 >= contentsSize) {
					contentsSize=strlen(importedContents)+strlen(contents)+TEXTUAL_BASIC_SIZE_STRIDE;
					contents=realloc(contents, contentsSize);
				}
				sprintf(contents, "%s%s", contents, importedContents);
			} else {
				int i=0;
				while(isspace(buffer[i]) && buffer[i] != '\0' && i < 1024) i++;
				if (buffer[i] != '#') {
					if (strlen(buffer)+strlen(contents)+1 >= contentsSize) {
						contentsSize+=TEXTUAL_BASIC_SIZE_STRIDE;
						contents=realloc(contents, contentsSize);
					}
					sprintf(contents, "%s%s", contents, buffer);
				} else {
					// Empty line to preserve line numberings
					if (strlen(buffer)+2 >= contentsSize) {
						contentsSize+=TEXTUAL_BASIC_SIZE_STRIDE;
						contents=realloc(contents, contentsSize);
					}
					sprintf(contents, "%s\n", contents);
				}
			}
		}
		if (strlen(contents)+7 >=contentsSize) {
			contents=realloc(contents, contentsSize+7);
		}
		sprintf(contents, "%s\n>>>\n", contents);
		fclose(sourceCode);
		return contents;
	} else {
		fprintf(stderr, "Opening of Python file '%s' failed, are you sure this file exists?\n", filename);
		exit(0);
	}
}

static char* getIncludeFileWithPath(char * filename) {
	if(access(filename, F_OK) != -1 ) {
		char * tr=(char*) malloc(strlen(filename) + 1);
		strcpy(tr, filename);
		return tr;
	} else {
	    char * testFilename=(char*) malloc(strlen(filename) + 10);
	    sprintf(testFilename, "modules/%s", filename);
	    if(access(testFilename, F_OK) != -1 ) {
            return testFilename;
	    } else {
            free(testFilename);
	    }

		char * prev = getenv("PYTHONPATH");
		if (prev == NULL) return NULL;
		char * pch=strchr(prev, ':');
		while (pch != NULL) {
			char * newPath=(char*) malloc((pch-prev)+1);
			strncpy(newPath, prev, pch-prev);
			if (prev[(pch-prev)-1] == '/') {
				newPath[(pch-prev)-1]='\0';
			} else {
				newPath[pch-prev]='\0';
			}
			testFilename=(char*) malloc(strlen(newPath) + strlen(filename) + 2);
			sprintf(testFilename, "%s/%s", newPath, filename);
			free(newPath);
			if(access(testFilename, F_OK) != -1 ) return testFilename;
			free(testFilename);
			prev=pch+1;
			pch=strchr(prev,':');
		}
		if (prev[strlen(prev)-1] == '/') {
			prev[strlen(prev)-1]='\0';
		}
		testFilename=(char*) malloc(strlen(prev) + strlen(filename) + 2);
		sprintf(testFilename, "%s/%s", prev, filename);
		if(access(testFilename, F_OK) != -1 ) return testFilename;
		free(testFilename);
	}
	return NULL;
}

/**
 * Displays the parsed basic information, giving an idea of the size of the processed byte code, symbol table and memory free on each core
 */
static void displayParsedBasicInfo() {
	int memSize=getMemoryFilledSize();
	int symbolEntries=getNumberEntriesInSymbolTable();
#ifndef HOST_STANDALONE
	printf("%d bytes for code, %u bytes for symbol table (%d entries), %d bytes free\n",
			memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries, (0x8000-CORE_DATA_START)-(memSize+(symbolEntries*5)));
#else
	printf("%d bytes for code, %u bytes for symbol table (%d entries)\n", memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries);
#endif
}

/**
 * Starts the interpreter from a byte code file
 */
void loadByteCode(char * loadByteFilename) {
	FILE * byteFile=fopen(loadByteFilename, "rb");
	if (byteFile != NULL) {
		unsigned int len;
		fread(&len, sizeof(unsigned int), 1, byteFile);
		setMemoryFilledSize(len);
		unsigned short symbols;
		fread(&symbols, sizeof(unsigned short), 1, byteFile);
		setNumberEntriesInSymbolTable(symbols);
		char * code=(char*) malloc(len);
		fread(code, sizeof(char), len, byteFile);
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
