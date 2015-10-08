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
    int size, width;
    char * type;
    void **data;
};

struct identifier_exp {
	char * identifier;
	struct memorycontainer* exp;
};

#include "byteassembler.h"

struct stack_t* getNewStack(void);
void clearStack(struct stack_t*);
void initStack(struct stack_t*);
int getStackSize(struct stack_t*);
int pop(struct stack_t*);
void push(struct stack_t*, int);
char* popIdentifier(struct stack_t*);
void pushIdentifier(struct stack_t*, char*);
int peek(struct stack_t*);
int getTopType(struct stack_t*);
struct memorycontainer* popExpression(struct stack_t*);
void pushExpression(struct stack_t*, struct memorycontainer*);
void pushIdentifierAssgnExpression(struct stack_t*, char*, struct memorycontainer*);
struct identifier_exp* popExpressionIdentifier(struct stack_t*);
struct memorycontainer* getExpressionAt(struct stack_t*, int);
struct identifier_exp* getExpressionIdentifierAt(struct stack_t*, int);
char* getIdentifierAt(struct stack_t*, int);
int getTypeAt(struct stack_t*, int);

#endif /* HOST_STACK_H_ */
