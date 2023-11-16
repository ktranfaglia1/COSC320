/* Kyle Tranfaglia
*  COSC320 - Homework03 - Ex. 1
*  Last updated 09/22/23
*  This program tests the functionality of the IntBinaryTree class that was altered to specialize in sorting with a complete tree
*/
#include <iostream>
#include "IntBinaryTree.h"

using namespace std;

int main() {
	srand(time(0)); // Sets seed for random number generator
	int size = 0;

	cout << "Input Array Size: ";
	cin >> size;

	int *A = new int[size];

	// Sets array values between 1 and 100 inclusive for size ... prints the values as they are assigned
	for (int i = 0; i < size; i++) {
		A[i] = (rand() % 100) + 1;
		cout << A[i] << " ";
	}
	cout << endl;
	
	IntBinaryTree intTree; // Creates binary tree

	intTree.LoadArray(A, size); // Calls function to load array into tree

	intTree.PrintTree(); // Prints the tree after loaded

	intTree.ReturnSortedArray(A, size); // Returns the array (updated by paramter reference) as sorted

	// Loop to print all the elements of the array
	for (int i = 0; i < size; i++) {
		cout << A[i] << " ";
	}
	cout << endl;

	delete [] A; // Free the memeory for the dynamically allocated array
	
	return 0;
}