/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * Templated BST object declaration and implimentation file inhereted off of the binary tree class - Code provided by Dr. Spickler -
 * Minor alterations were made to ensure functionality with derived crossref class
*/
#ifndef BST_H_
#define BST_H_

#include "BinaryTree.h"

template<class T, class Node = TreeNode<T>>
class BST: public BinaryTree<T> {
protected:
	void insert(Node*&, Node*&);
	void deleteNode(T, Node*&);
	void makeDeletion(Node*&);

public:
	BST();
	virtual ~BST();

    void insert(T, int);
	void remove(T);

	virtual bool find(const T&);
	virtual Node* findNode(const T&);
};
// Constructor
template<class T, class Node>
BST<T, Node>::BST() {
}
// Destructor
template<class T, class Node>
BST<T, Node>::~BST() {
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

template<class T, class Node>
void BST<T, Node>::insert(Node *&nodePtr, Node *&newNode) {
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

template<class T, class Node>
void BST<T, Node>::insert(T item, int num) {
	Node *newNode = new Node(item); // Create a new node and store num in it
	newNode->list.pushBack(num);
	insert(BinaryTree<T>::root, newNode); // Inserts new node with recursive function
}

//***************************************************
// find determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************

template<class T, class Node>
bool BST<T, Node>::find(const T &item) {
	return findNode(item) != nullptr;
}

/*
 * findNode determines if an item is in the tree.  If so
 * a pointer to the item is returned and if not nullptr
 * is returned.  Note that if we returned T then the data
 * type T would possibly need a copy constructor.
 */
template<class T, class Node>
Node* BST<T, Node>::findNode(const T &item) {
	Node *nodePtr = BinaryTree<T>::root;

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

template<class T, class Node> void BST<T, Node>::remove(T item) {
	deleteNode(item, BinaryTree<T>::root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

template<class T, class Node> void BST<T, Node>::deleteNode(T item, Node *&nodePtr) {
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

template<class T, class Node> void BST<T, Node>::makeDeletion(Node *&nodePtr) {
	Node *tempNodePtr = nullptr; // Define a temporary pointer to use in reattaching the left subtree.
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

#endif /* BST_H_ */