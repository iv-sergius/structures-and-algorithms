#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"

bool setNewTree(STree * tree, size_t size)
{
    tree->size = size;
    tree->nChildren = (size_t*) calloc (size, sizeof(size_t));
    tree->firstChildren = (size_t*) calloc (size + 1, sizeof(size_t));
    tree->relations = (size_t*) calloc (2 * (size - 1), sizeof(size_t));
    return (tree->nChildren) && (tree->firstChildren) && (tree->relations);
}

bool readTreeFromFile(STree *tree, const char * fileName)
{
    // open file
    FILE *file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", fileName);
        return false;
    }
    // read size from first line
    size_t size;
    if (fscanf(file, "%zu", &size) != 1) {
        fprintf(stderr, "Error: Can't read size\n");
        return false;
    }
    // allocate memory in tree
    if (!setNewTree(tree, size)) {
        fprintf(stderr, "Error: Can't allocate memory\n");
        return false;
    }
    // calculate nChildren number of vertices
    size_t from, to;
    while (fscanf(file, "%zu%zu", &from, &to) == 2) {
        tree->nChildren[from] ++;
        tree->nChildren[to] ++;
    }
    //fclose(file);
    // calculate firstChildren
    for (size_t i = 0; i < size; ++i) {
        tree->firstChildren[i + 1] = tree->firstChildren[i] + tree->nChildren[i];
        tree->nChildren[i] = 0;
    }
    // reopen
    file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", fileName);
        return false;
    }
    if (fscanf(file, "%zu", &size) != 1) {
        fprintf(stderr, "Error: Can't read size\n");
        return false;
    }
    // fill data
    while (fscanf(file, "%zu%zu", &from, &to) == 2) {
        tree->relations[tree->firstChildren[from] + tree->nChildren[from]] = to;
        tree->relations[tree->firstChildren[to] + tree->nChildren[to]] = from;
        tree->nChildren[from]++;
        tree->nChildren[to]++;
    }
    //fclose(file);
    return true;
}

void sendWaveInTree(STree tree, size_t beginNode, long *resultMarks)
{
    for (int i = 0; i < tree.size; ++i)
    {
        resultMarks[i] = -1;
    }
    SQueue currentWave, nextWave;
    setNewQueue(&nextWave);
    long level = 0;
    // set inition of wave
    pushToQueue(&nextWave, beginNode);
    resultMarks[beginNode] = level;

    long node, nextNode;
    while (!isEmpty(&nextWave)){
        ++level;
        // currentWave := nextWave
        currentWave.head = nextWave.head;
        currentWave.tail = nextWave.tail;
        setNewQueue(&nextWave);

        while (!isEmpty(&currentWave)) {
            // pop from currentWave node#
            popFromQueue(&currentWave, &node);
            // for all children
            for (size_t i = tree.firstChildren[node]; i < tree.firstChildren[node + 1]; ++i) {
                // push to nextWave
                nextNode = tree.relations[i];
                if (resultMarks[nextNode] == -1)
                {
                    resultMarks[nextNode] = level;
                    pushToQueue(&nextWave, nextNode);
                }
            }
        }
    }
}

bool findTreeCenter(STree tree, SQueue *answer)
{
    SQueue currentWave, nextWave;
    setNewQueue(&nextWave);
    long * marks = (long*)calloc(tree.size, sizeof(long));
    long level = 1;
    // set inition of wave
    sendWaveInTree(tree, tree.size / 2, marks);
    // find the far node from current
    size_t farNode = 0;
    for (size_t i = 0; i < tree.size; ++i) {
        if (marks[i] > marks[farNode]) {
            farNode = i;
        }
    }
    size_t firstNode = farNode;
    sendWaveInTree(tree, firstNode, marks);
    // find the farest node from far
    size_t secondNode = farNode;
    for (size_t i = 0; i < tree.size; ++i) {
        if (marks[i] > marks[secondNode]) {
            secondNode = i;
        }
    }
//    printf("%zu %zu %zu\n", firstNode, secondNode, marks[secondNode] - marks[firstNode]);
    // search the longest path 
    size_t * path = (size_t*)calloc(tree.size, sizeof(size_t));
    // from farest element
    size_t len = marks[secondNode];
    path[len] = secondNode;
    size_t node, nextNode;
    // to far
    for (/*len already set*/; len > 0; --len) {
        // len == length from firstNode to node
        node = path[len];
        for (size_t i = tree.firstChildren[node]; i < tree.firstChildren[node + 1]; ++i) {
            // push to nextWave
            nextNode = tree.relations[i];
            if (marks[nextNode] == len -1) {
//                printf("%zu %zu\n", len-1, nextNode);
                path[len - 1] = nextNode;
            }
        }
    }
    len = marks[secondNode];
    if (len % 2 == 0) {
        pushToQueue(answer, path[len / 2]);
    } else {
        pushToQueue(answer, path[len / 2]);
        pushToQueue(answer, path[len / 2 + 1]);
    }

    //////////
    // for (size_t i = 0; i < tree.size; ++i)
    // {
    //     printf("%zu-%zu  ", i, marks[i]);
    // }
    //printf("  for node %zu\n", nextNode);
    ///////////
    return true;
}
