// Main.h

#ifndef MAIN
#define MAIN

#include "HeapClass.h"

class Main {
private:
	HeapClass heap;
public:
	void displayTree();
	void insertNode(int x);
	void displayMin();
	void displayMax();
	void deleteMin();
	void deleteMax();

};

#endif // !MAIN
