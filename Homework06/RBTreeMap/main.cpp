/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.3
 * 11/03/2023
 * Program to test the functionality of the Map class
*/
#include <iostream>
#include <string>
#include "Map.h"

int main() {
    // Create map
    Map<int, string> mapA;

    // Insert to map with set and insert
    mapA.set(1, "hahaha");
    mapA.set(2, "yipee");
    mapA.set(3, "hurray");

    mapA.insert(4, "please work");
    mapA.insert(5, "no seg faults");
    mapA.insert(6, "manifest");
    mapA.insert(7, "please dont show up");
    mapA.insert(3, "overwrite");

    mapA.erase(7); // Test erase

    cout << mapA.size() << endl; // Test size function

    cout << mapA << endl;

    Map<int, string> mapB = mapA; // Test copy constructor

    cout << mapB << endl;
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

    mapB = mapA; // test assignment
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

    if (mapB.find(6)) {
        cout << "element found!" << endl;
    }
    else {
        cout << "element not found!" << endl;
    }
    // Try to get values and print ... otherwise catch error and print
    try {
        cout << mapB.get(6) << endl;
        cout << mapB.get(7) << endl; // Shgould throw an error
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}