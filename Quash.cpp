#include <stdio.h>
#include <stdlib.h>
#include "Quash.h"

Quash::Quash()
{
	int i;
	for(i = 0;i<43;i++){
		hashArray[i] = NULL;
	}
	heapArray = new HeapNode*[20];
	for(i = 0; i<20;i++){
		heapArray[i] = NULL;
	}
	heapSize = 20;
	fIndex = 0;
}

	
bool Quash::deleteElement(int value)
{
	HeapNode *heapPtr;

	
	//find node in the hashtable
	int hashValue = abs(value%43);
	HashNode *n = hashArray[hashValue];
	HashNode *hashPtr;
	bool found = false;
	while(n != NULL && found == false)
	{
		if(n->val == value)
		{
			heapPtr = n->heap;
			found = true;
			hashPtr = n;
		}
		else
		{
		n = n->next;
		}	
	}

	//if the element was not found then exit the function
	if(found == false)
	{
		return false;
	}
	
	//remove the node from the hash table
	HashNode *prevNode = hashPtr->prev;
	HashNode *nextNode = hashPtr->next;
        //if(hashPtr->count == 1) {
	if(prevNode != NULL)
	{
		prevNode->next = nextNode;
	}
	
	if(nextNode != NULL)
	{
		nextNode->prev = prevNode;
	}

//else {
//hashPtr->count--;
//}

	delete hashPtr;

	int heapIndex = heapPtr->index;
	

	// if we are deleting the last heapnode, just remove it and return true 	
	if(heapIndex == fIndex)
	{
		heapArray[heapIndex] = NULL;
		fIndex = fIndex -1;
		delete heapPtr;
		return true;
	}
	
	int sIndex = heapIndex;
	int parentI;
	HeapNode *swapNode;
	//begin the swap up
	while(sIndex != 1)
	{
		parentI = sIndex * (.5);
		swapNode = heapArray[parentI];
		heapArray[parentI] = heapArray[sIndex];
		heapArray[parentI]->index=parentI;
		heapArray[sIndex] = swapNode;
		heapArray[sIndex]->index=sIndex;
		sIndex = parentI;
	}
	heapIndex = sIndex;
	delete heapPtr;
	heapArray[heapIndex] = heapArray[fIndex];
	heapArray[fIndex] = NULL;
	fIndex = fIndex - 1;
	heapArray[heapIndex]->index = heapIndex;
	
	//begin the swap down
	int noSwap = 0;
	int hIndex = heapIndex;
	while(noSwap == 0)
	{
		int lval, rval;
		if(hIndex*2>fIndex)
		{
			noSwap = 1;
		}
		else if(hIndex*2<=fIndex && ((hIndex*2)+1)>fIndex)
		{	
			if(heapArray[hIndex]->val > heapArray[hIndex*2]->val)
			{
				HeapNode *tmp = heapArray[hIndex*2];
				heapArray[hIndex*2]=heapArray[hIndex];
				heapArray[hIndex*2]->index = hIndex*2;
				heapArray[hIndex] = tmp;
				heapArray[hIndex]->index = hIndex;
			}
			noSwap = 1;
		}
		else if(hIndex*2<=fIndex &&((hIndex*2)+1)<=fIndex)
		{
			int newIndex;
			lval = heapArray[hIndex*2]->val;
			rval = heapArray[(hIndex*2)+1]->val;
			
			if((heapArray[hIndex]->val)>lval || (heapArray[hIndex]->val)>rval)
			{
				if(lval>rval)
				{
					newIndex = (hIndex*2)+1;
				}
				else{
					newIndex =(hIndex*2);
				}
				
				HeapNode *tmp = heapArray[newIndex];
				heapArray[newIndex] = heapArray[hIndex];
				heapArray[newIndex]->index = newIndex;
				heapArray[hIndex] = tmp;
				heapArray[hIndex]->index = hIndex;
				hIndex = newIndex;
			
			}
			else
			{
				noSwap = 1;
			}


		}
	
	}
	return true;
			

}

bool Quash::isMin()
{
	HeapNode *heapPtr = heapArray[1];
	if(heapPtr == NULL)
		return false;
	return true;
}
	
int Quash::getMin()
{
	return heapArray[1]->val;
}


