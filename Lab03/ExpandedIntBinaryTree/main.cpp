/* Kyle Tranfaglia
*  COSC320 - Lab03 - Ex.1
*  Last updated 09/13/23
*  Program to test the functionality of the IntBinaryTree class, specifically the node count,
*  leaf count, height, and path functions - Code provided by Dr. Spickler
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "IntBinaryTree.h"

using namespace std;

int main() {
	srand(time(0));

	int sz = 0;

	cout << "Input Array Size: ";
	cin >> sz;

	int *A = new int[sz];
	IntBinaryTree B;

	for (int i = 0; i < sz; i++)
		A[i] = rand() % 100 + 1;

	for (int i = 0; i < sz; i++)
		cout << A[i] << " ";

	cout << endl;
	for (int i = 0; i < sz; i++)
		B.insertNode(A[i]);

	cout << endl;
	B.PrintTree();

	cout << "Number of Nodes: " << B.numNodes() << endl;
	cout << "Number of Leaves: " << B.numLeaves() << endl;
	cout << "Height: " << B.height() << endl;
	cout << "Height Paths" << endl;

	B.PrintHeightPaths();

	delete[] A;

	return 0;
}