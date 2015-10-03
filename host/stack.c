/*
 * stack.c
 *
 *  Created on: 9 July 2015
 *      Author: Nick Brown
 */

#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack_t* getNewStack() {
	struct stack_t* newStack=(struct stack_t*) malloc(sizeof(struct stack_t));
	initStack(newStack);
	return newStack;
}

void initStack(struct stack_t* stack) {
    stack->width=INITIAL_STACK_SIZE;
    stack->size=0;
    stack->data=(void**) malloc(sizeof(void*) * INITIAL_STACK_SIZE);
}

int getStackSize(struct stack_t* stack) {
	return stack->size;
}

int pop(struct stack_t* stack) {
   if (stack->size > 0) {
	   int data=*((int*) stack->data[stack->size-1]);
	   free(stack->data[--stack->size]);
       return data;
   }
   return -1;
}

char* popIdentifier(struct stack_t* stack) {
   if (stack->size > 0) {
       return (char*) stack->data[--stack->size];
   }
   return NULL;
}

void push(struct stack_t* stack, int val) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(void**) realloc(&stack->data, sizeof(void*) * stack->width);
    }
    stack->data[stack->size-1]=malloc(sizeof(int));
    memcpy(stack->data[stack->size-1], &val, sizeof(int));
}

void pushIdentifier(struct stack_t* stack, char* val) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(void**) realloc(&stack->data, sizeof(void*) * stack->width);
    }
    stack->data[stack->size-1]=malloc(strlen(val)+1);
    strcpy(stack->data[stack->size-1], val);
}

int peek(struct stack_t* stack) {
	if (stack->size > 0) {
		return *((int*) stack->data[stack->size-1]);
	}
	return -1;
}
