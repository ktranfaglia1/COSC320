/* Kyle Tranfaglia
 * COSC320 - Project02
 * Last updated 11/10/23
 * Templated Map Declaration and Implimentation - Uses RBTree as member variable to store the set of elements of type key and type value
*/
#ifndef Map_H
#define Map_H

#include <vector>
#include <stdexcept>
#include "RBTree.h"

template <class T, class L>
class Map  {
private:
    RBTree<T, L> tree;
public:
    Map(); // Constructor
    ~Map(); // Destructor

    Map(const Map<T, L> &); // Copy Constructor
    Map<T, L>* operator=(const Map<T, L> &); // Assignment operator

    // Functions
    bool isEmpty();
    bool find(T);
    int size();
    void print();

    // Mutators
    void insert(T, L);
    void erase(T);
    void clear();

    // Get and Set
    L get(T);
    void set(T, L);

    // Operator Overloads
    bool operator==(Map<T, L> &);
    bool operator!=(Map<T, L> &);

    // Friend outstream function
    template <class w, class z>
    friend ostream& operator<<(ostream &, Map<w, z> &);
};
// Constructor ... Has nothing to do ... RBTree Object takes care of all initialization of object that needs done
template <class T, class L>
Map<T, L>::Map() {
}
// Destructor ... Has nothing to do ... RBTree Object takes care of all deleteion that needs done for Map
template <class T, class L>
Map<T, L>::~Map() {
}
// Copy Constructor to create a Map object and copy the contents of the Map ... Utilizes RBTree assignment
template <class T, class L>
Map<T, L>::Map(const Map<T, L> &obj) {
    tree = obj.tree; // Uses tree assignment
}
// Assigment overload ... clears map then uses RBTree assignment
template <class T, class L>
Map<T, L>* Map<T, L>::operator=(const Map<T, L> &obj) {
    // Self assignment
    if (this == &obj) {
        return this;
    }
    clear(); // clears Map
    tree = obj.tree; // Uses tree assignment
    return this;
}
// Function to return true if the Map is empty
template <class T, class L>
bool Map<T, L>::isEmpty() {
   return tree.isEmpty();
}
// Function to find a key in the Map ... returns true if found
template <class T, class L>
bool Map<T, L>::find(T key) {
    return tree.find(key);
}
// Function to return the size of the Map
template <class T, class L>
int Map<T, L>::size() {
    return tree.size();
}
// Function to insert a key and value into the Map without duplication ... if the key already exists, update the value
template <class T, class L>
void Map<T, L>::insert(T key, L value) {
    tree.insert(key, value); // RBTree insert takes care of replacing value if key exists
}
// Function to remove a pair from the Map given the key
template <class T, class L>
void Map<T, L>::erase(T key) {
    tree.remove(key);
}
// Function to remove all elements in the Map
template <class T, class L>
void Map<T, L>::clear() {
    tree.clear();
}
// Map equality operator overload ... uses equality from RBTree
template <class T, class L>
bool Map<T, L>::operator==(Map<T, L> &obj) {
    return tree == obj.tree;
}
// inEquality overload to check Map equality
template <class T, class L>
bool Map<T, L>::operator!=(Map<T, L> &obj) {
    return !(tree == obj.tree);
}
// Get function to return the value associated with a key, or if the key is not found, it throws an error
template <class T, class L>
L Map<T, L>::get(T key) {
    // Searches for key value - if found, get the value, otherwise throw and error
    if (find(key)) {
        return tree.getVal(key);
    } 
    else {
        throw std::out_of_range("Key not found");
    }
}
// Map function to insert a new node of key and value ... if the key already exists replace the value for the pair with the new value 
template <class T, class L>
void Map<T, L>::set(T key, L value) {
    tree.insert(key, value); // RBTree insert takes care of replacing value if key exists
}
// STD out strm overload
template <class w, class z>
ostream& operator<<(ostream &strm, Map<w, z> &obj) {
    // Create vectors of key type and value type - parallel vectors
    vector<w> vec1;
    vector<z> vec2;
    obj.tree.inOrderTraversal(vec1, vec2); // Fill parallel vetcors with keys and values 
    // If the map contains pairs
    if (!vec1.empty()) {
        // Stream out all keys and values from the vectors with appropriate map formatting ... does not stream last pair 
        for (unsigned int i = 0; i < vec1.size() - 1; i++) {
            strm << "(" << vec1[i] << ", \"" << vec2[i] << "\"), ";   
        }
        strm << "(" << vec1[vec1.size() - 1] << ", \"" << vec2[vec1.size() - 1] << "\")"; // Streams final pair seperately to perserve formatting
    } 
    return strm;
}
#endif