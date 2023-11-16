/* Kyle Tranfaglia
 * COSC320 - Homework05 - Ex.3
 * 10/06/2023
 * Templated Declaration and Implimentation for the Binary Tree object
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

using namespace std;

template<class T>
class TreeNode {
public:
	T value;
	TreeNode *left;
	TreeNode *right;

	TreeNode() { left = right = nullptr; }
};

template<class T, class Node = TreeNode<T>>
class BinaryTree {
protected:
	Node *root;

	void destroySubTree(Node*);
	void InOrderRec(Node*, void (*fct)(T&)) const;
	void PreOrderRec(Node*, void (*fct)(T&)) const;
	void PostOrderRec(Node*, void (*fct)(T&)) const;
	void IndentBlock(int num);
	void PrintTreeRec(Node *t, int Indent, int Level);

	Node* copyTree(Node*); // Added Copy function

public:
	BinaryTree() { root = nullptr; }

	virtual ~BinaryTree() { destroySubTree(root); }

    BinaryTree(BinaryTree&); // Added copy constructor

    void operator=(BinaryTree&); // Added assignment operator overload

	virtual void insert(T) = 0;
	virtual void mergeRemove(T) = 0;

	void InOrder(void (*fct)(T&)) const {
		InOrderRec(root, fct);
	}

	void PreOrder(void (*fct)(T&)) const {
		PreOrderRec(root, fct);
	}

	void PostOrder(void (*fct)(T&)) const {
		PostOrderRec(root, fct);
	}

	void PrintTree(int Indent = 4, int Level = 0);
};
// Copy constructor that sets root to the node returned by copy function
template<class T, class Node>
BinaryTree<T, Node>::BinaryTree(BinaryTree<T, Node>& obj) {
	root = copyTree(obj.root); // Sends object root as parameter to copy tree
}
// Assignment operator overload that sets root to the node returned by copy function
template<class T, class Node>
void BinaryTree<T, Node>::operator=(BinaryTree<T, Node>& obj) {
	destroySubTree(root); // Destroys the current tree before copying
	root = copyTree(obj.root); // Sends object root as parameter to copy tree
}

/*
 * Recursive function to copy a tree or subtree.
 */
template<class T, class Node>
Node* BinaryTree<T, Node>::copyTree(Node *nodeptr) {
	Node *newlptr, *newrptr, *newNode;
	// Checks if node is not null
	if (!nodeptr) {
		return nullptr;
	}
	if (nodeptr->left) { // If left subtree exists, recursively copy it
		newlptr = copyTree(nodeptr->left);
	} else {
		newlptr = nullptr;
	}
	if (nodeptr->right) { // If right subtree exists, recursively copy it
		newrptr = copyTree(nodeptr->right);
	} else {
		newrptr = nullptr;
	}

	newNode = new Node; // Craete new node
	newNode->value = nodeptr->value; // Insert value at node into new node
	newNode->left = newlptr; // Connect left subtree
	newNode->right = newrptr; // Connect right subtree

	return newNode;
}

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