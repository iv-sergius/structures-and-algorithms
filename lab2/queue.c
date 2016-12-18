#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// push to tail of queue
bool pushToQueue(SQueue *q, long dataToTail)
{
    // create new node to push
    SQueueNode *newNode;
    newNode = (SQueueNode *) malloc (sizeof(SQueueNode));
    if (!newNode) {
        fprintf(stderr, "Error: Can't allocate memory for new node\n");
        return false;
    }
    // conforming newNode
    newNode->data = dataToTail;
    newNode->next = NULL;
    // conforming structures
    if (isEmpty(q))
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    return true;
}

bool popFromQueue(SQueue *q, long *dataFromHead)
{
    if (isEmpty(q)){
        fprintf(stderr, "Warning: Queue is empty so no data\n");
        return false;
    }
    SQueueNode *oldHead = q->head;
    *dataFromHead = oldHead->data;
    if (oldHead->next == NULL)
    {
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        q->head = q->head->next;
    }
    free(oldHead);
    return true;
}

bool isEmpty(SQueue *q)
{
  return (q->head == NULL);
}

void setNewQueue(SQueue *q)
{
  q->head = NULL;
  q->tail = NULL;
}
