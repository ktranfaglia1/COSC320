/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * Tenplated Binary Tree object declaration and implimentation file to serve as a base class for some derived classes (BST, crossref) -
 * Code provided by Dr.Spickler - Minor alterations were made to ensure functionality with derived BST and crossref class
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

#include "CrossRefListNode.h"

using namespace std;

// TreeNode Specialized for the CrossRef Program
template <class T>
class TreeNode {
	public:
		T value; // Data storage for node ... will be a string
		ListCollection<int> list; // Integer linked list to store line numbers
		TreeNode *left; // Left pointer
		TreeNode *right; // Right pointer

		// Constructor
		TreeNode(T val) { value = val; left = right = nullptr; } 
};
// Binary tree class that will be used as a base class for inheretence 
template<class T, class Node = TreeNode<T>>
class BinaryTree {
protected:
	Node *root; // root node pointer

	// Recursive functions
	void destroySubTree(Node*);
	void InOrderRec(Node*, void (*fct)(T&)) const;
	void PreOrderRec(Node*, void (*fct)(T&)) const;
	void PostOrderRec(Node*, void (*fct)(T&)) const;
	void IndentBlock(int num);
	void PrintTreeRec(Node *t, int Indent, int Level);

public:
	// Inline constructor
	BinaryTree() {
		root = nullptr;
	}
	// virtual inline destructor
	virtual ~BinaryTree() {
		destroySubTree(root);
	}
 
	void insert(T, int);
	void remove(T);

	// Inline traversal functions
	void InOrder(void (*fct)(T&)) const {
		InOrderRec(root, fct);
	}

	void PreOrder(void (*fct)(T&)) const {
		PreOrderRec(root, fct);
	}

	void PostOrder(void (*fct)(T&)) const {
		PostOrderRec(root, fct);
	}

	void PrintTree(int Indent = 4, int Level = 0); // Prints the tree
};

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template<class T, class Node>
void BinaryTree<T, Node>::destroySubTree(Node *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

/*
 * The InOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive inorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::InOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		InOrderRec(nodePtr->left, fct);
		fct(nodePtr->value);
		InOrderRec(nodePtr->right, fct);
	}
}
/*
 * The PreOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive preorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::PreOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		fct(nodePtr->value);
		PreOrderRec(nodePtr->left, fct);
		PreOrderRec(nodePtr->right, fct);
	}
}
/*
 * The PostOrderRec member function displays the values in the subtree
 * pointed to by nodePtr, via recursive postorder traversal.
 */
template<class T, class Node> void BinaryTree<T, Node>::PostOrderRec(
		Node *nodePtr, void (*fct)(T&)) const {
	if (nodePtr) {
		PostOrderRec(nodePtr->left, fct);
		PostOrderRec(nodePtr->right, fct);
		fct(nodePtr->value);
	}
}
//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template<class T, class Node> void BinaryTree<T, Node>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}
//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************
template<class T, class Node>
void BinaryTree<T, Node>::PrintTreeRec(Node *t, int Indent, int Level) {
	if (t) {
		PrintTreeRec(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTreeRec(t->left, Indent, Level + 1);
	}
}
//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************
template<class T, class Node> void BinaryTree<T, Node>::PrintTree(int Indent,
		int Level) {
	if (root)
		PrintTreeRec(root, Indent, Level);
}

#endif