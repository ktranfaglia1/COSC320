/* Kyle Tranfaglia
 * COSC320 - Homework01 - Ex.3
 * Last updated 09/08/2023
 * Main Program to test the functionality of the thing class - Code Provided by Dr. Spickler
*/
#include <iostream>
#include "Thing.h"

using namespace std;

int main() {
    Thing t1(2, 3);
    Thing t2(1, 3);
    Thing t3(1, 2);
    Thing t4(2, 4);

    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    cout << (t1 < t2) << endl;
    cout << (t1 > t2) << endl;
    cout << (t1 <= t2) << endl;
    cout << (t1 >= t2) << endl;
    cout << (t1 == t2) << endl;
    cout << (t1 != t2) << endl;
    cout << (t3 == t4) << endl;

    cout << t1.getA() << " " << t1.getB() << endl;
    t1.setA(5);
    t1.setB(7);
    cout << t1 << endl;
    cout << t1.getA() << " " << t1.getB() << endl;

    t1.set(10, 17);
    cout << t1 << endl;

    return 0;
}