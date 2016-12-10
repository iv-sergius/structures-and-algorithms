
struct Node
{
    bool isLeaf;
    size_t n;
    int data;
    struct Node *childen;
}

struct BTree
{
    size_t t;
    struct Node *root;
}
