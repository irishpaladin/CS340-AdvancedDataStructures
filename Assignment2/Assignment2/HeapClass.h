//HeapClass.h

#ifndef HEAP_CLASS
#define HEAP_CLASS

#include "math.h"

const int MAX_ITEM = 500;
class HeapClass
{
private:
	int heap[MAX_ITEM];
	int N;
public:
	HeapClass();
	int getN()const;
	int getElement(int index);
	void swapValue(int i, int j);
	bool isEmpty()const;
	int max(int a, int b);
	int maxIndex(int start, int end);
	int minIndex(int start, int end);

	void insertNode(int x);
	void perculateUpMin(int index);
	void perculateUpMax(int index);

	int getMin()const;
	int getMax();

	void deleteMin();
	void perculateDownMin(int index);

	void deleteMax();
	void perculateDownMax(int index);
	
};

#endif // !1



