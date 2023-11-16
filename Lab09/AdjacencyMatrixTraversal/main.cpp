/* Kyle Tranfaglia
 * COSC320 - Lab09
 * 11/17/2023
 * Program to take a matrix reprsentation of a graph, stored as a list of lists, and do a breadth-first and depth-first search
*/
#include <iostream>
#include <vector>
#include <deque>

#include "ListOfLists.h"

using namespace std;

// Prototypes
void Print(ListOfLists<int>);
void breadthFirstTraversal(int, ListOfLists<int>);
void depthFirstTraversal(int, ListOfLists<int>);
void DFT(int, vector<int>&, ListOfLists<int>);

int main() {
	ListOfLists<int> matrix1(7, 7); // First matrix, 7x7

	cout << "Matrix 1" << endl << "--------" << endl << endl;

	// Set matrix ... position one 0 is A, 1 is B ... 1 in the matrix represents a mapping and 0 represents no existing edge
	matrix1[0] = { 0, 1, 1, 0, 1, 0, 1 };
	matrix1[1] = { 0, 1, 0, 1, 1, 0, 0 };
	matrix1[2] = { 1, 1, 0, 0, 0, 1, 1 };
	matrix1[3] = { 0, 0, 0, 0, 0, 1, 1 };
	matrix1[4] = { 1, 0, 0, 1, 0, 1, 0 };
	matrix1[5] = { 1, 0, 0, 0, 1, 0, 0 };
	matrix1[6] = { 0, 1, 0, 1, 0, 0, 0 };

	// Test breadth-first and depth-first Traversals (Searches) for the matrix representation of a graph and print the matrix
	breadthFirstTraversal(0, matrix1);
	cout << endl;
	depthFirstTraversal(0, matrix1);
	Print(matrix1);
	cout << endl;

	ListOfLists<int> matrix2(10, 10); // Second matrix, 10x10

	cout << "Matrix 2" << endl << "--------" << endl << endl;

	// Set matrix ... position one 0 is A, 1 is B ... 1 in the matrix represents a mapping and 0 represents no existing edge
	matrix2[0] = { 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 };
	matrix2[1] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 };
	matrix2[2] = { 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 };
	matrix2[3] = { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 };
	matrix2[4] = { 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 };
	matrix2[5] = { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
	matrix2[6] = { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0 };
	matrix2[7] = { 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 };
	matrix2[8] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 };
	matrix2[9] = { 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 };

	// Test breadth-first and depth-first Traversals (Searches) for the matrix representation of a graph and print the matrix
	breadthFirstTraversal(0, matrix2);
	cout << endl;
	depthFirstTraversal(0, matrix2);
	Print(matrix2);
	cout << endl;

	ListOfLists<int> matrix3(10, 10); // Third matrix, 10x10

	cout << "Matrix 3" << endl << "--------" << endl << endl;

	// Set matrix ... position one 0 is A, 1 is B ... 1 in the matrix represents a mapping and 0 represents no existing edge
	matrix3[0] = { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 };
	matrix3[1] = { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 };
	matrix3[2] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };
	matrix3[3] = { 0, 0, 1, 0, 1, 1, 0, 1, 0, 0 };
	matrix3[4] = { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 };
	matrix3[5] = { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 };
	matrix3[6] = { 0, 0, 1, 0, 1, 1, 0, 1, 0, 0 };
	matrix3[7] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };
	matrix3[8] = { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 };
	matrix3[9] = { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 };

	// Test breadth-first and depth-first Traversals (Searches) for the matrix representation of a graph and print the matrix
	breadthFirstTraversal(3, matrix3);
	cout << endl;
	depthFirstTraversal(8, matrix3);
	Print(matrix3);
	cout << endl;

	return 0;
}
// Print function to iteratively display the list of lists in a matrix format
void Print(ListOfLists<int> L) {
	if (L.size() == 0)
		return;
	// Loop to print each column values for all rows of the list of lists - formated to construct a matrix
	for (int i = 0; i < L.size(); i++) {
		for (unsigned int j = 0; j < L[i].size(); j++)
			cout << L[i][j] << " ";
		cout << endl;
	}
}
// Function to perform a breadth-first search on a matrix reprsented as a list of lists
void breadthFirstTraversal(int startVertex, ListOfLists<int> matrix) {
	vector<int> visited(matrix.size(), 0); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	deque<int> bftQueue; // Queue (deque) to hold verticies not yet traversed

	visited[startVertex] = 1; // Starting vertex visited
	cout << "Breadth First Traversal starting from vertex " << static_cast<char>(startVertex + 'A') << ": " << endl;

	bftQueue.push_back(startVertex); // enque starting vertex
	// Loop until all verticies are traversed ... queue is empty
	while (!bftQueue.empty()) {
		int currentVertex = bftQueue.front(); // Store current vertex from front of queue
		bftQueue.pop_front(); // Removed vertex from queue
		// Loop to run for matrix size and check all possible mappings
		for (int i = 0; i < matrix.size(); ++i) {
			// Check if there is a mapping and the vertex has not been visited
			if (matrix[currentVertex][i] == 1 && !visited[i]) {
				cout << static_cast<char>(currentVertex + 'A') << " - " << static_cast<char>(i + 'A') << endl; // Print mapping
				visited[i] = 1; // Set visited to true
				bftQueue.push_back(i); // Push the visited vertex to queue
			}
		}
	}
}
// Function to recursively and iteravely performn a depth-first search on a matrix reprsented as a list of lists
void DFT(int currentVertex, vector<int>& visited, ListOfLists<int> matrix) {
	visited[currentVertex] = 1; // Starting vertex visited
	// Loop to iterate for matrix size
	for (int i = 0; i < matrix.size(); i++) {
		// Check if there is a mapping and the vertex has not been visited
		if (matrix[currentVertex][i] == 1 && !visited[i]) {
			cout << static_cast<char>(currentVertex + 'A') << " - " << static_cast<char>(i + 'A') << endl; // Print mapping
			DFT(i, visited, matrix); // Recursive call
		}
	}
}
// Function to set up and call the recursive depth-first search function
void depthFirstTraversal(int startVertex, ListOfLists<int> matrix) {
	vector<int> visited(matrix.size(), 0); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	cout << "Depth First Traversal starting from vertex " << static_cast<char>(startVertex + 'A') << ": " << endl;
	DFT(startVertex, visited, matrix); // Call recursive function
	cout << endl;
}