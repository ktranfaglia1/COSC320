/* Kyle Tranfaglia
 * COSC320 - Project03
 * 12/01/2023
 * Library of functions to take a matrix reprsentation of a graph, stored as a list of lists, and perform some analyses: cycle detection, minimal spanning tree, traversals, shortest path
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <vector>
#include <deque>

#include "tinyfiledialogs.h"
#include "ListOfLists.h"

using namespace std;

// Prototypes
void Print(ListOfLists<double>);
void breadthFirstTraversal(int, ListOfLists<double>&);
void depthFirstTraversal(int, ListOfLists<double>&);
void DFT(int, vector<int>&, ListOfLists<double>&);
void dijkstra(int, ListOfLists<double>&);
void ford(int, ListOfLists<double>&);
bool istxt(const char*);

int main() {
	ListOfLists<double> adjacencyMatrix;
	vector<double> tempVector;
	string line = "";
	double num = 0;
	// Set-up for tiny dialog box: Gets an Matrix file (.txt) from the user 
    char const *lFilterPatterns[1] = { "*.txt" };
    char *matrixFileName = tinyfd_openFileDialog("Open an adjaceny matrix file", NULL, 1, lFilterPatterns, "adjaceny matrix File", 0);
	// char *matrixFileName = "MatrixTest1.txt";
    fstream matrixFile;

    matrixFile.open(matrixFileName, ios::in); // Opens input file
    // Try to open file and assess its contents. If the file is of the wrong type, fails to open, or fails within iss data extraction, an error will be caught 
    try {
        // Check if the filename is a valid string
        if (!matrixFileName) {
            throw std::invalid_argument("Invalid filename");
        }
        // Uses C-string fucntions to test if the filename ends in '.txt'
        else if (!istxt(matrixFileName)) {
            throw std::ios_base::failure("File must be of type '.txt'");
        }
        // Checks if file opened, if not, throws error
        else if (!matrixFile) {
            throw std::ios_base::failure("Error opening file ... an adjaceny matrix file is required for the program");
        }
        else {
            cout << "Opening " << matrixFileName << endl; // File successfully opened
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
	cout << endl;
	Print(adjacencyMatrix);
	cout << endl;
	dijkstra(0, adjacencyMatrix);

	return 0;
}
// Print function to iteratively display the list of lists in a matrix format
void Print(ListOfLists<double> L) {
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
void breadthFirstTraversal(int startVertex, ListOfLists<double> &matrix) {
	vector<int> visited(matrix.size(), 0); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	deque<double> bftQueue; // Queue (deque) to hold verticies not yet traversed

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
void DFT(int currentVertex, vector<int>& visited, ListOfLists<double> &matrix) {
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
void depthFirstTraversal(int startVertex, ListOfLists<double> &matrix) {
	vector<int> visited(matrix.size(), 0); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	cout << "Depth First Traversal starting from vertex " << static_cast<char>(startVertex + 'A') << ": " << endl;
	DFT(startVertex, visited, matrix); // Call recursive function
	cout << endl;
}
// Fucntion to perform dijsktra's algorithm to find the shortest path from a starting vertex to each other vertex in the graph using a adjacency matrix represented as a list of lists
void dijkstra(int startVertex, ListOfLists<double>& matrix) {
	const double INF = numeric_limits<double>::infinity(); // Store infinity representation for a double
	int matrixSize = matrix.size(); // Get size of matrix
	
	vector<double> distance(matrixSize, INF); // Vector to hold the distances from a vertex (starting vertex) initialized with infinity and will be updated throughout the algorithm
	vector<int> visited(matrixSize, 0); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex

	distance[startVertex] = 0.0; // Sets the starting vertex distance to zero (no distance from start vertex to itself)
	// Start Dijkstra's algorithm and run for one less than matrix size (self min distance already determined)
	for (int i = 0; i < matrixSize - 1; i++) {
		double minDistance = INF; // Initialize minumum distance to infinity for double
		int minIndex = -1; // initialize a minimum index to impossible value
		// Find the vertex with the minimum distance value
		for (int j = 0; j < matrixSize; j++) {
			// Check if vertex has been not been visited and if distance is smaller than current smallest, if so, set the variables
			if (!visited[j] && distance[j] < minDistance) {
				minDistance = distance[j];
				minIndex = j;
			}
		}
		visited[minIndex] = 1; // Denote the selected vertex as visited
		// Loop to update the distances of neighboring vertices
		for (int k = 0; k < matrixSize; k++) {
			// Check that vertex not vistied, an edge exists to the vertex, the distance is not infinity, and finally, if there is a shorter path utilizing a neighboring vertex
			if (!visited[k] && matrix[minIndex][k] != 0.0 && distance[minIndex] != INF && distance[minIndex] + matrix[minIndex][k] < distance[k]) {
				distance[k] = distance[minIndex] + matrix[minIndex][k];
			}
		}
	}
	// Print the final result: The shortest distances from the starting vertex to each vertex in the graph
	cout << "Shortest distances from Vertex " << static_cast<char>('A' + startVertex) << endl;
	for (int i = 0; i < matrixSize; i++) {
		cout << static_cast<char>('A' + startVertex) << " - " << static_cast<char>('A' + i) << ": " << distance[i] << endl;
	}
}
void ford(int startVertex, ListOfLists<double> &matrix) {
	const double INF = numeric_limits<double>::infinity(); // Store infinity representation for a double
	int matrixSize = matrix.size(); // Get size of matrix

	vector<double> distance(matrixSize, INF); // Vector to hold the distances from a vertex (starting vertex) initialized with infinity and will be updated throughout the algorithm

	distance[startVertex] = 0.0; // Sets the starting vertex distance to zero (no distance from start vertex to itself)

	for (int i = 0; i < matrixSize - 1; i++) {
		for (int j = 0; j < matrixSize; j++) {
			for (int k = 0; k < matrixSize; k++) {
				if (distance[j] != INF && distance[j] + matrix[j][k] < distance[k]) {
					distance[k] = distance[j] + matrix[j][k];
					if (distance[k] < 0.0) {
						cout << "Negative Weight Cycle Detected ... Ford's algorithm cannot Compute the shortest path for this matrix" << endl;
						return;
					}
				}
			}
		}
	}
	// Print the final result: The shortest distances from the starting vertex to each vertex in the graph
	cout << "Shortest distances from Vertex " << static_cast<char>('A' + startVertex) << endl;
	for (int i = 0; i < matrixSize; i++) {
		cout << static_cast<char>('A' + startVertex) << " - " << static_cast<char>('A' + i) << ": " << distance[i] << endl;
	}
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