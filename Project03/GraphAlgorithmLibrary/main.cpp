/* Kyle Tranfaglia
 * COSC320 - Project03
 * 12/01/2023
 * Library of functions to take a matrix reprsentation of a graph, stored as a list of lists, and perform some analyses: cycle detection, minimal spanning tree, traversals, shortest path
*/
#include <algorithm>
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
void kruskalAlgorithm(ListOfLists<double>&);
void cycleDFS(int, int &, bool &, vector<double> &, ListOfLists<double>&);
bool detectCycles(ListOfLists<double>&);
bool cycleDFS2(int, int, vector<bool>&, ListOfLists<double>&);
bool detectCycles2(ListOfLists<double>&);
bool istxt(const char*);

int main() {
	ListOfLists<double> adjacencyMatrix;
	vector<double> tempVector;
	string line = "";
	double num = 0;
	// Set-up for tiny dialog box: Gets an N-Gram file (.txt) from the user 
    // char const *lFilterPatterns[1] = { "*.txt" };
    // char *matrixFileName = tinyfd_openFileDialog("Open an adjaceny matrix file", NULL, 1, lFilterPatterns, "adjaceny matrix File", 0);
	char *matrixFileName = "MatrixTest3.txt";
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
	cout << endl;
	ford(0, adjacencyMatrix);
	cout << endl;
	kruskalAlgorithm(adjacencyMatrix);


	if (detectCycles(adjacencyMatrix)) {
		cout << "Matrix contains a cycle" << endl;
	}
	else {
		cout << "Matrix does not contain a cycle" << endl;
	}
	if (detectCycles2(adjacencyMatrix)) {
		cout << "Matrix contains a cycle" << endl;
	}
	else {
		cout << "Matrix does not contain a cycle" << endl;
	}
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
// Fucntion to perform Dijsktra's algorithm to find the shortest path from a starting vertex to each other vertex in the graph using a adjacency matrix represented as a list of lists
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
			// Check that vertex not vistied, an edge exists to the vertex, the distance is valid (not INF), and finally, if there is a shorter path utilizing a neighboring vertex
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
// Fucntion to perform Fords's algorithm to find the shortest path from a starting vertex to each other vertex in the graph using a adjacency matrix represented as a list of lists
void ford(int startVertex, ListOfLists<double> &matrix) {
	const double INF = numeric_limits<double>::infinity(); // Store infinity representation for a double
	int matrixSize = matrix.size(); // Get size of matrix

	vector<double> distance(matrixSize, INF); // Vector to hold the distances from a vertex (starting vertex) initialized with infinity and will be updated throughout the algorithm

	distance[startVertex] = 0.0; // Sets the starting vertex distance to zero (no distance from start vertex to itself)
	// Fords algorithm to iteratively relax the over-estimated weights (INF) and continue to update the path weight until shortest path is determined
	for (int i = 0; i < matrixSize - 1; i++) {
		for (int j = 0; j < matrixSize; j++) {
			for (int k = 0; k < matrixSize; k++) {
				// Checks if the edge to vertex exists, if its a valid path distance (not INF), and if the path is shorter than what is currently stored 
				if (matrix[j][k] != 0.0 && distance[j] != INF && distance[j] + matrix[j][k] < distance[k]) {
					distance[k] = distance[j] + matrix[j][k];
				}
			}
		}
	}
	// Error Check Ford Algorithm: Tests if there is a negative weight cycles which causes Ford's algorithm to fail and thus we must return without printing the incorrect result 
	for (int j = 0; j < matrixSize; j++) {
		for (int k = 0; k < matrixSize; k++) {
			// Checks if the edge to vertex exists, if its a valid path distance (not INF), and if the path is shorter than what is currently stored ... If this continues Ford's Algorithm so there is a negative weight cycle
			if (matrix[j][k] != 0.0 && distance[j] != INF && distance[j] + matrix[j][k] < distance[k]) {
				cout << "Negative Weight Cycle Detected ... Ford's algorithm cannot Compute the shortest path for this matrix" << endl;
				return; // Return after error message to avoid the result print out
			}
		}
	}
	// Print the final result: The shortest distances from the starting vertex to each vertex in the graph
	cout << "Shortest distances from Vertex " << static_cast<char>('A' + startVertex) << endl;
	for (int i = 0; i < matrixSize; i++) {
		cout << static_cast<char>('A' + startVertex) << " - " << static_cast<char>('A' + i) << ": " << distance[i] << endl;
	}
}
// *Note: The following version of cycle detection only works on directed graphs
// Set-up function for cycle detection using a adjacency matrix represented as a list of lists to represent a graph - calls recursive DFS function to detect a cycle
bool detectCycles(ListOfLists<double> &matrix) {
	// Variables
	vector<double> num; // Vector to hold vertex values
	int count = 1; // Counter
	bool cycle = false; // Store cycle detection results
	// Initialize the number vector with 0s
	for (int i = 0; i < matrix.size(); i++) {
		num.push_back(0);
	}
	// Search for a cycle as long as there exists a 0 in the number vector ... will equal num.end() when find fails and exit loop
	while (find(num.begin(), num.end(), 0) < num.end()) {
		int pos = find(num.begin(), num.end(), 0) - num.begin(); // Get the position of the 0
		cycleDFS(pos, count, cycle, num, matrix); // Call recursive DFS function to detect a cycle
	}
	return cycle;
}
// *Note: The following version of cycle detection only works on directed graphs
// Recursive DFS function to detect a cycle
void cycleDFS(int pos, int &count, bool &cycle, vector<double> &num, ListOfLists<double> &matrix) {
	// Variables
	const double INF = numeric_limits<double>::infinity(); // Store infinity representation for a double
	vector<double> Adj = matrix[pos]; // Get the nested list of vertex connections
	num[pos] = count++; // Set number vector at position to count
	// Loop through entire vertex adjacency vector and check for non-zero values 
	for (long unsigned int i = 0; i < Adj.size(); i++) {
		double vertex = Adj[i]; // Get vertex value
		// check for non-zero vertex
		if (vertex != 0.0) {
			// Check if number is 0
			if (num[i] == 0.0) {
				cycleDFS(i, count, cycle, num, matrix); // Recursive call
			} 
			// Check if number is INF
			else if (num[i] != INF) {
				cycle = true; // Cycle found!
			}
		}
	}
	num[pos] = INF; // Sets number vector at position to INF (no longer count)
}
// *Note: The following version of cycle detection only works on undirected graphs
// Alternative method to detecting cycles: Set-up function for cycle detection using a adjacency matrix represented as a list of lists to represent a graph - calls recursive DFS function to detect a cycle
bool detectCycles2(ListOfLists<double> &matrix) {
    int matrixSize = matrix.size(); // Store matrix size
	// Boolean vectors to track visited vertices
    vector<bool> visited(matrixSize, false);
	// Perform a DFS with recursive function for all vertices
    for (int i = 0; i < matrixSize; ++i) {
		// If vertex has not been visited
        if (!visited[i]) {
			// Call recursive function to check for a cycle ... returns true if cycle found
            if (cycleDFS2(i, -1, visited, matrix)) {
                return true;
			}
        }
    }
    return false;
}
// *Note: The following version of cycle detection only works on undirected graphs
// Alternative method to detecting cycles: Recursive DFS function to detect a cycle
bool cycleDFS2(int vertex, int parent, vector<bool>& visited, ListOfLists<double> &matrix) {
	// Set the current vertex as visited
    visited[vertex] = true;
	// Traverse all the neighboring (adjacent) verticies to the current vertex
    for (int i = 0; i < matrix.size(); ++i) {
		// Check if there is an edge from the current vertex to its neighbor 
        if (matrix[vertex][i] != 0.0) {
			// If the neighbor is not visited, check for cycles with recursive calls
            if (!visited[i]) {
				// Call recursive function to check for a cycle ... returns true if cycle found
                if (cycleDFS2(i, vertex, visited, matrix)) {
                    return true;
				}
            }
			// If the neighbor is visited and not the parent, a back edge is detected and there exists a cycle, so retrun true
			else if (i != parent) {
                return true;
            }
        }
    }
    return false;
}
void kruskalAlgorithm(ListOfLists<double> &matrix) {
	// Variables
    int matrixSize = matrix.size();
    vector<pair<int, int>> edges;
    ListOfLists<double> minimumSpanningTree(matrixSize, matrixSize);

    // Build edges from the matrix's adjacency matrix
    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            if (matrix[i][j] != 0.0) {
                edges.emplace_back(i, j);
            }
        }
    }

    // Sort edges by weight in ascending order
    sort(edges.begin(), edges.end());

    for (const auto& edge : edges) {
        minimumSpanningTree[edge.first][edge.second] = matrix[edge.first][edge.second];
        minimumSpanningTree[edge.second][edge.first] = matrix[edge.first][edge.second];
		
        if (detectCycles2(minimumSpanningTree)) {
            minimumSpanningTree[edge.first][edge.second] = minimumSpanningTree[edge.second][edge.first] = 0.0; // Remove the last edge if it creates a cycle
		}
	}
	Print(minimumSpanningTree);

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