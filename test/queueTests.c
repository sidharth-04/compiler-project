#include "testutils.h"
#include "../util/structures/queue.h"

void testCreateQueue() {
	QueueTy queue = createQueue();
	assertFalse(queue->hasNextElement(queue));
	int a = 1;
	queue->attachNodeToQueue(queue, (void*)&a);
	assertTrue(queue->hasNextElement(queue));
	assertInt(*(int*)queue->getNextElement(queue), 1);
	assertFalse(queue->hasNextElement(queue));
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
	assertInt(*(int*)queue->getNextElement(queue), 1);
	assertInt(*(int*)queue->getNextElement(queue), 2);
	assertInt(*(int*)queue->getNextElement(queue), 4);
	assertInt(*(int*)queue->getNextElement(queue), 3);
}

void runQueueTests() {
	log_info_header("running queue tests...\n");
	testCreateQueue();
	testGetNextElement();
}
