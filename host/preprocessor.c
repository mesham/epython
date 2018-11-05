/*
 * Copyright (c) 2016, Nick Brown
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include "preprocessor.h"

#define TEXTUAL_BASIC_SIZE_STRIDE 5000
#define INSTALL_MODULE_LOCATION "/usr/include/epython/modules"

struct included_source_files {
	char * fileName;
	struct included_source_files * next;
};

struct included_source_files * included_src_root=NULL;

static char * getSourceFileContents(char*);
static void appendIncludedSourceFileToStore(char*);
static int hasSourceFileAlreadyBeenIncluded(char*);
static char* getIncludeFileWithPath(char*);

/**
 * Given the name of a file will read it and return the char array containing the contents, an error
 * is reported along with program exit if the file cannot be read for whatever reason
 */
char * preprocessSourceFile(char * filename) {
	included_src_root=NULL;
	return getSourceFileContents(filename);
}

/**
* Returns the preprocessed source based on the file provided. It will recursively visit included files to build up preprocessed representations of these also
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
				int startIdx=0, idx=0, foundSpace=0;
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
				if (!hasSourceFileAlreadyBeenIncluded(entirePathForFile)) {
					appendIncludedSourceFileToStore(entirePathForFile);
					char * importedContents=getSourceFileContents(entirePathForFile);
					if (strlen(importedContents)+strlen(contents)+1 >= contentsSize) {
						contentsSize=strlen(importedContents)+strlen(contents)+TEXTUAL_BASIC_SIZE_STRIDE;
						contents=realloc(contents, contentsSize);
					}
					sprintf(contents, "%s%s", contents, importedContents);
				}
				free(newFilename);
				free(entirePathForFile);
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

/**
* Appends the name of a source file to the store, this is used to keep track of what files have been included and what not to avoid duplication
*/
static void appendIncludedSourceFileToStore(char * filename) {
	struct included_source_files * newNode=(struct included_source_files *) malloc(sizeof(struct included_source_files));
	newNode->fileName=(char*) malloc(strlen(filename) + 1);
	strcpy(newNode->fileName, filename);
	newNode->next=included_src_root;
	included_src_root=newNode;
}

/**
* Determines whether a source file has already been included or not
*/
static int hasSourceFileAlreadyBeenIncluded(char * filename) {
	struct included_source_files * head=included_src_root;
	while (head != NULL) {
		if (strcmp(head->fileName, filename) == 0) return 1;
		head=head->next;
	}
	return 0;
}

/**
* Given the name of the file will search paths to locate where that file is stored and return the full path to the file
*/
static char* getIncludeFileWithPath(char * filename) {
	if(access(filename, F_OK) != -1 ) {
		char * tr=(char*) malloc(strlen(filename) + 1);
		strcpy(tr, filename);
		return tr;
	} else {
		char * testFilename=(char*) malloc(strlen(filename) + 10 + strlen(INSTALL_MODULE_LOCATION));
		sprintf(testFilename, "modules/%s", filename);
		if(access(testFilename, F_OK) != -1 ) {
			return testFilename;
		}
		sprintf(testFilename, "%s/%s", INSTALL_MODULE_LOCATION, filename);
		if(access(testFilename, F_OK) != -1 ) {
			return testFilename;
		} else {
			free(testFilename);
		}

		char * prev = getenv("EPYTHONPATH");
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
