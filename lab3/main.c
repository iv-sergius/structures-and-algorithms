#include <stdio.h>
#include <iostream>
#include <vector>
#include "graph.h"
#include "cycle.h"

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
    PrintGraph(&debts);
    CycleStore store;
    FindCycles(&debts, store);
	size_t cycleNumber;
	do {
		PrintStore(store);
		std::cout << std::endl << "Chose cycle for relief > ";
input:
		if (!(std::cin >> cycleNumber)) {
			std::cout << "Incorrect value try again > ";
			goto input;
		}
		if (cycleNumber >= store.size()) {
			std::cout << "Incorrect value try again > ";
			goto input;
		}
		ReliefGraph(&debts, store[cycleNumber]);
		PrintGraph(&debts);
		store = CycleStore();
		FindCycles(&debts, store);
	} while (!store.empty());
	
}
