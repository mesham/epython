/*
 * stack.h
 *
 *  Created on: 9 July 2015
 *      Author: Nick Brown
 */

#ifndef HOST_STACK_H_
#define HOST_STACK_H_

#define INITIAL_STACK_SIZE 10

struct stack_t {
    int size, width, *data;
};

void initStack(struct stack_t*);
int pop(struct stack_t*);
void push(struct stack_t*, int);
int peek(struct stack_t*);

#endif /* HOST_STACK_H_ */
