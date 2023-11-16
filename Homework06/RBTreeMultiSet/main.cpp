/* Kyle Tranfaglia
 * COSC320 - Homework06 - Ex.2
 * 10/27/2023
 * Program to test the functionality of the MultiSet class
*/
#include <iostream>
#include "MultiSet.h"

int main() {
    // Create two sets and populate them
    MultiSet<int> setA, setB;
    setA.insert(1);
    setA.insert(2);
    setA.insert(3);
    setA.insert(6);
    setA.insert(6);
    setA.insert(6);
    setA.insert(99);

    setB.insert(1);
    setB.insert(1);
    setB.insert(4);
    setB.insert(5);
    setB.insert(6);
    setB.insert(6);
    setB.insert(99);

    setA.erase(99);
    setB.erase(99);

    // Test basic set functions
    cout << "Set A: " << setA << endl;
    cout << "Set B: " << setB << endl;
    cout << "Number of 6s in Set A: " << setA.count(6) << endl;
    
    cout << "Is set A empty? ";
    if (setA.isEmpty()) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Set A size: " << setA.size() << endl;
    
    // Test union and intersection
    MultiSet<int> unionSet = setA + setB;
    cout << "Union of A and B: " << unionSet << endl;
    
    MultiSet<int> intersectionSet = setA * setB;
    cout << "Intersection of A and B: " << intersectionSet << endl;
    
    // Test set difference
    MultiSet<int> differenceSet = setA - setB;
    cout << "Set A - Set B: " << differenceSet << endl;
    
    // Test subset operators
    cout << "Is Set A = Set B? ";
    if (setA == setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A != B? ";
    if (setB != setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a subset of Set B? ";
    if (setA <= setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a subset of Set A? ";
    if (setB <= setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a strict subset of Set B? ";
    if (setA < setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a strict subset of Set A? ";
    if (setB < setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    // Test Copy Constructor
    MultiSet<int> setC = setA;
    cout << "Set C (assigned from set A): " << setC << endl;

    // Clear set A
    setA.clear();
    cout << "Set A after clear: " << setA << endl;
    // Test assignment operator
    setA = setC;
    cout << "Set A after assigned to C: " << setA << endl;

    setA.clear();
    setB.clear();

    cout << "Set A after clear: " << setA << endl;
    cout << "Set B after clear: " << setB << endl;

    setA.insert(1);
    setA.insert(2);
    setA.insert(2);
    setA.insert(3);
    setA.insert(3);

    setB.insert(1);
    setB.insert(2);
    setB.insert(2);
    setB.insert(3);
    setB.insert(3);
    setB.insert(3);
    setB.insert(4);

    cout << "Set A after inserts: " << setA << endl;
    cout << "Set B after inserst: " << setB << endl;

    // Test subset operators
    cout << "Is Set A = Set B? ";
    if (setA == setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A != B? ";
    if (setB != setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a subset of Set B? ";
    if (setA <= setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a subset of Set A? ";
    if (setB <= setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a strict subset of Set B? ";
    if (setA < setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a strict subset of Set A? ";
    if (setB < setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }

    setA = setB;

    cout << "Set A after assignment to B: " << setA << endl;
    cout << "Set B: " << setB << endl;

    // Test subset operators
    cout << "Is Set A = Set B? ";
    if (setA == setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A != B? ";
    if (setB != setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a subset of Set B? ";
    if (setA <= setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a subset of Set A? ";
    if (setB <= setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set A a strict subset of Set B? ";
    if (setA < setB) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "Is Set B a strict subset of Set A? ";
    if (setB < setA) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }

    return 0;
}