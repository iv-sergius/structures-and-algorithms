#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int pushToStack(struct stack **head, int newData)
{
    struct stack *newNode;
    newNode = (struct stack*) malloc (sizeof(struct stack));
    if (!newNode)
    {
        puts("Error: Can't allocate memory");
        return 1;
    }
    newNode->data = newData;
    newNode->previous = *head;
    *head = newNode;
    return 0;
}

int popFromStack(struct stack **head, int *dataFromHead)
{
    if (!(*head)) // empty struct stack 
    {
        puts("Warning: Pop from empty stack");
//        newData = NULL;
        return 1;
    }
    *dataFromHead = (*head)->data;
    struct stack *tmpStackNode;
    tmpStackNode = *head;
    *head = (*head)->previous;
    free(tmpStackNode);
    return 0;
}

int isStackEmpty(struct stack *head)
{
    return (!head);
}