/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * Program to test the functionality of the crossref class, as in, provides a text file and prints the output of the object
*/
#include "CrossRef.h"

int main() {
    string textFile;

    cout << "Enter a text file: ";
    cin >> textFile;

    Crossref test(textFile); // Creates object and provides text file from user

    test.printTheStuff(); // Prints the information stored in with the object

    return 0;
}