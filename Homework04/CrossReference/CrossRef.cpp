/* Kyle Tranfaglia
 * COSC320 - Homework04 - Ex.1
 * 09/29/2023
 * CrossRef object implimentation file for the constructor and print function
*/
#include "CrossRef.h"
// Constructor that reads in the file and creates BST structure
Crossref::Crossref(string fileName) {
    ifstream inputFile;

    inputFile.open(fileName); // Opens file

    // Checks if the file opened
    if (!inputFile) {
        cout << "Not a valid file name ... nothing can be read" << endl;
    }
    else {
        string line = "", dummy = "";
        int lineNum = 0;
        // Loop to run as long as EOF has not been reached, as in a line can be read in
        while (getline(inputFile, line)) {
            lineNum++; // Line counter
            istringstream iss(line); //  input stream operations, specifically for reading formatted input from a string, used to tokenize and extract words from a string
            // Loop to run as long as a word can be extracted from the string
            while (iss >> dummy) {
                string newDummy = "";
                // Loop to convert the word to lowercase by converting each letter to lowercase and only concat letters such that any non-letters will be removed
                for (unsigned int i = 0; i < dummy.length(); i++) {
                    if ((dummy[i] >= 'A' && dummy[i] <= 'Z') || (dummy[i] >= 'a' && dummy[i] <= 'z'))
                        newDummy += tolower(dummy[i]);
                }
                // Checks that the string is not empty
                if (newDummy != "") {
                    TreeNode<string>* nodeptr; 
                    // Searches for word in tree, if it exists, find the node and pushback the linecount onto the linked list, otherwise, the word does not exist so create a node with that word and line number
                    if (find(newDummy)) {
                        nodeptr = findNode(newDummy);
                        nodeptr->list.pushBack(lineNum);
                    }
                    else {
                        insert(newDummy, lineNum);
                    }
                }
            }
        }
    }
    inputFile.close(); /// Close the file
}
// Destructor
Crossref::~Crossref() {

}
// Function to print the words in order followed by their corresponding linked list of line numbers by calling recursive function
void Crossref::printTheStuff() {
    printTheStuff(root); // Calls recursive function with root
}
// Function to Recursively print the words in order followed by their corresponding linked list of line numbers
void Crossref::printTheStuff(TreeNode<string> *nodeptr) {
    // While there is still a node ... recurse through the tree in order and print the word of stored in each node and the corresponding linked list of line numbers
    if (nodeptr) {
		printTheStuff(nodeptr->left);
        cout << nodeptr->value << ": ";
        nodeptr->list.displayList(); 
		printTheStuff(nodeptr->right);
	}
 }