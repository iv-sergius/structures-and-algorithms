#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "cycle.h"

struct Graph
{
    size_t n;
    int ** adjacency;
};
typedef struct Graph SGraph;

bool ReadGraphFromFile(SGraph *g, const char * fileName);

void PrintGraph(const SGraph *g);

bool FindCycles(SGraph *g, CycleStore &store);

void ReliefGraph(SGraph *g, const Cycle &store);

void FreeGraph(SGraph *g);

#endif
