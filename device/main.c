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

#include <e-lib.h>
#include "shared.h"
#include "interpreter.h"
#include "main.h"
#include "functions.h"

volatile e_barrier_t syncbarriers[TOTAL_CORES], collectivebarriers[TOTAL_CORES];
e_barrier_t *sync_tgt_bars[TOTAL_CORES], *collective_tgt_bars[TOTAL_CORES];
volatile unsigned char syncValues[TOTAL_CORES];
volatile struct shared_basic * sharedData;
int myId, lowestCoreId;

static void init_barrier(volatile e_barrier_t[], e_barrier_t *[]);

/**
 * Core entry point, sets the stuff up and then runs the interpreter
 */
int main() {
	myId=e_group_config.core_row * e_group_config.group_cols + e_group_config.core_col;
	sharedData=(void*) (e_emem_config.base + EXTERNAL_MEM_ABSOLUTE_START);

	while (sharedData->core_ctrl[myId].core_run == 0) {};
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

	init_barrier(syncbarriers, sync_tgt_bars);
	init_barrier(collectivebarriers, collective_tgt_bars);

	if (sharedData->codeOnCores) {
		cpy(sharedData->edata, sharedData->esdata, sharedData->length);
	}

	syncCores();
	processAssembledCode(sharedData->edata, sharedData->length, sharedData->symbol_size, myId, sharedData->num_procs, sharedData->baseHostPid);
	sharedData->core_ctrl[myId].core_busy=0;
	sharedData->core_ctrl[myId].core_run=0;
	return 0;
}

/**
 * Initialises an Epiphany barrier, this is based upon the version in elib, but works when core 0 is not in use
 * and over a subset of cores
 */
static void init_barrier(volatile e_barrier_t barrier_array[], e_barrier_t  * target_barrier_array[]) {
	int i, row, col;
	for (i=0; i<TOTAL_CORES; i++)
		barrier_array[i] = 0;

	if (myId == lowestCoreId) {
		for (i=0; i<TOTAL_CORES; i++) {
			row=i/e_group_config.group_cols;
			col=i-(row*e_group_config.group_cols);
			target_barrier_array[i] = (e_barrier_t *) e_get_global_address(row, col, (void *) &(barrier_array[0]));
		}
	} else {
		row=lowestCoreId/e_group_config.group_cols;
		col=lowestCoreId-(row*e_group_config.group_cols);
		target_barrier_array[0] = (e_barrier_t *) e_get_global_address(row, col, (void *) &(barrier_array[myId]));
	}
}
