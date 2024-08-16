#include "stack.h"

void push(StackTy stack, void *element) {
    StackNodeTy newTop = (StackNodeTy)malloc(sizeof(struct StackNode));
	newTop->curr = element;
	if (!stack->top) {
		stack->top = newTop;
	} else {
		newTop->prev = stack->top;
		stack->top = newTop;
	}
}	

void *getTop(StackTy stack) {
	return (void*)stack->top->curr;
}

void *pop(StackTy stack) {
	void *returnVal = stack->getTop(stack);
	StackNodeTy newTop = stack->top->prev;
	free(stack->top);
	stack->top = newTop;
	return returnVal;
}

StackTy createStack() {
	StackTy stack = (StackTy)malloc(sizeof(struct Stack));
	stack->top = NULL;
	// methods
	stack->push = push;
	stack->pop = pop;
	stack->getTop = getTop;
	return stack;
}
void destroyStack(StackTy stack) {
	return;
}

void printStack(StackTy st) {
	log_info_header("Printing Stack...\n");
	log_info("----------------------\n");
}
