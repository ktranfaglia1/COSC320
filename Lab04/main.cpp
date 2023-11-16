/* Kyle Tranfaglia
*  COSC320 - Lab04
*  Last updated 09/20/23
*  This program creates a tree of longs, populates it with random values, and times inorder, preorder, 
*  and postorder for recursive and iterative functions 
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "BinaryTree.h"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0)); // Random seed generator

	BinaryTree<long> longTree; // Create the binary tree.
    long nodeCount = 0; // Variable to hold number of nodes determined by user

    cout << "How many Nodes would you like to add to the tree?: ";
    cin >> nodeCount;

    // Loop to populate tree with random long values for a count provided by the user ... uses insertNode function
	for (int i = 0; i < nodeCount; i++) {
		longTree.insertNode(rand());
	}

    // Timings ... Starts timer, calls function, ends timer, prints time ... repeats for all 7 functions
    auto start = high_resolution_clock::now();

    longTree.incrementInOrder();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementInOrder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementPreOrder();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementPreOrder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementPostOrder();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementPostOrder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementIterativeInorder();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementIterativeInorder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementIterativePreorder();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementIterativePreorder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementIterativePostorder();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementIterativePostorder: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();

    longTree.incrementIterativePostorder2Stacks();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to incrementIterativePostorder2Stacks: " << duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}