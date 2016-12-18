#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "queue.h"

struct Tree
{
    size_t size;
    size_t *nChildren;
    size_t *firstChildren;
    size_t *relations;
};
typedef struct Tree STree;

bool setNewTree(STree * tree, size_t size);

bool readTreeFromFile(STree *tree, const char *fileName);

bool findTreeCenter(STree tree, SQueue *answer);
