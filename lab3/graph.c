#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int**AllocMatrix(size_t n)
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
    graph->adjacency = AllocMatrix(n);
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



bool RelifGraph(SGraph *graph)
{
	size_t * stack = (size_t*)calloc(graph->n, sizeof(size_t));
	if (stack == NULL) {
	    fprintf(stderr, "Error: can't allocate memory\n");
        return false;
    }
    for (size_t i = 0; i < graph->n; ++i) stack[i] = -1;
    stack[0] = 0;
    level = 0;
    // find circle
    bool isCircle = false
    while (!isCircle) {
		// find next vertex
		for (size_t to = stack[0] + 1; (to < graph->n) 
			&& (graph->adjacency[stack[level][to]  0); ++i );
		if()
		// if don't find go on top
		// else check for circle
	}
    // relif
}
