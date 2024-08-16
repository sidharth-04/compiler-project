#include "testutils.h"
#include "../util/structures/queue.h"

void testCreateQueue() {
	QueueTy queue = createQueue();
	ASSERT_FALSE(queue->hasNextElement(queue));
	int a = 1;
	queue->attachNodeToQueue(queue, (void*)&a);
	ASSERT_TRUE(queue->hasNextElement(queue));
	ASSERT_INT(*(int*)queue->getNextElement(queue), 1);
	ASSERT_FALSE(queue->hasNextElement(queue));
}

void testGetNextElement() {
	QueueTy queue = createQueue();
	int a = 1;
	queue->attachNodeToQueue(queue, (void*)&a);
	int b = 2;
	queue->attachNodeToQueue(queue, (void*)&b);
	int c = 4;
	queue->attachNodeToQueue(queue, (void*)&c);
	int d = 3;
	queue->attachNodeToQueue(queue, (void*)&d);
	ASSERT_INT(*(int*)queue->getNextElement(queue), 1);
	ASSERT_INT(*(int*)queue->getNextElement(queue), 2);
	ASSERT_INT(*(int*)queue->getNextElement(queue), 4);
	ASSERT_INT(*(int*)queue->getNextElement(queue), 3);
}

void runQueueTests() {
	testCreateQueue();
	testGetNextElement();
}
