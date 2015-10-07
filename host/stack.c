/*
 * stack.c
 *
 *  Created on: 9 July 2015
 *      Author: Nick Brown
 */

#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack_t* getNewStack(void) {
	struct stack_t* newStack=(struct stack_t*) malloc(sizeof(struct stack_t));
	initStack(newStack);
	return newStack;
}

void initStack(struct stack_t* stack) {
    stack->width=INITIAL_STACK_SIZE;
    stack->size=0;
    stack->data=(void**) malloc(sizeof(void*) * INITIAL_STACK_SIZE);
    stack->type=(char*) malloc(sizeof(char) * INITIAL_STACK_SIZE);
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

void clearStack(struct stack_t* stack) {
	stack->size=0;
	free(stack->data);
	free(stack->type);
	stack->width=INITIAL_STACK_SIZE;
}

char* popIdentifier(struct stack_t* stack) {
   if (stack->size > 0) {
       return (char*) stack->data[--stack->size];
   }
   return NULL;
}

struct memorycontainer* popExpression(struct stack_t* stack) {
   if (stack->size > 0) {
       return (struct memorycontainer*) stack->data[--stack->size];
   }
   return NULL;
}

struct memorycontainer* getExpressionAt(struct stack_t* stack, int index) {
   if (stack->size > index) {
       return (struct memorycontainer*) stack->data[index];
   }
   return NULL;
}

int getTopType(struct stack_t* stack) {
	if (stack->size > 0) {
		return stack->type[stack->size];
	}
	return 0;
}

int getTypeAt(struct stack_t* stack, int index) {
	if (stack->size > index) {
		return stack->type[index];
	}
	return 0;
}

void push(struct stack_t* stack, int val) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(void**) realloc(&stack->data, sizeof(void*) * stack->width);
        stack->type=(char*) realloc(&stack->type, sizeof(char) * stack->width);
    }
    stack->data[stack->size-1]=malloc(sizeof(int));
    stack->type[stack->size-1]=1;
    memcpy(stack->data[stack->size-1], &val, sizeof(int));
}

void pushIdentifier(struct stack_t* stack, char* val) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(void**) realloc(&stack->data, sizeof(void*) * stack->width);
        stack->type=(char*) realloc(&stack->type, sizeof(char) * stack->width);
    }
    stack->data[stack->size-1]=malloc(strlen(val)+1);
    stack->type[stack->size-1]=2;
    strcpy(stack->data[stack->size-1], val);
}

void pushExpression(struct stack_t* stack, struct memorycontainer* exp) {
	stack->size++;
    if (stack->size >= stack->width) {
        stack->width*=2;
        stack->data=(void**) realloc(&stack->data, sizeof(void*) * stack->width);
        stack->type=(char*) realloc(&stack->type, sizeof(char) * stack->width);
    }
    stack->data[stack->size-1]=exp;
    stack->type[stack->size-1]=3;
}

int peek(struct stack_t* stack) {
	if (stack->size > 0) {
		return *((int*) stack->data[stack->size-1]);
	}
	return -1;
}
