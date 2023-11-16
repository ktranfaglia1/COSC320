/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * Linked List ListCollection Object and template Declaration and Implementation
*/
#ifndef CROSSREFLISTNODE_H
#define CROSSREFLISTNODE_H

#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class ListNode {
    public:
        T value;           // Node value
        ListNode<T> *next; // Pointer to the next node

        // Constructor
        ListNode(T val) { value = val; next = nullptr; }
};

// Templated ListCollection class using linked list as a data structure
template<class T, class Node = ListNode<T>>
class ListCollection {
private:
    Node *head; // Head pointer to keep track of linked list start

    bool isValid(int); // Validation checker for index accessing of linked list
public:
    ListCollection(int sz = 10); // Constructor with default size of ten ...  size does nothing in this case
    ~ListCollection(); // Destructor to delete all nodes of an object

    // Accessor and Mutator for an index
    void setElement(int, T);
    T getElement(int);

    void displayList(bool nl = false) const; // Display function with a defaulted display type formating of false

    // Copy constructor and assignment =operator overload
    ListCollection(const ListCollection &obj);
    const ListCollection<T> operator=(const ListCollection &right);

    // Functions to Access and Mutate the list 
    int size();
    int capacity();
    void pushFront(T);
    void pushBack(T);
    T popFront();
    T popBack();
    void insertOrdred(T);
    void removeElement(T);
};

//**************************************************
// Templated ListCollection Object implementation  *
//**************************************************

