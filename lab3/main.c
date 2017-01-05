#include "graph.h"
#include <stdio.h>

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        fprintf(stderr, "Error: Need only one element\n");
        fprintf(stderr, "example: <lab4.out> <file name>\n");
        return 3;
    }
    SGraph debts;
    if(!ReadGraphFromFile(&debts, argc[1])) {
		return 1;
	};
    printf("%zu\n", debts.n);
    PrintGraph(&debts);
    RelifGraph(&debts);
    return 0;
}
