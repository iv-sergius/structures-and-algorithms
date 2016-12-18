#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>

struct QueueNode
{
    struct QueueNode *next;
//    struct qNode_s *prev;
    long data;
};
typedef struct QueueNode SQueueNode;

struct Queue
{
    SQueueNode *head;
    SQueueNode *tail;
};
typedef struct Queue SQueue;

// push to end
bool pushToQueue(SQueue *q, long dataToTail);

// pop from head
bool popFromQueue(SQueue *q, long *dataFromHead);

bool isEmpty(SQueue *q);

void setNewQueue(SQueue *q);

void erase(SQueue *q);

#endif
