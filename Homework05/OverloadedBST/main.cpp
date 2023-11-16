/* Kyle Tranfaglia
 * COSC320 - Homework05 - Ex.3
 * 10/06/2023
 * Program to test the functionality of the BST with the added delete by rotation and its variation with deleet by merge and copy
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "BST.h"

using namespace std;

int main() {
    srand(time(0)); // Sets the seed for the rand
    // Variables
    BST<int> intBST1, intBST2, intBST3;
    int insertDeleteCount = 0, maxNodeVal = 0, minNodeVal = 0, nodeCount= 0, deleteVal = 0, insertVal = 0, startHeight = 0;

    // Gets some information from the user
    cout << "Enter the number of nodes to insert in the tree: ";
    cin >> nodeCount;

    cout << "Enter the minimum node value (inclusive) and the maximum node value (inclusive) for the trees (seperate by space): ";
    cin >> minNodeVal;
    cin >> maxNodeVal;
    // Checks that the random value range is valid
    while (maxNodeVal <= minNodeVal) {
        cout << "Why would you enter that? Enter a valid range" << endl;
        cout << "Enter the minimum node value (inclusive) and the maximum node value (inclusive) for the trees (seperate by space): ";
        cin >> minNodeVal;
        cin >> maxNodeVal;
    }
    // Inserts nodeCount random elements [minNodeVal, maxNodeVal] in the integer BST
    for (int i = 0; i < nodeCount; i++) {
        intBST1.insert(rand() % (maxNodeVal - minNodeVal + 1) + minNodeVal);
    }

    startHeight = intBST1.getHeight(); // Stores the height of the the integer tree
    
    // Uses assignment and copy constructor to copy tree
    intBST2 = intBST1;
    intBST3 = intBST1;
    BST<int> intBST4 = intBST1;

    // Gets the number of inserts and deletions from user
    cout << "Enter the amount of insertions and deletions to perform on the tree: ";
    cin >> insertDeleteCount;
    // Loop to insert and delete values of varying random values using user range. Each integer BST uses a different delete node method
    for (int i = 0; i < insertDeleteCount; i++) {
        insertVal = rand() % (maxNodeVal - minNodeVal + 1) + minNodeVal; // Stores rand input
        deleteVal = rand() % (maxNodeVal - minNodeVal + 1) + minNodeVal; // Stores rand delete

        // Inserts the same value into all the trees
        intBST1.insert(insertVal);
        intBST2.insert(insertVal);
        intBST3.insert(insertVal);
        intBST4.insert(insertVal);
        // Gets a new random delete value if it is the same value as the insert or is not in the BST
        while (insertVal == deleteVal || !intBST1.find(deleteVal)) {
            deleteVal = rand() % (maxNodeVal - minNodeVal + 1) + minNodeVal;
        }
        // Removes the value from each tree using corresponding method
        intBST1.mergeRemove(deleteVal);
        intBST2.copyRemove(deleteVal);
        intBST3.heightRotationDelete(deleteVal);
        intBST4.nodeRotationDelete(deleteVal);
    }
    
    // Output of Height and Height ratio information of the four trees to compare to original
    cout << "Heights" << endl << "-------" << endl;

    cout << "Original tree: "<< startHeight << endl;
    cout << "Tree 1 (Merge): " << intBST1.getHeight() << endl;
    cout << "Tree 2 (Copy): " << intBST2.getHeight() << endl;
    cout << "Tree 3 (Height Rotation): " << intBST3.getHeight() << endl;
    cout << "Tree 4 (Node Count Rotation): " << intBST4.getHeight() << endl << endl;

    cout << "Ratios" << endl << "------" << endl;

    cout << "Tree 1: " << (static_cast<double>(intBST1.getHeight()) / startHeight) << endl;
    cout << "Tree 2: " << (static_cast<double>(intBST2.getHeight()) / startHeight) << endl;
    cout << "Tree 3: " << (static_cast<double>(intBST3.getHeight()) / startHeight) << endl;
    cout << "Tree 4: " << (static_cast<double>(intBST4.getHeight()) / startHeight) << endl;

    return 0;
}