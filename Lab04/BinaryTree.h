/* Kyle Tranfaglia
*  COSC320 - Lab04
*  Last updated 09/20/23
*  BinaryTree class declaration and implementation - Code provided by Dr. Spickler 
*  - added functions to increment tree node values for each traversal
*/
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <deque>

using namespace std;

template<class T> class BinaryTree {
private:
	class TreeNode {
	public:
		T value;
		TreeNode *left;
		TreeNode *right;

		TreeNode() {
			left = nullptr;
			right = nullptr;
		}
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

	// Added Functions
	void incrementInOrder(TreeNode*) const;
	void incrementPreOrder(TreeNode*) const;
	void incrementPostOrder(TreeNode*) const;

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
	void remove(T);
	T* search(T &item);

	void displayInOrder() const {
		displayInOrder(root);
	}

	void displayPreOrder() const {
		displayPreOrder(root);
	}

	void displayPostOrder() const {
		displayPostOrder(root);
	}

	void displayBreadthFirst();
	void iterativePreorder();
	void iterativePostorder2Stacks();
	void iterativePostorder();
	void iterativeInorder();

	void PrintTree(int Indent = 4, int Level = 0);

	// Added functions
	void incrementInOrder() const {
		incrementInOrder(root);
	}

	void incrementPreOrder() const {
		incrementPreOrder(root);
	}

	void incrementPostOrder() const {
		incrementPostOrder(root);
	}

	void incrementIterativePreorder();
	void incrementIterativePostorder2Stacks();
	void incrementIterativePostorder();
	void incrementIterativeInorder();
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template<class T>
void BinaryTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode; // Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template<class T> void BinaryTree<T>::insertNode(T item) {
	TreeNode *newNode = nullptr; // Pointer to a new node.

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
template<class T> void BinaryTree<T>::destroySubTree(TreeNode *nodePtr) {
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
template<class T> bool BinaryTree<T>::searchNode(T item) {
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

/*
 * search determines if an item is in the tree.  If so
 * a pointer to the item is returned and if not nullptr
 * is returned.  Note that if we returned T then the data
 * type T would possibly need a copy constructor.
 */
template<class T> T* BinaryTree<T>::search(T &item) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return &nodePtr->value;
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
template<class T> void BinaryTree<T>::remove(T item) {
	deleteNode(item, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template<class T> void BinaryTree<T>::deleteNode(T item, TreeNode *&nodePtr) {
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
template<class T> void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr) {
	// Define a temporary pointer to use in reattaching
	// the left subtree.
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left; // Reattach the left child
		delete tempNodePtr;
	} else if (nodePtr->left == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right; // Reattach the right child
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
template<class T> void BinaryTree<T>::displayInOrder(TreeNode *nodePtr) const {
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

/*
 * Does a Breadth First display of the tree.
 */
template<class T>
void BinaryTree<T>::displayBreadthFirst() {
	deque<TreeNode*> queue;
	TreeNode *nodePtr = root;
	if (nodePtr) {
		queue.push_back(nodePtr);
		while (!queue.empty()) {
			nodePtr = queue.front(); 
			queue.pop_front();
			cout << nodePtr->value << endl;
			if (nodePtr->left)
				queue.push_back(nodePtr->left);
			if (nodePtr->right)
				queue.push_back(nodePtr->right);
		}
	}
}

/*
 * Does a preorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 */
template<class T>
void BinaryTree<T>::iterativePreorder() {
	deque<TreeNode*> stack;

	TreeNode *nodePtr = root;
	if (nodePtr) {
		stack.push_back(nodePtr);
		while (!stack.empty()) {
			nodePtr = stack.back();
			stack.pop_back();
			cout << nodePtr->value << endl;
			if (nodePtr->right)
				stack.push_back(nodePtr->right);
			if (nodePtr->left)
				stack.push_back(nodePtr->left);
		}
	}
}

/*
 * Does a postorder traversal of the tree replacing the recursive calls
 * with its own stack structures of tree node pointers.
 * In post order we do a left-right-visit LRV which if reversed is VRL,
 * a right to left preorder traversal.  Hence we reverse the visit order
 * by using a second stack.
 */
template<class T>
void BinaryTree<T>::iterativePostorder2Stacks() {
	deque<TreeNode*> stack;
	deque<TreeNode*> visitstack;

	TreeNode *nodePtr = root;
	if (nodePtr) {
		stack.push_back(nodePtr);
		while (!stack.empty()) {
			nodePtr = stack.back();
			stack.pop_back();
			visitstack.push_back(nodePtr);
			if (nodePtr->left)
				stack.push_back(nodePtr->left);
			if (nodePtr->right)
				stack.push_back(nodePtr->right);
		}

		while (!visitstack.empty()) {
			nodePtr = visitstack.back();
			visitstack.pop_back();
			cout << nodePtr->value << endl;
		}
	}
}

/*
 * Does a postorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 *
 * This implementation will push a node on the stack with two descendants twice,
 * once before traversing its left subtree and once before traversing its right
 * subtree. A pointer q is used to distinguish between these two cases. Nodes with
 * one descendant are pushed only once, and leaves do not need to be pushed at all.
 */
template<class T>
void BinaryTree<T>::iterativePostorder() {
	deque<TreeNode*> stack;

	TreeNode *p = root, *q = root;
	while (p) {
		while (p->left) {
			stack.push_back(p);
			p = p->left;
		}
		while (!p->right || p->right == q) {
			cout << p->value << endl;
			q = p;
			if (stack.empty())
				return;
			p = stack.back();
			stack.pop_back();
		}
		stack.push_back(p);
		p = p->right;
	}
}

/*
 * Does an inorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 */
template<class T>
void BinaryTree<T>::iterativeInorder() {
	deque<TreeNode*> stack;
	TreeNode *p = root;

	while (p != 0) {
		while (p != 0) {
			// stack the right child (if any)
			if (p->right)
				stack.push_back(p->right);

			// and the node itself when going to the left;
			stack.push_back(p);
			p = p->left;
		}
		// pop a node with no left child
		p = stack.back();
		stack.pop_back();
		while (!stack.empty() && !p->right) {
			// visit it and all nodes with no right.
			cout << p->value << endl;
			p = stack.back();
			stack.pop_back();
		}
		//visit p
		cout << p->value << endl;
		// visit also the first node with
		// a right child (if any)
		if (!stack.empty()) {
			p = stack.back();
			stack.pop_back();
		} else
			p = 0;
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T> void BinaryTree<T>::IndentBlock(int num) {
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
template<class T> void BinaryTree<T>::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

//****************************************************************
// The incrementInOrder member function increments the values    *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template<class T> void BinaryTree<T>::incrementInOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		incrementInOrder(nodePtr->left);
		(nodePtr->value)++;
		incrementInOrder(nodePtr->right);
	}
}
//****************************************************************
// The incrementPreOrder member function increments the values   *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************
template<class T>
void BinaryTree<T>::incrementPreOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		(nodePtr->value)++;
		incrementPreOrder(nodePtr->left);
		incrementPreOrder(nodePtr->right);
	}
}
//****************************************************************
// The incrementPostOrder member function increments the values  *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************
template<class T>
void BinaryTree<T>::incrementPostOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		incrementPostOrder(nodePtr->left);
		incrementPostOrder(nodePtr->right);
		(nodePtr->value)++;
	}
}
/*
 * Does a preorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 */
template<class T>
void BinaryTree<T>::incrementIterativePreorder() {
	deque<TreeNode*> stack;

	TreeNode *nodePtr = root;
	if (nodePtr) {
		stack.push_back(nodePtr);
		while (!stack.empty()) {
			nodePtr = stack.back();
			stack.pop_back();
			(nodePtr->value)++;
			if (nodePtr->right)
				stack.push_back(nodePtr->right);
			if (nodePtr->left)
				stack.push_back(nodePtr->left);
		}
	}
}
/*
 * Does a postorder traversal of the tree replacing the recursive calls
 * with its own stack structures of tree node pointers.
 * In post order we do a left-right-visit LRV which if reversed is VRL,
 * a right to left preorder traversal.  Hence we reverse the visit order
 * by using a second stack.
 */
template<class T>
void BinaryTree<T>::incrementIterativePostorder2Stacks() {
	deque<TreeNode*> stack;
	deque<TreeNode*> visitstack;

	TreeNode *nodePtr = root;
	if (nodePtr) {
		stack.push_back(nodePtr);
		while (!stack.empty()) {
			nodePtr = stack.back();
			stack.pop_back();
			visitstack.push_back(nodePtr);
			if (nodePtr->left)
				stack.push_back(nodePtr->left);
			if (nodePtr->right)
				stack.push_back(nodePtr->right);
		}

		while (!visitstack.empty()) {
			nodePtr = visitstack.back();
			visitstack.pop_back();
			(nodePtr->value)++;
		}
	}
}
/*
 * Does a postorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 *
 * This implementation will push a node on the stack with two descendants twice,
 * once before traversing its left subtree and once before traversing its right
 * subtree. A pointer q is used to distinguish between these two cases. Nodes with
 * one descendant are pushed only once, and leaves do not need to be pushed at all.
 */
template<class T>
void BinaryTree<T>::incrementIterativePostorder() {
	deque<TreeNode*> stack;

	TreeNode *p = root, *q = root;
	while (p) {
		while (p->left) {
			stack.push_back(p);
			p = p->left;
		}
		while (!p->right || p->right == q) {
			(p->value)++;
			q = p;
			if (stack.empty())
				return;
			p = stack.back();
			stack.pop_back();
		}
		stack.push_back(p);
		p = p->right;
	}
}
/*
 * Does an inorder traversal of the tree replacing the recursive calls
 * with its own stack structure of tree node pointers.
 */
template<class T>
void BinaryTree<T>::incrementIterativeInorder() {
	deque<TreeNode*> stack;
	TreeNode *p = root;

	while (p != 0) {
		while (p != 0) {
			// stack the right child (if any)
			if (p->right)
				stack.push_back(p->right);

			// and the node itself when going to the left;
			stack.push_back(p);
			p = p->left;
		}
		// pop a node with no left child
		p = stack.back();
		stack.pop_back();
		while (!stack.empty() && !p->right) {
			// visit it and all nodes with no right.
			(p->value)++;
			p = stack.back();
			stack.pop_back();
		}
		// Increment p
		(p->value)++;
		// visit also the first node with
		// a right child (if any)
		if (!stack.empty()) {
			p = stack.back();
			stack.pop_back();
		} else
			p = 0;
	}
}

#endif