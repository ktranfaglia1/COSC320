/* Kyle Tranfaglia
*  COSC320 - Lab02
*  Last updated 09/08/23
*  This program creates a dynamic array and displays the counts for numerous sorting methods
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Sorts.h"

using namespace std;

int main () {
    srand(time(0)); // Random seed generator

    // Variables
    int size = 1, type = 1, slow = 1;

    cout << "Array Size: ";
    cin >> size;

    cout << "Array type (1 = Best, 2 = Worst, 3 = Average): ";
    cin >> type;

    cout << "Include slow sorts (1 = Yes, 2 = No): ";
    cin >> slow;

    // Dynamically allocates an array of size and a copy for repeated sorting
    int* array = new int[size];
    int* arrayCopy = new int[size];

    // Checks for 1, 2, 3 as inputs and populates the array for best, worst, or average cases accordingly
    if (type == 1) {
        for (int i = 0; i < size; i++) {
            array[i] = i; // Ascending order
        }
    }
    else if (type ==2) {
        for (int i = 0; i < size; i++) {
            array[i] = size - i - 1; // Descending order
        }
    }
    else if (type ==3) {
        for (int i = 0; i < size; i++) {
            array[i] = rand () % 1000001; // Random number 0 - 1000000 inclusively
        }
    }
    copy(array, array + size, arrayCopy); // Copies array for sorting

    // Prints only fast sorts or all sorts depending on user input : 1, 2
    if (slow == 1) {
        cout << "Bubble Sort Operation Count: " << bubble(arrayCopy, size) << endl;
        copy(array, array + size, arrayCopy);
        cout << "Selection Sort Operation Count: " << selection(arrayCopy, size) << endl;
        copy(array, array + size, arrayCopy);
        cout << "Insertion Sort Operation Count: " << insertion(arrayCopy, size) << endl;
        copy(array, array + size, arrayCopy);
        cout << "Merge Sort Operation Count: " << mergeSort(arrayCopy, size) << endl;
        copy(array, array + size, arrayCopy);
        cout << "Quick Sort Operation Count: " << quickSort(arrayCopy, size) << endl;
    }
    else if (slow == 2) {
        cout << "Merge Sort Operation Count: " << mergeSort(arrayCopy, size) << endl;
        copy(array, array + size, arrayCopy);
        cout << "Quick Sort Operation Count: " << quickSort(arrayCopy, size) << endl;
    }
    // Deallocates the memory
    delete [] array;
    delete [] arrayCopy;
}