/* Kyle Tranfaglia
*  COSC320 - Homework01 - Ex.6
*  Last updated 09/08/23
*  Templated Thing2 Declaration and Implimentation
*/
#ifndef Thing2_H
#define Thing2_H

#include <iostream>

#include "Thing1.h"

using namespace std;

template<class T>
class Thing2 : public Thing1<T> {
    private:
        ListNode<T>* iter;
    public:
        Thing2(); // Constructor
        ~Thing2(); // Destructor

        // Reset iterator functions
        void resetIteratorToFront();
        void resetIteratorToBack();
        // Operator overloads
        void operator += (const int &); 
        void operator -= (const int &); 
        void operator ++ ();					
        void operator ++ (int);				
        void operator -- ();					
        void operator -- (int);
        // Get, insert, delete
        T get();
        void insertval(const T &);
        void deleteval();
};
// Constructor
template<class T>
Thing2<T>::Thing2() {
    iter = nullptr;
}
// Destructor (default)
template<class T>
Thing2<T>::~Thing2() {
}
// Function to set iterator to front by setting it to node after head
template<class T>
void Thing2<T>::resetIteratorToFront() {
    // If node is empty, iterator points to head, otherwise it points to first node of value
    if (Thing1<T>::head->next != Thing1<T>::tail) {
        iter = Thing1<T>::head->next;
    }
    else {
        iter = Thing1<T>::head;
    }
}
// Function to set iterator to back by setting it to node before tail
template<class T>
void Thing2<T>::resetIteratorToBack() {
     // If node is empty, iterator points to tail, otherwise it points to last node of value
     if (Thing1<T>::head->next != Thing1<T>::tail) {
        iter = Thing1<T>::tail->prev;
    }
    else {
        iter = Thing1<T>::tail;
    }
}
// += operator overload
template<class T>
void Thing2<T>::operator += (const int &shiftAmount) {
    int count = 0;
    // Shifts towards the tail ShiftAmount times or until node before tail is reached
    while (count != shiftAmount && iter->next != Thing1<T>::tail) {
        iter = iter->next;
        count++;
    }
}
// -= operator overload
template<class T>
void Thing2<T>::operator -= (const int &shiftAmount) {
    int count = 0;
    // Shifts towards the head ShiftAmount times or until node after head is reached
    while (count != shiftAmount && iter->prev != Thing1<T>::head) {
        iter = iter->prev;
        count++;
    }
}
// Prefix ++ operator overload
template<class T>
void Thing2<T>::operator ++ () {
    // Increments one time or does not increment if there is no next node (or next node is tail)
    if (iter->next && iter != Thing1<T>::tail) {
        iter = iter->next;
    }
}
// Postfix ++ operator overload
template<class T>			
void Thing2<T>::operator ++ (int) {
    // Increments one time or does not increment if there is no next node (or next node is tail)
     if (iter->next && iter != Thing1<T>::tail) {
        iter = iter->next;
    }
}
// Prefix -- operator overload
template<class T>			
void Thing2<T>::operator -- () {
    // Decrements one time or does not decrement if there is no prev node (or prev node is head)
    if (iter->prev && iter != Thing1<T>::head) {
        iter = iter->prev;
    }
}
// Prefix -- operator overload	
template<class T>			
void Thing2<T>::operator -- (int) {
    // Decrements one time or does not decrement if there is no prev node (or prev node is head)
    if (iter->prev && iter != Thing1<T>::head) {
        iter = iter->prev;
    }
}
// Function to return the value that the iterator is pointing at
template<class T>
T Thing2<T>::get() {
    T val = T();
    // Captures value at iterator or does not if there is no node holding a value at iterator
    if (iter && iter != Thing1<T>::head && iter != Thing1<T>::tail) {
        val = iter->value;
    }
    return val;
}
// Function to create a node of given value and insert it in the last after the current position of iterator
template<class T>
void Thing2<T>::insertval(const T &element) {
     // Creates a node of value after iterator or does not if there is no node holding a value at iterator (iterator is null)
    if (iter && iter != Thing1<T>::head && iter != Thing1<T>::tail) {
        ListNode<T> *newNode = new ListNode<T>; // Creates node
        newNode->value = element;
        newNode->next = iter->next; 
        iter->next->prev = newNode;
        iter->next = newNode;
        newNode->prev = iter;
    }
}
// Function to remove the node currently pointed at by the iterator
template<class T>
void Thing2<T>::deleteval() {
     // Delates node at iterator or does not if there is no node holding a value at iterator (iterator is null)
    if (iter && iter != Thing1<T>::head && iter != Thing1<T>::tail) {
        ListNode<T> *nodeptr = iter;

        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        iter = iter->next;

        delete nodeptr;
    }
}

#endif