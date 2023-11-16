/* Kyle Tranfaglia
 * COSC320 - Homework01 - Ex.3
 * Last updated 09/08/2023
 * Thing Object Declaration
*/
#ifndef Thing_H
#define Thing_H

#include <iostream>

using namespace std;

class Thing; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Thing &);

class Thing {
    private:
        int a, b;
    public:
        Thing(int x1 = 0, int x2 = 1); // Constructor
        ~Thing(); // Destructor

        // Mutators
        void setA(int); 
        void setB(int); 
        void set(int, int);
        
        // Accessors
        int getA() const; 
        int getB() const;

        bool operator > (const Thing &);		// Overloaded >
	    bool operator < (const Thing &);		// Overloaded <
        bool operator == (const Thing &);		// Overloaded ==
        bool operator >= (const Thing &);		// Overloaded >=
        bool operator <= (const Thing &);		// Overloaded <=
        bool operator != (const Thing &);		// Overloaded !=

        friend ostream &operator << (ostream &, const Thing &);
};

#endif