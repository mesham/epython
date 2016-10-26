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

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include "python_interoperability.h"
#include "../shared.h"
#include "configuration.h"
#include "interpreter.h"
#include "host-functions.h"
#include "functions.h"
#include "misc.h"

#define LISTENER_PIPE_NAME "toepython"
#define WRITER_PIPE_NAME "fromepython"

enum command {SEND, RECV, NUMCORES, COREID, NONE, SYNC, REDUCE, BCAST, EXIT, SENDRECV};

static char * buffered_line;
static int listener_pipe_handle, writer_pipe_handle;

static void initialise_namedPipes(void);
static enum command blockOnCommand(pthread_t*);
static void issueSend(struct interpreterconfiguration*);
static void issueRecv(struct interpreterconfiguration*);
static void issueNumcores(struct interpreterconfiguration*);
static void issueCoreId(struct interpreterconfiguration*);
static void issueSync(void);
static void issueReduce(struct interpreterconfiguration*);
static void issueBcast(struct interpreterconfiguration*);
static void issueSendRecv(struct interpreterconfiguration*);

/**
 * Runs interactivity with full Python on this host CPU, will send over commands to different Epiphany cores
 */
void runFullPythonInteractivityOnHost(struct interpreterconfiguration* configuration, struct shared_basic * basicState, pthread_t* emanagementThread) {
	initialise_namedPipes();
	initHostCommunicationData(1, basicState);
	while (1==1) {
		enum command cmd=blockOnCommand(emanagementThread);
		if (cmd == SEND) issueSend(configuration);
		if (cmd == RECV) issueRecv(configuration);
		if (cmd == NUMCORES) issueNumcores(configuration);
		if (cmd == COREID) issueCoreId(configuration);
		if (cmd == SYNC) issueSync();
		if (cmd == REDUCE) issueReduce(configuration);
		if (cmd == BCAST) issueBcast(configuration);
		if (cmd == SENDRECV) issueSendRecv(configuration);
		if (cmd == EXIT) return;
	}
}

/**
 * Retrieves the overall number of cores
 */
