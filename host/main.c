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

#include "configuration.h"
#include "interpreter.h"
#include "memorymanager.h"
#include "byteassembler.h"
#ifndef HOST_STANDALONE
#include "shared.h"
#include "device-support.h"
#endif

#define TEXTUAL_BASIC_SIZE_STRIDE 5000

extern int yyparse();
extern int yy_scan_string(const char*);

static void doParse(char*);
static char * getSourceFileContents(char*);
static void displayParsedBasicInfo(void);
void writeOutByteCode(char*);
void loadByteCode(char*);
#ifdef HOST_STANDALONE
static void runCodeOnHost(void);
#else
static void runCodeOnEpiphany(struct ebasicconfiguration*);
#endif

/*
 * Host program entry point, bootstraps reading configuration, lexing & parsing (if applicable) and running the code
 */
int main (int argc, char *argv[]) {
	srand(time(NULL));
	struct ebasicconfiguration* configuration=readConfiguration(argc, argv);
	if (configuration->filename != NULL) {
		char * contents = getSourceFileContents(configuration->filename);
		doParse(contents);
	} else if (configuration->loadByteFilename != NULL) {
		loadByteCode(configuration->loadByteFilename);
	}
	if (configuration->displayStats) displayParsedBasicInfo();
	if (configuration->compiledByteFilename != NULL) {
		writeOutByteCode(configuration->compiledByteFilename);
	} else {
#ifdef HOST_STANDALONE
		runCodeOnHost();
#else
		runCodeOnEpiphany(configuration);
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
	yy_scan_string(contents);
	yyparse();
}

#ifndef HOST_STANDALONE
/*
 * Runs the code on the Epiphany cores, acts as a monitor whilst it is running and then finalises the cores afterwards
 */
static void runCodeOnEpiphany(struct ebasicconfiguration* configuration) {
	struct shared_basic * deviceState=loadCodeOntoEpiphany(configuration);
	monitorCores(deviceState, configuration);
	finaliseCores();
}
#endif

#ifdef HOST_STANDALONE
/**
 * Runs the code on the host if compiled in standalone mode (helpful for development)
 */
static void runCodeOnHost() {
	processAssembledCode(getAssembledCode(), getMemoryFilledSize(), getNumberEntriesInSymbolTable(), 0);
}
#endif

/**
 * Given the name of a BASIC file will read it and return the char array containing the contents, an error
 * is reported along with program exit if the file cannot be read for whatever reason
 */
static char * getSourceFileContents(char * filename) {
	int singleLineLength=0, contentsSize=TEXTUAL_BASIC_SIZE_STRIDE;
	char * contents=(char*) malloc(contentsSize);
	char buffer[1024];
	contents[0]='\0';
	FILE * sourceCode=fopen(filename, "r");
	if (sourceCode != NULL) {
		while (fgets(buffer, 1024, sourceCode) != NULL) {
			singleLineLength+=strlen(buffer);
			if (singleLineLength >= contentsSize) {
				contentsSize+=TEXTUAL_BASIC_SIZE_STRIDE;
				contents=realloc(contents, contentsSize);
			}
			sprintf(contents, "%s%s", contents, buffer);
		}
		sprintf(contents, "%s\n", contents);
		fclose(sourceCode);
		return contents;
	} else {
		fprintf(stderr, "Opening of BASIC file '%s' failed, are you sure this file exists?\n", filename);
		exit(0);
	}
}

/**
 * Displays the parsed basic information, giving an idea of the size of the processed byte code, symbol table and memory free on each core
 */
static void displayParsedBasicInfo() {
	int memSize=getMemoryFilledSize();
	int symbolEntries=getNumberEntriesInSymbolTable();
#ifndef HOST_STANDALONE
	printf("%d bytes for code, %ld bytes for symbol table (%d entries), %d bytes free\n",
			memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries, (0x8000-CORE_DATA_START)-(memSize+(symbolEntries*5)));
#else
	printf("%d bytes for code, %ld bytes for symbol table (%d entries)\n", memSize, symbolEntries*sizeof(struct symbol_node), symbolEntries);
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