// Constructor taking in size with default as 10 but linked list will always start size 0, so parameter is ignored
template<class T, class Node>
ListCollection<T, Node>::ListCollection(int sz) {
   head = nullptr;
}
// Destructor to go through linked list and delete one node at a time from header to end of list
template<class T, class Node>
ListCollection<T, Node>::~ListCollection() {
    Node *nodePtr;   // To traverse the list
	Node *nextNode;  // To point to the next node

	nodePtr = head; // Sets positional pointer varaiable to head of list

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr) {
		nextNode = nodePtr->next; // Save a pointer to the next node.
		delete nodePtr; // Delete the current node.
		nodePtr = nextNode; // Position nodePtr at the next node.
	}
}
// Copy constructor
template<class T, class Node>
ListCollection<T, Node>::ListCollection(const ListCollection &obj) {
    Node *nodePtr = obj.head; // Traversing varaiable to go through the list, pointer set to list header of object
    // Loops as long as nodePtr points to something (not nullptr indicating end of list) and pushbacks the value for construted obj list
    while (nodePtr) {
        pushBack(nodePtr->value); // Adds node to back of linked list with value from the obj linked list at corresponding element
        nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
    }
}
// Operator overload = to set left obj equal to right obj
template<class T, class Node>
const ListCollection<T> ListCollection<T, Node>::operator = (const ListCollection &right) {
    // Code from destructor is used to delete the previous linked list before copying the incoming object list with pushback
    Node *nodePtr;   // To traverse the list
	Node *nextNode;  // To point to the next node

	nodePtr = head; // Sets positional pointer varaiable to head of list

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr) {
		nextNode = nodePtr->next; // Save a pointer to the next node.
		delete nodePtr; // Delete the current node.
		nodePtr = nextNode; // Position nodePtr at the next node.
	}
    head = nullptr; // Sets the head to nullptr as there is currently no first element

    nodePtr = right.head; // Traversing varaiable to go through the list, pointer set to list header of object
    // Loops as long as nodePtr points to something (not nullptr indicating end of list) and pushbacks the value for construted obj list
    while (nodePtr) {
        pushBack(nodePtr->value); // Adds node to back of linked list with value from the obj linked list at corresponding element
        nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
    }
    return *this;
}
// Function to return number of elements in object list
template<class T, class Node>
int ListCollection<T, Node>::size() {
    int count = 0; // Variable to keep count of traverses through list
    Node *nodePtr = head; // Traverssing pointer set to head

    // Loop to traverse list until nodePtr = nullptr
    while (nodePtr) {
        count++;
        nodePtr = nodePtr->next;
    }
    return count;
}
// Function to return capacity of object list, which is the same as the size for this version
template<class T, class Node>
int ListCollection<T, Node>::capacity() {
    return size();
}
// Function for input validation that returns true if valid
template<class T, class Node>
bool ListCollection<T, Node>::isValid(int element) {
    // Input Validation for linked list bounds. Returns true if both statment conditions are met, otherwise false 
    return (element >= 0 && element < size());
}
// Function to set the value of a node in the linked list given element and value
template<class T, class Node>
void ListCollection<T, Node>::setElement(int element, T value) {   
    // Sets the element in the linked list to given value if element is valid (within allowed bounds)
    if (isValid(element)) {
        Node *nodePtr = head; // Traversing pointer set to head of list
        
        // Loop to traverse to list up to element
        for (int i = 0; i < element; i++)
            nodePtr = nodePtr->next;

        nodePtr->value = value; // sets the node value to parameter for value
    }
}
// Function to get the value of a node from the linked list
template<class T, class Node>
T ListCollection<T, Node>::getElement(int position) {
    T defaultObj = T(); // Default return for an object
    int sz = size(); // variable to hold size of list

    // Checks if the position is valid or holds a value and returns or changes position accordingly
    if (sz == 0)
        return defaultObj;

    else if (position < 0)
        return head->value;

    else if (position > sz - 1)
        position = sz - 1;

    Node *nodePtr = head; // Traversing pointer set to head of list

    // Loop to traverse to list up to position
    for (int i = 0; i < position; i++)
        nodePtr = nodePtr->next;

    return nodePtr->value;
}
// Function to display the value of each node in the linked list
template<class T, class Node>
void ListCollection<T, Node>::displayList(bool nl) const {
    Node *nodePtr = head; // Traversing pointer set to head of list

    // Displays each node in order with a space or newline depedending on boolean and if the list is empty, it is stated
    if (nl) {
        if (head) {
            while (nodePtr) {
                std::cout << nodePtr->value << std::endl;
                nodePtr = nodePtr->next;
            }
        }
        else
            std::cout << "List is empty!" << std::endl;
    }
    else {
        if (head) {
            while (nodePtr) {
                std::cout << nodePtr->value << " ";
                nodePtr = nodePtr->next;
            }
        }
        else 
            std::cout << "List is empty!" << std::endl;
        std::cout << std::endl;
    }
}
// Function to add the incoming parameter value as a new node at the end of the list
template<class T, class Node>
void ListCollection<T, Node>::pushBack(T element) {
    Node *newNode = new Node(element); // Creates a new node pointer of with a value of element

    // Checks if head is pointing to nullptr, otherwise puts new node at end of list
    if (!head)
        head = newNode;
    else {
        Node *nodePtr = head; // Traversing pointer set to head of list

        // Loop to run while nodeptr is not equal to nullptr
        while (nodePtr->next) {
            nodePtr = nodePtr->next;
        }
        nodePtr->next = newNode; // nodePtr now at last node, so the link is set to the new node
     }
}
// Function to remove a node from the back of the linked list and return the value of the node removed
template<class T, class Node>
T ListCollection<T, Node>::popBack() {
	T defaultret = T(); // Default return for an object

    // Checks if head is pointing to nullptr
    if (!head)
        return defaultret;

    Node *nodePtr = head; // Traversing pointer set to head of list
    Node *previousNode = nullptr; // Pointer to keep track of previous node

    // Loop to run while nodeptr is not equal to nullptr
    while (nodePtr->next) {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }

    T retval = nodePtr->value; // Stores the value of the node that is being deleted

    // Pointer control statement. Either sets head to nullptr or the last node to nullptr since the link is being deleted. Otherwise, it would point to something non-existent
    if (previousNode)
        previousNode->next = nullptr;
    else
        head = nullptr;

    delete nodePtr; // Deletes pointer

    return retval;
}
// Function to add the incoming parameter value as a node to the strat of the linked list
template<class T, class Node>
void ListCollection<T, Node>::pushFront(T element) {
    Node *newNode = new Node(element); // Creates a new node pointer of with a value of element

    // Checks if head is pointing to nullptr, otherwise puts new node at front of list
    if (!head)
        head = newNode;
    else {
        newNode->next = head; // Sets new node as head
        head = newNode; // sets head to new node
    }
}
// Function to remove a node from the front of the linked list and return the value removed
template<class T, class Node>
T ListCollection<T, Node>::popFront() {
    T defaultret = T(); // Default return for an object

    // Checks if head is pointing to nullptr
    if (!head)
        return defaultret;

    T retval = head->value; // Stores the value being deleted

    Node *nodePtr = head; // Sets a node pointer to head
    head = nodePtr->next; // Sets the head to the following node
    delete nodePtr; // Deletes nodeptr, the old head

    return retval;
}
// Function to insert a Node into the list based on its value. The value of the node is sent as a parameter, then the node of that value is created and inserted in ascending order into the list
template<class T, class Node>
void ListCollection<T, Node>::insertOrdred(T element) {
    Node *newNode = new Node(element); // Creates a new node pointer of with a value of element

    Node *nodePtr = head; // Traversing pointer set to head of list
    Node *previousNode = nullptr; // Pointer to track previous node

    // Checks if head = nullptr, otherwise it proceeds to do a linear seach to place new node
    if (!head)
        head = newNode;
    else {
        // Loop to linear search where to place new node by checking if the pointer is pointing to a node and if the value of the node is less than the element of the new node
        while (nodePtr && (nodePtr->value < element)) {
            previousNode = nodePtr; // Sets previous node to current node
            nodePtr = nodePtr->next; // Sets node pointer to next node
        }
        newNode->next = nodePtr; // links new node to node pointed to by nodeptr, the following ordered node value
        // Checks if the previous node if pointing to nullptr and sets head to new node, otherwise previous node is linked to new node
        if (!previousNode) {
            head = newNode;
        }
        else {
            previousNode->next = newNode; // sets the previous node, the next lowest value node, to the new node
        }
    }
}
// Function to remove an element from a list by searching for a node value passed as a parameter and deletes the node if found while maintaining the list
template<class T, class Node>
void ListCollection<T, Node>::removeElement(T element) {
    Node *nodePtr = head; // Traversing pointer set to head of list
    Node *previousNode = nullptr; // Pointer to track previous node

    // Loop to run until nodeptr = nullptr, meaning end of list, or if a match is found with node value and element value
    while (nodePtr && (nodePtr->value != element)) {
        previousNode = nodePtr; // Sets previous node to current node
        nodePtr = nodePtr->next; // Sets node pointer to next node
    }
    // Checks if nodeptr points to nullptr, if previous node points to nullptr, or othewise each pointer is pointing to a node
    if (!nodePtr)
        return; // Returns without deleting as a match for the element value to a node was not identified (went through entire linked list, so nodePtr points to nullptr)
    else if (!previousNode) {
        head = nodePtr->next; // Sets head to the node after nodeptr as the node to delete is the head (never entered while loop)
        delete nodePtr; // deletes nodeptr ... the old head node
    } 
    else {
        previousNode->next = nodePtr->next; // A match was found for a node deletion so previous node is linked to the node after nodeptr ...  nodeptr's link
        delete nodePtr; // nodeptr then gets deleted as its the node before it was linked to the node after it
    }
}

#endif