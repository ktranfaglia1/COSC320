/* Kyle Tranfaglia
*  COSC320 - Homework01 - Ex.6
*  Last updated 09/08/23
*  Templated Thing1 and ListNode Declaration and Implimentation
*/
#ifndef Thing1_H
#define Thing1_H

#include <iostream>

using namespace std;

template<class T>
class ListNode {
    public:
        T value;
        ListNode *next;   
        ListNode *prev; 

        ListNode() { next = prev = nullptr; } // Inline ListNode Constructor
};
template<class T>
class Thing1 {
    protected:
        ListNode<T> *head;
        ListNode<T> *tail;
    public:
        Thing1(); // Constructor
        ~Thing1(); // Destructor

        // Add and remove functions
        void pushback(const T &);
        T popback();
        void pushfront(const T &);
        T popfront();
        // Size and clear functions
        int size();
        void clear();
        // Print functions
        void printforward(bool status = false);
        void printbackward(bool status = false);
        // Find functions
        bool find(const T &);
        int findpos(const T &);
        // Empty check and get/set functions
        bool isempty();
        T getValue(const int &);
        void setValue(const int &, const T &);

        template<class L>
        friend ostream &operator << (ostream &, const Thing1<L> &); // Friend ostream operator overload with individual template
};
// Constructor
template<class T>
Thing1<T>::Thing1() {
    head = tail = nullptr;
    head = new ListNode<T>;
    tail  = new ListNode<T>;
    // This is done since head and tail do not ever hold values as nodes so their direct connectivity identifies an empty list
    head->next = tail; 
    tail->prev = head;
}
// Destructor
template<class T>
Thing1<T>::~Thing1(){
    ListNode<T> *nodeptr = head; // To traverse the list starting at header node
    ListNode<T> *nextNode = nullptr; // To point to the next node
    
    // While nodeptr is not at the end of the list...
    while (nodeptr) {
        nextNode = nodeptr->next; // Save a pointer to the next node.
		delete nodeptr; // Delete the current node.
		nodeptr = nextNode; // Position nodePtr at the next node.
    }
}
// Function to add a node of incoming value to the back of the doubly linked list
template<class T>
void Thing1<T>::pushback(const T &element) {
    // Creates new node with value from paramter
    ListNode<T> *newNode = new ListNode<T>;
    newNode->value = element;

    // Adjusts the connection pointers with repect to tailer and the new node
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
}
// Function to remove the last node in the doubly linked list ... first before tail
template<class T>
T Thing1<T>::popback() {
    T removed = T(); // Holds default value
    // Checks if there is elments to remove, if not, prints list is empty, otherwise removes back node
    if (size() != 0) {
        // Creates pointer and sets it to node to remove, then adjust the prev and next pointers to point to the following node or previous node as necessary, then deletes the node
        ListNode<T> *nodeptr = tail->prev;
        tail->prev = nodeptr->prev;
        nodeptr->prev->next = tail;
        removed = nodeptr->value;
        delete nodeptr;
    }
    return removed;
}
// Function to add a node of incoming value to the front of the doubly linked list
template<class T>
void Thing1<T>::pushfront(const T &element) {
    // Creates new node with value from paramter
    ListNode<T> *newNode = new ListNode<T>;
    newNode->value = element;

    // Adjusts the connection pointers with repect to header and the new node
    newNode->prev = head;
    newNode->next = head->next;
    head->next->prev = newNode;
    head->next = newNode;
}
// Function to remove the first node in the doubly linked list ... first after head
template<class T>
T Thing1<T>::popfront() {
    T removed = T();
    if (size() != 0) {
        // Creates pointer and sets it to node to remove, then adjust the prev and next pointers to point to the following node or previous node as necessary, then deletes the node
        ListNode<T> *nodeptr = head->next;
        head->next = nodeptr->next;
        nodeptr->next->prev = head;
        removed = nodeptr->value;
        delete nodeptr;
    }
    return removed;
}
// Function to count and return the number of nodes in the doubly linked list
template<class T>
int Thing1<T>::size() {
    int count = 0;
    ListNode<T> *nodePtr = head->next; // Traversing varaiable to go through the list, pointer set to list header of object
    // Loops as long as nodePtr points to something that is not the tail 
    while (nodePtr != tail) {
        count++; // Increments element count for each iteration
        nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
    }
    return count;
}
// Function that acts like a destructor such that it clears a list by deleting all nodes, however, it does not delete the head and tail
template<class T>
void Thing1<T>::clear() {
    ListNode<T> *nodeptr = head->next; // To traverse the list starting at header node
    ListNode<T> *nextNode = nullptr; // To point to the next node
    
    // While nodeptr is not at the end of the list...
    while (nodeptr != tail) {
        nextNode = nodeptr->next; // Save a pointer to the next node.
		delete nodeptr; // Delete the current node.
		nodeptr = nextNode; // Position nodePtr at the next node.
    }
    // Connects head and tail to indicate empty list
    head->next = tail;
    tail->prev = head; 
}
// Function to print the list in a forward order
template<class T>
void Thing1<T>::printforward(bool status) {
    ListNode<T> *nodePtr = head->next; // Traversing varaiable to go through the list, pointer set to list header of object
    // inner Loops as long as nodePtr points to something that is not the tail. Incoming status (defaulted to false) determines formatting
    if (status) {
         while (nodePtr != tail) {
            cout << nodePtr->value << endl; // Prints value of node with a space at end
            nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
        }
    }
    else {
        while (nodePtr != tail) {
            cout << nodePtr->value << " "; // Prints value of node with a space at end
            nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
        }
        cout << endl;
    }
}
// Function to print the list in a backward order
template<class T>
void Thing1<T>::printbackward(bool status) {
    ListNode<T> *nodePtr = tail->prev; // Traversing varaiable to go through the list, pointer set to list header of object
    // inner Loops as long as nodePtr points to something that is not the tail. Incoming status (defaulted to false) determines formatting
    if (status) {
         while (nodePtr != head) {
            cout << nodePtr->value << endl; // Prints value of node with a space at end
            nodePtr = nodePtr->prev;  // Moves tranversing pointer to next node 
        }
    }
    else {
        while (nodePtr != head) {
            cout << nodePtr->value << " "; // Prints value of node with a space at end
            nodePtr = nodePtr->prev;  // Moves tranversing pointer to next node 
        }
        cout << endl;
    }
}
// Function to return true if it finds a node with the value passed as a parameter
template<class T>
bool Thing1<T>::find(const T &val) {
    bool status = false; // Defaults bool return to false
    ListNode<T> *nodeptr = head->next; // creates traversing pointer

    // Loops as long as nodePtr points to something that is not the tail
    while (nodeptr != tail) {
        // Checks if node value and parameter value are equal, if so, return status set to true
        if (nodeptr->value == val) {
            status = true;
        }
        nodeptr = nodeptr->next; // Moves pointer to next node
    }
    return status;
}
// Function to return position of first node containing the incoming parameter value and returns -1 if not found
template<class T>
int Thing1<T>::findpos(const T &val) {
    int count = 0; //counter to return the position if found
    ListNode<T> *nodeptr = head->next; // creates traversing pointer

    // Loops as long as nodePtr points to something that is not the tailer
    while (nodeptr != tail) {
        // Checks if node value and parameter value are equal, if so, return status set to true
        if (nodeptr->value == val) {
            return count;
        }
        count++;
        nodeptr = nodeptr->next; // Moves pointer to next node
    }
    return -1;
}
// Function to determine if the list is empty ...  do head and tail directly connect?
template<class T>
bool Thing1<T>::isempty() {
    return (head->next == tail);
}
// Function to return the value of the node at a given position and returns the default value if position is not valid
template<class T>
T Thing1<T>::getValue(const int &pos) {
    T val = T();
    // Checks if pos is valid and continues if true
    if (size() > pos && pos >= 0) {
        int count = 0; // Counter to navigate to position
        ListNode<T> *nodeptr = head->next; // nodeptr starting after head to traverse all nodes with values
        // Loop to traverse entire array until tail
        while (nodeptr != tail) {
            // Checks if position has been reached
            if (count == pos) {
                val = nodeptr->value; // Captures value at position
            }
            count++;
            nodeptr = nodeptr->next;
        }
    } 
    return val;
}
// Function to set the value of a node given position and the value
template<class T>
void Thing1<T>::setValue(const int &pos, const T &element) {
    // Checks if the position is valid
    if (size() <= pos || pos < 0) {
        cout << "Invalid position. 0 =< position <= size. The value was not set" << endl;
    }
    // Else runs if position is valid
    else {
        int count = 0;
        ListNode<T> *nodeptr = head->next;
        // Loop to traverse entire array until tail
        while (nodeptr != tail) {
            if (count == pos) {
            nodeptr->value = element; // Sets value to element
            }
            count++;
            nodeptr = nodeptr->next;
        }
    }
}
// Ostream operator overload to enable functionality of cout with the object
template<class T>
ostream &operator << (ostream &strm, const Thing1<T> &obj) {
    ListNode<T> *nodePtr = obj.head->next; // Traversing varaiable to go through the list, pointer set to list header of object
    // Loops as long as nodePtr points to something that is not the tail
    while (nodePtr != obj.tail) {
        strm << nodePtr->value << " "; // Prints value of node with a space at end
        nodePtr = nodePtr->next;  // Moves tranversing pointer to next node 
    }
    strm << endl;

	return strm;
}
#endif