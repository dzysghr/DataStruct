
#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef List Stack;

#define stack_destroy list_destroy
#define stack_init list_init
#define stack_peek(stack) ((stack)->head == NULL? NULL:(stack)->head->data)
#define stack_size(stack) list_size(stack);
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack,void **data);


#endif