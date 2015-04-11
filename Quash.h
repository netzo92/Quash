#ifndef QUASH_H
#define QUASH_H

#include <stdlib.h>
#include <stdio.h>

#include "HashNode.h"
#include "HeapNode.h"

class Quash {
	HashNode *hashArray[43];
	HeapNode **heapArray;
	int heapSize;
	int fIndex;

	public:
		Quash();
		bool deleteElement(int );
		bool deleteMin();
		bool lookupElement(int );
		void printHeap();	
		//void printCount(int);
                bool insertElement(int );
		int getMin();
		bool isMin();
};
#endif
