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

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "configuration.h"
#ifndef HOST_STANDALONE
#include "device-support.h"
#else
#define TOTAL_CORES 1
#endif

static void parseCommandLineArguments(struct interpreterconfiguration*, int, char**);
static void parseCoreActiveInfo(struct interpreterconfiguration*, char*);
static int areStringsEqualIgnoreCase(char*, char*);
static void displayHelp(void);

/**
 * Given the command line arguments this will read the configuration and return the configuration structure
 * which has the appropriate flags set and contains strings etc
 */
struct interpreterconfiguration* readConfiguration(int argc, char *argv[]) {
	int i;
	struct interpreterconfiguration* configuration=(struct interpreterconfiguration*) malloc(sizeof(struct interpreterconfiguration));
	configuration->intentActive=(char*) malloc(TOTAL_CORES);
	for (i=0;i<TOTAL_CORES;i++) configuration->intentActive[i]=1;
	configuration->displayStats=configuration->displayTiming=configuration->forceCodeOnCore=
			configuration->forceCodeOnShared=configuration->forceDataOnShared=configuration->displayPPCode=0;
	configuration->filename=configuration->compiledByteFilename=configuration->loadByteFilename=configuration->pipedInContents=NULL;
	parseCommandLineArguments(configuration, argc, argv);
	return configuration;
}

/**
 * Parses command line arguments
 */
