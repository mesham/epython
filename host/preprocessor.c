#include "preprocessor.h"

static void appendIncludedSourceFileToStore(char*);
static int hasSourceFileAlreadyBeenIncluded(char*);
static char* getIncludeFileWithPath(char*);

struct included_source_files {
    char * fileName;
    struct included_source_files * next;
};

struct included_source_files * included_src_root=NULL;

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

static void appendIncludedSourceFileToStore(char * filename) {
	struct included_source_files * newNode=(struct included_source_files *) malloc(sizeof(struct included_source_files));
	newNode->fileName=(char*) malloc(strlen(filename) + 1);
	strcpy(newNode->fileName, filename);
	newNode->next=included_src_root;
	included_src_root=newNode;
}

static int hasSourceFileAlreadyBeenIncluded(char * filename) {
	struct included_source_files * head=included_src_root;
	while (head != NULL) {
		if (strcmp(head->fileName, filename) == 0) return 1;
		head=head->next;
	}
	return 0;
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
