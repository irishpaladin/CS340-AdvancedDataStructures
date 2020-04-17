/*
	Stephanie Irish Paladin
	200413341

	**** COMPILE ****
	>> alias newg++ g++ -std=c++11
	>> newg++ -c assign3srp796.cpp
	>> newg++ assign3srp796.o -o main

	**** EXCECUTE ****
	>> main 10 4			(where 10 is the N and 4 is the K)

	***** OR *****
	>> main  10 4 d			(add d to display the unsorted and sorted elements)


	**** READ ME ****
	(c) All the sorting algorithms are taken from website geeksforgeeks.org
	> This programs assumes that you are giving it a right data type value
		when you have correct number of arguments
	> ** This program works correctly only if you compile and run it in cli **
	> ** Use the above two commands to run the program **
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h> 
#include <chrono> 

using namespace std;

// Global varibles
const int MAX_LENGTH = 10000;
int arr[MAX_LENGTH];		// array that will be sorted
int arr_orig[MAX_LENGTH];	// contains the original array


// Insertion Sort Algorithm
// n - number of elements to be sorted
void insertionSort(int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}


// Merge Sort Algorithm
// l - left index
// r - right index of the
// m - middle index
void merge(int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[MAX_LENGTH], R[MAX_LENGTH];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(l, m);
		mergeSort(m + 1, r);

		merge(l, m, r);
	}
}


// Quick Sort Algorithm
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int low, int high)
{
	int pivot = arr[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}


// Quick Insertion Sort ALgorithm
void quickInsertion(int low, int high, int k)
{
	if ((high - low + 1) < k) {
		int pi = partition(low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickInsertion(low, pi - 1, k);
		quickInsertion(pi + 1, high, k);
	}
	else {
		insertionSort(high - low + 1);
	}
}


// Function that copies the arr_orig to arr array
void copyArray(int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = arr_orig[i];
	}
}


// Function that prints the arr array
void printArr(int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
}


int main(int argc, char** argv) {

	double time_taken;	// variable to store the runtimes
	srand(time(NULL)); // initialize seed to produce random numbers
	bool display = false;

	// Commands validation
	// Check if elements are needed to be display
	if (argc == 4) {
		if (argv[3][0] == 'd') {
			display = true;
		}
		else {
			cout << endl << "    Invalid command. Please try again with either of this format: " << endl;
			cout << "     srp796 <N> <K>       ->   displays just the running time" << endl;
			cout << "     srp796 <N> <K> d     ->   displays just running time and the elements" << endl << endl;
			exit(0);
		}
	}
	// Check is command has right number of argument
	if (argc != 3 && argc != 4) {
		cout << endl << "    Invalid command. Please try again with either of this format: " << endl;
		cout << "     srp796 <N> <K>       ->   displays just the running time" << endl;
		cout << "     srp796 <N> <K> d     ->   displays just running time and the elements" << endl << endl;
		exit(0);
	}

	// Take the N and K in the cmd argument
	int n = std::atoi(argv[1]);
	int k = std::atoi(argv[2]);

	// Generate random n values
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
		arr_orig[i] = arr[i];

	}
	cout << endl;
	if (display) {
		cout << "Unsorted elements: " << endl;
		printArr(n);
	}


	// Insertion Sort
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);
	insertionSort(n);
	auto end = chrono::high_resolution_clock::now();
	if (display) {
		cout << "\nAfter Insertion sort: " << endl;
		printArr(n);
	}
	// Calculating total time taken by the program. 
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Insertion sort : ";
	cout << fixed << time_taken << setprecision(9);
	cout << " sec" << endl;

	copyArray(n);

	// Merge Sort
	start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);
	mergeSort(0, n - 1);
	end = chrono::high_resolution_clock::now();
	if (display) {
		cout << "\nAfter Merge sort: " << endl;
		printArr(n);
	}
	// Calculating total time taken by the program. 
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Merge sort     : ";
	cout << fixed << time_taken << setprecision(9);
	cout << " sec" << endl;


	copyArray(n);


	// Quick Sort
	start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);
	quickSort(0, n - 1);
	end = chrono::high_resolution_clock::now();
	if (display) {
		cout << "\nAfter Quick sort: " << endl;
		printArr(n);
	}
	// Calculating total time taken by the program. 
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Quick Sort     : ";
	cout << fixed << time_taken << setprecision(9);
	cout << " sec" << endl;


	copyArray(n);


	// Quick Insertion Sort
	start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);
	quickInsertion(0, n - 1, k);
	end = chrono::high_resolution_clock::now();
	if (display) {
		cout << "\nAfter Quick-Insertion sort: " << endl;
		printArr(n);
	}
	// Calculating total time taken by the program. 
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Quick Insertion: ";
	cout << fixed << time_taken << setprecision(9);
	cout << " sec" << endl;

	cout << endl;
	return 0;
}