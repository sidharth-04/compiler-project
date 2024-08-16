#include "testutils.h"
#include "../util/structures/stack.h"

void testCreateStack() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	assertInt(*(int*)stack->pop(stack), 1);
}

void testPushPopStack() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	int b = 3;
	stack->push(stack, &b);
	assertInt(*(int*)stack->pop(stack), 3);
	int c = 12;
	stack->push(stack, &c);
	assertInt(*(int*)stack->pop(stack), 12);
	assertInt(*(int*)stack->pop(stack), 1);
}

void testStackGetTop() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	int b = 10;
	stack->push(stack, &b);
	assertInt(*(int*)stack->getTop(stack), 10);
	assertInt(*(int*)stack->getTop(stack), 10);
	assertInt(*(int*)stack->pop(stack), 10);
	assertInt(*(int*)stack->getTop(stack), 1);
}

void runStackTests() {
	printf("running stack tests\n");
	testCreateStack();
	testPushPopStack();
	testStackGetTop();
}
