/* Kyle Tranfaglia
*  COSC320 - Homework01 - Ex.6
*  Last updated 09/08/23
*  This program tests the functionality of the Thing1 class and the inherited Thing2 class - Code provided by Dr. Spickler
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Thing1.h"
#include "Thing2.h"

using namespace std;

int main() {
    srand(time(0));

    Thing1<int> list1;
    Thing2<int> list2; 

    list1.pushback(5);
    list1.pushback(7);
    list1.pushback(2);
    list1.pushback(10);
    list1.pushback(3);
    list1.pushback(15);

    cout << list1.size() << endl;

    list1.printforward();
    cout << endl;

    list1.printbackward();
    cout << endl;

    cout << list1.popback() << endl;
    list1.printforward();
    cout << endl;

    cout << list1.popfront() << endl;

    list1.printforward();
    cout << endl;
    cout << list1.size() << endl;

    cout << list1.find(10) << " " << list1.findpos(10) << endl;
    cout << list1.find(15) << " " << list1.findpos(15) << endl;
    
    cout << list1 << endl;

    cout << list1.getValue(0) << endl;
    cout << list1.getValue(2) << endl;
    cout << list1.getValue(5) << endl;

    list1.setValue(2, 123);
    cout << list1 << endl;
    
    cout << list1.isempty() << endl;
    list1.clear();
    cout << list1.isempty() << endl;

    for (int i = 1; i < 10; i++)
        list2.pushback(rand() % 100);
    
    cout << list2 << endl;
    list2.resetIteratorToFront();
    cout << list2.get() << endl;
    list2++;
    cout << list2.get() << endl;

    list2.resetIteratorToBack();
    cout << list2.get() << endl;
    list2--;
    cout << list2.get() << endl;
    list2--;
    cout << list2.get() << endl;
    ++list2;
    cout << list2.get() << endl;
    list2 -= 3;
    cout << list2.get() << endl;
    list2 += 2;
    cout << list2.get() << endl;
    list2 += 12345;
    cout << list2.get() << endl;

    list2.insertval(123);
    cout << list2 << endl;
    list2 -= 3;
    list2.insertval(-25);
    cout << list2 << endl;

    list2.resetIteratorToFront();
    list2 += 5;
    cout << list2.get() << endl;

    list2.deleteval();
    cout << list2 << endl;
    cout << list2.get() << endl;

    return 0;
}