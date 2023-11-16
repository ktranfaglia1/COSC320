/* Kyle Tranfaglia
*  COSC320 - Homework03 - Ex. 2
*  Last updated 09/22/23
*  Implimentation for the IntBinaryTree class - Code Provided by Dr. Spickler - Altered to sort using a complete binary tree and create trees given arrays
*/
#include "IntBinaryTree.h"

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

// Function to get the max value in the array and return this value as an integer
int IntBinaryTree::getMaxValue(int *A, int sz) {
	int maxValue = *(A); // Sets the current max value as first element
	// Loop to compare each index of the array to the max value and if maxValue is less than that index value, maxValue is updated to the index value
	for (int i = 1; i < sz; i++) {
		if (*(A + i) > maxValue) {
			maxValue = *(A + i);
		}
	}
	return maxValue;
}
// Function to load an array passed as a pointer into a queue which will be used to make a complete tree via function call to makeTree function 
void IntBinaryTree::LoadArray(int *A, int sz) {	
	queue<int> elementQueue; // Creates queue of integers
	// Loop to push every element of the array to the queue
	for (int i = 0; i < sz; i++) {
		elementQueue.push(*(A + i));
	}
	// Function call to make the tree by sending the root for traversal, queue to pop elements into tree, the needed height of the tree, and the E value (max + 1)
	makeTree(root, elementQueue, ceil(log2(sz)) + 1, getMaxValue(A, sz) + 1);
	setMin(root); // Calls function to fill the parent nodes with the min value of the children
}
// Function to make the tree recursively using the element queue to create the leaves and filling the remaining nodes of the complete tree with the max value E if they are leaves and the default -1 otherwise
void IntBinaryTree::makeTree(TreeNode *&nodeptr, queue<int> &elementQueue, int depth, int maxValue) {
	depth--; // Decrements depth ... once it reaches 0, we are at the lowest level ... leaves of compete tree
	// If the lowest level is reached ... create a leaf node
	if (depth == 0) { 
		// If elements in the queue create a leaf node with the next element in the queue ... otherwise, create a leaf node of the max E value
		if (elementQueue.size() > 0) { 
			nodeptr = new TreeNode(elementQueue.front());
			elementQueue.pop();
		}
		else { 
			nodeptr = new TreeNode(maxValue);
		}
	}
	// Otherwise, create a node using the default -1 value and traverse the tree recursively ... left children, then right children
	else {
		nodeptr = new TreeNode();
		makeTree(nodeptr->left, elementQueue, depth, maxValue); 
		makeTree(nodeptr->right, elementQueue, depth, maxValue); 
	}
}
// Function to set the parent nodes as the minimum value of the children for all parent nodes in the tree ... resulting in the lowest value at the root
int IntBinaryTree::setMin(TreeNode *&nodeptr) {
	// If there is a non-leaf node
	if (nodeptr->left && nodeptr->right) { 
	
		int leftChild = setMin(nodeptr->left); // Recursively get value of left child
		int rightChild = setMin(nodeptr->right); // Recursively get value of right child
		// Compare the values of the children and set the current node (parent) to the lower value
		if (rightChild < leftChild) {
			nodeptr->value = rightChild;
		}
		else { 
			nodeptr->value = leftChild;
		}
	}
	return nodeptr->value; // Returns the of the current node so that the left and right child variables can capture the values 
}
// Function to replace every minimum value in the tree with the max E value, unless it is a duplicate
void IntBinaryTree::replaceMin(TreeNode *&nodeptr, int minVal, int maxVal, int &count) {
	// If there are no more nodes to traverse ... finished derecursing or went beyond leaf ... return (base case)
	if (!nodeptr) {
        return;
    }
	// Checks if the value of the traversal node is the minimum value
    else if (nodeptr->value == minVal) {
		// If it is a minimum value and the node is not a leaf, chnage the value to the max
		if (nodeptr->left && nodeptr->right) {
        	nodeptr->value = maxVal;
		}
		// If it is a minimum value and it is at a leaf, allow one and only one leaf to be updated to max value ... tracked using count
		else if (!nodeptr->left && !nodeptr->right && count != 1) {
			count++; // increment count to denote that a duplicate value (same value in another leaf) cannot be updated to the max
			nodeptr->value = maxVal;
		}
    }
    // Recursively traverses the tree starting the the left and then the right sub tree
    replaceMin(nodeptr->left, minVal, maxVal, count);
    replaceMin(nodeptr->right, minVal, maxVal, count);
}
// Returns a sorted array by calling the setMin and replaceMin functions of the tree for every leaf in the tree (non-max). The array is directly updated by pointer from parameter
void IntBinaryTree::ReturnSortedArray(int *A, int sz) {
	int maxVal = getMaxValue(A, sz) + 1, count = 0; // Variables for the max value and the count to stop duplicates from being replaced
	// Loop for size of array calling the setMin and replaceMin functions of the tree for every leaf in the tree (non-max)
	for (int i = 0; i < sz; i++) {
		count = 0;
		setMin(root); // Calls function to set parent nodes to min of children
		*(A + i) = root->value; // The minimum value is now at the root, so set this value to current index in array
		replaceMin(root, root->value, maxVal, count); // Calls function to replace every minimum value besides leaf duplicates with the max value
	}
}