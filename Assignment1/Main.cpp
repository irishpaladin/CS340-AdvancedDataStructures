#include <string>
#include "Main.h"
#include <sstream>


int main(){
    // Get the input
    string input;
	cout<<endl<<endl<<"====================================================="<<endl;
	cout << "This program assumes you are giving a valid expression" << endl;
	cout << "It should: " << endl << "\tHave spaces every operator and operand" << endl
		<< "\tEvery operator should have its corresponding operands " << endl
		<< "\tNegative number should have no spaces between symbol and the number" << endl
		<< "Example: ( 3 + -5 ) * 4" << endl;
	cout<<"====================================================="<<endl << endl;

    cout<<"Enter expression: ";
    getline(cin, input);

    // Check if input is valid. Loop otherwise
    while(!Main::isExpression(input)){
        cout<< endl <<"You did not enter an expression. Please try again." <<endl;
        cout<<"Enter expression: ";
        getline(cin, input);
    }
    
    // Variable declaration
    Main main(input);

	if (main.isInfix(input)) {
		cout << "Expression is Infix" << endl;
		cout << "Converting to postfix... "<<endl;
		main.infixToPostfix();
		cout << "Generating Binary Tree..." << endl;
		main.buildTree();
		cout << endl;
	}
	else {
		cout << "Expression is Postfix" << endl;
		cout << "Generating Binary Tree..." << endl;
		main.buildTree();
		cout << endl;
	}

	cout << "Preorder traversal (prefix): ";
	main.displayPrefix();
	cout << endl << "Inorder traversal (infix): ";
	main.displayInfix();
	cout << endl << "Postorder traversal (postfix): ";
	main.displayPostfix();

	cout << endl << endl <<"Evaluating expression..."<<endl;
	cout << "Result: " << main.evaluateExpression() << endl << endl;
	

    return 0;
}

// Constructor
// Change the expression to array of strings
Main::Main(string str){
	num = 0;
	p_num = 0;
    toArray(str);
}

// Convert the string expression into an Array of operand and operator
// Stores it in the exression[]
void Main::toArray(string input){
    input+=" ";
    string term = ""; 
    num=0;
    for (int i=0;i<input.length();i++) 
    { 
        if(input[i]==' ' && term==""){
            continue;
        }
        else if (input[i] == ' ') 
        { 
            expression[num] = term; 
            num++;
            term = ""; 
        } 
        else
        { 
            term = term + input[i]; 
        } 
    }
}

// Returns true if the input is a valid expression
bool Main::isExpression(string input){
    for (int i=0;i<input.length();i++){
        if(!(isOperand(string(1,input[i])) || isOperator(string(1, input[i])) || input[i] == ' '
           || input[i] == '(' || input[i] == ')'))
        {
            return false;
        }
    }
    return true;
}

// Returns true if character is an operator
bool Main::isOperator(string chr){
    if(chr == "+" || chr == "-" || chr == "*" || chr == "/" )
        return true;
    
    return false;
}

// Returns true if character is a number
bool Main::isOperand(string chr){
	if (isdigit(chr[0]))
		return true;
	else if (chr.length() > 1 && chr[0] == '-')
		return true;
    
    return false;
}

// Returns true if there's operator at the end of expression
bool Main::isPostfix(string str){
    int strlen = str.length()-1;

    // Check for spaces
    while(strlen>0 && str[strlen] == ' ')
        strlen--;

    // Check if char is operator
    if(isOperator(string(1,str[strlen])))
        return true;
    
    // Otherwise return false
    return false;
}

// Returns true if there's operator at the start of expression
bool Main::isPrefix(string str){
    int strlen = str.length();
    int i = 0;

    // Check for spaces
    while(strlen>i && str[i] == ' ')
        i++;

    // Check if negative number
    if(str[i]=='-'){   
        if(!isOperand(string(1,str[++i])))
            return false;
        else
            return true;
    }

    // Check if  char is operator
    if(isOperator(string(1,str[i])))
        return true;
    
    // Otherwise return false
    return false;
}

