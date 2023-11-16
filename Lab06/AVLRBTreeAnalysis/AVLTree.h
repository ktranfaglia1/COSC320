/* Kyle Tranfaglia
*  COSC320 - Lab06
*  Last updated 10/11/23
*  Templated AVL tree object Declaration and Implimentation - Code provided by Dr Spickler - added some functions
*/
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

template <class T> class AVLTree {
  private:
    struct TreeNode {
        T value;
        int height = 1;  //  Height of the subtree below the node.
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
    };

    TreeNode *root;

    // Private member functions
    void insert(TreeNode *&, TreeNode *&);
    void destroySubTree(TreeNode *);
    void deleteNode(T, TreeNode *&);
    void displayInOrder(TreeNode *) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;
    void IndentBlock(int);
    void PrintTree(TreeNode *, int, int);

    void LeftRotation(TreeNode *&);
    void RightRotation(TreeNode *&);
    int getBalanceFactor(TreeNode *);
    int getHeight(TreeNode *);
    void Balance(TreeNode *&);

    // Testing Functions
    bool isBalanced(TreeNode *);
    void PrintTreeHB(TreeNode *, int, int);

    int height(TreeNode*) const;
	int calculateIPL(TreeNode*, int);
	int calculateNodeCount(TreeNode*);

  public:
    AVLTree() { root = nullptr; }
    ~AVLTree() { destroySubTree(root); }

    void insertNode(T);
    bool searchNode(T);
    void remove(T);
    void displayInOrder() const { displayInOrder(root); }
    void displayPreOrder() const { displayPreOrder(root); }
    void displayPostOrder() const { displayPostOrder(root); }
    void PrintTree(int Indent = 4, int Level = 0);

    // Testing Functions
    bool isBalanced();
    void PrintTreeHB(int Indent = 4, int Level = 0);

    int height();
	int getIPL();
	int getNodeCount();
	double getAverageIPL();
};

/*
Does a right rotation at the input node.  In a right rotation, the sub tree of
 nodePtr
    |
    X
   / \
  Y   C
 / \
A   B

becomes

 nodePtr
    |
    Y
   / \
  A   X
     / \
    B   C

The function also updates the height values for the X and Y nodes.  Note that
the heights of the A, B, and C subtrees are not changed by the rotation.

Parameters
nodePtr --- pointer to the node to rotate right around.
*/

template <class T> void AVLTree<T>::RightRotation(TreeNode *&nodePtr) {
    TreeNode *L = nodePtr->left;
    TreeNode *temp = L->right;
    L->right = nodePtr;
    nodePtr->left = temp;
    nodePtr->height =
        max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
    L->height = max(getHeight(L->left), getHeight(L->right)) + 1;
    nodePtr = L;
}

/*
Does a left rotation at the input node.  In a left rotation, the sub tree of
 nodePtr
    |
    Y
   / \
  A   X
     / \
    B   C

becomes

 nodePtr
    |
    X
   / \
  Y   C
 / \
A   B

The function also updates the height values for the X and Y nodes.  Note that
the heights of the A, B, and C subtrees are not changed by the rotation.

Parameters
nodePtr --- pointer to the node to rotate right around.
*/

template <class T> void AVLTree<T>::LeftRotation(TreeNode *&nodePtr) {
    TreeNode *R = nodePtr->right;
    TreeNode *temp = R->left;
    R->left = nodePtr;
    nodePtr->right = temp;
    nodePtr->height =
        max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
    R->height = max(getHeight(R->left), getHeight(R->right)) + 1;
    nodePtr = R;
}

/*
Returns the height of the subtree pointed to by nodePtr.

Parameters
nodePtr --- pointer to the node.
*/
template <class T> int AVLTree<T>::getHeight(TreeNode *nodePtr) {
    if (!nodePtr)
        return 0;

    return nodePtr->height;
}

/*
Returns the balance factor of the node pointed to by nodePtr.

Parameters
nodePtr --- pointer to the node.
*/
template <class T> int AVLTree<T>::getBalanceFactor(TreeNode *nodePtr) {
    if (!nodePtr)
        return 0;

    return getHeight(nodePtr->left) - getHeight(nodePtr->right);
}