static void parseCommandLineArguments(struct interpreterconfiguration* configuration, int argc, char *argv[]) {
	if (argc == 1) {
		displayHelp();
		exit(0);
	} else {
#ifdef HOST_STANDALONE
		configuration->hostProcs=1;
#else
		configuration->hostProcs=0;
#endif
		configuration->coreProcs=0;
		configuration->loadElf=1;
		configuration->loadSrec=0;
		configuration->fullPythonHost=0;
		int i, coreplacement=0;
		for (i=1;i<argc;i++) {
			if (areStringsEqualIgnoreCase(argv[i], "-s")) {
				configuration->displayStats=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-pp")) {
				configuration->displayPPCode=1;
                        } else if (areStringsEqualIgnoreCase(argv[i], "-srec")) {
				configuration->loadElf=0;
		                configuration->loadSrec=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-elf")) {
				configuration->loadElf=1;
		                configuration->loadSrec=0;
			} else if (areStringsEqualIgnoreCase(argv[i], "-t")) {
				configuration->displayTiming=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-fullpython")) {
				configuration->fullPythonHost=1;
				configuration->hostProcs=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-datashared")) {
				configuration->forceDataOnShared=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-codecore")) {
				configuration->forceCodeOnCore=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-codeshared")) {
				configuration->forceCodeOnShared=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-o")) {
				if (i+1 ==argc) {
					fprintf(stderr, "When specifying to output compiled bytes then you must provide a filename for this\n");
					exit(0);
				} else {
					configuration->compiledByteFilename=argv[++i];
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-l")) {
				if (i+1 ==argc) {
					fprintf(stderr, "When specifying to load from a byte file then you must provide a filename for this\n");
					exit(0);
				} else {
					configuration->loadByteFilename=argv[++i];
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-help")) {
				displayHelp();
				exit(0);
			} else if (areStringsEqualIgnoreCase(argv[i], "-h")) {
				if (i+1 ==argc) {
					fprintf(stderr, "You must provide a number of host processes to use\n");
					exit(0);
				} else {
					if (coreplacement) {
						fprintf(stderr, "Can not specify explicit core placement and have host virtual processes\n");
						exit(0);
					}
					configuration->hostProcs=atoi(argv[++i]);
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-d")) {
				if (i+1 ==argc) {
					fprintf(stderr, "You must provide a number of device processes to use\n");
					exit(0);
				} else {
					int j, device_procs=atoi(argv[++i]);
					for (j=0;j<16;j++) {
						configuration->intentActive[j]=j<device_procs ? 1 : 0;
					}
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-pipein")) {
				if (i+1 ==argc) {
					fprintf(stderr, "You must provide the Python code contents with the -pipein flag\n");
					exit(0);
				} else {
					configuration->pipedInContents=argv[++i];
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-c")) {
				if (i+1 ==argc) {
					fprintf(stderr, "When specifying core placement you must provide arguments\n");
					exit(0);
				} else {
					if (configuration->hostProcs > 0) {
						fprintf(stderr, "Can only specify explicit core placement with no host virtual processes\n");
						exit(0);
					}
					coreplacement=1;
					parseCoreActiveInfo(configuration, argv[++i]);
				}
			} else {
				if (configuration->filename != NULL) {
					fprintf(stderr, "Only one filename can be provided, you have suppled '%s' and '%s'\n", configuration->filename, argv[i]);
					exit(0);
				} else {
					configuration->filename=argv[i];
				}
			}
		}
		if (configuration->loadByteFilename == NULL && configuration->filename == NULL && configuration->pipedInContents == NULL) {
			fprintf(stderr, "You must supply a file to run as an argument, see -h for details\n");
			exit(0);
		}
#ifndef HOST_STANDALONE
		for (i=0;i<16;i++) if (configuration->intentActive[i]) configuration->coreProcs++;
#endif
	}
}

/**
 * Determines the active cores if the user supplied -c n, can be a single integer, a list, a range or
 * all to select all cores
 */
static void parseCoreActiveInfo(struct interpreterconfiguration* configuration, char * info) {
	int i;
	if (areStringsEqualIgnoreCase(info, "all")) {
		for (i=0;i<16;i++) configuration->intentActive[i]=1;
	} else {
		if (strchr(info, ',') != NULL) {
			char vn[5];
			int s;
			for (i=0;i<16;i++) configuration->intentActive[i]=0;
			while (strchr(info, ',') != NULL) {
				s=strchr(info, ',')-info;
				memcpy(vn, info, s);
				vn[s]='\0';
				configuration->intentActive[atoi(vn)]=1;
				info=strchr(info, ',')+1;
			}
			configuration->intentActive[atoi(info)]=1;
		} else if (strchr(info, ':') != NULL) {
			char vn[5];
			int s;
			s=strchr(info, ':')-info;
			memcpy(vn, info, s);
			vn[s]='\0';
			int from=atoi(vn);
			int to=atoi(strchr(info, ':')+1);
			for (i=0;i<16;i++) {
				if (i >= from && i<= to) {
					configuration->intentActive[i]=1;
				} else {
					configuration->intentActive[i]=0;
				}
			}
		} else {
			for (i=0;i<16;i++) configuration->intentActive[i]=0;
			configuration->intentActive[atoi(info)]=1;
		}
	}
}

/**
 * Displays the help message with usage information
 */
static void displayHelp() {
	printf("Epiphany Python version %s\n", VERSION_IDENT);
	printf("epython [arguments] filename\n\nWhere filename is the source code to execute by default on all cores\n\nArguments\n--------\n");
#ifndef HOST_STANDALONE
	printf("-c placement   Specify core placement; can be a single id, all, a range (a:b) or a list (a,b,c,d)\n");
	printf("-d processes   Specify number of process on the device\n");
	printf("-h processes   Specify number of process on the host\n");
	printf("-t             Display core run timing information\n");
	printf("-codecore      Placement code on each core (default up to %d bytes length)\n", CORE_CODE_MAX_SIZE);
	printf("-codeshared    Placement code in shared memory (automatic after %d bytes in length)\n", CORE_CODE_MAX_SIZE);
	printf("-datashared    Data (arrays and strings) stored in shared memory, storage on core is default\n");
        printf("-elf           Use ELF device executable\n");
        printf("-srec          Use SREC device executable\n");
#endif
	printf("-s             Display parse statistics\n");
	printf("-pp            Display preprocessed code\n");
	printf("-o filename    Write out the compiled byte representation of processed Python code and exits (does not run code)\n");
	printf("-l filename    Loads from compiled byte representation of code and runs this\n");
	printf("-help          Display this help and quit\n");
}

/**
 * Tests two strings for equality, ignoring the case - this is for case insensitive variable name matching
 */
static int areStringsEqualIgnoreCase(char * s1, char * s2) {
	size_t s1_len=strlen(s1), s2_len=strlen(s2), i;
	if (s1_len != s2_len) return 0;
	for (i=0;i<s1_len;i++) {
		if (tolower(s1[i]) != tolower(s2[i])) return 0;
	}
	return 1;
}
