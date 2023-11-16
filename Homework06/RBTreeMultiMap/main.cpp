/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.4
 * 11/03/2023
 * Program to test the functionality of the MultiMap class
*/
#include <iostream>
#include <string>
#include "MultiMap.h"

int main() {
    // Create map
    MultiMap<int, string> mapA;

    // Insert to map with set and insert
    mapA.set(1, "hahaha");
    mapA.set(2, "yipee");
    mapA.set(2, "yay");
    mapA.set(2, "wow");
    mapA.set(0, "Dont display");

    mapA.insert(4, "please work");
    mapA.insert(5, "no seg faults");
    mapA.insert(6, "manifest");
    mapA.insert(7, "please dont show up");
    mapA.insert(3, "more");
    mapA.insert(3, "another");
    mapA.insert(3, "last one");

    mapA.erase(7); // Test erase
    mapA.erase(0); // Test erase

    cout << mapA.size() << endl; // Test size function
    cout << mapA.count(3) << endl; // Test count function

    cout << mapA << endl; // Test outstream

    MultiMap<int, string> mapB = mapA; // Test copy constructor
   
    cout << mapB << endl; // Test outstream

    // Test empty fucntion
    if (mapB.isEmpty()) {
        cout << "The map is empty" << endl;
    }
    else {
        cout << "The map is not empty" << endl;
    }

    mapB.clear(); // Test clear
    cout << mapB << endl;

    // Test empty again (should be empty this time)
    if (mapB.isEmpty()) {
        cout << "The map is empty" << endl;
    }
    else {
        cout << "The map is not empty" << endl;
    }

    mapB = mapA; // Test assignment
    cout << mapB.size() << endl;
    cout << mapB << endl;

    // Test equality and inequality
    if (mapA == mapB) {
        cout << "Maps are equal!" << endl;
    }
    else if (mapA != mapB) {
        cout << "Maps are not equal!" << endl;
    }
    else {
        cout << "Something went wrong :(" << endl;
    }

    mapB.erase(1);
    mapB.erase(2);
    mapB.erase(5);

    // Test equality and inequality
    if (mapA == mapB) {
        cout << "Maps are equal!" << endl;
    }
    else if (mapA != mapB) {
        cout << "Maps are not equal!" << endl;
    }
    else {
        cout << "Something went wrong :(" << endl;
    }

    // Test find element
    if (mapB.find(6)) {
        cout << "element found!" << endl;
    }
    else {
        cout << "element not found!" << endl;
    }
    if (mapB.find(0)) {
        cout << "element found!" << endl;
    }
    else {
        cout << "element not found!" << endl;
    }

    cout << mapA << endl;
    cout << mapB << endl;

    // Try to get values and print ... otherwise catch error and print
    try {
        vector<string> vec1 = mapB.get(6);
         for (unsigned int i = 0; i < vec1.size(); i++) {
            cout << vec1[i];
            if (i + 1 < vec1.size()) {
                cout << ", ";
            }
        }
        cout << endl;
        vec1 = mapB.get(7);
        for (unsigned int i = 0; i < vec1.size(); i++) {
            cout << vec1[i];
            if (i + 1 < vec1.size()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}