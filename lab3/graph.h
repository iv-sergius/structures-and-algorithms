#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct Graph
{
    size_t n;
    int ** adjacency;
    //int ** data;
};

typedef struct Graph SGraph;

//bool SetNewGraph(SGraph g, size_t n);

bool ReadGraphFromFile(SGraph *g, const char * fileName);

void PrintGraph(const SGraph *g);

bool RelifGraph(SGraph *g);

