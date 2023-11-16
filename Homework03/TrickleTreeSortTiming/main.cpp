/* Kyle Tranfaglia
*  COSC320 - Homework03 - Ex. 2
*  Last updated 09/22/23
*  This program tests the functionality of the IntBinaryTree class that was altered to specialize in sorting 
*  with a complete tree and times the sort for the trickle tree sort and also insertion and bubble sort
*/
#include <iostream>
#include "IntBinaryTree.h"
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Prototypes
void trickleTreeSort(int *A, int size);
void bubble(int A[], int size);
void insertion(int A[], int size);

int main() {
	srand(time(0)); // Sets seed for random number generator

	int size = 0, sort = 0;

	// Gets user input for sort
	cout << "Input Array Size: ";
	cin >> size;
	cout << endl;

	cout << "Time the Tree sort or all of the sorts (1 Tree, 2 all): ";
	cin >> sort;

	int *A = new int[size]; // Dynamically allocate array integer array of size
	// Sets array values between 1 and 100 inclusive for size
	for(int i = 0; i < size; i++) {
        A[i] = ( rand() % 100) + 1;
	}
	// Checks the sorting that the user choose .. if 1, just trickle tree sort, if 2, all sorts, if other give error message and exit the program
	if (sort == 1) { 
		trickleTreeSort(A, size); // Calls trickle tree function
	}
	else if (sort == 2) {
		int *ACopy = new int[size]; // Dynamically allocate array integer array of size

		copy(A, A + size, ACopy); // Copies array A into ACopy
		trickleTreeSort(ACopy, size); // Calls trickle tree function

		copy(A, A + size, ACopy); // Copies array A into ACopy
		insertion(ACopy, size); // Calls insertion function

		copy(A, A + size, ACopy); // Copies array A into ACopy
		bubble(ACopy, size); // Calls bubble function

		delete [] ACopy; // Free the memeory for the dynamically allocated array
	} 
	else {
		delete [] A; // Free the memeory for the dynamically allocated array ... must be done here if the program exits from error before deleting at end of program
		cerr << "Not a valid input ... closing the program" << endl; // Error message
		exit(1); // Error indicated exit of program
	}
	delete [] A; // Free the memeory for the dynamically allocated array
	
	return 0;
}
// Trickle tree sort function to create a binary integer tree and time the trickle tree sort (load and return)
void trickleTreeSort(int *A, int size) {
	IntBinaryTree intTree; // Creates binary integer tree
    
	auto start = high_resolution_clock::now();

	intTree.LoadArray(A, size); // Calls load array function
    intTree.ReturnSortedArray(A, size); // Calls return array function

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time to sort using the trickle tree sort: " << duration.count() / 1000000.0 << " seconds"<< endl;
}
// Insertion sort function to sort a given array and time it
void insertion(int A[], int size) {
	auto start = high_resolution_clock::now();
	// Loop to sort the function using the insertion method		
	for (int i = 0; i < size; i++) {
		int j = 0;
		int val = A[i];
		for (j = i; j > 0 && A[j - 1] > val; j--)
			A[j] = A[j - 1];

		A[j] = val;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time to sort using insertion sort algorithm: " << duration.count() / 1000000.0 << " seconds"<< endl;
}
// bubble sort function to sort a given array and time it
void bubble(int A[], int size) {
	auto start = high_resolution_clock::now();
	// Loop to sort the function using the bubble method		
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (A[j] > A[j + 1]) {
				int temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	
	cout << "Time to sort using bubble sort algorithm: " << duration.count() / 1000000.0 << " seconds"<< endl;
}