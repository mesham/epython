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

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libxlnk_cma.h"
#include "microblaze-support.h"
#include "memorymanager.h"
#include "configuration.h"

#define PROGRAM_NAME "epython-microblaze.bin"
#define ADDRESS_BASE 0x40000000
#define ADDRESS_RANGE 65536
#define SHARED_MEMORY_SIZE 1024 * 1024

struct gpio_state {
  int index, direction; // direction is 0 for out and 1 for everything else (specifically in)
  char * filename;
};

struct mmio_state {
  char * buffer;
  int file_handle;
  unsigned int length, address_base, virt_base, virt_offset;
};

static void place_ePythonVMOnMicroblaze(char*);
static struct mmio_state * createMMIO(unsigned int, unsigned int);
static void closeMMIO(struct mmio_state*);
static void writeMMIO(struct mmio_state*, unsigned int, void*, unsigned int);
static void readMMIO(struct mmio_state*, unsigned int, void*, unsigned int);
static struct gpio_state * openGPIO(int, char*);
static void writeGPIO(struct gpio_state*, int);
static int readGPIO(struct gpio_state*);
static void closeGPIO(struct gpio_state*);

struct gpio_state * reset_pin;
struct mmio_state * microblaze_memory;
char * shared_buffer;

struct shared_basic * loadCodeOntoMicroblaze(struct interpreterconfiguration* configuration) {
  struct shared_basic * basicCode;
  reset_pin=openGPIO(960, "out");
  microblaze_memory=createMMIO(ADDRESS_BASE, ADDRESS_RANGE);

  writeGPIO(reset_pin, 1); // Reset Microblaze
  place_ePythonVMOnMicroblaze(PROGRAM_NAME);

  shared_buffer=(char*) cma_alloc(SHARED_MEMORY_SIZE, 0);
  unsigned int physical_address=cma_get_phy_addr((void*) shared_buffer);
  writeMMIO(microblaze_memory, 0xF004, &physical_address, 4);
  int busy_flag=1;
  writeMMIO(microblaze_memory, 0xF000, &busy_flag, 4);

  basicCode=(void*) shared_buffer;
  basicCode->length=getMemoryFilledSize();

  writeGPIO(reset_pin, 0); // Run code on Microblaze
  while (busy_flag != 0) {
    readMMIO(microblaze_memory, 0xF000, &busy_flag, 4);
  }
  return basicCode;
}

void monitorMicroblaze(struct shared_basic * basicState, struct interpreterconfiguration * configuration) {

}

void finaliseMicroblaze(void) {
  cma_free(shared_buffer);
  closeMMIO(microblaze_memory);
  closeGPIO(reset_pin);
}

static void place_ePythonVMOnMicroblaze(char * exec_name) {
  int handle=open(exec_name, O_RDONLY);
  struct stat st;
  fstat(handle, &st);
  int code_size =ceil(st.st_size /getpagesize()) * getpagesize();
  char * exec_buffer=(char*) malloc(code_size);
  read(handle, exec_buffer, code_size);
  writeMMIO(microblaze_memory, 0, exec_buffer, code_size);
  free(exec_buffer);
  close(handle);
}

static struct mmio_state * createMMIO(unsigned int address_base, unsigned int length) {
  struct mmio_state * state=(struct mmio_state *) malloc(sizeof(struct mmio_state));
  // Align the base address with the pages
  state->virt_base = address_base & ~(getpagesize() - 1);
  state->virt_offset = address_base - state->virt_base;
  state->length=length;
  state->address_base=address_base;

  state->file_handle=open("/dev/mem", O_RDWR | O_SYNC);
  state->buffer=mmap(NULL, length+state->virt_offset, PROT_READ | PROT_WRITE, MAP_SHARED, state->file_handle, state->virt_base);
  return state;
}

static void closeMMIO(struct mmio_state * state) {
  close(state->file_handle);
  free(state);
}

static void writeMMIO(struct mmio_state * state, unsigned int offset, void * data, unsigned int size_data) {
  memcpy(&(state->buffer[offset]), data, size_data);
}

static void readMMIO(struct mmio_state * state, unsigned int offset, void * data, unsigned int size_data) {
  memcpy(data, &(state->buffer[offset]), size_data);
}

static struct gpio_state * openGPIO(int index, char * direction) {
  struct gpio_state * state = (struct gpio_state *) malloc(sizeof(struct gpio_state));
  state->index=index;
  state->direction=strcmp(direction, "out");

  char path[150];
  sprintf(path, "/sys/class/gpio/gpio%d", index);
  if (access(path, F_OK) == -1 ) {
   FILE * create_handle=fopen("/sys/class/gpio/export", "w");
   fprintf(create_handle, "%d", index);
   fclose(create_handle);
  }
  char f_name[150];
  sprintf(f_name,"%s/direction", path);
  FILE * handle=fopen(f_name, "w");
  fprintf(handle, "%s", direction);
  fclose(handle);

  state->filename=(char*) malloc(strlen(path) + 7);
  sprintf(state->filename,"%s/value", path);
  return state;
}

static void writeGPIO(struct gpio_state * state, int val) {
  FILE * file_handle=fopen(state->filename, state->direction==0 ? "w" : "r");
  fprintf(file_handle, "%d", val);
  fclose(file_handle);
}

static int readGPIO(struct gpio_state * state) {
  FILE * file_handle=fopen(state->filename, state->direction==0 ? "w" : "r");
  int val=fgetc(file_handle);
  fclose(file_handle);
  return val;
}

static void closeGPIO(struct gpio_state * state) {
  FILE * handle=fopen("/sys/class/gpio/unexport", "w");
  fprintf(handle, "%d", state->index);
  fclose(handle);
  free(state->filename);
  free(state);
}
