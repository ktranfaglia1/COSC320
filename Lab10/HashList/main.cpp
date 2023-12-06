/* Kyle Tranfaglia
 * COSC320 - Lab10
 * 12/06/2023
 * Driver program to test the functionality of the HashTable structure that uses chaining for collision handling
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "HashTable.h"

using namespace std;

int hf(int &val) {
	return val;
}

int main() {
	srand(time(0));

	HashTable<int> table(10, hf);

	table.insert(437543);
	table.insert(3284);
	table.insert(234);
	table.insert(11111);
	table.insert(1103);

	table.print();
	cout << endl;
	cout << table.find(3284) << endl;
	cout << table.find(123456) << endl;
	cout << table.find(1103) << endl;

	table.remove(1103);
	cout << table.find(1103) << endl;
	cout << endl;

	cout << table.find(22) << endl;
	cout << endl;

	table.print();
	cout << endl;

	table.rehash(7);
	table.print();
	cout << endl;

	cout << table.find(3284) << endl;
	cout << table.find(123456) << endl;
	cout << table.find(1103) << endl;

	return 0;
}