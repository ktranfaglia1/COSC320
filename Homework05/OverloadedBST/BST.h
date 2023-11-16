/* Kyle Tranfaglia
 * COSC320 - Homework05 - Ex.3
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

	// Added Functions for delete by copy
	void findAndDeleteByCopy(T, TreeNode<T> *&);
	void deleteByCopying(TreeNode<T> *&);
	// Added Functions for rotation deletion
	void findAndDeleteByRotateHeight(T, TreeNode<T> *&);
	void deleteByRotateHeight(TreeNode<T>*&);
	void findAndDeleteByRotateNodes(T, TreeNode<T> *&);
	void deleteByRotateNodes(TreeNode<T>*&);

    void rotateLeft(TreeNode<T>*&);
	void rotateRight(TreeNode<T>*&);

	int calculateNodeCount(TreeNode<T>*) const;
    int height(TreeNode<T>*) const;

public:
	BST();
	virtual ~BST();

	void insert(T);

	void mergeRemove(T); // Standard merge remove
	void copyRemove(T); //Added copy remove

	void heightRotationDelete(T); // rotation delete using height
	void nodeRotationDelete(T); // rotation delete using node count

	int getNodeCount(); // Function to get node count
    int getHeight(); // Function to get height

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

/*
 * Nonrecursive start to deleting a tree node.
 */
template<class T> void BST<T>::copyRemove(T item) {
	findAndDeleteByCopy(item, BinaryTree<T>::root);
}

/*
 * Recursive find for deleting a node. Once the value is found the
 * deleteByCopying function is called on the node.
 */
template<class T> void BST<T>::findAndDeleteByCopy(T item, TreeNode<T> *&nodePtr) {
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
void BST<T>::deleteByCopying(TreeNode<T> *&node) {
	TreeNode<T> *previous, *tmp = node;
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
// Non-recursive delete by rotate function using height
template<class T>
void BST<T>::heightRotationDelete(T element) {
	findAndDeleteByRotateHeight(element, BinaryTree<T>::root);
}

// Recursive findAndDeleteByRotate function to find the item and then call a delete by rotate function to delete the node containing the pointer
template<class T> void BST<T>::findAndDeleteByRotateHeight(T item, TreeNode<T> *&nodeptr) {
	// Return if node is null
	if (!nodeptr) {
		return;
    }
	if (item < nodeptr->value) { // Checks if item is less than node value
		findAndDeleteByRotateHeight(item, nodeptr->left); // Recursive call, go to left
    }
	else if (item > nodeptr->value) { // Checks if item is greater than node value
		findAndDeleteByRotateHeight(item, nodeptr->right); // Recursive call, go to right
    }
	else {
		deleteByRotateHeight(nodeptr); // Once node is found, call recursive delete by rotate function
    }
}
// Recursive delete by rotate function that rotates around the sub tree of a smaller height and then deletes the node once the node has at most one child
template<class T>
void BST<T>::deleteByRotateHeight(TreeNode<T>*& nodeptr) {
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
            deleteByRotateHeight(nodeptr->right);
        }
        else {
            rotateLeft(nodeptr);
            deleteByRotateHeight(nodeptr->left);
        }
    }
}
// Non-recursive delete by rotate function using node count
template<class T>
void BST<T>::nodeRotationDelete(T element) {
	findAndDeleteByRotateNodes(element, BinaryTree<T>::root);
}

/*
 * Recursive find for deleting a node.  Once the value is found the
 * deleteByrotate function s called on the node.
 */
template<class T> void BST<T>::findAndDeleteByRotateNodes(T item, TreeNode<T> *&nodeptr) {
	// Return if node is null
	if (!nodeptr) {
		return;
    }
	if (item < nodeptr->value) { // Checks if item is less than node value
		findAndDeleteByRotateNodes(item, nodeptr->left); // Recursive call, go to left
    }
	else if (item > nodeptr->value) { // Checks if item is greater than node value
		findAndDeleteByRotateNodes(item, nodeptr->right); // Recursive call, go to right
    }
	else {
		deleteByRotateNodes(nodeptr); // Once node is found, call recursive delete by rotate function
    }
}

template<class T>
void BST<T>::deleteByRotateNodes(TreeNode<T>*& nodeptr) {
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
        if (calculateNodeCount(nodeptr->left) > calculateNodeCount(nodeptr->right)) {
            rotateRight(nodeptr);
            deleteByRotateNodes(nodeptr->right);
        }
        else {
            rotateLeft(nodeptr);
            deleteByRotateNodes(nodeptr->left);
        }
    }
}

#endif