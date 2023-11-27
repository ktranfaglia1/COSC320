/* Kyle Tranfaglia
 * COSC320 - Project03
 * 12/01/2023
 * Library of functions to take a matrix reprsentation of a graph, stored as a list of lists, and perform some analyses: cycle detection, minimal spanning tree, traversals, shortest path
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <deque>

#include "tinyfiledialogs.h"
#include "ListOfLists.h"

using namespace std;

// Prototypes
void Print(ListOfLists<int>);
void breadthFirstTraversal(int, ListOfLists<int>);
void depthFirstTraversal(int, ListOfLists<int>);
void DFT(int, vector<int>&, ListOfLists<int>);
bool istxt(const char*);


int main() {
	ListOfLists<int> adjacencyMatrix;
	vector<int> tempVector;
	string line = "";
	double num = 0;
	// Set-up for tiny dialog box: Gets an N-Gram file (.txt) from the user 
    char const *lFilterPatterns[1] = { "*.txt" };
    char *matrixFilename = tinyfd_openFileDialog("Open an adjaceny matrix file", NULL, 1, lFilterPatterns, "adjaceny matrix File", 0);
    fstream matrixFile;

    matrixFile.open(matrixFilename, ios::in); // Opens input file
    // Try to open file and assess its contents. If the file is of the wrong type, fails to open, or fails within iss data extraction, an error will be caught 
    try {
        // Check if the filename is a valid string
        if (!matrixFilename) {
            throw std::invalid_argument("Invalid filename");
        }
        // Uses C-string fucntions to test if the filename ends in '.txt'
        else if (!istxt(matrixFilename)) {
            throw std::ios_base::failure("File must be of type '.txt'");
        }
        // Checks if file opened, if not, throws error
        else if (!matrixFile) {
            throw std::ios_base::failure("Error opening file ... an adjaceny matrix file is required for the program");
        }
        else {
            cout << "Opening " << matrixFilename << endl; // File successfully opened
            while (!matrixFile.eof() || !tempVector.empty()) {
				if (tempVector.empty()) {
					matrixFile >> num;
					tempVector.push_back(num);
				}
				else if (matrixFile.get() == ' ') {
					matrixFile >> num;
					tempVector.push_back(num);
				}
				else {
					adjacencyMatrix.push_back(tempVector);
					tempVector.clear();
				}
			}
			matrixFile.close(); // Closes input file
            cout << "adjaceny matrix file loaded" << endl;
        }
    } // If there is an error thrown, catch it and print the error with a program exit
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
	Print(adjacencyMatrix);

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
// Function to check that the file extension is "txt"
bool istxt(const char* filename) {
    bool status = true;
    // Get the length of the filename
    size_t len = strlen(filename);
    // Uses C-string functions to check that the file extension is ".txt"
    if (len < 4 || strcmp(filename + len - 4, ".txt") != 0) {
        status = false;
    }
    return status;
}