#ifndef queue_h
#define queue_h

#include <stdlib.h>

typedef struct Queue *QueueTy;
typedef struct QueueNode *QueueNodeTy;

struct QueueNode {
  void *value;
  QueueNodeTy next;
};

struct Queue {
  int size;
  int currIndex;
  int isEmpty;
  QueueNodeTy head;
  QueueNodeTy tail;
  QueueNodeTy currNode;
  // methods
  void (*attachNodeToQueue)(QueueTy, void*);
  void (*resetQueue)(QueueTy);
  int (*hasNextElement)(QueueTy);
  void* (*getNextElement)(QueueTy);
};

void attachNodeToQueue(QueueTy acc, void *tail);
void resetQueue(QueueTy queue);
int hasNextElement(QueueTy queue);
void *getNextElement(QueueTy queue);
QueueTy createQueue();

#endif
