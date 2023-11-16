/* Kyle Tranfaglia
 * COSC320 - Project02
 * Last updated 11/10/23
 * Templated RBTree Declaration and Implimentation - Code provided by Dr. Spickler - Updated with some useful functions
*/
#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <vector>

using namespace std;

enum color_t {
	RED, BLACK
// Red = 0, Black = 1
};

template<class T, class L>
class RBTreeNode {
public:
	T key;
	L value;
	color_t color;
	RBTreeNode *left;
	RBTreeNode *right;
	RBTreeNode *parent;

	RBTreeNode() {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RED;
	}

	RBTreeNode(T k, L val, color_t col, RBTreeNode *l, RBTreeNode *r, RBTreeNode *p) {
		key = k;
		value = val;
		left = l;
		right = r;
		parent = p;
		color = col;
	}
};

template<class T, class L>
class RBTree {
protected:
	RBTreeNode<T, L> *root;
	RBTreeNode<T, L> *NIL;
	void IndentBlock(int num);
	void PrintTree(RBTreeNode<T, L>*, int, int);

	void LeftRotation(RBTreeNode<T, L>*);
	void RightRotation(RBTreeNode<T, L>*);
	void insertFix(RBTreeNode<T, L>*);

	void transplant(RBTreeNode<T, L>*, RBTreeNode<T, L>*);
	void deleteFix(RBTreeNode<T, L>*);
	RBTreeNode<T, L>* getMinNode(RBTreeNode<T, L>*);

	void destroySubTree(RBTreeNode<T, L>*);

	// Added Functions
	void inOrderTraversal(RBTreeNode<T, L>*, vector<T> &, vector<L> &) const;
	RBTreeNode<T, L>* copyTree(RBTreeNode<T, L>*, RBTreeNode<T, L>*, RBTreeNode<T, L>*);
	int calculateNodeCount(RBTreeNode<T, L>*) const;
	int getSize(RBTreeNode<T, L>*) const;
	RBTreeNode<T, L>* findNode(const T&);
	bool compareNodes(RBTreeNode<T, L>*, RBTreeNode<T, L>*, RBTreeNode<T, L>*);

public:
	RBTree();
	virtual ~RBTree();

	void insert(T, L);
	void insert2(T, L);
	void remove(T);

	bool find(const T &);
	
	void PrintTree(int Indent = 4, int Level = 0);

	// Added Functions
	void inOrderTraversal(vector<T> &, vector<L> &);
	void operator=(const RBTree<T, L>&);
	RBTree(const RBTree<T, L>&);
	int getNodeCount();
	bool isEmpty();
	int size();
	void clear();
	bool operator==(const RBTree<T, L>&);
	L getVal(T);

};
// Constructor
template<class T, class L>
RBTree<T, L>::RBTree() {
	NIL = new RBTreeNode<T, L>(T(), L(), BLACK, nullptr, nullptr, nullptr);
	root = NIL;
}
// Destructor
template<class T, class L>
RBTree<T, L>::~RBTree() {
	destroySubTree(root);
	delete NIL;
}

/*
 * Recursively frees the memory of the subtree pointed to by nodePtr.
 */
