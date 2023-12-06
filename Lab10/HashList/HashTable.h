/* Kyle Tranfaglia
 * COSC320 - Lab10
 * 12/06/2023
 * Declaration and Implimentation of a Hash Table object using a list of list structure
*/
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class HashTable {
protected:
	int size = 0;
	// T *tab = nullptr;
	// int (*hf)(T&);
	vector<vector<T>> tab;
	T empty;
	T removed;

	// int probe(int pos);

public:
	HashTable(int size, T e, T r);
	virtual ~HashTable();
	void insert(T);
	void remove(T);
	bool find(T);
	void rehash(int sz);
	void print();
};

template<class T>
HashTable<T>::HashTable(int sz, T e, T r) {
	size = sz;
	empty = e;
	removed = r;

	for (int i = 0; i < size; i++) {
		tab[i][0] = empty;
	}
}

template<class T>
HashTable<T>::~HashTable() {
	// delete[] tab;
}

// template<class T>
// int HashTable<T>::probe(int pos) {
// 	// Linear probe.
// 	return (pos + 1) % size;
// }

template<class T>
void HashTable<T>::insert(T item) {
	// int pos = hf(item) % size;
	// int initpos = pos;

	// // If position is open probe loop is not done.
	// while (tab[pos] != empty && tab[pos] != removed) {
	// 	pos = probe(pos);
	// 	if (pos == initpos)
	// 		return;
	// }

	// tab[pos] = item;
	int pos = item % size;
	tab[pos].push_back(item);
}

template<class T>
void HashTable<T>::remove(T item) {
	// int pos = hf(item) % size;
	// int initpos = pos;

	// // If item is in first guess, probe loop is not done.
	// while (tab[pos] != item) {
	// 	pos = probe(pos);
	// 	if (pos == initpos || tab[pos] == empty)
	// 		return;
	// }
	// tab[pos] = removed;
	int outterPos = item % size;
	if (int innerPos = find(tab[outterPos].begin(), tab[outterPos].end(), item) != tab[outterPos].end()) {
		tab[outterPos].erase(innerPos);
	}
	
	
}

template<class T>
bool HashTable<T>::find(T item) {
	// int pos = hf(item) % size;
	// int initpos = pos;

	// // If item is in first guess, probe loop is not done.
	// while (tab[pos] != item) {
	// 	pos = probe(pos);
	// 	if (pos == initpos || tab[pos] == empty)
	// 		return false;
	// }

	// return true;
	int outterPos = item % size;
	return find(tab[outterPos].begin(), tab[outterPos].end(), item) != tab[outterPos].end();
}

template<class T>
void HashTable<T>::rehash(int sz) {
	HashTable<T> newtable(sz, hf, empty, removed);
	for (int i = 0; i < size; i++) {
		if (tab[i] != empty && tab[i] != removed) {
			T item = tab[i];
			newtable.insert(item);
		}
	}

	delete[] tab;
	tab = newtable.tab;
	size = newtable.size;
	newtable.tab = nullptr;
}

template<class T>
void HashTable<T>::print() {
	for (int i = 0; i < size; i++)
		cout << i << ": " << tab[i] << endl;
}

#endif /* HASHTABLE_H_ */