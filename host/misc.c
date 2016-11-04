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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "basictokens.h"

void errorCheck(int value, char * errorMessage) {
    if (value == -1) {
        fprintf(stderr, "Error: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}

char* translateErrorCodeToMessage(unsigned char errorCode) {
    char * errorMessage=NULL;
    switch (errorCode) {
    case ERR_STR_ONLYTEST_EQ:
        errorMessage="Can only test for equality with strings";
        break;
    case ERR_NONE_ONLYTEST_EQ:
        errorMessage="Can only test for equality with none";
        break;
    case ERR_ONLY_ADDITION_STR:
        errorMessage="Can only perform addition with strings";
        break;
    case ERR_TOO_MANY_ARR_INDEX:
        errorMessage="Too many array indexes in expression";
        break;
    case ERR_NEG_ARR_INDEX:
        errorMessage="Not allowed negative array indexes";
        break;
    case ERR_ARR_INDEX_EXCEED_SIZE:
        errorMessage="Array index in expression exceeds array size in that dimension";
        break;
    case ERR_ONLY_DISPLAY_STR_WITH_INPUT:
        errorMessage="Can only display strings with input statement";
        break;
    case ERR_OUT_OF_SHARED_HEAP_MEM:
        errorMessage="Out of shared heap memory for data";
        break;
    case ERR_OUT_OF_CORE_SHARED_HEAP_MEM:
        errorMessage="Out of core and shared heap memory for data";
        break;
    case ERR_OUT_OF_SHARED_STACK_MEM:
        errorMessage="Out of shared stack memory for data";
        break;
    case ERR_OUT_OF_CORE_SHARED_STACK_MEM:
        errorMessage="Out of core and shared stack memory for data";
        break;
    case ERR_ONLY_SEND_INT_AND_REAL:
        errorMessage="Can only send integers and reals between cores";
        break;
    case ERR_SEND_TO_UNKNOWN_CORE:
        errorMessage="Attempting to send to non-existent or inactive process";
        break;
    case ERR_SEND_TO_INACTIVE_CORE:
        errorMessage="Attempting to send to inactive core";
        break;
    case ERR_RECV_FROM_UNKNOWN_CORE:
        errorMessage="Attempting to receive from non-existent or inactive process";
        break;
    case ERR_RECV_FROM_INACTIVE_CORE:
        errorMessage="Attempting to receive from inactive core";
        break;
    case ERR_SENDRECV_WITH_UNKNOWN_CORE:
        errorMessage="Attempting to sendrecv with non-existent or inactive process";
        break;
    case ERR_FREE_ON_NON_HEAP:
        errorMessage="Attempting to free non allocated heap memory";
        break;
    case ERR_INCORRECT_NUM_NATIVE_PARAMS:
        errorMessage="Incorrect number of parameters provided to native function call";
        break;
    case ERR_UNKNOWN_NATIVE_COMMAND:
        errorMessage="Unknown native command supplied to runtime library";
        break;
    }
    if (errorMessage != NULL) {
        char * msgToRet=(char*) malloc(strlen(errorMessage) + 1);
        strcpy(msgToRet, errorMessage);
        return msgToRet;
    } else {
        errorMessage="Unknown error code of";
        char * msgToRet=(char*) malloc(strlen(errorMessage) + 10);
        sprintf(msgToRet, "%s 0x%x", errorMessage, errorCode);
        return msgToRet;
    }
}