static void issueNumcores(struct interpreterconfiguration* configuration) {
	char dataToWrite[20];
	sprintf(dataToWrite, "%d", configuration->hostProcs + configuration->coreProcs);
	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Retrieves my Core ID
 */
static void issueCoreId(struct interpreterconfiguration* configuration) {
	char dataToWrite[20];
	sprintf(dataToWrite, "%d", configuration->coreProcs);
	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Issues a synchronisation
 */
static void issueSync(void) {
	syncCores(1, 0);
	char dataToWrite[20];
	sprintf(dataToWrite, "0");
	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Issues a broadcast and sends the results back over
 */
static void issueBcast(struct interpreterconfiguration* configuration) {
	int root=atoi(strtok(NULL, " "));
	int type=atoi(strtok(NULL, " "));
	int dtype=atoi(strtok(NULL, " "));
	struct value_defn valueToSend;
	valueToSend.dtype=(char) dtype;
	if (type == INT_TYPE) {
		valueToSend.type=INT_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
	} else if (type == REAL_TYPE) {
		valueToSend.type=REAL_TYPE;
		float data=atof(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(float));
	} else if (type == BOOLEAN_TYPE) {
		valueToSend.type=BOOLEAN_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
	}

	struct value_defn bcastedData=bcastData(valueToSend, root, 0, configuration->hostProcs + configuration->coreProcs, configuration->coreProcs);

	char dataToWrite[50];
	if (bcastedData.type==INT_TYPE || bcastedData.type==BOOLEAN_TYPE) {
        int i_v;
        memcpy(&i_v, bcastedData.data, sizeof(int));
		sprintf(dataToWrite, "%d %d %d", bcastedData.type, bcastedData.dtype, i_v);
	} else if (bcastedData.type==REAL_TYPE) {
	    float f_v;
	    memcpy(&f_v, bcastedData.data, sizeof(float));
	    double d=f_v;
		sprintf(dataToWrite, "%d %d %f", bcastedData.type, bcastedData.dtype, d);
	}

	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Issues a reduce and sends the results back over
 */
static void issueReduce(struct interpreterconfiguration* configuration) {
	int operator=atoi(strtok(NULL, " "));
	int type=atoi(strtok(NULL, " "));
	int dtype=atoi(strtok(NULL, " "));
	struct value_defn valueToSend;
	valueToSend.dtype=(char) dtype;
	if (type == INT_TYPE) {
		valueToSend.type=INT_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
	} else if (type == REAL_TYPE) {
		valueToSend.type=REAL_TYPE;
		float data=atof(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(float));
	} else if (type == BOOLEAN_TYPE) {
		valueToSend.type=BOOLEAN_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
	}
	struct value_defn reducedData=reduceData(valueToSend, (char) operator, 0, configuration->hostProcs + configuration->coreProcs, configuration->coreProcs);
	char dataToWrite[50];
	if (reducedData.type==INT_TYPE || reducedData.type==BOOLEAN_TYPE) {
        int i_v;
        memcpy(&i_v, reducedData.data, sizeof(int));
		sprintf(dataToWrite, "%d %d %d", reducedData.type, reducedData.dtype, i_v);
	} else if (reducedData.type==REAL_TYPE) {
	    float f_v;
	    memcpy(&f_v, reducedData.data, sizeof(float));
		double d=f_v;
		sprintf(dataToWrite, "%d %d %f", reducedData.type, reducedData.dtype, d);
	}

	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Issues a send recv and send the results back over
 */
static void issueSendRecv(struct interpreterconfiguration* configuration) {
	int target=atoi(strtok(NULL, " "));
	int type=atoi(strtok(NULL, " "));
	int dtype=atoi(strtok(NULL, " "));
	struct value_defn valueToSend;
	valueToSend.dtype=(char) dtype;
	if (type == INT_TYPE) {
		valueToSend.type=INT_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
		printf("Send integer %d to %d\n", data, target);
	} else if (type == REAL_TYPE) {
		valueToSend.type=REAL_TYPE;
		float data=atof(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(float));
		printf("Send real %f to %d\n", data, target);
	} else if (type == BOOLEAN_TYPE) {
		valueToSend.type=BOOLEAN_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
		printf("Send boolean %d to %d\n", data, target);
	}
	struct value_defn valToReturn=sendRecvData(valueToSend, target, 0, configuration->coreProcs);
	char dataToWrite[50];
	if (valToReturn.type==INT_TYPE || valToReturn.type==BOOLEAN_TYPE) {
        int i_v;
        memcpy(&i_v, valToReturn.data, sizeof(int));
		sprintf(dataToWrite, "%d %d %d", valToReturn.type, valToReturn.dtype, i_v);
	} else if (valToReturn.type==REAL_TYPE) {
		float f_v;
	    memcpy(&f_v, valToReturn.data, sizeof(float));
		double d=f_v;
		sprintf(dataToWrite, "%d %d %f", valToReturn.type, valToReturn.dtype, d);
	}

	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing data to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Issues a send from Python
 */
static void issueSend(struct interpreterconfiguration* configuration) {
	int target=atoi(strtok(NULL, " "));
	int type=atoi(strtok(NULL, " "));
	int dtype=atoi(strtok(NULL, " "));
	struct value_defn valueToSend;
	valueToSend.dtype=(char) dtype;
	if (type == INT_TYPE) {
		valueToSend.type=INT_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
		printf("Send integer %d to %d\n", data, target);
	} else if (type == REAL_TYPE) {
		valueToSend.type=REAL_TYPE;
		float data=atof(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(float));
		printf("Send real %f to %d\n", data, target);
	} else if (type == BOOLEAN_TYPE) {
		valueToSend.type=BOOLEAN_TYPE;
		int data=atoi(strtok(NULL, " "));
		memcpy(&valueToSend.data, &data, sizeof(int));
		printf("Send boolean %d to %d\n", data, target);
	}
	sendData(valueToSend, target, 0, configuration->coreProcs);
}

/**
 * Issues a receive and sends the results back over
 */
static void issueRecv(struct interpreterconfiguration* configuration) {
	int target=atoi(strtok(NULL, " "));
	struct value_defn valToReturn=recvData(target, 0, configuration->coreProcs);
	char dataToWrite[50];
	if (valToReturn.type==INT_TYPE || valToReturn.type==BOOLEAN_TYPE) {
        int i_v;
        memcpy(&i_v, valToReturn.data, sizeof(int));
		sprintf(dataToWrite, "%d %d %d", valToReturn.type, valToReturn.dtype, i_v);
	} else if (valToReturn.type==REAL_TYPE) {
		float f_v;
	    memcpy(&f_v, valToReturn.data, sizeof(float));
		double d=f_v;
		sprintf(dataToWrite, "%d %d %f", valToReturn.type, valToReturn.dtype, d);
	}

	errorCheck(write(writer_pipe_handle, dataToWrite, strlen(dataToWrite)), "Writing recv to python pipe");
	fsync(writer_pipe_handle);
}

/**
 * Blocks for either a message on the pipe which commands some action or all the Epiphany cores to have finished
 */
static enum command blockOnCommand(pthread_t* emanagementthread) {
	int i;
	struct pollfd ufds[1];
	ufds[0].fd = listener_pipe_handle;
	ufds[0].events = POLLIN | POLLPRI;
	int retVal=0;
	while ((retVal=poll(ufds, 1, 500))< 1) {
		if (retVal == 0 && emanagementthread != NULL) {
			if (pthread_kill(*emanagementthread, 0) != 0) return EXIT;
		}
	}
	for (i = 0; i < 1024; i++) {
		errorCheck(read(listener_pipe_handle, &buffered_line[i], 1), "Reading python pipe");
		if (buffered_line[i] == '\n') {
			buffered_line[i] = '\0';
			break;
		}
	}
	char * commandStr=strtok(buffered_line, " ");
	if (strcmp(commandStr, "1") == 0) return SEND;
	if (strcmp(commandStr, "2") == 0) return RECV;
	if (strcmp(commandStr, "3") == 0) return NUMCORES;
	if (strcmp(commandStr, "4") == 0) return COREID;
	if (strcmp(commandStr, "5") == 0) return SYNC;
	if (strcmp(commandStr, "6") == 0) return REDUCE;
	if (strcmp(commandStr, "7") == 0) return BCAST;
	if (strcmp(commandStr, "8") == 0) return SENDRECV;
	return NONE;
}

/**
 * Initialises the named pipes ready for communication from Python
 */
static void initialise_namedPipes(void) {
	mkfifo(LISTENER_PIPE_NAME, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	mkfifo(WRITER_PIPE_NAME, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

	listener_pipe_handle=open(LISTENER_PIPE_NAME, O_RDWR | O_NONBLOCK);
	writer_pipe_handle=open(WRITER_PIPE_NAME, O_RDWR | O_NONBLOCK);

	buffered_line = (char*)malloc(1024);
}