// Returns true if it's neither Postfix or Prefix
bool Main::isInfix(string str){
    if(!(isPrefix(str)||isPostfix(str)))
        return true;
	p_num = num;
	for (int i = 0; i < num; i++) {
		postfix[i] = expression[i];
	}
    return false;
}

// Converts the expression from infix to postfix
void Main::infixToPostfix(){
    Stack temp;
	for (int i = 0; i < num; i++){
		// If the scanned character is an operand, add it to output string. 
		if (isOperand(expression[i]))
		postfix[p_num++]=expression[i];

		// If the scanned character is an ‘(‘, push it to the stack. 
		else if (expression[i] == "(")
			temp.Push("(");

		// If the scanned character is an ‘)’, pop and to output string from the stack 
		// until an ‘(‘ is encountered. 
		else if (expression[i] == ")")
		{
			 while (!temp.IsEmpty() && temp.getTop() != "(")
			 {
				 if (temp.getTop() == "(") {
					 string s = temp.Pop();
				 }
				 else {
					 postfix[p_num++]=temp.Pop();
				 }
			 }
			 if (!temp.IsEmpty() && temp.getTop() == "(") {
				 string s = temp.Pop();
			 }
			 
		 }

		//If an operator is scanned 
		else {
			while (!temp.IsEmpty() && getPriority(expression[i]) <= getPriority(temp.Top()))
			{
				 postfix[p_num++]=temp.Pop();
			}
			temp.Push(expression[i]);
		}

	}
	//Pop all the remaining elements from the stack 
	 while (!temp.IsEmpty()){
		 postfix[p_num++]=temp.Pop();
	 }

}


int Main::getPriority(string op){
	if (op == "*" || op == "/")
		return 2;
	else if (op == "+" || op == "-")
		return 1;
	else
		return -1;
}

void Main::displayPostfix() {
	postOrder(head);
}

void Main::displayInfix() {
	inOrder(head);
}

void Main::displayPrefix() {
	preOrder(head);
}

void Main::inOrder(Node* p)
{
	if (p!=NULL)
	{
		inOrder(p->left);
		cout << p->value << " ";
		inOrder(p->right);
	}
}

void Main::postOrder(Node* p)
{
	if (p != NULL)
	{
		postOrder(p->left);
		postOrder(p->right);
		cout << p->value << " ";
	}
}

void Main::preOrder(Node* p)
{
	if (p != NULL)
	{

		cout << p->value << " ";
		preOrder(p->left);
		preOrder(p->right);
	}
}

// A utility function to create a new node 
Node* Main::createNode(string str)
{
	Node* temp = new Node;
	temp->left = temp->right = NULL;
	temp->value = str;
	return temp;
}
int Main::evaluateExpression(){
	return evaluate(head);
}

int Main::evaluate(Node* node) {
	if (node == NULL)
		return 0;
	if (node->right == NULL && node->left == NULL) {
		stringstream ss(node->value);
		int int_val;
		ss >> int_val;
		return int_val;
	}
	int l_result = evaluate(node->left);
	int r_result = evaluate(node->right);
	if (node->value == "+")
		return l_result + r_result;

	if (node->value == "-")
		return l_result - r_result;

	if (node->value == "*")
		return l_result * r_result;

	return l_result / r_result;
}
;

void Main::buildTree() {
	// Returns root of constructed tree for given 
// postfix expression 
		Node* t, * t1, * t2 ;
		Stack temp;

		// Traverse through every character of 
		// input expression 
		for (int i = 0; i < p_num; i++)
		{
			// If operand, simply push into stack 
			if (!isOperator(postfix[i]))
			{
				//t = createNode(postfix[i]);
				temp.Push(postfix[i]);
			}
			else // operator 
			{
				t = createNode(postfix[i]);

				// Pop two top nodes 
				if (!temp.IsEmpty())
					t1 = createNode(temp.Pop()); // Store top 
				else
					t1 = head;
				if (!temp.IsEmpty())
					t2 = createNode(temp.Pop());
				else {
					if (t1 == head)
						t2 = NULL;
					else
						t2 = head;
				}
					

				//  make them children 
				t->right = t1;
				t->left = t2;

				// Add this subexpression to stack 
				head = t;
			}
		}
}