#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

const int MAX_HEIGHT = 8;

class Stack
{
public:
	Stack();
	int Height()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Push(string x);
	string Pop();
	string Top() const;
	void Clear();
	string getTop()const;

private:
	int top;
	string a[MAX_HEIGHT];
};


#endif