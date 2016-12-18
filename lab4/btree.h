#include <stdbool.h>
#include <stddef.h>

struct BNode
{
    bool isLeaf;
    size_t n;
    int * data;
    struct BNode *childen;
};
typedef struct BNode SBNode;

struct BTree
{
    const size_t t;
    SBNode *root;
};
typedef struct BTree SBtree;