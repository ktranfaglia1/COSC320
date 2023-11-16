/* Kyle Tranfaglia
 * COSC320 - Lab09
 * 11/17/2023
 * List of Lists declaration and implimentation - Code provided by Dr. Spickler
*/
#ifndef LISTOFLISTS_H_
#define LISTOFLISTS_H_

#include <vector>

using namespace std;

template<class T>
class ListOfLists {
protected:
	vector<vector<T>> list;

public:
	ListOfLists(int rows = 0, int cols = 0);
	virtual ~ListOfLists();

	int size();
	void addRow();
	void addRows(int n = 1, int m = 0);
	void push_back(vector<T>);
	vector<T>& operator[](const int&);
};

template<class T>
ListOfLists<T>::ListOfLists(int rows, int cols) {
	if (rows > 0) {
		for (int i = 0; i < rows; i++) {
			vector<T> thisrow(cols);
			list.push_back(thisrow);
		}
	}
}

template<class T>
ListOfLists<T>::~ListOfLists() {
}

template<class T>
int ListOfLists<T>::size() {
	return list.size();
}

template<class T>
void ListOfLists<T>::addRow() {
	vector<T> empty;
	list.push_back(empty);
}

template<class T>
void ListOfLists<T>::addRows(int n, int m) {
	if (n > 0)
		for (int i = 0; i < n; i++) {
			vector<T> empty(m);
			list.push_back(empty);
		}
}

template<class T>
void ListOfLists<T>::push_back(vector<T> r) {
	list.push_back(r);
}

template<class T>
vector<T>& ListOfLists<T>::operator[](const int &sub) {
	if (size() == 0) {
		vector<T> empty;
		return empty;
	}

	if (sub < 0)
		return list[0];
	else if (sub >= size())
		return list[size() - 1];
	else
		return list[sub];
}

#endif /* LISTOFLISTS_H_ */

