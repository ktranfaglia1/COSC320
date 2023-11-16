/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.4
 * 11/03/2023
 * Templated MultiMap Declaration and Implimentation - Uses RBTree as member variable to store the set of elements of type key and type value
*/
#ifndef MultiMap_H
#define MultiMap_H

#include <vector>
#include <stdexcept>
#include "RBTree.h"

template <class T, class L>
class MultiMap  {
private:
    RBTree<T, L> tree;
public:
    MultiMap(); // Constructor
    ~MultiMap(); // Destructor

    MultiMap(const MultiMap<T, L> &); // Copy Constructor
    MultiMap<T, L>* operator=(const MultiMap<T, L> &); // Assignment operator

    // Functions
    bool isEmpty();
    bool find(T);
    int size();
    void print();
    int count(T);

    // Mutators
    void insert(T, L);
    void erase(T);
    void clear();

    // Get and Set
    vector<L> get(T);
    void set(T, L);

    // Operator Overloads
    bool operator==(MultiMap<T, L> &);
    bool operator!=(MultiMap<T, L> &);

    // Friend outstream function
    template <class w, class z>
    friend ostream& operator<<(ostream &, MultiMap<w, z> &);
};
// Constructor ... Has nothing to do ... RBTree Object takes care of all initialization of object that needs done
template <class T, class L>
MultiMap<T, L>::MultiMap() {
}
// Destructor ... Has nothing to do ... RBTree Object takes care of all deleteion that needs done for MultiMap
template <class T, class L>
MultiMap<T, L>::~MultiMap() {
}
// Copy Constructor to create a MultiMap object and copy the contents of the MultiMap ... Utilizes RBTree assignment
template <class T, class L>
MultiMap<T, L>::MultiMap(const MultiMap<T, L> &obj) {
    tree = obj.tree; // Uses tree assignment
}
// Assigment overload ... clears MultiMap then uses RBTree assignment
template <class T, class L>
MultiMap<T, L>* MultiMap<T, L>::operator=(const MultiMap<T, L> &obj) {
    // Self assignment
    if (this == &obj) {
        return this;
    }
    clear(); // clears MultiMap
    tree = obj.tree; // Uses tree assignment
    return this;
}
// Function to return true if the MultiMap is empty
template <class T, class L>
bool MultiMap<T, L>::isEmpty() {
   return tree.isEmpty();
}
// Function to find a key in the MultiMap ... returns true if found
template <class T, class L>
bool MultiMap<T, L>::find(T key) {
    return tree.find(key);
}
// Function to return the size of the MultiMap
template <class T, class L>
int MultiMap<T, L>::size() {
    return tree.size();
}
// Function to insert a key and value into the MultiMap ... if the key already exists, append the value
template <class T, class L>
void MultiMap<T, L>::insert(T key, L value) {
    tree.insert(key, value); // RBTree insert takes care of replacing value if key exists
}
// Function to remove a pair from the MultiMap given the key
template <class T, class L>
void MultiMap<T, L>::erase(T key) {
    tree.remove(key);
}
// Function to remove all elements in the MultiMap
template <class T, class L>
void MultiMap<T, L>::clear() {
    tree.clear();
}
// Map equality operator overload ... uses equality from RBTree
template <class T, class L>
bool MultiMap<T, L>::operator==(MultiMap<T, L> &obj) {
    return tree == obj.tree;
}
// inEquality overload to check MultiMap equality
template <class T, class L>
bool MultiMap<T, L>::operator!=(MultiMap<T, L> &obj) {
    return !(tree == obj.tree);
}
// Get function to return the vector of values associated with a key, or if the key is not found, it throws an error
template <class T, class L>
vector<L> MultiMap<T, L>::get(T key) {
    // Searches for key value - if found, get the value, otherwise throw and error
    if (find(key)) {
        return tree.getVal(key);
    } 
    else {
        throw std::out_of_range("Key not found");
    }
}
// MultiMap function to insert a new node of key and value ... if the key already exists replace append the value to the value tree
template <class T, class L>
void MultiMap<T, L>::set(T key, L value) {
    tree.insert(key, value); // RBTree insert takes care of replacing value if key exists
}
// Function to count the number of values stored with an associated key by calling a function in the RBTree
template <class T, class L>
int MultiMap<T, L>::count(T key) {
    return tree.countValues(key);
}
// STD out strm overload
template <class w, class z>
ostream& operator<<(ostream &strm, MultiMap<w, z> &obj) {
    // Create vectors of key type and value type
    vector<w> vec;
    vector<z> tempVec;
    obj.tree.inOrderTraversal(vec); // Fill key vector
    strm << "{ ";
    // If the Multimap contains any elements
    if (!vec.empty()) {
        // Stream out all keys and values from the vectors with appropriate Multimap formatting
        for (unsigned int i = 0; i < vec.size(); i++) {
            strm << "(" << vec[i] << ", "; // Prints key
            tempVec = obj.get(vec[i]); // Gets vector of values at the associated key
            // Loop to stream out all elements in the vector containing values
            for (int j = 0; j < obj.count(vec[i]); j++) {
                strm << tempVec[j]; // Prints the value
                // If no more values follow, contain in parenthesis, otherwise, seperate values with a forward slash
                if (j + 1 >= obj.count(vec[i])) {
                    strm << ")";
                }
                else {
                    strm << " / ";
                }
            } 
            // If there are more keys to be listed, add a comma
            if (i + 1 < vec.size()) {
                strm << ", ";
            }
        }
    } 
    strm << " }";
    return strm;
}

#endif