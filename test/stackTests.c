#include "testutils.h"
#include "../util/structures/stack.h"

void testCreateStack() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	ASSERT_INT(*(int*)stack->pop(stack), 1);
}

void testPushPopStack() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	int b = 3;
	stack->push(stack, &b);
	ASSERT_INT(*(int*)stack->pop(stack), 3);
	int c = 12;
	stack->push(stack, &c);
	ASSERT_INT(*(int*)stack->pop(stack), 12);
	ASSERT_INT(*(int*)stack->pop(stack), 1);
}

void testStackGetTop() {
	StackTy stack = createStack();
	int a = 1;
	stack->push(stack, &a);
	int b = 10;
	stack->push(stack, &b);
	ASSERT_INT(*(int*)stack->getTop(stack), 10);
	ASSERT_INT(*(int*)stack->getTop(stack), 10);
	ASSERT_INT(*(int*)stack->pop(stack), 10);
	ASSERT_INT(*(int*)stack->getTop(stack), 1);
}

void runStackTests() {
	testCreateStack();
	testPushPopStack();
	testStackGetTop();
}
