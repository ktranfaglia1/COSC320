/* Kyle Tranfaglia
*  COSC320 - Lab03 - Ex.1
*  Last updated 09/13/23
*  IntBinary Tree Implimentation - Code provided by Dr. Spickler - Updated with added functions
*/

// Implementation file for the IntBinaryTree class
#include "IntBinaryTree.h"

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
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

void IntBinaryTree::insertNode(int num) {
	TreeNode *newNode = nullptr;	// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;

	// Insert the node.
	insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************

void IntBinaryTree::destroySubTree(TreeNode *nodePtr) {
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

bool IntBinaryTree::searchNode(int num) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == num)
			return true;
		else if (num < nodePtr->value)
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

void IntBinaryTree::remove(int num) {
	deleteNode(num, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

void IntBinaryTree::deleteNode(int num, TreeNode *&nodePtr) {
	if (num < nodePtr->value)
		deleteNode(num, nodePtr->left);
	else if (num > nodePtr->value)
		deleteNode(num, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************

void IntBinaryTree::makeDeletion(TreeNode *&nodePtr) {
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

void IntBinaryTree::displayInOrder(TreeNode *nodePtr) const {
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

void IntBinaryTree::displayPreOrder(TreeNode *nodePtr) const {
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

void IntBinaryTree::displayPostOrder(TreeNode *nodePtr) const {
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

void IntBinaryTree::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

void IntBinaryTree::PrintTree(TreeNode *t, int Indent, int Level) {
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

void IntBinaryTree::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

// Public function to return the number of nodes by creating a count variables and using a recursive function to increment count and return it
int IntBinaryTree::numNodes() {
	int count = 0;
	numNodes(count, root); // Call to recursive function sending in count variable and the root to the node
	return count;
}
// Recursive function to count tye number of nodes in which it performs an inorder traversal and counts each node
void IntBinaryTree::numNodes(int &cnt, TreeNode* nodePtr) const {
	// As long as there is a node ... count the node and move left, then right, counting the nodes pointed throughout the traversal
	if (nodePtr) {
		cnt++;
		numNodes(cnt, nodePtr->left);
		numNodes(cnt, nodePtr->right);
	}
}
// Public function to return the number of leaves in a tree
int IntBinaryTree::numLeaves() {
	int count = 0; // Count variable to send as a referenced parameter
	numLeaves(count, root); // Call to recursive function sending in count variable and the root to the node
	return count;
}
// Recursive function find the number of leaves in a tree by traversing the tree in order and counting nodes without children
void IntBinaryTree::numLeaves(int &cnt, TreeNode* nodePtr) const {
	// As long as there is a node ... check to increment count, move left, then right recursively. In order traversal
	if (nodePtr) {
		// Increments count variable if the node does not have any children
		if (nodePtr->left == nullptr && nodePtr->right == nullptr)
			cnt++;
		numLeaves(cnt, nodePtr->left);
		numLeaves(cnt, nodePtr->right);
	}
}
// Public function to return the height (number of levels) in the tree
int IntBinaryTree::height() {
	return height(root); // returns the value from recursive height function
}
// Recursive function to count the levels of the tree
int IntBinaryTree::height(TreeNode* nodePtr) const {
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
// Public function to print the node values of each path from the root to a leaf that is the same length as the height of the tree  
void IntBinaryTree::PrintHeightPaths() {
	vector<int> v; // Creates an integer vector to push path values onto in recursive function
	PrintHeightPaths(v, root); // Calls recursive function to print the path sending a vector and the root node
}
// Recursive function to push back node values as the tree is traversed in order and 
// print those values if a leaf at the  same length as the height of the tree is reahced
void IntBinaryTree::PrintHeightPaths(vector<int> vec, TreeNode* nodePtr) const {
	// While there is a node ...
	if (nodePtr) {
		vec.push_back(nodePtr->value); // Pushes value to back of vector ... reverts to prevous state of vector when the function derecurses ... gotta love vectors
		PrintHeightPaths(vec, nodePtr->left); 
		PrintHeightPaths(vec, nodePtr->right);
		// Checks if a leaf at height of tree has been reached by comparing height count to vector size
		if (vec.size() == height(root)) {
			// Loop to print all of the indices of the vector ... no need to remove the elements! yay for vectors!
			for (int i = 0; i < vec.size(); i++)
				cout << vec[i] << " ";
			cout << endl;
		}
	}
}