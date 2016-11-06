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

#ifndef MISC_H_
#define MISC_H_

#define SQRT_MATHS_OP 0
#define SIN_MATHS_OP 1
#define COS_MATHS_OP 2
#define TAN_MATHS_OP 3
#define ASIN_MATHS_OP 4
#define ACOS_MATHS_OP 5
#define ATAN_MATHS_OP 6
#define SINH_MATHS_OP 7
#define COSH_MATHS_OP 8
#define TANH_MATHS_OP 9
#define FLOOR_MATHS_OP 10
#define CEIL_MATHS_OP 11
#define LOG_MATHS_OP 12
#define LOG10_MATHS_OP 13
#define RANDOM_MATHS_OP 14

void errorCheck(int, char*);
char* translateErrorCodeToMessage(unsigned char);

#endif /* CONFIGURATION_H_ */
