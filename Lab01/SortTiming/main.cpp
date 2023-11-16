/* Kyle Tranfaglia
*  COSC320 - Lab01 - Ex.1
*  Last updated 08/30/23
*  This program creates a dynamic array with random values, sorts it, and times the process
*/
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Prototype
template<class T>
void insertion(T *A, int sz);
template<class T>
bool sorted( T *A, int sz);

int main() {
    srand(time(0));

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

    int *array = new int[size];
    // Fills array with integer values between -1000 and 1000 inclusively
    for (int i = 0; i < size; i++) {
        *(array + i) = (rand () % 2001) - 1000;
        // cout << array[i] << endl;
    }

    auto start = high_resolution_clock::now();

    insertion(array, size);

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
    return 0;
}
template<class T>
void insertion(T *A, int sz) {
    for (int i = 0; i < sz; i++) {
        int j = 0;
        T value = *(A + i);
        for (j = i; j > 0 && *(A + j - 1) > value; j--) {
            *(A + j) = *(A + j -1);
        }
        *(A + j) = value;
    }
}
template<class T>
bool sorted(T *A, int sz) {
    for (int i = 0; i < sz - 1; i++) {
        if (*(A + i) > *(A + i + 1)) {
            return false;
        }
    }
    return true;
}