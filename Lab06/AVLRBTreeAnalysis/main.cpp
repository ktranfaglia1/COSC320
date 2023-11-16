/* Kyle Tranfaglia
*  COSC320 - Lab06
*  Last updated 10/11/23
*  This program creates an AVl tree and an Red-Black tree and times insertions and insertion deletion cycles and compares average IPL
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "RBTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0)); // Random seed generator
    // Variables
    AVLTree<int> intAVLTree; // Create the AVL tree
    RBTree<int> intRBTree; // Create the RB tree
    // Variable to hold base insertions, max value of rand and number of nodes to insert determined by user
    int n = 0, maxrand = 0, insertDeletes = 0, insertVal = 0, deleteVal = 0; 
    double AVLIPLPrev = 0, RBIPLPrev = 0, AVLIPLAfter = 0, RBIPLAfter = 0;

    // Gets user input for variables to influence timing results
    cout << "Enter the number of nodes to insert into the tree: ";
    cin >> n;

    cout << "Enter the max random value for the node insertion (not inclusive): ";
    cin >> maxrand;

    cout << "Enter the amount insertion and deletion cycles: ";
    cin >> insertDeletes;

    cout << endl << "Insertion Data" << endl << "--------------" << endl;
    // Timing for insertions in AVL tree
    auto start = high_resolution_clock::now();
    // Loop to insert n elements into AVL tree with random numbers [0, maxRand)
    for (int i = 0; i < n; i++) {
		intAVLTree.insertNode(rand() % maxrand);
	}
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time to insert " << n << " nodes in an AVL Tree: " << duration.count() / 1000000.0 << " seconds" << endl;
    AVLIPLPrev = intAVLTree.getAverageIPL(); // Gets average IPL
    cout << "AVL IPL after insertion: " << AVLIPLPrev << endl;

    start = high_resolution_clock::now();
    // Loop to insert n elements into Binary tree with random numbers [0, maxRand) with a balance of the tree every b insertions
    for (int i = 0; i < n; i++) {
		intRBTree.insert(rand() % maxrand);
	}
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to insert " << n << " nodes in Red-Balck Tree: " << duration.count() / 1000000.0 << " seconds" << endl;
    RBIPLPrev = intRBTree.getAverageIPL(); // Gets average IPL
    cout << "Red-Black IPL after insertion: " << RBIPLPrev << endl;

    start = high_resolution_clock::now();

    cout << endl << "Insertion and Deletion Cycle Data" << endl << "---------------------------------" << endl;
    // Loop to get a random insert value and a delete value that is in the tree and cycles until insertDeletes
    for (int i = 0; i < insertDeletes; i++) {
        insertVal = rand() % maxrand;
        deleteVal = rand() % maxrand;

        intAVLTree.insertNode(insertVal);
        // Checks that insert and delete value are not same and that delete value is in the tree
        while (insertVal == deleteVal || !intAVLTree.searchNode(deleteVal)) {
            deleteVal = rand() % maxrand;
        }
        intAVLTree.remove(deleteVal);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to do " << insertDeletes << " insertions and deletions in AVL Tree: " << duration.count() / 1000000.0 << " seconds" << endl;
    AVLIPLAfter = intAVLTree.getAverageIPL(); // Gets average IPL
    cout << "AVL IPL after cycle: " << AVLIPLAfter << endl;

    start = high_resolution_clock::now();
    // Loop to get a random insert value and a delete value that is in the tree and cycles until insertDeletes
    for (int i = 0; i < insertDeletes; i++) {
        insertVal = rand() % maxrand;
        deleteVal = rand() % maxrand;

        intRBTree.insert(insertVal);
    // Checks that insert and delete value are not same and that delete value is in the tree
        while (insertVal == deleteVal || !intRBTree.find(deleteVal)) {
            deleteVal = rand() % maxrand;
        }
        intRBTree.remove(deleteVal);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time to do " << insertDeletes << " insertions and deletions in Red-Balck Tree: " << duration.count() / 1000000.0 << " seconds" << endl;
    RBIPLAfter = intRBTree.getAverageIPL(); // Gets average IPL
    cout << "Red-Black IPL after cycle: " << RBIPLAfter << endl;

    // Prints IPL ratios
    cout << endl << "Before and After IPL ratios" << endl << "---------------------------" << endl;
    cout << "AVL: " << AVLIPLAfter/AVLIPLPrev << endl; // Computes IPL ratio for AVL tree
    cout << "Red-Black: " << RBIPLAfter/RBIPLPrev << endl;  // Computes IPL ratio for Red-Balck tree

    return 0;
}