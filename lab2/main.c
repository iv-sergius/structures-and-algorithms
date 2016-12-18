#include <stdio.h>
#include <time.h>
#include "tree.h"
#include "queue.h"

int main (int argv, char * argc[])
{
    time_t t1, t2, t3;
    if (argv != 2)
    {
        fprintf(stderr, "Error: Need only one argument\n");
        fprintf(stderr, "Need: <lab2> <name of file with nodes>\n");
        return 3;
    }
t1 = clock();
    STree tree;
    if (!readTreeFromFile(&tree, argc[1])) return 2;
    SQueue q;
t2 = clock();
    setNewQueue(&q);
    findTreeCenter(tree, &q);
t3 = clock();
    printf("Central node(s) of tree: \n");
    size_t node;
    while (!isEmpty(&q)) {
        popFromQueue(&q, &node);
        printf("%zu\n", node);
    }
    printf("Time of read file %.2f sec\n", (float)(t2 - t1) / CLOCKS_PER_SEC);
    printf("Time of solve problem %.2f sec\n", (float)(t3 - t2) / CLOCKS_PER_SEC);
    return 0;
}
