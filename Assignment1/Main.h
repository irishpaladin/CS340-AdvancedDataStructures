//BinaryTree algorithms is modified and originally taken from: https://www.geeksforgeeks.org/expression-tree/

// Main.h
#include <iostream>
#include "Stack.h"

using namespace std;
const int MAX_ITEM = 50;

struct Node
{
	string value;
	Node* left, * right;
};

class Main{
    private:
    int num;
	int p_num;
	int evaluate(Node* node);

    public: 
    string expression[MAX_ITEM];
	string postfix[MAX_ITEM];
	Stack stack;
    Main(string str);
    void toArray(string str);
    int getNum() {return num;};
    static bool isExpression(string input);
    static bool isOperator(string chr);
    static bool isOperand(string chr);
    bool isPrefix(string str);
    bool isPostfix(string str);
    bool isInfix(string str);
    void infixToPostfix();
    int getPriority(string op);

	void displayPostfix();
	void displayInfix();
	void displayPrefix();

	Node* head;
	void buildTree();
	void inOrder(Node* p);
	void postOrder(Node* p);
	void preOrder(Node* p);
	Node* createNode(string str);

	int evaluateExpression();

};