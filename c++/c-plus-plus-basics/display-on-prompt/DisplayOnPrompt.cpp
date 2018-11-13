/*
Title: DisplayOnPrompt.cpp
Description: Opens a (text) file, and displays the contents of that file one line at
	a time. After a line has been displayed, the program waits for the user 
	to press the <enter> key before displaying the next line in the file.
Date: January 23rd, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
#include <fstream> // File stream declarations
#include <string> // Use of string variables
using namespace std;

int main() {
	ifstream inputFile("80File.txt"); // Opens file
	string line; // Used to input lines from the file
	getline(inputFile, line); // Gets first line from file
	do {
		cout << line << " (press enter for next line)"; // Displays lines from the file
		cin.get(); // Waits for <enter> key press
	} while (getline(inputFile, line)); // loops while the file has more lines
}
