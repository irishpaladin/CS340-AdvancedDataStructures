#include "Stack.h"

Stack::Stack()
{
	// this is the constructor
	// initializes the stack
	// sets top
	top = -1;	
}

int Stack::Height() const
{
	// returns the number of items on the stack
	return top+1;
}

bool Stack::IsEmpty() const
{
	// checks whether the stack is empty
	if (top == -1)
		return true;
	else return false;
}

bool Stack::IsFull() const
{
	// checks whether the stack is full
	if (top == MAX_HEIGHT - 1)
		return true;
	else
		return false;
}

void Stack::Push(string x)
{
	// inserts a new item on the top of the stack
	// always call IsFull prior to calling Push
	// sets top
	top++;
	a[top] = x;
	return;
}

string Stack::Pop()
{
	// removes the item on the top of the stack and returns the value it contained
	// always call IsEmpty prior to calling Pop
	// sets top
	string x = a[top];
	top--;
	return x;
}

string Stack::Top() const
{
	// returns the value of the item on the top of the stack
	// always call IsEmppty prior to calling Top
	return a[top];
}

void Stack::Clear()
{
	// reinitializes the stack
	// sets top
	top = -1;
	return;
}

string Stack::getTop()const
{
	return a[top];
}