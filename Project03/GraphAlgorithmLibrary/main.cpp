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
#include <set>

#include "tinyfiledialogs.h"
#include "ListOfLists.h"

using namespace std;

// Prototypes
void breadthFirstTraversal(int, ListOfLists<double>&);
void depthFirstTraversal(int, ListOfLists<double>&);
void DFT(int, vector<bool>&, ListOfLists<double>&);
void DFS(int, vector<bool>&, ListOfLists<double>&);
void dijkstra(int, ListOfLists<double>&);
void ford(int, ListOfLists<double>&);
void kruskal(ListOfLists<double>&);
void boruvka(ListOfLists<double>&);
void jarnikPrim(ListOfLists<double>&);
void printShortestPath(int, vector<double>&);
void printMST(ListOfLists<double>&);
void Print(ListOfLists<double>&);
bool detectCycles(ListOfLists<double>&);
void cycleDFS(int, int &, bool &, vector<double>&, ListOfLists<double>&);
bool detectCycles2(ListOfLists<double>&);
bool cycleDFS2(int, int, vector<bool>&, ListOfLists<double>&);
bool isConnected(ListOfLists<double>&);
bool isSymmetric(ListOfLists<double>&);
bool istxt(const char*);

int main() {
	// Variables
	ListOfLists<double> adjacencyMatrix;
	vector<double> tempVector;
	string line = "";
	double num = 0;
	// Set-up for tiny dialog box: Gets an N-Gram file (.txt) from the user 
    char const *lFilterPatterns[1] = { "*.txt" };
    char *matrixFileName = tinyfd_openFileDialog("Open an adjaceny matrix file", NULL, 1, lFilterPatterns, "adjaceny matrix File", 0);
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
			// Load in the matrix ... while end of file not reached and vector contains elements
            while (!matrixFile.eof() || !tempVector.empty()) {
				// If Vector empty then newline reached, so get the value
				if (tempVector.empty()) {
					matrixFile >> num;
					tempVector.push_back(num);
				}
				// If a space is retrieved, capture the number following the space
				else if (matrixFile.peek() == ' ') {
					matrixFile.get();
					matrixFile >> num;
					tempVector.push_back(num);
				}
				// Otherwise, end of line must be reached, so add vector to lsit of list and clear it to store next row
				else {
					adjacencyMatrix.push_back(tempVector);
					tempVector.clear();
				}
			}
			matrixFile.close(); // Closes input file
            cout << "Adjaceny matrix file loaded" << endl;
        }
    } // If there is an error thrown, catch it and print the error with a program exit
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
	// Print Matrix
	cout << endl << "Matrix\n------" << endl;
	Print(adjacencyMatrix);
	cout << endl;
	// Do the Traversals
	depthFirstTraversal(0, adjacencyMatrix);
	breadthFirstTraversal(0, adjacencyMatrix);
	// Do the Algorithms
	cout << "\nDijkstra's algorithm\n--------------------" << endl;
	dijkstra(0, adjacencyMatrix);
	cout << "\nFord's algorithm\n----------------" << endl;
	ford(0, adjacencyMatrix);
	// Check if the matrix is symmetric (undirected) to determine the appropriate cycle detection function and if Kruskal's, Boruvka's, and Jarnik & Prim's algorithm can be used (connected undirected graph)
	if (!isSymmetric(adjacencyMatrix)) {
		cout << "\nThis is a directed graph" << endl; // Not symmetric matrix, so graph is directed
		if (detectCycles(adjacencyMatrix)) {
			cout << "Matrix contains a cycle" << endl;
		}
		else {
			cout << "Matrix does not contain a cycle" << endl;
		}
	}
	else {
		// Check if matrix is connected, then continue with Kruskal's, Boruvka's, and Jarnik & Prim's algorithm
		if (isConnected(adjacencyMatrix)) {
			cout << "\nKruskal's algorithm\n-------------------" << endl;
			kruskal(adjacencyMatrix);
			cout << "\nBoruvka's algorithm\n-------------------" << endl;
			boruvka(adjacencyMatrix);
			cout << "\nJarnik & Prim's algorithm\n-------------------------" << endl;
			jarnikPrim(adjacencyMatrix);
		}
		cout << "\nThis is an undirected graph" << endl; // Symmetric matrix, so graph is undirected
		if (detectCycles2(adjacencyMatrix)) {
			cout << "Matrix contains a cycle" << endl;
		}
		else {
			cout << "Matrix does not contain a cycle" << endl;
		}
	}
	return 0;
}
// Function to perform a breadth-first search on a matrix reprsented as a list of lists
void breadthFirstTraversal(int startVertex, ListOfLists<double> &matrix) {
	vector<bool> visited(matrix.size(), false); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	deque<double> bftQueue; // Queue (deque) to hold verticies not yet traversed

	visited[startVertex] = true; // Starting vertex visited
	cout << "Breadth First Traversal starting from vertex " << static_cast<char>(startVertex + 'A') << ": " << endl;

	bftQueue.push_back(startVertex); // enque starting vertex
	// Loop until all verticies are traversed ... queue is empty
	while (!bftQueue.empty()) {
		int currentVertex = bftQueue.front(); // Store current vertex from front of queue
		bftQueue.pop_front(); // Removed vertex from queue
		// Loop to run for matrix size and check all possible mappings
		for (int i = 0; i < matrix.size(); ++i) {
			// Check if there is a mapping and the vertex has not been visited
			if (matrix[currentVertex][i] != 0 && !visited[i]) {
				cout << static_cast<char>(currentVertex + 'A') << " - " << static_cast<char>(i + 'A') << endl; // Print mapping
				visited[i] = true; // Set visited to true
				bftQueue.push_back(i); // Push the visited vertex to queue
			}
		}
	}
}
// Function to set up and call the recursive depth-first search function
void depthFirstTraversal(int startVertex, ListOfLists<double> &matrix) {
	vector<bool> visited(matrix.size(), false); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex
	cout << "Depth First Traversal starting from vertex " << static_cast<char>(startVertex + 'A') << ": " << endl;
	DFT(startVertex, visited, matrix); // Call recursive function
	cout << endl;
}
// Function to recursively and iteravely performn a depth-first search on a matrix reprsented as a list of lists and print the traversal
void DFT(int currentVertex, vector<bool> &visited, ListOfLists<double> &matrix) {
	visited[currentVertex] = true; // Starting vertex visited
	// Loop to iterate for matrix size
	for (int i = 0; i < matrix.size(); i++) {
		// Check if there is a mapping and the vertex has not been visited
		if (matrix[currentVertex][i] != 0 && !visited[i]) {
			cout << static_cast<char>(currentVertex + 'A') << " - " << static_cast<char>(i + 'A') << endl; // Print mapping
			DFT(i, visited, matrix); // Recursive call
		}
	}
}
// Function to recursively and iteravely performn a depth-first search on a matrix reprsented as a list of lists without printing (search only)
void DFS(int currentVertex, vector<bool> &visited, ListOfLists<double> &matrix) {
	visited[currentVertex] = true; // Starting vertex visited
	// Loop to iterate for matrix size
	for (int i = 0; i < matrix.size(); i++) {
		// Check if there is a mapping and the vertex has not been visited
		if (matrix[currentVertex][i] != 0 && !visited[i]) {
			DFS(i, visited, matrix); // Recursive call
		}
	}
}
// Fucntion to perform Dijsktra's algorithm to find the shortest path from a starting vertex to each other vertex in the graph using a adjacency matrix represented as a list of lists
void dijkstra(int startVertex, ListOfLists<double>& matrix) {
	const double INF = numeric_limits<double>::infinity(); // Store infinity representation for a double
	int matrixSize = matrix.size(); // Get size of matrix
	
	vector<double> distance(matrixSize, INF); // Vector to hold the distances from a vertex (starting vertex) initialized with infinity and will be updated throughout the algorithm
	vector<bool> visited(matrixSize, false); // Vector to track visited verticies initialized with size of list set to 0 ... 1 represents a vistited vertex

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
		visited[minIndex] = true; // Denote the selected vertex as visited
		// Loop to update the distances of neighboring vertices
		for (int k = 0; k < matrixSize; k++) {
			// Check that vertex not vistied, an edge exists to the vertex, the distance is valid (not INF), and finally, if there is a shorter path utilizing a neighboring vertex
			if (!visited[k] && matrix[minIndex][k] != 0.0 && distance[minIndex] != INF && distance[minIndex] + matrix[minIndex][k] < distance[k]) {
				distance[k] = distance[minIndex] + matrix[minIndex][k];
			}
		}
	}
	printShortestPath(startVertex, distance); // Print the shortest path
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
	printShortestPath(startVertex, distance); // Print the shortest path
}
// Fucntion to perform kruskal's algorithm to find a minimal spanning tree of a connected undirected graph using an adjacency matrix represented as a list of lists
void kruskal(ListOfLists<double> &matrix) {
	// Variables
    int matrixSize = matrix.size(); // Store matrix size
    vector<pair<int, int>> edges; // Create a vector pair to represent the edges in the graph (from and to verticies)
    ListOfLists<double> minimumSpanningTree(matrixSize, matrixSize); // Create a matrix to hold the minimum spanning tree
    // Build edges from the matrix's adjacency matrix by going through entire matrix
    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
			// Check that there exists an edge (not zero)
            if (matrix[i][j] != 0.0) {
                edges.emplace_back(i, j); // Create and insert the edge in the vector of edges
            }
        }
    }
    // Sort edges by weight in ascending order ... I am unsure how I feel about writing the comparator this way
    sort(edges.begin(), edges.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
        return matrix[a.first][a.second] < matrix[b.first][b.second];
    });
	// Get the weights of all the edges in the graph, from smallest to largest weighted edge, and assign them to the minimal spanning tree ... If adding an edge weight creates a cycle, remove it
    for (const auto& edge : edges) {
		// Gets both row and column representation of edge weight (symmetric since graph must be undriected)
        minimumSpanningTree[edge.first][edge.second] = minimumSpanningTree[edge.second][edge.first] = matrix[edge.first][edge.second];
		// Check if adding an edge weight creates a cycle, if so, remove it
        if (detectCycles2(minimumSpanningTree)) {
            minimumSpanningTree[edge.first][edge.second] = minimumSpanningTree[edge.second][edge.first] = 0.0; // Remove the last edge if it creates a cycle
		}
	}
	printMST(minimumSpanningTree); // Display minimum spannign tree 
	cout << endl;
	Print(minimumSpanningTree); // Display the minimum spanning tree as matrix
}
// Fucntion to perform Boruvka's algorithm to find a minimal spanning tree of a connected undirected graph using an adjacency matrix represented as a list of lists
void boruvka(ListOfLists<double> &matrix) {
	int matrixSize = matrix.size(); // Store matrix size
	ListOfLists<double> minimumSpanningTree(matrixSize, matrixSize); // Create minimum spanning tree
	vector<pair<int, pair<int, int>>> edges;  // create vector to store all edges with their endpoints
	vector<int> treeRoot(matrixSize); // Vector to represent the one-node trees (vertex is root)
    // Initialize each vertex as the root of its own tree
    for (int i = 0; i < matrixSize; ++i) {
        treeRoot[i] = i;
    }
	// Boruvka's algorithm Try to run forever ... will stop when only one tree exists (break)
    while (1) {
        vector<double> minEdgeWeight(matrixSize, numeric_limits<double>::infinity()); // Create vector to hold a minimum edge
        vector<pair<int, int>> minEdge(matrixSize, {-1, -1}); // Create parallel vector to hold the minimum edge
		int tempI = 0, tempJ = 0;
        // Iterate through each edge (all indices of matrix) and update minimum weight edges
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
				// If there exists an edge
                if (matrix[i][j] != 0.0) {
                    tempI = treeRoot[i];
                    tempJ = treeRoot[j];
					// Check for minimum weight edge and update the vectors to store the edge information .. in the case of edges to self, we do not want to consider it
                    if (tempI != tempJ && matrix[i][j] < minEdgeWeight[tempI]) {
                        minEdgeWeight[tempI] = matrix[i][j];
                        minEdge[tempI] = {i, j};
                    }
                }
            }
        }
        // Check how many unique trees are left remaining
        int uniqueTree = 0;
        for (int i = 0; i < matrixSize; ++i) {
			// Check if unique tree (vertex is root of its own tree)
            if (treeRoot[i] == i) {
                ++uniqueTree;
            }
        }
		// Check if only one unique tree left, if so, the minimum spanning tree is formed (break loop condition)
        if (uniqueTree == 1) {
            break; 
        }
        // Combine trees (make forest or add to forest) based on the minimum weight edges
        for (int i = 0; i < matrixSize; ++i) {
            if (minEdge[i].first != -1) {
                tempI = treeRoot[minEdge[i].first];
                tempJ = treeRoot[minEdge[i].second];
				// Check if the verticies belong to different trees
                if (tempI != tempJ) {
                    treeRoot[tempJ] = tempI; // Combine the trees
                    // Update the graph to reflect the new forest structure
                    for (int k = 0; k < matrixSize; ++k) { 
                        if (treeRoot[k] == tempJ) {
                            treeRoot[k] = tempI;
                        }
                    }
                    // Store the edge in the minimum spanning tree adjacency matrix
					minimumSpanningTree[minEdge[i].first][minEdge[i].second] = minimumSpanningTree[minEdge[i].second][minEdge[i].first] = matrix[minEdge[i].first][minEdge[i].second];
                }
            }
        }
    }
	printMST(minimumSpanningTree); // Display minimum spannign tree
	cout << endl;
	Print(minimumSpanningTree); // Display the minimum spanning tree as matrix
}
void jarnikPrim(ListOfLists<double>& matrix) {
	int matrixSize = matrix.size(); // Store the size of the graph
	vector<bool> inTree(matrixSize, false); // Array to keep track of whether a vertex is included in the minimum spanning tree
	vector<pair<pair<int, int>, double>> edges; // List to store all edges of the graph and their weights, sorted by weight
    ListOfLists<double> minimumSpanningTree(matrixSize, matrixSize); // Initialize a list to store the resulting minimum spanning tree
    // Populate the edges vector with non-zero (existing) edges from the matrix
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = i + 1; j < matrixSize; ++j) {
			// If the edge exists (non-zero), make the pair representation of the edge with its weight and add it to edge vector
            if (matrix[i][j] != 0.0) {
                edges.emplace_back(make_pair(i, j), matrix[i][j]);
            }
        }
    }
	// Sort edges based on their weights in ascending order with the denoted comparator (compare weights)
    sort(edges.begin(), edges.end(), [](const pair<pair<int, int>, double>& a, const pair<pair<int, int>, double>& b) {
		return a.second < b.second;
	});

    inTree[0] = true; // Add the first vertex to the tree
    // Iterate through all edges and add them to the minimum spanning tree if they satisfy the required conditions
    for (int i = 1; i < matrixSize; i++) {
        for (const auto& edge : edges) {
            int u = edge.first.first;
            int v = edge.first.second;
			// Check if one vertex is in the tree (MST) and the other is not
            if ((inTree[u] && !inTree[v]) || (inTree[v] && !inTree[u])) {
                minimumSpanningTree[u][v] = minimumSpanningTree[v][u] = matrix[u][v]; // Add the edge to the minimum spanning tree
                inTree[u] = inTree[v] = true; // Denote the vertices as in the tree
                break; // Edge added, break out of inner loop
            }
        }
    }
	printMST(minimumSpanningTree); // Display minimum spannign tree
	cout << endl;
	Print(minimumSpanningTree); // Display the minimum spanning tree as matrix
}
// Print function for the shortest path of a graph to iteratively display the edges and weights
void printShortestPath(int startVertex, vector<double> &distance) {
	// Print the final result: The shortest distances from the starting vertex to each vertex in the graph
	cout << "Shortest distances from Vertex " << static_cast<char>('A' + startVertex) << endl;
	// Print the shortest path by looping through the entire distance vector and listing the distances to each vertex from the starting vertex
	for (long unsigned int i = 0; i < distance.size(); i++) {
		cout << static_cast<char>('A' + startVertex) << " - " << static_cast<char>('A' + i) << ": " << distance[i] << endl;
	}
}
// Print function for a minimial spanning tree to iteratively display the edges and weights
void printMST(ListOfLists<double> &matrix) {
	int matrixSize = matrix.size(); // Store matrix size
	// Print the minimum spanning tree by looping through the entire minimal spanning tree matrix
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
			// If there exists an edge in the minimal spanning tree, print the edge
            if (matrix[i][j] != 0.0) {
                cout << static_cast<char>('A' + i) << " - " << static_cast<char>('A' + j) << ": " << matrix[i][j] << endl;
            }
        }
    }
}
// Print function to iteratively display the list of lists in a matrix format
void Print(ListOfLists<double> &L) {
	if (L.size() == 0)
		return;
	// Loop to print each column values for all rows of the list of lists - formated to construct a matrix
	for (int i = 0; i < L.size(); i++) {
		for (unsigned int j = 0; j < L[i].size(); j++)
			cout << L[i][j] << " ";
		cout << endl;
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
    vector<bool> visited(matrixSize, false); // Boolean vector to track visited vertices
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
bool cycleDFS2(int vertex, int parent, vector<bool> &visited, ListOfLists<double> &matrix) {
    visited[vertex] = true; // Set the current vertex as visited
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
// Function to check if the matrix represents a connected graph
bool isConnected(ListOfLists<double> &matrix) {
    int matrixSize = matrix.size();
    // If only one vertex, it is connected
    if (matrixSize < 2) {
        return true;
    }
    vector<bool> visited(matrixSize, false); // Create vector to keep track of visited vertices during DFT

    DFS(0, visited, matrix); // Perform DFT starting from the first vertex
    // Check if all the vertices were visited
    for (bool isVisited : visited) {
		// If the vertex is not visited, so the graph is not connected
        if (!isVisited) {
            return false;
        }
    }
    return true; // All the vertices were visited, so the graph is connected
}
// Function to determine if a matrix represented as a list of lists is symmetric, meaning the graph is undirected
bool isSymmetric(ListOfLists<double>& matrix) {
    // Check if the matrix is symmetric by comparing the matrix at each lower triangular position and its diagonal mirrior 
    for (int i = 1; i < matrix.size(); i++) {
        for (int j = 0; j < i; j++) {
			// Check if matrix at position and its diagonal mirrior are the same, if not, return false ... matrix is not symmetric
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
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