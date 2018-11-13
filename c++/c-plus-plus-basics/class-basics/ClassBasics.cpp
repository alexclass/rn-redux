/*
Title: ClassBasics.cpp
Description: Creates a Text class that contains a string object to hold the text of a file. 
	     Gives it two constructors: a default constructor, and a constructor that takes
	     a string argument that is the name of the file to open. When the second 
	     constructor is used, the file is opened and the contents of the file read into 
	     the string member object. A member function contents() returns the string so 
	     that it can be displayed. In main(), a file is opened using Text, and displays
	     the contents.
Date: February 16th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written using information from "Thinking in C++" by Bruce Eckel
#include <fstream> // File stream declarations
#include <string> // String usage
#include <iostream> // Stream declarations
using namespace std;

class Text {
	string fileInput; // stores contents of file opened by constructor
public:
	Text(); // default constructor
	Text(string filename); // constructor that accepts file to be opened
	string contents(); // member function which returns contents of file
}; // Text

Text::Text() {} // declaration of default constructor

Text::Text(string filename) { // accepts string of file to be used with class
	ifstream inFile(filename.c_str()); // opens specified file
	string line; // used to store each line in the file
	while(getline(inFile, line)) // continues until all file contents have been copied
		fileInput += line + "\n"; // adds each line of contents to member data + new line
} // Text()

string Text::contents() {
	return fileInput; // returns contents of file/member data
} // contents()

int main() {
	Text text("DVDRentalList.txt"); // creates instance of Text class with specified file
	string contents = text.contents(); // gets contwnts of text member data
	cout << contents << endl; // displays contents of text member data
} // main()