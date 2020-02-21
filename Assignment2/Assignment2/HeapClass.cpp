// HeapClass.cpp

#include "HeapClass.h"


// Constructor
HeapClass::HeapClass()
{
	heap[0] = 0;
	N = 0;
}

// Returns the total number of nodes
int HeapClass::getN() const
{
	return N;
}

// Returns an element given index argument
int HeapClass::getElement(int index)
{
	return heap[index];
}

// Swap value given two indeces
void HeapClass::swapValue(int i, int j)
{
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

// Returns true if heap is empty
bool HeapClass::isEmpty() const
{
	return N==0? true:false;
}

// Insert node with value x as ergument
void HeapClass::insertNode(int x)
{
	// Insert at the end of the heap
	N += 1;
	heap[N] = x;

	int level = log2(N);
	int parent = N/2;

	// If heap has only 1 element no need to repair
	if (N <= 1)return;

	// Added in Min heap level
	if (level % 2 == 0) {
		if (parent > 0 && heap[N] > heap[parent]) {
			swapValue(N, parent);
			perculateUpMax(parent);
		}
		else {
			perculateUpMin(N);
		}
	}

	//Added in Max heap level
	else{
		if (parent > 0 && heap[N] < heap[parent]) {
			swapValue(N, parent);
			perculateUpMin(parent);
		}
		else{
			perculateUpMax(N);
		}

	}
}

// Repairs the heap in Min heap level
void HeapClass::perculateUpMin(int index)
{
	int nextMax = index / 4;
	if (nextMax <= 0) return;

	if (heap[index] < heap[nextMax]) {
		swapValue(index, nextMax);
		perculateUpMax(nextMax);
	}
}

// Repairs the heap in Max heap level
void HeapClass::perculateUpMax(int index)
{
	int nextMin = index/4;
	if (nextMin == 0) return;

	if (heap[index] > heap[nextMin]){
		swapValue(index, nextMin);
		perculateUpMax(nextMin);
	}
}

// Returns the least value in the heap
int HeapClass::getMin() const
{
	return heap[1];
}

// Returns the biggest value in the heap
int HeapClass::getMax()
{ 
	return max(heap[2],heap[3]);
}

// Removes the smallest value in the heap
void HeapClass::deleteMin()
{
	// Heap contains only 1 node
	if (N == 1) {
		N = 0;
		return;
	}
	
	// Heap contains > 1 node
	heap[1] = heap[N];
	N--;
	perculateDownMin(1); // repair
	
}

// Repair Heap after deleting Min
void HeapClass::perculateDownMin(int index)
{
	int minLeft = index * 4;
	if (minLeft <= N) {
		int minChild = minIndex(minLeft, minLeft + 3);
		if (heap[minChild] < heap[index]) {
			swapValue(minChild, index);	
			perculateDownMin(minChild);
		}
		
	} 
	else {
		int leftchild = index * 2;
		int level = log2(index);
		int parent = index / 2;

		if (level % 2 == 0) { // Min heap level
			if (leftchild <= N) {
				leftchild = minIndex(leftchild, leftchild + 1);
				if (heap[leftchild] < heap[index]) {
					swapValue(leftchild, index);
					perculateUpMin(index);
					perculateUpMax(leftchild);
				}
			}
			else if (parent >= 1) {
				if (heap[parent] < heap[index]) {
					swapValue(parent, index);
					perculateUpMax(parent);
					perculateUpMin(index);
				}
			}
		}

		else { // Max heap level
			if (leftchild <= N) {
				leftchild = maxIndex(leftchild, leftchild + 1);
				if (heap[leftchild] > heap[index]) {
					swapValue(leftchild, index);
					perculateUpMax(index);
					perculateUpMin(leftchild);
				}
			}
			else if (parent >= 1) {
				if (heap[parent] > heap[index]) {
					swapValue(parent, index);
					perculateUpMin(parent);
					perculateUpMax(index);
				}
			}
		}
	}
}

// Removes biggest value in the heap
void HeapClass::deleteMax()
{
	// Heap contains only 1 node
	if (N == 1) {
		N = 0;
		return;
	}
	
	// Heap contains > 1 node
	int max = heap[2] > heap[3] ? 2 : 3;
	heap[max] = heap[N];
	N--;
	perculateDownMax(max);
}

// Repair Heap after deleting Max
void HeapClass::perculateDownMax(int index)
{
	int maxLeft = index * 4;
	if (maxLeft <= N) {
		int maxChild = maxIndex(maxLeft, maxLeft + 3);
		if (heap[maxChild] > heap[index]) {
			swapValue(maxChild, index);
			perculateDownMax(maxChild);
		}
	}
	else {
		int leftchild = index * 2;
		int level = log2(index);
		int parent = index / 2;

		if (level % 2 == 0) { // Min heap level
			if (leftchild <= N) {
				leftchild = minIndex(leftchild, leftchild + 1);
				if (heap[leftchild] < heap[index]) {
					swapValue(leftchild, index);
					perculateUpMin(index);
					perculateDownMax(leftchild);
				}
			}
			else if (parent >= 1) {
				if (heap[parent] < heap[index]) {
					swapValue(parent, index);
					perculateUpMax(parent);
					perculateUpMin(index);
				}
			}
		}

		else { // Max heap level
			if (leftchild <= N) {
				leftchild = maxIndex(leftchild, leftchild + 1);
				if (heap[leftchild] > heap[index]) {
					swapValue(leftchild, index);
					perculateUpMax(index);
					perculateUpMin(leftchild);
				}
			}
			else if (parent >= 1) {
				if (heap[parent] > heap[index]) {
					swapValue(parent, index);
					perculateUpMin(parent);
					perculateUpMax(index);
				}
			}
		}
	}
}

// Returns the bigger value between the two
int HeapClass::max(int a, int b)
{
	return a>b? a:b;
}

// Returns the index of the biggest element in the range of index [start , end]
int HeapClass::maxIndex(int start, int end)
{
	int index = start;
	for (int i = start; i <= end; i++) {
		if (i <= N) index = heap[i] > heap[index] ? i : index;
		else break;
	}
	return index;
}

// Returns the index of the smallest element in the range of index [start , end]
int HeapClass::minIndex(int start, int end)
{
	int index = start;
	for (int i = start; i <= end; i++) {
		if (i <= N) index = heap[i] < heap[index] ? i : index;
		else break;
	}
	return index;
}


