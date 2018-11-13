/*
Title: WordsInFile.cpp
Description: Opens a file and counts the whitespace-separated words in that file
Date: January 23rd, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <iostream> // stream declarations
#include <fstream> // file declarations
#include <string> // use of string variables
using namespace std;

int main() {
	ifstream inputFile("WCFile.txt"); // Opens hard-coded file
	string word; // used to input words from the file
	int count = 0; // used to count words in the file
	while(inputFile >> word) // gets one word at a time from file
		count++; // increments counter each iteration of the loop (for each word)
	cout << "The total # of whitespace-separated words "
			"in the file is " << count << endl; // displays result
} ///:~
