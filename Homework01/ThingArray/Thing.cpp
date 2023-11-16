/* Kyle Tranfaglia
 * COSC320 - Homework01 - Ex.4
 * Last updated 09/08/2023
 * Thing Object Implimentation
*/
#include "Thing.h"
// Constructor with default parameter values 
Thing::Thing(int x1, int x2) {
    a = x1;
    // Checks that b parameter is not 0 and if so sets value to 1
    if (x2 != 0) {
        b = x2;
    }
    else {
        cout << "Invalid input for second variable (cannot equal 0) ... setting value to 1" << endl;
        b = 1;
    }
}
// Default destructor
 Thing::~Thing() {
}
// Function to set value of a
void Thing::setA(int x) {
    a = x;
}
// Function to set value of b
void Thing::setB(int x) {
    // Checks that b parameter is not 0 and if so sets value to 1
    if (x != 0) {
        b = x;
    }
    else {
        cout << "Invalid input for second variable (cannot equal 0) ... setting value to 1" << endl;
        b = 1;
    }
}
// Function to set value of a and b
void Thing::set(int x1, int x2) {
    a = x1;
    // Checks that b parameter is not 0 and if so sets value to 1
    if (x2 != 0) {
        b = x2;
    }
    else {
        cout << "Invalid input for second variable (cannot equal 0) ... setting value to 1" << endl;
        b = 1;
    }
}
// Function to return value of a
int Thing::getA() const {
    return a;
} 
// Function to return value of b
int Thing::getB() const {
    return b;
}
// Comparison > Operator overload with boolean return
bool Thing::operator > (const Thing &obj) {
	return ((a*obj.b) > (b*obj.a));
}
// Comparison < Operator overload with boolean return
bool Thing::operator < (const Thing &obj) {
    return ((a*obj.b) < (b*obj.a));
}
// Comparison == Operator overload with boolean return
bool Thing::operator == (const Thing &obj) {
    return ((a*obj.b) == (b*obj.a));
}
// Comparison >= Operator overload with boolean return
bool Thing::operator >= (const Thing &obj) {
    return ((a*obj.b) >= (b*obj.a));
}
// Comparison <= Operator overload with boolean return
bool Thing::operator <= (const Thing &obj) {
    return ((a*obj.b) <= (b*obj.a));
}
// Comparison != Operator overload with boolean return
bool Thing::operator != (const Thing &obj) {
    return ((a*obj.b) != (b*obj.a));
}
// Ostream operator overload that allows a cout of the object with the specified formatting
ostream &operator << (ostream &strm, const Thing &obj) {
    strm << "(" << obj.a << ", " << obj.b << ")";
	return strm;
}