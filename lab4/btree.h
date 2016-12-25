#ifndef _BTREE_H
#define _BTREE_H

#include <stdbool.h>
#include <stddef.h>

struct BNode
{
    bool isLeaf;
    size_t n;
    char **data;
    struct BNode **childen;
};
typedef struct BNode SBNode;

struct BTree
{
    const size_t t;
    SBNode *root;
};
typedef struct BTree SBTree;

bool PrintBTree(SBTree * const bTree);

bool AddDataToBTree(SBTree *bTree, char * dataToAdd);

#endif
