/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.2
 * 09/29/2023
 * Program to test the Average IPL of a tree undergoing deletion by copy and merge compared to the expected IPL
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "BinaryTree.h"

using namespace std;

int main() {
    srand(time(0)); // Random seed generator
    BinaryTree<int> tree1, tree2;
    int height = 0, iterations = 1000;

    // Gets user input for tree height and iterations
    cout << "Enter a height for the tree: ";
    cin >> height;

    cout << "Enter an amount of insertions and deletions: ";
    cin >> iterations;
    // Loop to run until the tree is of height ... tree inserted with random numbers [0, 99]
    while (tree1.height() != height) {
        int random = rand() % 100;
        tree1.insertNode(random);
        tree2.insertNode(random);
    }

    // Prints tree information prior to insertions and deletions
    cout << endl << "Tree Data before alternating insertions and deletions" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Tree1 IPL: " << tree1.getIPL() << endl;
    cout << "Tree1 average IPL: " << tree1.getAverageIPL() << endl;
    cout << "Tree1 height: " << tree1.height() << endl;
    cout << "Tree1 node count:: " << tree1.getNodeCount() << endl;

    cout << endl;

    cout << "Tree2 IPL: " << tree2.getIPL() << endl;
    cout << "Tree2 average IPL: " << tree2.getAverageIPL() << endl;
    cout << "Tree2 height: " << tree2.height() << endl;
    cout << "Tree2 node count:: " << tree2.getNodeCount() << endl;

    cout << endl << "Expected IPL: " << 1.386*log2(tree1.getNodeCount()) << endl;
    // Loop to perform insertions and deletions on the tree where the insertion and deletion are randomized
    for (int i = 0; i < iterations; i++) {
        int randomInsert = rand() % 100;
        int randomDelete = rand() % 100;

        tree1.insertNode(randomInsert);
        tree2.insertNode(randomInsert);
        // Generates a random value until it finds that value in the tree, then allows a deletion of that value
        while (!tree1.searchNode(randomDelete)) {
            randomDelete = rand() % 100;
        }
        tree1.mergeRemove(randomDelete);
        tree2.copyRemove(randomDelete);
    }
    // Prints tree information after to insertions and deletions
    cout << endl << "Tree Data after alternating insertions and deletions" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Tree1 IPL: " << tree1.getIPL() << endl;
    cout << "Tree1 average IPL: " << tree1.getAverageIPL() << endl;
    cout << "Tree1 height: " << tree1.height() << endl;
    cout << "Tree1 node count:: " << tree1.getNodeCount() << endl;

    cout << endl;

    cout << "Tree2 IPL: " << tree2.getIPL() << endl;
    cout << "Tree2 average IPL: " << tree2.getAverageIPL() << endl;
    cout << "Tree2 height: " << tree2.height() << endl;
    cout << "Tree2 node count:: " << tree2.getNodeCount() << endl;

    cout << endl << "Expected IPL: " << 1.386*log2(tree1.getNodeCount()) << endl;

    return 0;
}