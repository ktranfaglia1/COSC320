/* Kyle Tranfaglia
*  COSC320 - Lab03 - Ex.1
*  Last updated 09/13/23
*  IntBinary Tree Declaration - Code provided by Dr. Spickler - Updated with added functions
*/

// Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <iostream>
#include <vector>

using namespace std;

class IntBinaryTree {
private:
	struct TreeNode {
		int value;
		TreeNode *left;
		TreeNode *right;
	};

	TreeNode *root;

	// Private member functions
	void insert(TreeNode*&, TreeNode*&);
	void destroySubTree(TreeNode*);
	void deleteNode(int, TreeNode*&);
	void makeDeletion(TreeNode*&);
	void displayInOrder(TreeNode*) const;
	void displayPreOrder(TreeNode*) const;
	void displayPostOrder(TreeNode*) const;
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);

	// Added recursive functions
	void numNodes(int &, TreeNode*) const;
	void numLeaves(int &, TreeNode*) const;
	int height(TreeNode*) const;
	void PrintHeightPaths(vector<int>, TreeNode*) const;

public:
	// Constructor
	IntBinaryTree() {
		root = nullptr;
	}

	// Destructor
	~IntBinaryTree() {
		destroySubTree(root);
	}

	// Binary tree operations
	void insertNode(int);
	bool searchNode(int);
	void remove(int);

	void displayInOrder() const {
		displayInOrder(root);
	}

	void displayPreOrder() const {
		displayPreOrder(root);
	}

	void displayPostOrder() const {
		displayPostOrder(root);
	}

	void PrintTree(int Indent = 4, int Level = 0);

	// Added Functions
	int numNodes();
	int numLeaves();
	int height();
	void PrintHeightPaths();
};

#endif