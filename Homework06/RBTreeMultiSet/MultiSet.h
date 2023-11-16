/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.2
 * 10/27/2023
 * Templated MultiSet Declaration and Implimentation - Uses RBTree as member variable to store the set of elements
*/
#ifndef MultiSet_H
#define MultiSet_H

#include "RBTree.h"

template <class T>
class MultiSet  {
private:
    RBTree<T> tree;
public:
    MultiSet(); // Constructor
    ~MultiSet(); // Destructor

    MultiSet(const MultiSet<T> &); // Copy Constructor
    MultiSet<T>* operator=(const MultiSet<T> &); // Assignment operator

    // Functions
    bool isEmpty();
    bool find(T);
    int size();
    void print();
    int count(T);

    // Mutators
    void insert(T);
    void erase(T);
    void clear();

    // Structure Conversions
    void toVector(vector<T> &);
    void toArray(T*, int);

    // Operator Overloads
    bool operator==(MultiSet<T> &);
    bool operator!=(MultiSet<T> &);
    bool operator<(MultiSet<T> &);
    bool operator>(MultiSet<T> &);
    bool operator<=(MultiSet<T> &);
    bool operator>=(MultiSet<T> &);
    MultiSet<T> operator+(MultiSet<T> &);
    MultiSet<T> operator*(MultiSet<T> &);
    MultiSet<T> operator-(MultiSet<T> &);

