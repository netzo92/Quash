#ifndef HASHNODE_H
#define HASHNODE_H

using namespace std;
class HeapNode;
class HashNode
{
	public:
		int val;
                //int count;
		HashNode *prev;
		HashNode *next;
		HeapNode *heap;
};
#endif
