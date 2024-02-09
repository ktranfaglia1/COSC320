/* Kyle Tranfaglia
 * COSC320 - Lab10
 * 12/06/2023
 * Declaration and Implimentation of a Hash Table object using a list of list structure and chaining for collision handling
*/
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <algorithm>
#include <iostream>
#include <vector>

#include "ListOfLists.h"

using namespace std;

template<class T>
class HashTable {
protected:
	int (*hf)(T&);
	ListOfLists<T> tab;
public:
	HashTable(int, int (*)(T&));
	virtual ~HashTable();
	void insert(T);
	void remove(T);
	bool find(T);
	void rehash(int);
	void print();
};
// Constructor to set hash function and create initialize table
template<class T>
HashTable<T>::HashTable(int size, int (*hashfct)(T&)) {
	hf = hashfct;
	tab.addRows(size);
}
// Destructor ... nothing needs done, ListOfLists structure handles memory deallocation
template<class T>
HashTable<T>::~HashTable() {
}
// Insert fun ction to insert an item into the hash table using the hash function to update the inner list
template<class T>
void HashTable<T>::insert(T item) {
	int pos = hf(item) % tab.size(); // Get position to insert item using hash function
	tab[pos].push_back(item); // Add item to inner list
}
// Remove function to remove an item from the hash table using the hash function to update the inner list
template<class T>
void HashTable<T>::remove(T item) {
	int outterPos = hf(item) % tab.size(); // Get position to insert item using hash function
	// Check that the item exists in the inner list, if so remove it, otherwise do nothing
	if (std::find(tab[outterPos].begin(), tab[outterPos].end(), item) != tab[outterPos].end()) {
		tab[outterPos].erase(std::find(tab[outterPos].begin(), tab[outterPos].end(), item));
	}
}
// Find function that uses the algorithm find to return if an item exists in the hash table
template<class T>
bool HashTable<T>::find(T item) {
	int outterPos = hf(item) % tab.size(); // Get position to insert item using hash function
	return (std::find(tab[outterPos].begin(), tab[outterPos].end(), item) != tab[outterPos].end()); // Return boolean result of algorithm find
}
// Rehash function to rehash the hash table such that a new hash table is created with an updated size and set to the current hash table
template<class T>
void HashTable<T>::rehash(int size) {
	HashTable<T> newtable(size, hf); // Create new hash table with updated size (same hash function)
	// Loop through entire list of list structure to get each element in the inner list and insert it into the new hash table
	for (int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < tab[i].size(); j++) {
			T item = tab[i][j]; // Get item from hash table
			newtable.insert(item); // Add item to new hash tabale
		}
	}
	tab = newtable.tab; // Set hash table to new hash table
}
// Print function to display the contents of the hash table
template<class T>
void HashTable<T>::print() {
	// Loop through entire list of list structure to display the contents of the inner list all lists (outer list)
	for (int i = 0; i < tab.size(); i++) {
		cout << i << ": ";
		for (unsigned int j = 0; j < tab[i].size(); j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
}
#endif /* HASHTABLE_H_ */