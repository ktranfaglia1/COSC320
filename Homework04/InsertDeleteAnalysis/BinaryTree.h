/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.2
 * 09/29/2023
 * Templated Binary Tree Object Declaration and Implimentation - Code provided by Dr. Spickler - Updated with functions to analyze deletion and IPL
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

using namespace std;

template<class T>
class BinaryTree {
private:
	struct TreeNode {
		T value;
		TreeNode *left;
		TreeNode *right;
	};

	TreeNode *root;

	// Private member functions
	void insert(TreeNode*&, TreeNode*&);
	void destroySubTree(TreeNode*);
	void deleteNode(T, TreeNode*&);
	void makeDeletion(TreeNode*&);
	void displayInOrder(TreeNode*) const;
	void displayPreOrder(TreeNode*) const;
	void displayPostOrder(TreeNode*) const;
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);

	// Added delete by copy functions
	void findAndDeleteByCopy(T item, TreeNode *&nodePtr);
	void deleteByCopying(TreeNode *&node);

	// Added recursive functions
	int height(TreeNode*) const;
	int calculateIPL(TreeNode*, int);
	int calculateNodeCount(TreeNode*);

public:
	// Constructor
	BinaryTree() {
		root = nullptr;
	}

	// Destructor
	~BinaryTree() {
		destroySubTree(root);
	}

	// Binary tree operations
	void insertNode(T);
	bool searchNode(T);
	void mergeRemove(T);
	void copyRemove(T);

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
	int height();
	int getIPL();
	int getNodeCount();
	double getAverageIPL();
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template<class T>
void BinaryTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode;                  // Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);     // Search the left branch
	else
		insert(nodePtr->right, newNode);    // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template<class T>
void BinaryTree<T>::insertNode(T item) {
	TreeNode *newNode = nullptr;	// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = item;
	newNode->left = newNode->right = nullptr;

	// Insert the node.
	insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template<class T>
void BinaryTree<T>::destroySubTree(TreeNode *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************
template<class T>
bool BinaryTree<T>::searchNode(T item) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return true;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template<class T>
void BinaryTree<T>::mergeRemove(T item) {
	deleteNode(item, root);
}

//*************************************************
// remove calls findAndDeleteByCopy to delete the *
// node whose value member is the same as num.    *
//*************************************************
template<class T>
void BinaryTree<T>::copyRemove(T item) {
	findAndDeleteByCopy(item, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template<class T>
void BinaryTree<T>::deleteNode(T item, TreeNode *&nodePtr) {
	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************
template<class T>
void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr) {
	// Define a temporary pointer to use in reattaching
	// the left subtree.
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;   // Reattach the left child
		delete tempNodePtr;
	} else if (nodePtr->left == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;  // Reattach the right child
		delete tempNodePtr;
	}
	// If the node has two children.
	else {
		// Move one node the right.
		tempNodePtr = nodePtr->right;
		// Go to the end left node.
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		// Reattach the left subtree.
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree.
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template<class T>
void BinaryTree<T>::displayInOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << endl;
		displayInOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************
template<class T>
void BinaryTree<T>::displayPreOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		cout << nodePtr->value << endl;
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************
template<class T>
void BinaryTree<T>::displayPostOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << endl;
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T>
void BinaryTree<T>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

template<class T>
void BinaryTree<T>::PrintTree(TreeNode *t, int Indent, int Level) {
	if (t != NULL) {
		PrintTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************

template<class T>
void BinaryTree<T>::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByCopying function s called on the node.
 */
template<class T> void BinaryTree<T>::findAndDeleteByCopy(T item,
		TreeNode *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		deleteByCopying(nodePtr);
}

/*
 * Deletes a node using the copy algorithm.  Copies the node's
 * predecessor to the position of deletion. Then deletes the leaf
 * or adjusts the child node pointer and deletes the old predecessor
 * position.
 */
template<class T>
void BinaryTree<T>::deleteByCopying(TreeNode *&node) {
	TreeNode *previous, *tmp = node;
	// node has no right child
	if (!node->right)
		node = node->left;
	// node has no left child
	else if (node->left == 0)
		node = node->right;
	else {
		// node has both children.
		tmp = node->left;
		previous = node;
		while (tmp->right != 0) {
			previous = tmp;
			tmp = tmp->right;
		}
		node->value = tmp->value;
		if (previous == node)
			previous->left = tmp->left;
		else
			previous->right = tmp->left;
	}
	delete tmp;
}
// Public function to return the height (number of levels) in the tree
template<class T>
int BinaryTree<T>::height() {
	return height(root); // returns the value from recursive height function
}
// Recursive function to count the levels of the tree
template<class T>
int BinaryTree<T>::height(TreeNode* nodePtr) const {
	// Base case that is reached after going to a child node that does not exist ... traversing to a nullptr
	if (nodePtr == nullptr)
        return 0;
    else {
        int leftSubTree = height(nodePtr->left); // Recursively calls itself and stores a count of left sub tree levels
        int rightSubTree = height(nodePtr->right); // Recursively calls itself and stores a count of right sub tree levels
	
		// Increments the level count for the recursive sub tree count with a return of the greatest sub tree
        if (rightSubTree > leftSubTree)
            return rightSubTree + 1;
        else
            return leftSubTree + 1;
	}
}

// Recursive function to calculate the depth of a binary tree
template<class T>
int BinaryTree<T>::calculateIPL(TreeNode* nodeptr, int pathLength) {
    if (!nodeptr) {
        return 0;
    }

    // Recursively calculate the path lengths of the left and right subtrees
    int leftPathLength = calculateIPL(nodeptr->left, pathLength++);
    int rightPathLength = calculateIPL(nodeptr->right, pathLength++);

    // Return the sum of the path lengths of the left and right subtrees
    return pathLength + leftPathLength + rightPathLength;
}

// Function to calculate the Internal Path Length (IPL) of a binary tree
template<class T>
int BinaryTree<T>::getIPL() {
    if (!root) {
        return 0;
    }
    return calculateIPL(root, 0); // Call the recursive function to calculate the total path lengths of the tree
}
// Function to return the number of nodes by calling a recursive calculateNodeCount function
template<class T>
int BinaryTree<T>::getNodeCount() {
	return calculateNodeCount(root);
}

// Recursive function to count the number of nodes in a binary tree
template<class T>
int BinaryTree<T>::calculateNodeCount(TreeNode* nodeptr) {
    if (!nodeptr) {
        return 0;
    }
    return (calculateNodeCount(nodeptr->left) + calculateNodeCount(nodeptr->right)) + 1;
}

// Function to calculate the average Internal Path Length (IPL) of a binary tree
template<class T>
double BinaryTree<T>::getAverageIPL() {
    if (!root) {
        return 0;
    }
    return static_cast<double> (getIPL()) / (getNodeCount());  // Calculate and return the average IPL
}

#endif