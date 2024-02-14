#include "queue.h"

void attachNodeToQueue(QueueTy acc, void *tail) {
    QueueNodeTy tailNode = (QueueNodeTy)malloc(sizeof(struct QueueNode));
    tailNode->value = tail;
    if (acc->size == 0) {
        acc->head = tailNode;
        acc->tail = tailNode;
		acc->currNode = acc->head;
    } else {
        acc->tail->next = tailNode;
        acc->tail = tailNode;
    }
    acc->size ++;
	acc->isEmpty = 0;
}

void resetQueue(QueueTy queue) {
	queue->currNode = queue->head;
	queue->currIndex = 0;
}

int hasNextElement(QueueTy queue) {
	return queue->currIndex < queue->size;
}

void *getNextElement(QueueTy queue) {
	if (!queue->hasNextElement(queue)) return 0;
	void *result = queue->currNode->value;
	queue->currNode = queue->currNode->next;
	queue->currIndex ++;
	return result;
}

QueueTy createQueue() {
    QueueTy queue = (QueueTy)malloc(sizeof(struct Queue));
    queue->size = 0;
	queue->currIndex = 0;
	queue->isEmpty = 1;
    queue->head = NULL;
    queue->tail = NULL;
	queue->currNode = queue->head;
	// methods
	queue->attachNodeToQueue = attachNodeToQueue;
	queue->resetQueue = resetQueue;
	queue->hasNextElement = hasNextElement;
	queue->getNextElement = getNextElement;
    return queue;
}
