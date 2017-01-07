#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include "cycle.h"

void PrintStore(const CycleStore &store)
{
	std::ostream_iterator<size_t> outIterator(std::cout, " ");	
	for (size_t i = 0; i < store.size(); ++i) {
		std::cout << "Cycle " << i << ", length = " << store[i].size() << " : ";
		std::copy(store[i].begin(), store[i].end(), outIterator);
		std::cout << std::endl;
	}
}
