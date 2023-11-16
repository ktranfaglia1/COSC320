/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * CrossRef object declaration file inhereted off of the BST class of type string
*/
#ifndef CROSSREF_H
#define CROSSREF_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "BST.h"

using namespace std;

class Crossref : public BST<string> {
    protected: 
        void printTheStuff(TreeNode<string>*); // Function to Recursively print the words in order followed by their corresponding linked list of line numbers
    public: 
        void printTheStuff(); // Callable function that calls the recursive print function
        Crossref(string fileName); // Constructor that reads in the file and creates BST structure
        virtual ~Crossref(); // Destructor ... virtual so that base class destructor gets used
};  

#endif