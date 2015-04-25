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

static void parseCommandLineArguments(struct ebasicconfiguration*, int, char**);
static void parseCoreActiveInfo(struct ebasicconfiguration*, char*);
static int areStringsEqualIgnoreCase(char*, char*);
static void displayHelp(void);

/**
 * Given the command line arguments this will read the configuration and return the configuration structure
 * which has the appropriate flags set and contains strings etc
 */
struct ebasicconfiguration* readConfiguration(int argc, char *argv[]) {
	int i;
	struct ebasicconfiguration* configuration=(struct ebasicconfiguration*) malloc(sizeof(struct ebasicconfiguration));
	configuration->intentActive=(char*) malloc(TOTAL_CORES);
	for (i=0;i<TOTAL_CORES;i++) configuration->intentActive[i]=1;
	configuration->displayStats=configuration->displayTiming=configuration->forceCodeOnCore=configuration->forceCodeOnShared=configuration->forceDataOnShared=0;
	configuration->filename=configuration->compiledByteFilename=configuration->loadByteFilename=NULL;
	parseCommandLineArguments(configuration, argc, argv);
	return configuration;
}

/**
 * Parses command line arguments
 */
static void parseCommandLineArguments(struct ebasicconfiguration* configuration, int argc, char *argv[]) {
	if (argc == 1) {
		displayHelp();
		exit(0);
	} else {
#ifdef HOST_STANDALONE
		configuration->hostProcs=1;
#else
		configuration->hostProcs=0;
#endif
		int i;
		for (i=1;i<argc;i++) {
			if (areStringsEqualIgnoreCase(argv[i], "-s")) {
				configuration->displayStats=1;
			} else if (areStringsEqualIgnoreCase(argv[i], "-t")) {
				configuration->displayTiming=1;
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
					configuration->hostProcs=atoi(argv[++i]);
				}
			} else if (areStringsEqualIgnoreCase(argv[i], "-c")) {
				if (i+1 ==argc) {
					fprintf(stderr, "When specifying core placement you must provide arguments\n");
					exit(0);
				} else {
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
		if (configuration->loadByteFilename == NULL && configuration->filename == NULL) {
			fprintf(stderr, "You must supply a file to run as an argument, see -h for details\n");
			exit(0);
		}
	}
}

/**
 * Determines the active cores if the user supplied -c n, can be a single integer, a list, a range or
 * all to select all cores
 */
static void parseCoreActiveInfo(struct ebasicconfiguration* configuration, char * info) {
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
	printf("Epiphany BASIC version %s\n", VERSION_IDENT);
	printf("ebasic [arguments] filename\n\nWhere filename is the source code to execute by default on all cores\n\nArguments\n--------\n");
#ifndef HOST_STANDALONE
	printf("-c placement   Specify core placement; can be a single id, all, a range (a:b) or a list (a,b,c,d)\n");
	printf("-h processes   Specify number of process on the host\n");
	printf("-t             Display core run timing information\n");
	printf("-codecore      Placement code on each core (default up to %d bytes length)\n", CORE_CODE_MAX_SIZE);
	printf("-codeshared    Placement code in shared memory (automatic after %d bytes in length)\n", CORE_CODE_MAX_SIZE);
	printf("-datashared    Data (arrays and strings) stored in shared memory, storage on core is default\n");
#endif
	printf("-s             Display parse statistics\n");
	printf("-o filename    Write out the compiled byte representation of processed BASIC code and exits (does not run code)\n");
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
