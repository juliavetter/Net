#include "mylib.h"

//malloc with exit on error
void* mymalloc(size_t size) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
		printf("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}

//calloc with exit on error
void* mycalloc(size_t nmemb, size_t size) {
	void* ptr = calloc(nmemb, size);
	if (ptr == NULL) {
		printf("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}

//
//Stack functions
//

//initializes a stack with a null pointer at the bottom
Stack* newstack() {
	Stack* s = mymalloc(sizeof(Stack));
	s->top = NULL;
	return s;
}

//checks if the stack is empty
bool empty(Stack* stack) {
	return (stack->top == NULL);
}

//returns the data in the top node, removing it from the stack. Returns NULL if the stack is empty
void* pop(Stack* stack) {
	if (empty(stack))
		return NULL;
	void* d = stack->top->data;
	StackNode* n = stack->top->next;
	free(stack->top);
	stack->top = n;
	return d;
}

//returns the top node without popping it
void* peek(Stack* stack) {
	return stack->top->data;
}

//adds node to the stack
void push(Stack* stack, void* data) {
	StackNode* n = mymalloc(sizeof(StackNode));
	n->next = stack->top;
	
}

//pops all items, then frees memory
void freestack(Stack* stack) {
	while (!empty(stack)) {
		pop(stack);
	}
	free(stack);
}

//returns a random float
float randfloat() {
	return (float)rand()/(float)(RAND_MAX);
}
