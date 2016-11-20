struct stack{
    int data;
    struct stack *previous;
};

int pushToStack(struct stack **head, int newData);

int popFromStack(struct stack **head, int *newData);

int isStackEmpty(struct stack *head);
