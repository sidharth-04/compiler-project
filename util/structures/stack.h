#ifndef stack_h
#define stack_h

#include <stdlib.h>
#include "../loggers/logger.h"

typedef struct Stack *StackTy;
typedef struct StackNode *StackNodeTy;

struct StackNode {
	void *curr;
	StackNodeTy prev;
};
struct Stack {
	StackNodeTy top;
	void (*push)(StackTy, void*);
	void *(*pop)(StackTy);
	void *(*getTop)(StackTy);
};

void push(StackTy stack, void *element);
void *getTop(StackTy stack);
void *pop(StackTy stack);
StackTy createStack();
void destroyStack(StackTy stack);

#endif
