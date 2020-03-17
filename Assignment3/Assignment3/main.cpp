#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h> 

using namespace std;

struct timeval* tp;
struct timezone* tzp;

const int MAX_LENGTH = 10000;
int arr[MAX_LENGTH];
int arr_orig[MAX_LENGTH];

double  mytime2()
{
	gettimeofday(tp, tzp);
	return ((double)tp->tv_sec) * 1000000000.0 +
		((double)tp->tv_usec);
}


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
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
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

void copyArray(int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = arr_orig[i];
	}
}


int main(int argc, char** argv) {

	double mytime2(), starttime = 0, endtime = 0;
	tp = (struct timeval*) calloc(1, sizeof(struct timeval));

	srand(time(NULL));

	if (argc != 3) {
		cout << endl << "    Invalid command. Please try again with this format: srp796 <N> <K>" << endl << endl;
		exit(0);
	}
	int n = std::atoi(argv[1]);
	int k = std::atoi(argv[2]);

	//int n, k;
	//cout << "Enter the number of integer elements: ";
	//cin >> n;
	//cout << "Enter the number k: ";
	//cin >> k;

	// Generating random values
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
		arr_orig[i] = arr[i];
	}


	cout << "Insertion sort : ";
	starttime = mytime2();
	insertionSort(n);
	endtime = mytime2();
	cout << endtime - starttime << " micro seconds" << endl;
	copyArray(n);

	cout << "Merge sort     : ";
	starttime = mytime2();
	mergeSort(0, n - 1);
	endtime = mytime2();
	cout << endtime - starttime << " micro seconds" << endl;
	copyArray(n);

	cout << "Quick Sort     : ";
	starttime = mytime2();
	quickSort(0, n - 1);
	endtime = mytime2();
	cout << endtime - starttime << " micro seconds" << endl;
	copyArray(n);

	cout << "Quick Insertion: ";
	starttime = mytime2();
	quickInsertion(0, n - 1, k);
	endtime = mytime2();
	cout << endtime - starttime << " micro seconds" << endl;

	return 0;
}