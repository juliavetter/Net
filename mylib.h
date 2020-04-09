#ifndef MYLIB_H
#define MYLIB_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//generic functions
void* mymalloc(size_t size);
void* mycalloc(size_t nmemb, size_t size);

//Stack structs
typedef struct StackNode StackNode;
struct StackNode {
	void* data;
	StackNode* next;
};

typedef struct {
	StackNode* top;
} Stack;  

//Stack functions
//initializes a stack with a null pointer at the bottom
extern Stack* newstack();
//checks if the stack is empty
extern bool empty(Stack* stack);
//returns the top node, removing it from the stack
extern void* pop(Stack* stack);
//returns the top node without popping it
extern void* peek(Stack* stack);
//adds node to the stack
extern void push(Stack* stack, void* data);
//pops all items, then frees memory
extern void freestack(Stack* stack);
//returns a random float
extern float randfloat();

#endif
