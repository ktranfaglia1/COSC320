/* Kyle Tranfaglia
*  COSC320 - Lab05
*  Last updated 10/04/23
*  This program creates two binary trees and an AVL tree of integers and times the insertion of n elements with balance
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "BinaryTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0)); // Random seed generator
    // Variables
    BinaryTree<int> intBinaryTree1, intBinaryTree2; // Create the binary tree.
    AVLTree<int> intAVLTree; // Create the AVL tree
    int n = 0, maxrand = 0, b = 0; // Variable to hold number of nodes to insert determined by user

    // Gets user input for variables to influence timing results
    cout << "Enter the number of nodes to insert into the tree: ";
    cin >> n;

    cout << "Enter the max random value for the node insertion (not inclusive): ";
    cin >> maxrand;

    cout << "Enter the amount of insertions before a balance for Binary Tree 2: ";
    cin >> b;
    b = n/2;

    // Timing for insertions and balance
    auto start = high_resolution_clock::now();
    // Loop to insert n elements into AVL tree with random numbers [0, maxRand)
    for (int i = 0; i < n; i++) {
		intAVLTree.insertNode(rand() % maxrand);
	}
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time to insert " << n << " nodes in an AVL Tree: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();
    // Loop to insert n elements into Binary tree with random numbers [0, maxRand), then balances once at the end
    for (int i = 0; i < n; i++) {
		intBinaryTree1.insertNode(rand() % maxrand);
	}
    intBinaryTree1.balance();

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to insert " << n << " nodes in Binary Tree + DSW balance: " << duration.count() / 1000000.0 << " seconds" << endl;

    start = high_resolution_clock::now();
    // Loop to insert n elements into Binary tree with random numbers [0, maxRand) with a balance of the tree every b insertions
    for (int i = 0; i < n; i++) {
		intBinaryTree2.insertNode(rand() % maxrand);
        if (i % b == 0) {
            intBinaryTree2.balance();
        }
	}

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to insert " << n << " nodes in Binary Tree + DSW balance every " << b << " insertions: " 
    << duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}