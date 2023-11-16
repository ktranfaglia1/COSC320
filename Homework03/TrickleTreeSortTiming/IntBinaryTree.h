/* Kyle Tranfaglia
*  COSC320 - Homework03 - Ex. 2
*  Last updated 09/22/23
*  Declaration for the IntBinaryTree class - Code Provided by Dr. Spickler - Altered to sort using a complete binary tree and create trees given arrays
*/
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <iostream>
#include <queue>
#include <cmath>

using namespace std; 

class IntBinaryTree {
private:
	struct TreeNode {
		int value;
		TreeNode *left;
		TreeNode *right;

		// Added Constructor
		TreeNode(int v = -1) {value = v; left = right = nullptr;};
	};

	TreeNode *root;

	// Private member functions
	void destroySubTree(TreeNode*);
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);

	// Added Functions
	void makeTree(TreeNode*&, queue<int>&, int, int);
	int getMaxValue(int*, int);
	int setMin(TreeNode *&);
	void replaceMin(TreeNode *&, int, int, int&);

public:
	// Constructor
	IntBinaryTree() {
		root = nullptr;
	}

	// Destructor
	~IntBinaryTree() {
		destroySubTree(root);
	}

	void PrintTree(int Indent = 4, int Level = 0);

	// Added Functions
	void LoadArray(int*, int);
	void ReturnSortedArray(int*, int);
};
#endif