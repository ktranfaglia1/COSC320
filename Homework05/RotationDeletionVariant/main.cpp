/* Kyle Tranfaglia
 * COSC320 - Homework05 - Ex.1
 * 10/06/2023
 * Program to test the functionality of the BST with the added delete by rotation
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "BST.h"

using namespace std;

int main() {
    srand(time(0)); // Sets the seed for the rand
    BST<int> intBST;
    int deleteVal = 0, numDeletes = 0;
    const int NODECOUNT = 20;
    // Loop to insert NODECOUNT random values [0, 100) in a integer tree 
    for (int i = 0; i < NODECOUNT; i++) {
        intBST.insert(rand() % 100);
    }
    // Print the tree and some stats
    intBST.PrintTree(); 
    cout << "Height: " << intBST.getHeight() << endl;
    cout << "Nodes: " << intBST.getNodeCount() << endl;

    // Get number of deletions
    cout << "Enter the number of deletions to make: ";
    cin >> numDeletes;
    // Loop to run until the number of deletions
    for (int i = 0; i < numDeletes; i++) {
        // Gets value to delete
        cout << "Enter value to delete from the tree: ";
        cin >> deleteVal;
        
        intBST.rotationDelete(deleteVal); // Deletes value via rotation

        cout << endl << "Updated Tree" << endl << "------------" << endl << endl; 
        // Print the tree and some stats
        intBST.PrintTree();
        cout << "Height: " << intBST.getHeight() << endl;
        cout << "Nodes: " << intBST.getNodeCount() << endl;
    }

    return 0;
}