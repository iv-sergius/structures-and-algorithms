#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct Graph
{
    size_t n;
    int ** array;
};

typedef struct Graph SGraph;

bool SetNewGraph(SGraph g, size_t n);

bool ReadGraphFromFile(SGraph g, FILE *file);