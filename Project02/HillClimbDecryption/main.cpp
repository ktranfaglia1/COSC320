/* Kyle Tranfaglia
*  COSC320 - Project02
*  Last updated 11/10/23
*  This program takes an n input file of English letter patterns along with a frequency count, and a file containing 
*  the ciphertext of an encrypted message. Then, the program will apply the hill-climb algorithm to the ciphertext and
*  output the final best key along with the decrypted message using that best key
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <exception>

#include "Map.h"
#include "tinyfiledialogs.h"

using namespace std;

// Prototypes
bool compareDescending(pair<char, int>, pair<char, int>);
bool istxt(const char*);
void decryptMessage(string&, const string&);
void hillClimbAlgorithm();
double calculateFitnessMeasure(const string&, const int&, const long&, Map<string, double>&);

int main() {
    // Variables
    const string ENGLISHFREQUENCY = "ETAOINSHRDLCUMWFGYPBVKJXQZ"; // Most common to least common English letters
    const string ENGLISHALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // English alphabet
    const int ALPHABETLEGNTH = 26, MAXPASSES = 100; // Constants for loops
    fstream outputFile; // Output file for final key and decryped message
    Map<string, double> NGramMap; // Map for N-Gram structure
    vector<pair<char, int>> cypherCharFrequency; // Vector for cypher letter frequencies and corresponding letter
    // Temporary strings for instreaming, messages variables, and key variables
    string tempString = "", line = "", encryptedMessage = "", decryptedMessage = "", key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", tempKey = "", bestKey = "";
    int tempInt = 0, NGramType = 0, counter = 0; // instream variable, N-Gram letter grouping, and counter for hill climb loop
    long totalFrequency = 0; // Long for total frequencies of N-Grams
    double fitnessMeasure = 0.0, tempFitnessMeasure = 0.0, bestFitnessMeasure = 0.0; // Doubles for fitnessMeasures
    char tempChar = ' '; // temporary cahr variable 

    // Set-up for tiny dialog box: Gets an N-Gram file (.txt) from the user 
    char const *lFilterPatterns[1] = { "*.txt" };
    char *NGramFilename = tinyfd_openFileDialog("Open an N-Gram file", NULL, 1, lFilterPatterns, "N-Gram File", 0);
    ifstream NGramFile;

    NGramFile.open(NGramFilename); // Opens input file
    // Try to open file and assess its contents. If the file is of the wrong type, fails to open, or fails within iss data extraction, an error will be caught 
    try {
        // Check if the filename is a valid string
        if (!NGramFilename) {
            throw std::invalid_argument("Invalid filename");
        }
        // Uses C-string fucntions to test if the filename ends in '.txt'
        else if (!istxt(NGramFilename)) {
            throw std::ios_base::failure("File must be of type '.txt'");
        }
        // Checks if file opened, if not, throws error
        else if (!NGramFile) {
            throw std::ios_base::failure("Error opening file ... an N-Gram file is required for the program");
        }
        else {
            cout << "Opening " << NGramFilename << endl; // File successfully opened
            // While there is a line to read ... first read-in to get the total frequency of the N-Grams
            while (getline(NGramFile, line)) {
                istringstream iss(line); //  input stream operations, specifically for reading formatted input from a string, used to extract data pair from a string
                iss >> tempString; // Extract N-Gram
                iss >> tempInt; // Extract Frequency
                totalFrequency += tempInt;
            }
            // Moves file pointer to beginning
            NGramFile.clear();
            NGramFile.seekg(0, ios::beg);
            // While there is a line to read ... get N-gram data and insert to map
            while (getline(NGramFile, line)) {
                istringstream iss(line); //  input stream operations, specifically for reading formatted input from a string, used to extract data pair from a string
                iss >> tempString; // Extract N-Gram
                iss >> tempInt; // Extract Frequency
                NGramMap.insert(tempString, log10(static_cast<double>(tempInt)/totalFrequency)); // Insert data into a map ... NGram and Relative frequency
            }
            NGramType = tempString.length(); // Store the N-Gram type ... the value of N
            cout << "N-Gram file loaded" << endl;
        }
    } // If there is an error thrown, catch it and print the error with a program exit
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
    NGramFile.close(); // Closes input file

    // Set-up for tiny dialog box: Gets a Cipher file (.txt) from the user 
    char *cipherFilename = tinyfd_openFileDialog("Open an Cipher file", NULL, 1, lFilterPatterns, "Cipher File", 0);
    ifstream cypherFile;

    cypherFile.open(cipherFilename); // Opens input file
    // Try to open file and assess its contents. If the file is of the wrong type, fails to open, or fails within iss data extraction, an error will be caught 
    try {
        // Check if the filename is a valid string
        if (!cipherFilename) {
            throw std::invalid_argument("Invalid filename");
        }
        // Uses C-string fucntions to test if the filename ends in '.txt'
        else if (!istxt(cipherFilename)) {
            throw std::ios_base::failure("File must be of type '.txt'");
        }
        // Checks if file opened, if not, throws error
        else if (!cypherFile) {
            throw std::ios_base::failure("Error opening file ... a Cypher file is required for the program");
        }
        else {
            cout << "Opening " << cipherFilename << endl; // File successfully opened
            // Loop to initialize the frequency vector to zeros
            for (int i = 0; i < ALPHABETLEGNTH; i++) {
                cypherCharFrequency.push_back(make_pair('A' + i, 0));
            }
            // While there is a character that can be read from the file...
            while (cypherFile >> tempChar) {
                // Checks if the character is alphabetical
                if ((tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= 'a' && tempChar <= 'z')) {
                    encryptedMessage += tempChar; // Concatenates message to string
                    tempChar = toupper(tempChar); // Convert character to uppercase
                    tempInt = (tempChar - 'A'); // Get index value corresponding to the letter ... A-0, B-1, ... , Z-25
                    cypherCharFrequency[tempInt].second++; // Increment the frequnecy count at the character position in vector
                }
            }
            cout << "Cipher file loaded" << endl << endl;
        }
    } // If there is an error thrown, catch it and print the error with a program exit
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
    cypherFile.close(); // Closes input file
  
    sort(cypherCharFrequency.begin(), cypherCharFrequency.end(), compareDescending); // Sort array in descending order, as in, largest to smallest frequency

    // Get the base key for the decryption with a single character frequency analysis: Most frequent letter in cipher file equals most frequent English letter
    for (int i = 0; i < ALPHABETLEGNTH; i++) {
        key[cypherCharFrequency[i].first - 'A'] = ENGLISHFREQUENCY[i];
    }
    // Prints the English alphabet and the corresponding base key that displays the substituion for each letter
    cout << "Key from single character frquency analysis: " << endl;
    cout << ENGLISHALPHABET << endl;
    for (int i = 0; i < ALPHABETLEGNTH; i++) {
        cout << key[i];
    }
    cout << endl << endl;

    decryptedMessage = encryptedMessage; // Sets message to be decrypted

    // Decrypt the cipher message with the base key
    decryptMessage(decryptedMessage, key);

    // Calculate the fitness measure of the message after the first attempted decryption
    bestFitnessMeasure = calculateFitnessMeasure(decryptedMessage, NGramType, totalFrequency, NGramMap);

    // Hill Climb Algorithm to decrypt a message with by finding the substitution key
    do {
        tempFitnessMeasure = bestFitnessMeasure; // Store the previous Best Fitness Measure
        counter++;
        // Loop to transpose the key and find the best key based on the fitness measure of the decrypted message
        for (int i = 0; i < ALPHABETLEGNTH; i++) {
            for (int j = i + 1; j < ALPHABETLEGNTH; j++) {
                tempKey = key; // Hold current best key

                // Swap ith index and jth index of key
                tempChar = key[i];
                key[i] = key[j]; 
                key[j] = tempChar;

                decryptedMessage = encryptedMessage; // Sets message to be decrypted
                decryptMessage(decryptedMessage, key); // Decrypt the cipher message with the key
                
                fitnessMeasure = calculateFitnessMeasure(decryptedMessage, NGramType, totalFrequency, NGramMap); // Calculate the fitness measure of the message

                // Check if fitness measure is greater than the best fitness measure and update accordingly
                if (fitnessMeasure > bestFitnessMeasure) {
                    bestFitnessMeasure = fitnessMeasure;
                }
                else {
                    key = tempKey;
                }
            }
        } // Runs as long as max iterations has not been reached and best fitness measure is still increasing
    } while ((counter < MAXPASSES) && (bestFitnessMeasure > tempFitnessMeasure));

    // Print the English Alphabet and the final key, as in, the corresponding letter substitutions to console
    cout << "Final Key after " << counter << " iterations of the hill climb algorithm" << endl;
    cout << ENGLISHALPHABET << endl;
    for (int i = 0; i < ALPHABETLEGNTH; i++) {
        cout << key[i];
    }
    cout << endl << endl;

    // Do a final decryption of message with the final key  
    decryptedMessage = encryptedMessage;
    decryptMessage(decryptedMessage, key);
    
    cout << "Decryption using final key: " << endl << decryptedMessage << endl; // Print the final message to console

    // Try to print results to output file
    try {
        outputFile.open("DecyptedMessage.txt", ios::out); // Open output file
        // If file failed to open, throw error
        if (!outputFile) {
            throw std::ios_base::failure("Error opening file ... Decypted Message was not successfully inputted in the text file 'DecyptedMessage.txt'");
        }
        // Prints the English Alphabet and the final key, as in, the corresponding letter substitutions to output file
        outputFile << "Final Key after " << counter << " iterations of the hill climb algorithm" << endl;
        outputFile << ENGLISHALPHABET << endl;
        for (int i = 0; i < ALPHABETLEGNTH; i++) {
            outputFile << key[i];
        }
        outputFile << endl << endl;

        outputFile << "Decryption using final key: " << endl << decryptedMessage; // Print the final message in output file

        outputFile.close(); // Close output file
    }
    // If an error is thrown, catch it, display an error message and exit with fail
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
    
    return 0;
}
// Comparator function for algorithm sort to sort the vector pairs in descending order based on frequency values only
bool compareDescending(pair<char, int> a, pair<char, int> b) {
    // return ((a.second > b.second) || (a.second == b.second && a.first > b.first)); // Alternative to handle frequency tie ... resulted in slightly different base key
    return (a.second > b.second);
}
// Function to return the result of a substituion decryption
void decryptMessage(string& decryptedMessage, const string& key) {
    // Loop to use the provided key to replace the letters of the message with the corresponding letters denoted by the key
    for (unsigned int i = 0; i < decryptedMessage.length(); i++) {
        decryptedMessage[i] = key[decryptedMessage[i] - 'A'];
    }
}
// Function to calculate the fitness measure
double calculateFitnessMeasure(const string& encryptedMessage, const int& NGramType, const long& totalFrequency, Map<string, double> &NGramMap) {
    double fm = 0.0, frequency = 0.0; // Fitness measure and N-Gram frequency variavbles
    string NGram = ""; // String to hold the N-Gram retrieved from the map
    // Loop to go through the entire message and get the frequency of every N-Gram in the message with a map search (get) 
    for (unsigned int i = 0; i < encryptedMessage.length(); i++) {
        // Try and catch to handle an error if thrown by get function (failed search)
        try {
            NGram = encryptedMessage.substr(i, NGramType); // Gets the N-Gram
            frequency = NGramMap.get(NGram); // Gets the relative frequencies of the N-Gram from the map
        } // Handle error from get (failed search)
        catch (const exception& e) {
            frequency = log10((0.01)/static_cast<double>(totalFrequency)); // Set frequency to this default value (value is not 0 to minimize impact)
        }
        fm += frequency; // Running total of the frequencies ... final value is fitness measure
    }
    return fm;
}
// Function to check that the file extension is "txt"
bool istxt(const char* filename) {
    bool status = true;
    // Get the length of the filename
    size_t len = strlen(filename);
    // Uses C-string functions to check that the file extension is ".txt"
    if (len < 4 || strcmp(filename + len - 4, ".txt") != 0) {
        status = false;
    }
    return status;
}