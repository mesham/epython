/*
 * Copyright (c) 2018, Nick Brown
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

#ifndef MICROBLAZE_SHARED_H_
#define MICROBLAZE_SHARED_H_

#define TOTAL_CORES 3
// Start location in shared memory where we place the data structures
#define EXTERNAL_MEM_ABSOLUTE_START 0x01000000

#define SHARED_HEAP_DATA_AREA_PER_CORE 0x6D600
#define SHARED_STACK_DATA_AREA_PER_CORE 0xFA00
#define SHARED_DATA_AREA_START 0x00200000
#define SHARED_CODE_AREA_START 0x00100000
#define SHARED_DATA_SIZE 0x01000000
#define LOCAL_CORE_MEMORY_MAP_TOP 0x10000
#define LOCAL_CORE_STACK_SIZE 0x400

struct core_ctrl {
	unsigned int core_run, core_busy, core_command;
	char *symbol_table, *stack_start, *heap_start,
			*shared_heap_start, *shared_stack_start, *postbox_start,
			*host_shared_data_start;
	char data[15];
	char active;
} __attribute__((aligned(8)));

struct shared_basic {
	struct core_ctrl core_ctrl[16];
	unsigned int length, num_procs, baseHostPid;
	unsigned short symbol_size;
	char *edata, *data, *esdata, allInSharedMemory, codeOnCores;
} __attribute__((aligned(8)));

#endif /* MICROBLAZE_SHARED_H_ */
