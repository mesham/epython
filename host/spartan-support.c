/*
 * Copyright (c) 2017, Nick Brown
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

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "spartan-support.h"
#include "configuration.h"
#include "memorymanager.h"

#define BUFFER_SIZE 1024
#define DEBUG_SPARTAN 0

static char * portname = "/dev/ttyUSB1";
static char * buffer;
static int buffer_entries, buffer_point, spartan_fd;

static int set_interface_attribs(int, int, int);
static void set_blocking(int, int);
static void transmitIntegerToSpartan(int, int);
static int blockForMessage(int);
static char getCommand(int);

void loadCodeOntoSpartan(struct interpreterconfiguration* configuration) {
  spartan_fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
  if (spartan_fd < 0) {
    printf("error %d opening %s: %s", errno, portname, strerror (errno));
    return;
  }

  buffer=(char*) malloc(BUFFER_SIZE);

  set_interface_attribs (spartan_fd, B9600, 0);
  set_blocking (spartan_fd, 0);

  transmitIntegerToSpartan(spartan_fd, getMemoryFilledSize());
  tcdrain(spartan_fd);

  write(spartan_fd, getAssembledCode(), getMemoryFilledSize());
  tcdrain(spartan_fd);

  buffer_entries=0;
  buffer_point=0;

  char waitingForBooted=0x00;
  while (waitingForBooted != 0x01) {
    waitingForBooted=getCommand(spartan_fd);
  }
#if DEBUG_SPARTAN == 1
  printf("Spartan loaded byte code and executing\n");
#endif
}

void monitorSpartan(struct shared_basic * basicState, struct interpreterconfiguration* configuration) {
  while (1==1) {
    char commandReceived=getCommand(spartan_fd);
    if (commandReceived == 0x02) {
#if DEBUG_SPARTAN == 1
        printf("Exit command from Spartan\n");
#endif
        close(spartan_fd);
        return;
    }
  }
}

static char getCommand(int fd) {
  int buffer_idx=blockForMessage(fd);
  return buffer[buffer_idx];
}

static int blockForMessage(int fd) {
  if (buffer_point < buffer_entries) {
    buffer_point++;
  } else {
    buffer_entries=buffer_point=0;
    while (buffer_entries == 0) buffer_entries=read(fd, buffer, BUFFER_SIZE);
  }
  return buffer_point;
}

static void transmitIntegerToSpartan(int fd, int to_send) {
  unsigned char bytes[4];
  bytes[0] = (to_send >> 24) & 0xFF;
  bytes[1] = (to_send >> 16) & 0xFF;
  bytes[2] = (to_send >> 8) & 0xFF;
  bytes[3] = to_send & 0xFF;

  write (fd, bytes, 4);
}

static int set_interface_attribs(int fd, int speed, int parity) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
    printf("error %d from tcgetattr", errno);
    return -1;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;         /* 8-bit characters */
  tty.c_cflag &= ~PARENB;     /* no parity bit */
  tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
  //tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

  /* setup for non-canonical mode */
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  tty.c_oflag &= ~OPOST;

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    printf("error %d from tcsetattr", errno);
    return -1;
  }
  return 0;
}

static void set_blocking(int fd, int should_block) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
    printf("error %d from tggetattr", errno);
    return;
  }

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  if (tcsetattr (fd, TCSANOW, &tty) != 0) printf("error %d setting term attributes", errno);
}
