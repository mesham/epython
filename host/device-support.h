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

#include "shared.h"
#include "configuration.h"

#ifndef DEVICE_SUPPORT_H_
#define DEVICE_SUPPORT_H_

#define SHARED_DATA_AREA_PER_CORE 0x0007D000
#define SHARED_DATA_AREA_START 0x00200000
#define SHARED_CODE_AREA_START 0x00100000
#define SHARED_DATA_SIZE 0x01000000

#define EPIPHANY_BINARY_FILE "ebasic-device.srec"
// Binary directory path for finding ebasic device binary, needs trailing slash
#define BIN_PATH "/usr/bin/"

// Memory location for each core where we start the symbol table, bytecode, data area etc...
#define CORE_DATA_START 0x6000
// If the length of BASIC byte code is greater than this then place in shared memory (unless overridden by command line)
#define CORE_CODE_MAX_SIZE 2048

struct shared_basic * loadCodeOntoEpiphany(struct ebasicconfiguration*);
void monitorCores(struct shared_basic*, struct ebasicconfiguration*);
void finaliseCores(void);

#endif /* DEVICE_SUPPORT_H_ */
