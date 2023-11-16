/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.1
 * 10/27/2023
 * Templated Set Declaration and Implimentation - Uses RBTree as member variable to store the set of elements
*/
#ifndef SET_H_
#define SET_H_

#include "RBTree.h"

template <class T>
class Set  {
private:
    RBTree<T> tree;
public:
    Set(); // Constructor
    ~Set(); // Destructor

    Set(const Set<T> &); // Copy Constructor
    Set<T>* operator=(const Set<T> &); // Assignment operator

    // Functions
    bool isEmpty();
    bool find(T);
    int size();
    void print();

    // Mutators
    void insert(T);
    void erase(T);
    void clear();

    // Structure Conversions
    void toVector(vector<T> &);
    void toArray(T*, int);

    // Operator Overloads
    bool operator==(Set<T> &);
    bool operator!=(Set<T> &);
    bool operator<(Set<T> &);
    bool operator>(Set<T> &);
    bool operator<=(Set<T> &);
    bool operator>=(Set<T> &);
    Set<T> operator+(Set<T> &);
    Set<T> operator*(Set<T> &);
    Set<T> operator-(Set<T> &);

    template <class L>
    friend ostream& operator<<(ostream &, Set<L> &);
};
// Constructor ... Has nothing to do ... RBTree Object takes care of all initialization of object that needs done
template <class T>
Set<T>::Set() {
    // Possibly initialize with empty set {0}?
}
// Destructor ... Has nothing to do ... RBTree Object takes care of all deleteion that needs done for set
template <class T>
Set<T>::~Set() {
}
// Copy Constructor to create a set object and copy the contents of the set
template <class T>
Set<T>::Set(const Set<T> &obj) {
    tree = obj.tree; // Uses RBtree assignment
}
// Assignment Operator
template <class T>
Set<T>* Set<T>::operator=(const Set<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return this;
    }
    clear(); // Clears set ... redundant but just incase
    tree = obj.tree; // Uses RBtree assignment
    return this;
}
// Function to return true if the set is empty
template <class T>
bool Set<T>::isEmpty() {
   return tree.isEmpty();
}
// Function to find a value T in the set
template <class T>
bool Set<T>::find(T value) {
    return tree.find(value);
}
// Function to get the size of the set
template <class T>
int Set<T>::size() {
    return tree.size();
}
// Function to insert a value into the set without duplication
template <class T>
void Set<T>::insert(T value) {
    tree.insert(value, false);
}
// Function to remove a value from the set
template <class T>
void Set<T>::erase(T value) {
    tree.remove(value);
}
// Function to remove all elements in the set
template <class T>
void Set<T>::clear() {
    tree.clear();
}
// Function to print the tree representation of the set
template <class T>
void Set<T>::print() {
    tree.PrintTree();
}
// Function to clear a vector and place the elements of the set tree in the vector in ascending order
template <class T>
void Set<T>::toVector(vector<T> &vec) {
    vec.clear();
    tree.inOrderTraversal(vec);
}
//  Function to clear an array and place the elements of the set tree in the array in ascending order
template <class T>
void Set<T>::toArray(T *A, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = 0;
    }
    tree.inOrderTraversal(A);
}
// Equality overload to check set equality
template <class T>
bool Set<T>::operator==(Set<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return true;
    }
    // Checks sizes
    if (size() != obj.size()) {
        return false;
    }
    // Loads to vector
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);

    return leftVec == rightVec; // vector comparison
}
// inEquality overload to check set equality
template <class T>
bool Set<T>::operator!=(Set<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return false;
    }
    // Checks sizes
    if (size() != obj.size()) {
        return true;
    }
    // Loads to vector
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);

    return !(leftVec == rightVec); // vector comparison
}
// Strict subset operator overload
template <class T>
bool Set<T>::operator<(Set<T> &obj) {
    // self equality
    if (this == &obj) {
        return false;
    }
    // Loads vectors
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);
    // Loop to find values from A in B
    for (unsigned int i = 0; i < leftVec.size(); i++) {
        if (!obj.find(leftVec[i])) {
            return false;
        }
    }

    return leftVec != rightVec; // Check that vectors not equal
}
// Uses < overload by switching A and B
template <class T>
bool Set<T>::operator>(Set<T> &obj) {
    return obj < *this;
}
// Subset overload
template <class T>
bool Set<T>::operator<=(Set<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return false;
    }
    // Loads vector
    vector<T> leftVec;
    toVector(leftVec);
    // Loop to find values from A in B
    for (unsigned int i = 0; i < leftVec.size(); i++) {
        if (!obj.find(leftVec[i])) {
            return false;
        }
    }

    return true;
}
// Uses <= overload by switching A and B
template <class T>
bool Set<T>::operator>=(Set<T> &obj) {
    return obj <= *this;
}
// Set union
template <class T>
Set<T> Set<T>::operator+(Set<T> &obj) {
    Set<T> result; // Create a new set to store the union
    // Loads vector
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);

    // Loop to insert elements from the current set
    for (unsigned int i = 0; i < leftVec.size(); i++) {
        result.insert(leftVec[i]);
    }

    // Loop to insert elements from the other set
    for (unsigned int i = 0; i < rightVec.size(); i++) {
        result.insert(rightVec[i]);
    }

    return result;
}
// Set intersection
template <class T>
Set<T> Set<T>::operator*(Set<T> &obj) {
    Set<T> result; // Create a new set to store the intersection
    // Load vector
    vector<T> leftVec;
    toVector(leftVec);

    // Loop to insert elements in set A if found in set B
    for (unsigned int i = 0; i < leftVec.size(); i++) {
        if (obj.find(leftVec[i])) {
            result.insert(leftVec[i]);
        }
    }

    return result;
}
// Set difference
template <class T>
Set<T> Set<T>::operator-(Set<T> &obj) {
    Set<T> result; // Create a new set to store the difference
    // Load vectors
    vector<T> leftVec;
    toVector(leftVec);

    // Loop to insert elements in set A if not found in set B
    for (unsigned int i = 0; i < leftVec.size(); i++) {
        if (!obj.find(leftVec[i])) {
            result.insert(leftVec[i]);
        }
    }
    return result;

}
// STD out strm overload
template <class L>
ostream& operator<<(ostream &strm, Set<L> &obj) {
    // Loads vector
    vector<L> vec;
    obj.toVector(vec);
    strm << "{";
    // Checks if empty for empty set and to avoid segmentation fault ... loops through vector to print set in order
    if (vec.empty()) {
        strm << "}";
    }
    else {
        for (unsigned int i = 0; i < vec.size() - 1; i++) {
            strm << vec[i] << ", ";
        }
        strm << vec[vec.size() - 1] << "}";
    }
    return strm;
}

#endif