    template <class L>
    friend ostream& operator<<(ostream &, MultiSet<L> &);
};
// Constructor ... Has nothing to do ... RBTree Object takes care of all initialization of object that needs done
template <class T>
MultiSet<T>::MultiSet() {
    // Possibly initialize with empty set {0}?
}
// Destructor ... Has nothing to do ... RBTree Object takes care of all deleteion that needs done for Multiset
template <class T>
MultiSet<T>::~MultiSet() {
}
// Copy Constructor to create a Multiset object and copy the contents of the set
template <class T>
MultiSet<T>::MultiSet(const MultiSet<T> &obj) {
    tree = obj.tree; // Uses tree assignment
}
// Assigment overload
template <class T>
MultiSet<T>* MultiSet<T>::operator=(const MultiSet<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return this;
    }
    clear(); // clears Multiset
    tree = obj.tree; // Uses tree assignment
    return this;
}
// Function to return true if the Multiset is empty
template <class T>
bool MultiSet<T>::isEmpty() {
   return tree.isEmpty();
}
// Function to find a value T in the Multiset
template <class T>
bool MultiSet<T>::find(T value) {
    return tree.find(value);
}
// Function to get the size of the Multiset
template <class T>
int MultiSet<T>::size() {
    return tree.size();
}
// Function to insert a value into the Multiset with duplication
template <class T>
void MultiSet<T>::insert(T value) {
    tree.insert(value, true);
}
// Function to remove a value from the Multiset
template <class T>
void MultiSet<T>::erase(T value) {
    tree.remove(value);
}
// Function to remove all elements in the Multiset
template <class T>
void MultiSet<T>::clear() {
    tree.clear();
}
// Function to print the tree representation of the Multiset
template <class T>
void MultiSet<T>::print() {
    tree.PrintTree();
}
// Function to get the number of nodes of value T that are in the Multiset
template <class T>
int MultiSet<T>::count(T value) {
    return tree.count(value);
}
// Function to clear a vector and place the elements of the Multiset tree in the vector in ascending order
template <class T>
void MultiSet<T>::toVector(vector<T> &vec) {
    vec.clear();
    tree.inOrderTraversal(vec);
}
// Function to clear an array and place the elements of the Multiset tree in the array in ascending order
template <class T>
void MultiSet<T>::toArray(T *A, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = 0;
    }
    tree.inOrderTraversal(A);
}
// Multiset equality operator overload
template <class T>
bool MultiSet<T>::operator==(MultiSet<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return true;
    }
    // Size comparison
    if (size() != obj.size()) {
        return false;
    }
    // Loads vectors
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);

    return leftVec == rightVec; // Vector comparison
}
// inEquality overload to check Multiset equality
template <class T>
bool MultiSet<T>::operator!=(MultiSet<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return false;
    }
    // Size comparison
    if (size() != obj.size()) {
        return true;
    }
    // Loads vectors
    vector<T> leftVec, rightVec;
    toVector(leftVec);
    obj.toVector(rightVec);

    return !(leftVec == rightVec); // Vector comparison
}
// Strict subset operator overload
template <class T>
bool MultiSet<T>::operator<(MultiSet<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return false;
    }
    // Load vectors
    vector<T> vec;
    toVector(vec);
    // Loop to find values from A in B and compares quantity
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (tree.count(vec[i]) > obj.count(vec[i])) {
            return false; // An element of this multiset occurs more times in this multiset than in the other multiset.
        }
    }

    return tree.size() != obj.tree.size(); // Checks size to ensure not equal
}
// Uses < overload by switching A and B
template <class T>
bool MultiSet<T>::operator>(MultiSet<T> &obj) {
    return obj < *this;
}
// Subset overload
template <class T>
bool MultiSet<T>::operator<=(MultiSet<T> &obj) {
    // Self assignment
    if (this == &obj) {
        return false;
    }
    // Load vectors
    vector<T> vec;
    toVector(vec);
     // Loop to find values from A in B and compares quantity
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (tree.count(vec[i]) > obj.count(vec[i])) {
            return false; // An element of this multiset occurs more times in this multiset than in the other multiset.
        }
    }

    return true;
}
// Uses <= overload by switching A and B
template <class T>
bool MultiSet<T>::operator>=(MultiSet<T> &obj) {
    return obj <= *this;
}
// Multiset Union
template <class T>
MultiSet<T> MultiSet<T>::operator+(MultiSet<T> &obj) {
    MultiSet<T> result = *this; // Create a copy of the current multiset
    // Load vector
    vector<T> vec;
    obj.toVector(vec);
    // Gets the element count and checks if more elements need added to result for each index
    for (unsigned int i = 0; i < vec.size(); i++) {
        int count1 = result.tree.count(vec[i]);
        int count2 = obj.tree.count(vec[i]);

        if (count2 > count1) {
            // Loop to add additional occurrences to the result multiset
            for (int j = 0; j < (count2 - count1); j++) {
                result.insert(vec[i]);
            }
        }
    }
    return result;
}
// Multiset intersection
template <class T>
MultiSet<T> MultiSet<T>::operator*(MultiSet<T> &obj) {
    MultiSet<T> result;
    // Loads vectors
    vector<T> vec;
    toVector(vec);
    // Gets the element count and checks if more elements need added to result for each index
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (!result.find(vec[i])) {
            int count1 = tree.count(vec[i]);
            int count2 = obj.tree.count(vec[i]);
            int minCount = 0; 
            // Sets the minimum frequency
            if (count2 < count1) {
                minCount = count2;
            }
            else {
                minCount = count1;
            }

            // Add the element to the result with the minimum frequency
            for (int j = 0; j < minCount; j++) {
                result.insert(vec[i]);
            }
        }
    }

    return result;
}
// Multiset difference
template <class T>
MultiSet<T> MultiSet<T>::operator-(MultiSet<T> &obj) {
    MultiSet<T> result = *this; // Create a copy of the current multiset
    // Load vectors
    vector<T> vec;
    obj.toVector(vec);
    // Gets the element count and checks if more elements need removed from result for each index
    for (unsigned int i = 0; i < vec.size(); i++) {
        int count1 = result.tree.count(vec[i]);
        int count2 = obj.tree.count(vec[i]);
        // Gets maximum of the counts
        if (count1 > count2) {
            // Remove the additional occurrences in the result multiset
            for (int j = 0; j < (count1 - count2); j++) {
                result.erase(vec[i]);
            }
        } // Will removing remaining elements if difference wipes them out
        else if (count1 <= count2) {
            result.erase(vec[i]);
        }
    }

    return result;
}
// STD out strm overload
template <class L>
ostream& operator<<(ostream &strm, MultiSet<L> &obj) {
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