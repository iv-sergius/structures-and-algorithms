#include "btree.h"
#include "queue.h"
#include "stdio.h"

bool PrintBTree(SBTree * const bTree)
{
	// запускаем волну для поиска в ширину
	SQueue wave;
	SetNewQueue (&wave);
	if (!PushToQueue(&wave, bTree->root)) { 
		// can't alloc memory for node
        return false;
    }
	while (!IsEmpty(&wave)) {
		SBNode * nodeToPrint;
		PopFromQueue(&wave, &nodeToPrint);
		// print all data
		// 
	} 
}