/*
Does one balance of the subtree at the given node.  

Parameters
nodePtr --- pointer to the node.
*/
template <class T> void AVLTree<T>::Balance(TreeNode *&nodePtr) {
    if (!nodePtr)
        return;

    // Rebalance if needed.
    int balanceFactor = getBalanceFactor(nodePtr);

    // Rebalance if needed.
    // Left heavy.
    if (balanceFactor > 1) {
        if (getBalanceFactor(nodePtr->left) > 0)
            RightRotation(nodePtr);
        else {
            LeftRotation(nodePtr->left);
            RightRotation(nodePtr);
        }
    }

    // Right heavy.
    if (balanceFactor < -1) {
        if (getBalanceFactor(nodePtr->right) > 0) {
            RightRotation(nodePtr->right);
            LeftRotation(nodePtr);
        } else
            LeftRotation(nodePtr);
    }
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template <class T>
void AVLTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
    if (nodePtr == nullptr)
        nodePtr = newNode; // Insert the node.
    else if (newNode->value < nodePtr->value)
        insert(nodePtr->left, newNode); // Search the left branch
    else
        insert(nodePtr->right, newNode); // Search the right branch

    // Update the height of each node in the branches called.
    nodePtr->height =
        1 + max(getHeight(nodePtr->left), getHeight(nodePtr->right));

    Balance(nodePtr);
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template <class T> void AVLTree<T>::insertNode(T item) {
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
template <class T> void AVLTree<T>::destroySubTree(TreeNode *nodePtr) {
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
template <class T> bool AVLTree<T>::searchNode(T item) {
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
template <class T> void AVLTree<T>::remove(T item) { deleteNode(item, root); }

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template <class T> void AVLTree<T>::deleteNode(T item, TreeNode *&nodePtr) {
    if (!nodePtr)
        return;

    if (item < nodePtr->value)
        deleteNode(item, nodePtr->left);
    else if (item > nodePtr->value)
        deleteNode(item, nodePtr->right);
    else {
        if (!nodePtr->left || !nodePtr->right) {
            TreeNode *tempNodePtr = nullptr;
            if (!nodePtr->left)
                tempNodePtr = nodePtr->right;
            else
                tempNodePtr = nodePtr->left;

            if (!tempNodePtr) {
                tempNodePtr = nodePtr;
                nodePtr = nullptr;
            } else
                *nodePtr = *tempNodePtr;
            delete tempNodePtr;
        } else {
            TreeNode *tempNodePtr = nodePtr->right;
            // Go to the end left node.
            while (tempNodePtr->left)
                tempNodePtr = tempNodePtr->left;
            nodePtr->value = tempNodePtr->value;
            deleteNode(tempNodePtr->value, nodePtr->right);
        }
    }

    if (!nodePtr)
        return;

    // Update the height of each node in the branches called.
    nodePtr->height =
        1 + max(getHeight(nodePtr->left), getHeight(nodePtr->right));

    int balanceFactor = getBalanceFactor(nodePtr);
    while (balanceFactor > 1 || balanceFactor < -1) {
        Balance(nodePtr);
        balanceFactor = getBalanceFactor(nodePtr);
    }
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template <class T> void AVLTree<T>::displayInOrder(TreeNode *nodePtr) const {
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
template <class T> void AVLTree<T>::displayPreOrder(TreeNode *nodePtr) const {
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
template <class T> void AVLTree<T>::displayPostOrder(TreeNode *nodePtr) const {
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

template <class T> void AVLTree<T>::IndentBlock(int num) {
    for (int i = 0; i < num; i++)
        cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

template <class T>
void AVLTree<T>::PrintTree(TreeNode *t, int Indent, int Level) {
    if (t) {
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

template <class T> void AVLTree<T>::PrintTree(int Indent, int Level) {
    if (root)
        PrintTree(root, Indent, Level);
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template <class T>
void AVLTree<T>::PrintTreeHB(TreeNode *t, int Indent, int Level) {
    if (t) {
        int bal = getBalanceFactor(t);
        PrintTreeHB(t->right, Indent, Level + 1);
        IndentBlock(Indent * Level);
        cout << t->value << "/" << t->height << "/" << bal << "\n";
        PrintTreeHB(t->left, Indent, Level + 1);
    }
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template <class T> void AVLTree<T>::PrintTreeHB(int Indent, int Level) {
    if (root)
        PrintTreeHB(root, Indent, Level);
}

//****************************************************************
// This function is a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template <class T> bool AVLTree<T>::isBalanced(TreeNode *t) {
    if (!t)
        return true;

    if (getBalanceFactor(t) > 1 || getBalanceFactor(t) < -1)
        return false;
    else
        return isBalanced(t->left) && isBalanced(t->right);
}

//****************************************************************
// This function initiates a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template <class T> bool AVLTree<T>::isBalanced() {
    if (root)
        return isBalanced(root);

    return true;
}

// Public function to return the height (number of levels) in the tree
template<class T>
int AVLTree<T>::height() {
	return height(root); // returns the value from recursive height function
}
// Recursive function to count the levels of the tree
template<class T>
int AVLTree<T>::height(TreeNode* nodePtr) const {
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
int AVLTree<T>::calculateIPL(TreeNode* nodeptr, int pathLength) {
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
int AVLTree<T>::getIPL() {
    if (!root) {
        return 0;
    }
    return calculateIPL(root, 0); // Call the recursive function to calculate the total path lengths of the tree
}
// Function to return the number of nodes by calling a recursive calculateNodeCount function
template<class T>
int AVLTree<T>::getNodeCount() {
	return calculateNodeCount(root);
}

// Recursive function to count the number of nodes in a binary tree
template<class T>
int AVLTree<T>::calculateNodeCount(TreeNode* nodeptr) {
    if (!nodeptr) {
        return 0;
    }
    return (calculateNodeCount(nodeptr->left) + calculateNodeCount(nodeptr->right)) + 1;
}

// Function to calculate the average Internal Path Length (IPL) of a binary tree
template<class T>
double AVLTree<T>::getAverageIPL() {
    if (!root) {
        return 0;
    }
    return static_cast<double> (getIPL()) / (getNodeCount());  // Calculate and return the average IPL
}
#endif