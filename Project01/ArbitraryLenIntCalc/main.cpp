/* Kyle Tranfaglia
*  COSC320 - Project01
*  Last updated 10/20/23
*  This program constructs and provides an interface for the Abitrary Length Integer Calculator
*  It handles the operations: "^, %, /, *, +, -" and the functions: "fact(int), fib(int), sqrt(int)"
*  The result of the operations is an infinite precision integer and any errors are handled with std exceptions
*/
#include <fstream>
#include <vector>
#include <cstring>

#include "Function.h"
#include "tinyfiledialogs.h"

// Prototypes
void PrintMenu();
void PrintHelp();
bool IOInExpression(string);
bool isiwf(const char*);
void fixExpression(string&, const vector<InfInt>&);

int main() {
    // Variables
	Function expressionTree; // Function object for expression storage and evaluation
    vector<string> inputs; // Holds all user inputs of expressions
    vector<InfInt> outputs; // Holds all outputs from expressions
    string holdInput = " "; // Holds user input
    int inOutCount = 1; // Count of IO variables
    bool run = true; // Keep program running until set false

    PrintMenu(); // Function call to print menu on program startup

    // Loop to run the program unti the user selects "exit"
    while (run) {
        // Gets input line from user
        cout << "i" << inOutCount << " > ";
        getline(cin, holdInput);
        // Checks user input operates accordingly
        if (holdInput == "H" || holdInput == "h") {
            PrintHelp(); // Function call to print the help menu
        }
        else if (holdInput == "open" || holdInput == "Open") {
            // Tiny file dialogs setup for input file
            char const *lFilterPatterns[1] = { "*.iwf" };
            char *filename = tinyfd_openFileDialog("Open Arbitrary Precision Integer Calculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File", 0);
            ifstream inputFile;

            inputFile.open(filename); // Opens input file
            // Try catch to get catch error if file does not open
            try {
                // Check if the filename is a valid string
                if (!filename) {
                    throw std::invalid_argument("Invalid filename");
                }
                else if (!isiwf(filename)) {
                    throw std::ios_base::failure("File must be of type '.iwf'");
                }
                // Checks if file opened, if not, throws error
                else if (!inputFile) {
                    throw std::ios_base::failure("Error opening file");
                }
                else {
                    cout << "Opening " << filename << endl;
                    string holdLine = "";
                    // Loop to get each line of the file and check if it is an input or output
                    while (getline(inputFile, holdLine)) {
                        // Checks if input or output
                        if (holdLine[0] == 'i') {
                            holdLine = holdLine.substr(holdLine.find('>') + 1); // Gets the string after '>' ... gets input
                            inputs.push_back(holdLine); // Puts value in input vector
                            cout << "i" << inOutCount << " > " << holdLine << endl; // Prints the input value
                        }
                        else if (holdLine[0] == 'o') {
                            holdLine = holdLine.substr(holdLine.find('>') + 1); // Gets the string after '>' ... gets output
                            outputs.push_back(holdLine); // Puts value in output vector
                            cout << "o" << inOutCount << " > " << holdLine << endl << endl; // Prints the output value
                            inOutCount++; // IO Gathered ... increment count
                        }
                    }
                }
            } 
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            inputFile.close(); // closes input file
        }
        else if (holdInput == "save" || holdInput == "Save") {
            // Tiny file dialogs setup for input file
            char const *lFilterPatterns[1] = { "*.iwf" };
            char *filename = tinyfd_saveFileDialog("Save Arbitrary Precision IntegerCalculator Workspace File", NULL, 1, lFilterPatterns, "Workspace File");
            ofstream outputFile;

            outputFile.open(filename); // Open output file for a save file

            // Try catch to get catch error if file does not open
            try {
                // Check if the filename is a valid string
                if (!filename) {
                    throw std::invalid_argument("Invalid filename");
                }
                else if (!isiwf(filename)) {
                    throw std::ios_base::failure("File must be of type '.iwf'");
                }
                // Checks if file opened, if not, throws error
                else if (!outputFile) {
                    throw std::ios_base::failure("Error saving file");
                }
                else {
                    cout << "Saving Workspace to " << filename << endl;
                    // Loop to print all the IO values to the file using the IO vectors
                    for (unsigned int i = 0; i < inputs.size(); i++) {
                        outputFile << "i" << i << " > " << inputs[i] << endl;
                        outputFile << "o" << i << " > " << outputs[i] << endl << endl;
                    }
                }
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            outputFile.close(); // Close ouput file
        }
        // If user selected exit, set run variable to false to stop running program
        else if (holdInput == "exit" || holdInput == "Exit") {
            run = false;
        }
        else {
            // Checks if an I/O is used in expression
            if (IOInExpression(holdInput)) {
                fixExpression(holdInput, outputs); // Function call to fix the expression by replacing I/O with the output value
            }
            inputs.push_back(holdInput); // Input is expression (or wrong input that will be handled) so put in input vector
            try {
                expressionTree.ConvertExpression(holdInput); // Calls convert function for object to load it into a tree
                InfInt value = expressionTree.Evaluate(); // Gets the value of the expression
                outputs.push_back(value); // Places output value in vector
                cout << "o" << inOutCount << " > " << value << endl << endl; // Print the output value
                inOutCount++; // I/O cycle complete ... increment count
            }
            catch (const exception& e) {
                inputs.pop_back(); // Removes input from vector if error
                cout << "Error: " << e.what() << endl;
            }
        }
    }
	return 0;
}
// Function to print the start menu
void PrintMenu() {
	cout << "Arbitrary Precision Integer Calculator" << endl;
    cout << "Standard arithmetic expression evaluator with unlimited integer size " << endl;
    cout << "By Kyle Tranfaglia" << endl << endl;

	cout<<"Type 'H' for help" << endl;
    cout<<"Type 'exit' to quit" << endl;
    cout<<"Type 'open' to open a workspace file" << endl;
    cout<<"Type 'save' to save a workspace file" << endl << endl << endl;
}
// Function to print the help menu
void PrintHelp() {
    cout << "Supported Operations and Functions: " << endl;
    cout << "+: addition, Ex: 123 + 432" << endl;
    cout << "-: subtraction, Ex: 123 - 432" << endl;
    cout << "*: multiplication, Ex: 123 * 432" << endl;
    cout << "/: integer division, Ex: 123 / 432" << endl;
    cout << "%: modulus, Ex: 123 % 432" << endl;
    cout << "^: power, Ex: 123 ^ 432 --- exponent must be of integer size" << endl;
    cout << "(): parentheses for expression delimitation" << endl;
    cout << "fact: factorial, Ex: fact(1000) --- operand must be of integer size" << endl;
    cout << "fib: Fibonacci number , Ex: fib(1000) --- operand must be of integer size" << endl;
    cout << "sqrt: integer square root, Ex: sqrt(1000)" << endl;
    cout << "You can also use previous inputs and outputs by using their designations," << endl;
    cout << "for example, i4 * 2345 will take the input number 4 and multiply it by 2345" << endl;
    cout << "Similarly, i4 * o7 will multiply input 4 by output 7 " << endl;
}
// Function to return true if the expression contains an I/O that needs converted
bool IOInExpression(string expression) {
    bool status = false;
    // Loop to go through entire string by character looking for 'i' or 'o'
    for (unsigned int i = 0; i < expression.length(); i++) {
        // Checks if I/O found, and if so, sets status to true
        if ((expression[i] == 'i' || expression[i] == 'o') && (expression[i + 1] >= '0' && expression[i + 1] <= '9')){
            status = true;
        }
    }
    return status;
}
// Function to fix an expression, menaing if it uses I/O, replace it with the output value so it can be understood in evaluation
void fixExpression(string &expression, const vector<InfInt> &outputs) {
    // Variables
    unsigned int position, i = 0, j = 0;
    InfInt outValue = 0;
    string newString = "", temp = "";
    // Try catch to get any string manipulation errors
    try {
        // Loop to run for length of expression
        while (i < expression.length()) {
            // Checks if 'i' or 'o' is at the index
            if ((expression[i] == 'i' || expression[i] == 'o') && (expression[i + 1] >= '0' && expression[i + 1] <= '9')) {
                i++; // Increments index
                // While a number follows the I/O, increment and store the number as a string ... checks that expression index is in bound
                while ((expression[i] >= '0' && expression[i] <= '9') && i < expression.length()) {
                    temp += expression[i++]; // Store numeric value follwing I/O
                }
                position = stoi(temp); // Gets the I/O number using string to int fucntion from string class
                outValue = outputs[position - 1]; // Gets the value of the output at the position of I/O
                temp = outValue.toString(); // Converts output value to a string with function in InfInt.h
                // Loop to go for length of output and add each index to the new expression string ... replacing I/O in old expression
                for (unsigned int l = 0; l < temp.size(); l++) {
                    newString += temp[l];
                    j++;
                }
                // Resets temp and iterator incase of multiple I/O used
                temp = "";
            }
            else {
                newString += expression[i++]; // No I/O detected so expression directly copied
                j++;
            }
        }
        expression = newString; // Sets the expression to the updated string without I/O
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}
// Function to check that the file extension is "iwf"
bool isiwf(const char* filename) {
    bool status = true;
    // Get the length of the filename
    size_t len = strlen(filename);
    // Uses C-string functions to check that the file extension is ".iwf"
    if (len < 4 || strcmp(filename + len - 4, ".iwf") != 0) {
        status = false;
    }
    return status;
}