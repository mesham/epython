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

#ifndef BASICTOKENS_H_
#define BASICTOKENS_H_

#define LET_TOKEN 0x00
#define PRINT_TOKEN 0x01
#define STOP_TOKEN 0x02
#define OR_TOKEN 0x03
#define AND_TOKEN 0x04
#define EQ_TOKEN 0x05
#define NEQ_TOKEN 0x06
#define LT_TOKEN 0x07
#define GT_TOKEN 0x08
#define LEQ_TOKEN 0x09
#define GEQ_TOKEN 0x0A
#define ADD_TOKEN 0x0B
#define SUB_TOKEN 0x0C
#define MUL_TOKEN 0x0D
#define DIV_TOKEN 0x0E
#define MOD_TOKEN 0x0F
#define IDENTIFIER_TOKEN 0x10
#define REAL_TOKEN 0x11
#define STRING_TOKEN 0x12
#define INTEGER_TOKEN 0x13
#define IF_TOKEN 0x14
#define FOR_TOKEN 0x15
#define GOTO_TOKEN 0x16
#define INPUT_TOKEN 0x17
#define COREID_TOKEN 0x18
#define DIMARRAY_TOKEN 0x19
#define ARRAYACCESS_TOKEN 0x1A
#define ARRAYSET_TOKEN 0x1B
#define SEND_TOKEN 0x1C
#define RECV_TOKEN 0x1D
#define IFELSE_TOKEN 0x1E
#define POW_TOKEN 0x20
#define MATHS_TOKEN 0x21
#define RANDOM_TOKEN 0x22
#define DIMSHAREDARRAY_TOKEN 0x23
#define SYNC_TOKEN 0x24
#define BCAST_TOKEN 0x25
#define REDUCTION_TOKEN 0x26
#define INPUT_STRING_TOKEN 0x27
#define SENDRECV_TOKEN 0x28
#define NUMCORES_TOKEN 0x2A
#define ISHOST_TOKEN 0x2B
#define ISDEVICE_TOKEN 0x2C
#define RETURN_TOKEN 0x2D
#define FNCALL_TOKEN 0x2E
#define RETURN_EXP_TOKEN 0x2F
#define BOOLEAN_TOKEN 0x30
#define LEN_TOKEN 0x31
#define LETNOALIAS_TOKEN 0x32
#define NONE_TOKEN 0x33
#define IS_TOKEN 0x34
#define ARRAY_TOKEN 0x35
#define NOT_TOKEN 0x036
#define NUMDIM_TOKEN 0x37
#define DSIZE_TOKEN 0x38

#define SQRT_MATHS_OP 0x00
#define SIN_MATHS_OP 0x01
#define COS_MATHS_OP 0x02
#define TAN_MATHS_OP 0x03
#define ASIN_MATHS_OP 0x04
#define ACOS_MATHS_OP 0x05
#define ATAN_MATHS_OP 0x06
#define SINH_MATHS_OP 0x07
#define COSH_MATHS_OP 0x08
#define TANH_MATHS_OP 0x09
#define FLOOR_MATHS_OP 0x0A
#define CEIL_MATHS_OP 0x0B
#define LOG_MATHS_OP 0x0C
#define LOG10_MATHS_OP 0x0D
#define RANDOM_MATHS_OP 0x0E

#endif /* BASICTOKENS_H_ */
