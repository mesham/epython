/*
 * stack.c
 *
 *  Created on: 9 July 2015
 *      Author: Nick Brown
 */

#include <stdlib.h>
#include "stack.h"

void initStack(struct stack_t* stack) {
    stack->width=INITIAL_STACK_SIZE;
    stack->size=0;
    stack->data=(int*) malloc(sizeof(int) * INITIAL_STACK_SIZE);
}

int pop(struct stack_t* stack) {
   if (stack->size > 0) {
       return stack->data[--stack->size];
   }
   return -1;
}

void push(struct stack_t* stack, int val) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(int*) realloc(&stack->data, sizeof(int) * stack->width);
    }
    stack->data[stack->size-1]=val;
}

int peek(struct stack_t* stack) {
	if (stack->size > 0) {
		return stack->data[stack->size-1];
	}
	return -1;
}
