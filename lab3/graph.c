#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "cycle.h"

int**AllocMatrixInt(size_t n)
{
	int **matrix = NULL;
    matrix = (int **)calloc(n, sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Error: can't allocate memory\n");
        return NULL;		
	}
	for (size_t i = 0; i < n; ++i) {
		matrix[i] = (int *)calloc(n, sizeof(int));
		if (matrix[i] == NULL) {
			for (size_t j = i - 1; j >= 0; --j) free(matrix[i]);
			free(matrix);
			fprintf(stderr, "Error: can't allocate memory\n");
			return NULL;					
		}
	}
	return matrix;
}

void FreeMatrixInt(int ** matrix, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
	*matrix = NULL;	
}

bool ReadGraphFromFile(SGraph *graph, const char * fileName)
{
	// try open file
	FILE *file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", fileName);
        return false;
	}
	// try read size
	size_t n;
	if (fscanf(file, "%zu", &n) != 1) {
        fprintf(stderr, "Error: Can't read size\n");
        return false;
    }
    if (n < 2) {
        fprintf(stderr, "Error: size is too small\n");
        return false;
	}
    graph->n = n;
    // try alloc memory
    graph->adjacency = AllocMatrixInt(n);
    // read data
    size_t from, to;
    int weight;
    while (!feof(file)) {
		fscanf(file, "%zu%zu%d", &from, &to, &weight);
		graph->adjacency[from][to] = weight;
	}
	return true;
}

void PrintGraph(const SGraph *graph)
{
	int sum = 0;
	for (size_t i = 0; i < graph->n; ++i) {
		for (size_t j = 0; j < graph->n; ++j) {
			sum += graph->adjacency[i][j];
			printf("%5d", graph->adjacency[i][j]);
		}
		printf("\n");
	}
	printf("Total amount of all debts %d\n", sum);
}

bool IsEdge(SGraph *graph, size_t from, size_t to)
{
	return graph->adjacency[from][to] > 0;
}

bool FindCycles(SGraph *graph, CycleStore &store)
{
	size_t n = graph->n;
	size_t * stack = (size_t*)malloc((n +1) * sizeof(size_t));
	if (stack == NULL) {
	    fprintf(stderr, "Error: can't allocate memory\n");
        return false;
    }
    for (size_t i = 0; i < n + 1; ++i) stack[i] = -1;

	bool * wasVertex = (bool*)malloc((n) * sizeof(bool));
	if (wasVertex == NULL) {
	    fprintf(stderr, "Error: can't allocate memory\n");
        return false;
    }
    for (size_t i = 0; i < n; ++i) wasVertex[i] = false;

    int level = 0;
    stack[level] = 0;
    size_t to;
	for (size_t firstVertex = 0; firstVertex < n; ++firstVertex)
	{
		stack[0] = firstVertex;
		level = 1;
		while (level > 0) {// until return to stack's head
			if (stack[level] == -1){ // first time on this level
				to = firstVertex;
			} else { // was on this level
				// so start from previous vertex
				wasVertex[stack[level]] = false;
				to = stack[level] + 1;
			}
			// try find next vertex
			while (to < n && !(IsEdge(graph, stack[level - 1], to) && !wasVertex[to])) {
				++to;
			}
			if (to == n) { // no more child
				// go up
				stack[level] = -1;
				--level;
			} else 	{ // find vertex 
				stack[level] = to;
				wasVertex[to] = true;
				if (to == firstVertex) { // find circle
					wasVertex[to] = false;
					store.push_back(Cycle(stack, stack + level));
				} else { // no cycle
					// try go deep
					if (level == n) {
						wasVertex[stack[level]] = false;
						stack[level] = -1;
						--level;
					} else {
						++level;
					}
				}
			}			
		}
	}
	free(wasVertex);
	free(stack);
}

void FreeGraph(SGraph *g)
{
	FreeMatrixInt(g->adjacency, g->n);
	free(g);
	g = NULL;
}

void ReliefGraph(SGraph *graph, const Cycle &cycle)
{
	size_t minimum = graph->adjacency[cycle.back()][cycle.front()];
	for (size_t i = 1; i < cycle.size(); ++i) {
		minimum = (graph->adjacency[cycle[i - 1]][cycle[i]] < minimum) ? 
			graph->adjacency[cycle[i - 1]][cycle[i]] : minimum;
	}
	graph->adjacency[cycle.back()][cycle.front()] -= minimum;
	for (size_t i = 1; i < cycle.size(); ++i) {
		graph->adjacency[cycle[i - 1]][cycle[i]] -= minimum;
	}	
}

