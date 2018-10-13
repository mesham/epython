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

#include "microblaze-shared.h"
#include "interpreter.h"
#include "main.h"
#include "functions.h"
#include "mb_interface.h"

#define BOOTSTRAP_MAILBOX_ADDR 0xB800

volatile struct shared_basic * sharedData;
volatile unsigned char syncValues[TOTAL_CORES];
int myId, lowestCoreId;

/**
 * Core entry point, sets the stuff up and then runs the interpreter
 */
int main() {
  volatile int * data=(int*) BOOTSTRAP_MAILBOX_ADDR;
  myId=data[0];
  sharedData=(struct shared_basic *) (data[1] | 0x20000000);

  if (sharedData->core_ctrl[myId].core_run == 0) {
    microblaze_invalidate_dcache_range((u32) &(sharedData->core_ctrl[myId].core_run), 4);
    while (sharedData->core_ctrl[myId].core_run == 0) { }
  }
  sharedData->core_ctrl[myId].core_busy=1;
	sharedData->core_ctrl[myId].core_run=1;

	int i;
	lowestCoreId=TOTAL_CORES;
	for (i=0;i<TOTAL_CORES;i++) {
		syncValues[i]=0;
		if (sharedData->core_ctrl[i].active) {
			if (i< lowestCoreId) lowestCoreId=i;
		}
	}

  if (sharedData->codeOnCores) {
    cpy(sharedData->edata, sharedData->esdata, sharedData->length);
  }

  runIntepreter(sharedData->edata, sharedData->length, sharedData->symbol_size, myId, sharedData->num_procs, sharedData->baseHostPid);
  sharedData->core_ctrl[myId].core_busy=0;
	sharedData->core_ctrl[myId].core_run=0;
  return 0;
}
