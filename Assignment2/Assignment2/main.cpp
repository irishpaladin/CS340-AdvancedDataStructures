// main.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "Main.h"

using namespace std;


int main() {
	Main main;

	regex r1("[1|2|3|4|5|6|7|8|9|0| ]+");
	regex r2("[ ]+");

	// Get the initial heap values
	// Validates the user input
	bool valid = false;
	string values;
	while (!valid) {
		cout << "Enter values to build heap: ";
		getline(cin, values);
		if (regex_match(values, r1) || values =="") {
			valid = true;
		}
		else {
			cout << "\n Invalid Input.\n\n";
		}
	}

	// If no values was inserted
	if (!regex_match(values, r2) && values != "") {
		stringstream ss(values);
		if (!ss.good())cout << " \nInvalid Input! \n\n";
		while (ss.good()) {
			int val;
			ss >> val;
			main.insertNode(val);
		}
	}
	main.displayTree();
	
	
	char choice = ' ';
	while ((choice != 'Q') && (choice != 'q')) {
		cout << "\n\n***************************" << endl
			<< "* MIN-MAX Heap Operations *" << endl
			<< "***************************" << endl
			<< "0 - Display Tree" << endl
			<< "1 - Insert Node" << endl
			<< "2 - Find Min" << endl
			<< "3 - Find Max" << endl
			<< "4 - Delete Min" << endl
			<< "5 - Delete Max" << endl
			<< "q - Quit " << endl
			<< "***************************" << endl
			<< "Enter Choice: ";
		cin >> choice;

		switch (choice) {
		case '0': // Display Tree
			main.displayTree();
			break;
		case '1': // Insert Node
			int val;
			cout << "\nEnter int value: ";
			cin >> val;
			main.insertNode(val);
			main.displayTree();
			break;
		case '2': // Find Min
			main.displayMin();
			break;
		case '3': // Find Max
			main.displayMax();
			break;
		case '4': // Delete Min
			main.deleteMin();
			main.displayTree();
			break;
		case '5': // Delete Max
			main.deleteMax();
			main.displayTree();
			break;
		case 'q': case 'Q': // Quit
			break;
		default:
			cout << "Invalid input!" << endl;
			break;
		}
	}
	return 0;
}

// Displays the tree level by level
void Main::displayTree()
{
	// Heap is Empty
	if (heap.isEmpty()) {
		cout << "\n\nHeap is empty" << endl;
		return;
	}

	// Heap is not empty
	cout << "\n\n****************" << endl
		<< "* MIN-MAX Heap *" << endl
		<< "****************";
	int N = heap.getN();
	int level = 0, left = 1, i = 1;

	for (i = 1; i <= N; i++)
	{
		if (i == left) // starts new level
		{
			cout << "\nLevel " << level << ": ";
			level += 1;
			left *= 2;
		}
		cout << heap.getElement(i) << " ";
	}
	cout << "\n****************" << endl;
}

// Helper function for insertNode
void Main::insertNode(int x)
{
	heap.insertNode(x);
}

// Helper function for getMin
void Main::displayMin()
{
	if (heap.isEmpty())cout << "\n\nHeap is Empty" << endl;
	else cout << "\n\n Min value is: " << heap.getMin() << endl;
}

// Helper function for getMax
void Main::displayMax()
{
	if (heap.isEmpty())cout << "\n\nHeap is Empty" << endl;
	else if (heap.getN() == 1) cout << "\n\n Max value is: " << heap.getElement(1) << endl;
	else if (heap.getN() == 2) cout << "\n\n Max value is: " << heap.getElement(2) << endl;
	else cout << "\n\n Max value is: " << heap.getMax() << endl;
}

// Helper function for deleteMin
void Main::deleteMin()
{
	if (heap.isEmpty()) cout << "\n\nHeap is Empty" << endl;
	else heap.deleteMin();
}

// Helper funtion for deleteMax
void Main::deleteMax()
{
	if (heap.isEmpty()) cout << "\n\nHeap is Empty" << endl;
	else heap.deleteMax();
}

