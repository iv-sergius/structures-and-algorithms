#include "graph.h"
#include <stdio.h>

int main(int argv, char * argc[])
{
    if (argv != 2)
    {
        fprintf(stderr, "Error: Need only one element\n");
        fprintf(stderr, "example: <lab4.out> <file name>\n");
        return 3;
    }
    FILE *file = fopen(argc[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argc[1]);
        return false;
    }
    
    return 0;
}