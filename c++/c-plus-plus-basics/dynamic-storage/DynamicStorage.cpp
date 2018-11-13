// reference used: http://www.cs.fsu.edu/~jestes/cop3014/notes/dma.html
// reference used: https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html

/*
Title: DynamicStorage.cpp
Description: Dynamically creates pieces of storage of the following types using new: int,
	     long, an array of 100 chars, and an array of 100 floats. Prints the addresses
	     and values of these using the format: “type @ <address>= <value>”. After printing
	     all the addresses and values, frees the storage using delete. Fills the char array
	     using copies of the lowercase and uppercase alphabet (a-z, A-Z), and fills the 
	     float array using sequential numbers starting with 101.
Date: February 16th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written using information from "Thinking in C++" by Bruce Eckel
#include <iostream> // stream declarations
using namespace std;

int main() {
	int size = 100; // int used for size of the two arrays
	int* ip = new int; // dynamically creates storage for an int
	*ip = 59; // assigns value to int storage
	long* lp = new long; // dynamically creates storage for a long
	*lp = 123456; // assigns a value to long storage
	char* ca = new char[size]; // dynamically creates storage for a 100 element char array
	float* fa = new float[size]; // dynamically creates storage for a 100 element float array
	for(int i = 0; i < 100; i++) { // loop to populate char array
		if((i % 52) < 26) // used to control lowercase/uppercase rotation
			ca[i] = 'a' + (i % 26); // lowercase chars
		else
			ca[i] = 'A' + (i % 26); // uppercase chars
	}
	for(int i = 0; i < 100; i++) // used to populate float array
		fa[i] = i + 101; // sequential numbers starting at 101
	// displays all addresses and values in the format specified
	cout << "int @ <" << (long)ip << "> = <" << *ip << ">" << endl;
	cout << "long @ <" << (long)lp << "> = <" << *lp << ">" << endl;
	for(int i = 0; i < 100; i++) // loops through char array
		cout << "charArray[" << i << "] @ <" << (long)(ca + i) << "> = <" << ca[i] << ">" << endl;
	for(int i = 0; i < 100; i++) // loops through float array
		cout << "floatArray[" << i << "]  @ <" << (long)(fa + i) << "> = <" << fa[i] << ">" << endl;
	delete ip; // deletes int storage
	ip = 0;
	delete lp; // deletes long storage
	lp = 0;
	delete []ca; // deletes char array storage
	ca = 0;
	delete []fa; // delete float array storage
	fa = 0;
}