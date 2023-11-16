/* Kyle Tranfaglia
 * COSC320 - Homework05 - Ex.1
 * 10/06/2023
 * Templated Declaration and Implimentation for the inherited BST object
*/
#ifndef BST_H_
#define BST_H_

#include "BinaryTree.h"

template<class T>
class BST: public BinaryTree<T> {
protected:
	void insert(TreeNode<T>*&, TreeNode<T>*&);
	void deleteNode(T, TreeNode<T>*&);
	void makeDeletion(TreeNode<T>*&);

	// Added Functions for rotation deletion
	void findAndDeleteByRotate(T, TreeNode<T> *&);
	void deleteByRotate(TreeNode<T>*&);

    void rotateLeft(TreeNode<T>*&);
	void rotateRight(TreeNode<T>*&);

    int height(TreeNode<T>*) const;
	int calculateNodeCount(TreeNode<T>*) const;

public:
	BST();
	virtual ~BST();

	void insert(T);
	void mergeRemove(T);

	void rotationDelete(T val); // Added rotation delete for user

    int getHeight(); // Added get height function for user
	int getNodeCount(); // Added get node count for user

	virtual bool find(const T&);
	virtual TreeNode<T>* findNode(const T&);
};
// Constructor
template<class T>
BST<T>::BST() {
}
// Destructor
template<class T>
BST<T>::~BST() {
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

template<class T>
void BST<T>::insert(TreeNode<T> *&nodePtr, TreeNode<T> *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode; // insert node
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************

template<class T>
void BST<T>::insert(T item) {
	TreeNode<T> *newNode = new TreeNode<T>; // Create a new node
	newNode->value = item;
	insert(BinaryTree<T>::root, newNode); // Inserts new node with recursive function
}

//***************************************************
// find determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************

template<class T>
bool BST<T>::find(const T &item) {
	return findNode(item) != nullptr;
}

/*
 * findNode determines if an item is in the tree.  If so
 * a pointer to the item is returned and if not nullptr
 * is returned.  Note that if we returned T then the data
 * type T would possibly need a copy constructor.
 */
template<class T>
TreeNode<T>* BST<T>::findNode(const T &item) {
	TreeNode<T> *nodePtr = BinaryTree<T>::root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return nodePtr;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return nullptr;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************

template<class T>
void BST<T>::mergeRemove(T item) {
	deleteNode(item, BinaryTree<T>::root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

template<class T> 
void BST<T>::deleteNode(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

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
void BST<T>::makeDeletion(TreeNode<T> *&nodePtr) {
	TreeNode<T> *tempNodePtr = nullptr; // Define a temporary pointer to use in reattaching the left subtree.
	if (!nodePtr)
		cout << "Cannot delete empty node.\n";
	else if (!nodePtr->right) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left; // Reattach the left child
		delete tempNodePtr;
	} else if (!nodePtr->left) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right; // Reattach the right child
		delete tempNodePtr;
	// If the node has two children.
	} else {
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

// Function to return the number of nodes by calling a recursive calculateNodeCount function
template<class T>
int BST<T>::getNodeCount() {
    return calculateNodeCount(BinaryTree<T>::root);
}

// Recursive function to count the number of nodes in a binary tree
template<class T>
int BST<T>::calculateNodeCount(TreeNode<T> *nodeptr) const{
	// If no node, return 0
	if (!nodeptr) {
    	return 0;
    }
    return (calculateNodeCount(nodeptr->left) + calculateNodeCount(nodeptr->right)) + 1; // Sum of left and right tree plus root ... recursive call
}

// Public function to return the height (number of levels) in the tree
template<class T>
int BST<T>::getHeight() {
	return height(BinaryTree<T>::root); // returns the value from recursive height function
}

// Recursive function to count the levels of the tree
template<class T>
int BST<T>::height(TreeNode<T>* nodeptr) const{
	// Base case that is reached after going to a child node that does not exist ... traversing to a nullptr
	if (!nodeptr)
        return 0;
    else {
        int leftSubTree = height(nodeptr->left); // Recursively calls itself and stores a count of left sub tree levels
        int rightSubTree = height(nodeptr->right); // Recursively calls itself and stores a count of right sub tree levels
	
		// Increments the level count for the recursive sub tree count with a return of the greatest sub tree
        if (rightSubTree > leftSubTree)
            return rightSubTree + 1;
        else
            return leftSubTree + 1;
	}
}

/*
 * Does a left rotation about nodeptr.
 */
template<class T>
void BST<T>::rotateLeft(TreeNode<T>*& nodeptr) {
	TreeNode<T> *p = nodeptr->right;
	TreeNode<T> *q = p->left;
	p->left = nodeptr;
	nodeptr->right = q;
	nodeptr = p;
}

/*
 * Does a right rotation about nodeptr
 */
template<class T>
void BST<T>::rotateRight(TreeNode<T>*& nodeptr) {
	TreeNode<T> *p = nodeptr->left;
	TreeNode<T> *q = p->right;
	p->right = nodeptr;
	nodeptr->left = q;
	nodeptr = p;
}

// Public deletion function to call a recursive function to delete an element by rotation
template<class T>
void BST<T>::rotationDelete(T element) {
	findAndDeleteByRotate(element, BinaryTree<T>::root);
}

// Recursive findAndDeleteByRotate function to find the item and then call a delete by rotate function to delete the node containing the pointer
template<class T> void BST<T>::findAndDeleteByRotate(T item, TreeNode<T> *&nodeptr) {
	// Return if node is null
	if (!nodeptr) {
		return;
    }
	if (item < nodeptr->value) { // Checks if item is less than node value
		findAndDeleteByRotate(item, nodeptr->left); // Recursive call, go to left
    }
	else if (item > nodeptr->value) { // Checks if item is greater than node value
		findAndDeleteByRotate(item, nodeptr->right); // Recursive call, go to right
    }
	else {
		deleteByRotate(nodeptr); // Once node is found, call recursive delete by rotate function
    }
}

// Recursive delete by rotate function that rotates around the sub tree of a smaller height and then deletes the node once the node has at most one child
template<class T>
void BST<T>::deleteByRotate(TreeNode<T>*& nodeptr) {
	// If no left node, delete and move right
	if (!nodeptr->left) {
        TreeNode<T> *temp = nodeptr;
		nodeptr = nodeptr->right;
		delete temp;
	}
	else if (!nodeptr->right) { // If no right node, delete and move left
		TreeNode<T> *temp = nodeptr;
		nodeptr = nodeptr->left;
		delete temp;
	}
    else { // Compare heights, then rotate accordingly (rotate around smaller subtree height and recurse)
        if (height(nodeptr->left) > height(nodeptr->right)) {
            rotateRight(nodeptr);
            deleteByRotate(nodeptr->right);
        }
        else {
            rotateLeft(nodeptr);
            deleteByRotate(nodeptr->left);
        }
    }
}

#endif