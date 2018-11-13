/*
Title: FileStringManipulation.cpp 
Description: Creates an array of 100 string objects. Fills the array by opening a (text) 
	     file, and reading one line of the file into each string until the array is
	     filled. Displays the array using the format “line #: <string>”, where # is 
	     the actual line number, and <string> is the stored string.
Date: January 24th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
#include <string> // String usage
#include <fstream> // File stream declarations
using namespace std;

int main() {
	string aString[100]; // String array to store 100 lines from file
	ifstream inputFile("WCFile.txt"); // Opens file
	#ifdef DEBUG // Included as part of makefile
		cout << "***Debugging is turned on." << endl;
		cout << "***Input file is located at: " << inputFile << endl;
		cout << "***Array is located at: " << aString << endl;
	#endif // DEBUG
	for(int i = 0; i < 100; i++) // Iterates from 0 to 99 to fill array
		getline(inputFile, aString[i]); // Fills each array element with a line from the file
	for(int i = 0; i < 100; i++) // Iterates from 0 to 99 to display array
		cout << "line " << i << ": " << aString[i] << endl; // Displays array in requested format
} ///:~