bool Quash::deleteMin()
{
	int min;
	HeapNode *heapPtr = heapArray[1];
	if(heapPtr == NULL)
		return false;

	min = heapArray[1]->val;
	HashNode *hashPtr = heapArray[1]->hash;

	//delete the min from the hast table
	if(hashPtr->next != NULL){
		hashPtr->next->prev=hashPtr->prev;
	}
	if(hashPtr->prev != NULL){
		hashPtr->prev->next=hashPtr->next;
	}
	
	//Delete the HashNode and its equivalent HeapNode
	delete hashPtr;	
	delete heapPtr;
	if(1 == fIndex)
	{
		heapArray[1] = NULL;
		fIndex = fIndex -1;
		return true;
	}
	//Once the min, heap node is deleted, get the last node and put it at the top of the heap
	heapArray[1] = heapArray[fIndex];
	heapArray[fIndex] = NULL;
	heapArray[1]->index = 1;
	fIndex = fIndex - 1;


	int noSwap = 0;
	int hIndex = 1;
	while(noSwap == 0)
	{
		int lval, rval;
		if(hIndex*2 > fIndex)
		{
			noSwap = 1;	
		}
		else if(hIndex*2 <= fIndex && ((hIndex*2)+1)>fIndex)
		{
			if(heapArray[hIndex]->val > heapArray[hIndex*2]->val)
			{ 
				HeapNode *tmp = heapArray[hIndex*2];
				heapArray[hIndex*2]=heapArray[hIndex];
				heapArray[hIndex*2]->index = hIndex*2;
				heapArray[hIndex] = tmp;
				heapArray[hIndex]->index = hIndex;
			}
			noSwap = 1;
		}
		else if(hIndex*2 <=fIndex &&((hIndex*2)+1)<=fIndex)
		{
			int newIndex;
			lval = heapArray[hIndex*2]->val;
			rval = heapArray[(hIndex*2)+1]->val;
			if((heapArray[hIndex]->val)>lval || (heapArray[hIndex]->val)>rval)
			{	
				if(lval>rval)
				{
					newIndex = (hIndex*2)+1;
				}
				else{
					newIndex =(hIndex*2);
				}
			
				HeapNode *tmp = heapArray[newIndex];
				heapArray[newIndex] = heapArray[hIndex];
				heapArray[newIndex]->index = newIndex;
				heapArray[hIndex] = tmp;
				heapArray[hIndex]->index = hIndex;
				hIndex = newIndex;
			}
			else
			{
				noSwap = 1;
			}

		}
	}

	return true;
}
		




bool Quash::lookupElement(int value)
{
	int hashVal = abs(value%43);
	HashNode *n = hashArray[hashVal];
	while(n != NULL)
	{
		if(n->val == value)
			return true;
		n = n->next;
	}	
	return false;
}

void Quash::printHeap()
{
	int j;
	for(j = 1; j<fIndex+1;j++)
	{
		if(heapArray[j] != NULL)
		{
			if(j == fIndex)
				printf("%d", heapArray[j]->val);
			else	
				printf("%d ",heapArray[j]->val);
		}
	}
	printf("\n");
}

//////get count///
//void Quash::printCount(int num) {
//int hashF = abs(num%43);
//HashNode *n = hashArray[hashF];
//printf("%d", n->val);
//printf("%d", n->count);
//}

bool Quash::insertElement(int value)
{
	//Obtain the correct hashvalue
	int hashF = abs(value%43);
	//Check whether or not the value is already in the quash
	HashNode *n1 = hashArray[hashF];
	while(n1 != NULL)
	{
		if(n1->val == value)
		//{
                        printf( "item already in table\n");   
                     //n1->count++;
			return false;
		//}
		n1 = n1->next;
	}
		

	
	//insert the element into the hash first.
	HashNode *n = hashArray[hashF];
	HashNode *newNode;
	HashNode *hashPtr;
	if(n==NULL)
	{
		hashArray[hashF] = new HashNode();
		hashArray[hashF]->val = value;
                //hashArray[hashF]->count = 1;
		hashArray[hashF]->next = NULL;
		hashArray[hashF]->prev = NULL;
		hashPtr = hashArray[hashF];
	}
	else{
		newNode = new HashNode();
		newNode->val = value;
                //newNode->count = 1;
		n->prev = newNode;
		newNode->prev = NULL;
		newNode->next = n;
		hashArray[hashF]= newNode;
		hashPtr = newNode;
	}
	

	//begin inserting into the heap;
	
	fIndex = fIndex + 1;
	//resize
	if(fIndex >= heapSize)
	{
		int j;
		HeapNode **nHeapArray = new HeapNode*[heapSize*2];
		nHeapArray[0] = NULL;
		for(j=1;j<heapSize;j++)
		{	
			nHeapArray[j]=heapArray[j];		
		}
		for(j=heapSize;j<(heapSize*2);j++)
		{
			nHeapArray[j]=NULL;
		}
		
		heapSize =  heapSize*2;
		delete heapArray;
		heapArray = nHeapArray;	
	}
	
	heapArray[fIndex] = new HeapNode();
	heapArray[fIndex]->val = value;
	heapArray[fIndex]->index=fIndex;
	heapArray[fIndex]->hash = hashPtr;
	hashPtr->heap = heapArray[fIndex];
	int noSwap = 0;
	int cIndex = fIndex;
	while(noSwap == 0)
	{
		int parentIndex, parentVal,childVal;
		HeapNode *tmp;
		if(cIndex == 1)
		{
			noSwap = 1;
			break;
		}	
		
		parentIndex = (cIndex *(.5));		
		parentVal = heapArray[parentIndex]->val;
		childVal = heapArray[cIndex]->val;
		if(parentVal>childVal)
		{
			tmp = heapArray[parentIndex];	
			heapArray[parentIndex] = heapArray[cIndex];
			heapArray[parentIndex]->index = parentIndex;
			heapArray[cIndex] = tmp;
			heapArray[cIndex]->index = cIndex;
			cIndex = parentIndex;
		}
		else
		{
			noSwap = 1;
		}
	
	}
	
	return true;
}