template<class T, class L>
void RBTree<T, L>::destroySubTree(RBTreeNode<T, L> *nodePtr) {
	if (nodePtr != NIL) {
		if (nodePtr->left != NIL)
			destroySubTree(nodePtr->left);
		if (nodePtr->right != NIL)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}
// Inserts a new node of key and value to the tree and sorts by key
template<class T, class L>
void RBTree<T, L>::insert(T key, L val) {
	RBTreeNode<T, L> *newNode = new RBTreeNode<T, L>(key, val, RED, NIL, NIL, NIL);
	RBTreeNode<T, L> *y = NIL;
	RBTreeNode<T, L> *x = root;

	while (x != NIL) {
		y = x;
		if (key < x->key)
			x = x->left;
		else if (key > x->key)
			x = x->right;
		else { // Updated to handle a value replacement if key already exists
			x->value = val;
			delete newNode;
			return;
		}
	}

	newNode->parent = y;
	if (y == NIL)
		root = newNode;
	else if (newNode->key < y->key)
		y->left = newNode;
	else
		y->right = newNode;

	//  Adjust the RB tree to retain the properties.
	insertFix(newNode);
}

/*
 * Adjusts the tree back to an RB tree after insertion of a new node.
 */
template<class T, class L>
void RBTree<T, L>::insertFix(RBTreeNode<T, L> *z) {
	RBTreeNode<T, L> *y = NIL;

	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotation(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotation(z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					RightRotation(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotation(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

/*
 * This is a helper function to the node deletion process.
 */
template<class T, class L>
void RBTree<T, L>::transplant(RBTreeNode<T, L> *u, RBTreeNode<T, L> *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

/*
 * Finds the smallest node in the subtree pointed to by x.  As usual
 * we traverse down the left branch as far as possible.  The node y
 * tracks x's parent so that when x == NIL, y is the minimum valued
 * node.
 */
template<class T, class L>
RBTreeNode<T, L>* RBTree<T, L>::getMinNode(RBTreeNode<T, L> *x) {
	if (x == NIL)
		return NIL;

	RBTreeNode<T, L> *y = NIL;
	while (x != NIL) {
		y = x;
		x = x->left;
	}
	return y;
}

/*
 * Finds and deletes the node whose value is val.  Calls the deleteFix function
 * to readjust the tree back to RB format.
 */
template<class T, class L>
void RBTree<T, L>::remove(T val) {
	RBTreeNode<T, L> *z = findNode(val);
	if (z == NIL)
		return;

	RBTreeNode<T, L> *y = z;
	RBTreeNode<T, L> *x = NIL;
	color_t yorigcol = y->color;

	if (z->left == NIL) {
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (yorigcol == BLACK)
		deleteFix(x);
}

/*
 * Readjusts the RB tree to fix any violated properties after the deletion of a
 * node.
 */
template<class T, class L>
void RBTree<T, L>::deleteFix(RBTreeNode<T, L> *x) {
	RBTreeNode<T, L> *w = NIL;

	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotation(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotation(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotation(x->parent);
				x = root;
			}
		} else {
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotation(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotation(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotation(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 x --- pointer to the node to rotate right around.
 */

template<class T, class L>
void RBTree<T, L>::RightRotation(RBTreeNode<T, L> *x) {
	RBTreeNode<T, L> *y = x->left;
	x->left = y->right;

	if (y->right != NIL)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T, class L>
void RBTree<T, L>::LeftRotation(RBTreeNode<T, L> *x) {
	RBTreeNode<T, L> *y = x->right;
	x->right = y->left;

	if (y->left != NIL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

/*
 * This returns true if the item is in the RB-tree and false otherwise.
 * It simply calls the node based recursive version and checks the result
 * against the NIL object.
 */
template<class T, class L>
bool RBTree<T, L>::find(const T &item) {
	return findNode(item) != NIL;
}

/*
 * Recursive find function that finds the first node containing the value item.
 */
template<class T, class L>
RBTreeNode<T, L>* RBTree<T, L>::findNode(const T &item) {
	RBTreeNode<T, L> *nodePtr = root;

	while (nodePtr != NIL) {
		if (nodePtr->key == item)
			return nodePtr;
		else if (item < nodePtr->key)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return NIL;
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template<class T, class L>
void RBTree<T, L>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template<class T, class L>
void RBTree<T, L>::PrintTree(RBTreeNode<T, L> *t, int Indent, int Level) {
	if (t != NIL) {
		PrintTree(t->right, Indent, Level + 1);

		string RBstr;
		if (t->color == RED)
			RBstr = "R";
		else
			RBstr = "B";

		IndentBlock(Indent * Level);
		cout << t->value << " (" << RBstr << ")" << endl;

		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template<class T, class L>
void RBTree<T, L>::PrintTree(int Indent, int Level) {
	if (root)
		PrintTree(root, Indent, Level);
}

// Function to call recursive traversal to load two parallel vector for the pair
template<class T, class L>
void RBTree<T, L>::inOrderTraversal(vector<T> &vec1, vector<L> &vec2) {
	inOrderTraversal(root, vec1, vec2);
}

// Function to recursively traverse the tree and load the values to parallel vectors
template<class T, class L>
void RBTree<T, L>::inOrderTraversal(RBTreeNode<T, L>* nodeptr, vector<T> &vec1, vector<L> &vec2) const {
	if (nodeptr != NIL) {
    	inOrderTraversal(nodeptr->left, vec1, vec2);
    	vec1.push_back(nodeptr->key);
		vec2.push_back(nodeptr->value);
    	inOrderTraversal(nodeptr->right, vec1, vec2);
	}
}

/*
 * Recursive function to copy a tree or subtree.
 */
template<class T, class L>
RBTreeNode<T, L>* RBTree<T, L>::copyTree(RBTreeNode<T, L> *nodeptr, RBTreeNode<T, L> *parent, RBTreeNode<T, L> *NILptr) {
    if (nodeptr == NILptr) {
        return NIL;
    }

	RBTreeNode<T, L>* newNode = new RBTreeNode<T, L>(nodeptr->key, nodeptr->value, nodeptr->color, NIL, NIL, parent);
	newNode->left = copyTree(nodeptr->left, newNode, NILptr);
	newNode->right = copyTree(nodeptr->right, newNode, NILptr);

	return newNode;
}

// Assignment overload
template<class T, class L>
void RBTree<T, L>::operator=(const RBTree<T, L> &obj) {
	clear();
	root = copyTree(obj.root, NIL, obj.NIL); // Sends object root, NIL and object (NIL) as parameter to copy tree
}

// Copy Constructor
template<class T, class L>
RBTree<T, L>::RBTree(const RBTree<T, L> &obj) {
	root = copyTree(obj.root, NIL, obj.NIL); // Sends object root, NIL and object (NIL) as parameter to copy tree
}

// Function to return the number of nodes by calling a recursive calculateNodeCount function
template<class T, class L>
int RBTree<T, L>::getNodeCount() {
    return calculateNodeCount(root);
}

// Recursive function to count the number of nodes in a binary tree
template<class T, class L>
int RBTree<T, L>::calculateNodeCount(RBTreeNode<T, L> *nodeptr) const{
	// If no node, return 0
	if (nodeptr == NIL) {
        return 0;
    }
    return (calculateNodeCount(nodeptr->left) + calculateNodeCount(nodeptr->right)) + 1; // Sum of left and right tree plus root ... recursive call
}

// Function to return true if the tree is empty
template<class T, class L>
bool RBTree<T, L>::isEmpty() {
	bool status = false;
	// Sets status to true if the root is NIL
	if (root == NIL) {
		status = true;
	}
	return status;
}

// Function to get the size of the tree by calling recursive size function
template<class T, class L>
int RBTree<T, L>::size() {
	return getSize(root);
}

// Recursive size function
template<class T, class L>
int RBTree<T, L>::getSize(RBTreeNode<T, L>* nodeptr) const {
    if (nodeptr == NIL) {
        return 0;
    }
    return 1 + getSize(nodeptr->left) + getSize(nodeptr->right);
}

// Function to clear the tree by destroying the nodes and setting the root to NIL
template<class T, class L>
void RBTree<T, L>::clear() {
	destroySubTree(root);
	root = NIL;
}

// Check equality operator overload to return true if the key-value pairs of each map are the same
template <class T, class L>
bool RBTree<T, L>::operator==(const RBTree<T, L>& obj) {
    return compareNodes(root, obj.root, obj.NIL);
}

// Recursive function to check equality of the key-value pairs for two maps
template <class T, class L>
bool RBTree<T, L>::compareNodes(RBTreeNode<T, L> *nodeptr1, RBTreeNode<T, L> *nodeptr2, RBTreeNode<T, L> *NILptr) {
    // Check if both trees are empty
	if (nodeptr1 == NIL && nodeptr2 == NILptr) {
        return true;
    }
	// Check if one tree is empty and the other is not
    if (nodeptr1 == NIL || nodeptr2 == NILptr) {
        return false;
    }
	 // Check that Key-value pairs do match
    if (nodeptr1->key != nodeptr2->key || nodeptr1->value != nodeptr2->value) {
        return false;
    }

    // Recursively compare left and right subtrees
    return compareNodes(nodeptr1->left, nodeptr2->left, NILptr) && compareNodes(nodeptr1->right, nodeptr2->right, NILptr);
}

// Function to return the value of a node given its key
template <class T, class L>
L RBTree<T, L>::getVal(T k) {
	RBTreeNode<T, L> *nodeptr = findNode(k); // Searches for and returns node
	return nodeptr->value;
}

#endif /* RBTREE_H_ */