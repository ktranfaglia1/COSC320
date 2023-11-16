/* Kyle Tranfaglia
*  COSC320 - Homework01 - Ex.2
*  Last updated 09/08/23
*  This program creates a dynamic array with random double values, sorts it, and times the process
*/
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Templated Prototypes
template<class T>
void insertion(T *A, int sz);
template<class T>
bool sorted( T *A, int sz);

int main() {
    srand(time(0)); // Sets seed generator

    // Variables
    int size = 0;

    cout << "Enter a size for the array: ";
    cin >> size;
    // Input validation
    while (size <= 0) {
        cout << "Invalid input! Enter a positive integer" << endl;
        cout << "Enter a size for the array: ";
        cin >> size;
    }

    double *array = new double[size]; // Creates dynamic double array of size
    // Fills array with integer values [0,1)
    for (int i = 0; i < size; i++) {
        *(array + i) = static_cast<double>(rand ()) / RAND_MAX;
    }
    // Code for timing, utilizes chrono library
    auto start = high_resolution_clock::now();

    insertion(array, size);  // Insertion sort call

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time to sort: " << duration.count() / 1000000.0 << " seconds" << endl;

    // Displays if array is sorted determined by the sorted bollean function
    if (sorted(array, size)) {
        cout << "Array is sorted" << endl;
    }
    else {
        cout << "Array is not sorted" << endl;
    }
    // Deallocates the memory and resets the pointer
    delete [] array;
    array = nullptr;
    
    return 0;
}
// Templated insertion sort
template<class T>
void insertion(T *A, int sz) {
    // Compares element with previous element, and if the element is smaller than the previous, the nested for loop iterates
    // until that element is no longer smaller such that it continues to build a growing sorted array from i = 0 to size - 1 
    for (int i = 0; i < sz; i++) {
        int j = 0;
        T value = *(A + i);
        for (j = i; j > 0 && *(A + j - 1) > value; j--) {
            *(A + j) = *(A + j -1);
        }
        *(A + j) = value;
    }
}
// Templated sort checker function that returns true if the array is sorted
template<class T>
bool sorted(T *A, int sz) {
    // Loop iterates for size - 1 of array and checks every if every element is smaller than the following, and returns false if ever not true
    for (int i = 0; i < sz - 1; i++) {
        if (*(A + i) > *(A + i + 1)) {
            return false;
        }
    }
    return true;
}