/*
Title: OperatorOverloading.cpp
Description: Creates a simple class (DoStuff) containing an int, and overloads the 
	     operator+ as a member function. Also, provides a print() member function 
	     that takes an ostream& as an argument and prints to that ostream&. Adds 
	     a binary operator- and operator+ to the class as member functions. Allows 
	     use of the objects in complex expressions such as a + b – c. Adds the 
	     operator++ and operator--, both prefix and postfix versions. Overloads 
	     the << operator to provide the same functionality as the print() member function.
Date: March 19th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written using information from "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
#include <fstream> // File stream declarations
using namespace std;

class DoStuff {
	int i; // int data member which will be manipulated by operators
public:
	DoStuff(int ii = 0) : i(ii) {} // constructor sets data member to specified value
	const DoStuff operator+() const { // unary operator+ - has no effect
		cout << "In unary operator+\n";
		return *this;
	}
	void print(ostream& os) const { // prints value of data member to passed ostream
		os << i;
	}
	const DoStuff operator-(const DoStuff& right) const { // binary operator- (subtraction)
		return DoStuff(i - right.i);
	}
	const DoStuff operator+(const DoStuff& right) const { // binary operator+ (addition)
		return DoStuff(i + right.i);
	}
	const DoStuff& operator++() { // Prefix increment
		i++;
		return *this;
	}
	const DoStuff operator++(int) { // Postfix increment
		DoStuff before(i);
		i++;
		return before;
	}
	const DoStuff& operator--() { // Prefix decrement
		--i;
		return *this;
	}
	const DoStuff operator--(int) { // Postfix decrement
		DoStuff before(i);
		--i;
		return before;
	}
	friend ostream& operator<<(ostream& os, const DoStuff ds) { // adds data member to ostream
		return os << "[i] = " << ds.i;
	}
}; // class DoStuff

int main() {
	DoStuff ds(0); // Create instance of DoStuff with initial value of 0
	DoStuff ds2(2); // Create instance of DoStuff with initial value of 2
	DoStuff ds3(4); // Create instance of DoStuff with initial value of 4
	DoStuff ds4(6); // Create instance of DoStuff with initial value of 6
	cout << "Initial value of ds: "<< ds << endl; // display value of ds
	ofstream out("OpOv.txt"); // open file to test print()
	out << "i = "; // writes to ofstream
	ds.print(out); // tests print()
	+ds; // call unary operator+
	cout << "After unary operator+ (has no effect): " << ds << endl; // displays result
	ds = ds + 5; // calls binary operator+
	cout << "After binary operator+ 5 (ds = ds + 5): " << ds << endl; // displays result
	ds = ds - 2; // calls binary operator-
	cout << "After binary operator- 2 (ds = ds - 2): " << ds << endl; // displays result
	ds = ds + ds2 - ds3; // test complex expression
	cout << "After testing complex expression (ds = ds[3] + ds2[2] - ds3[4]: " << ds << endl; // displays result
	cout << "Calling ++ds (prefix): " << ++ds << endl; // tests ++operator
	cout << "Value after call: " << ds << endl; // displays results
	cout << "Calling ds++ (postfix): " << ds++ << endl; // tests operator++
	cout << "Value after call: " << ds << endl; // displays results
	cout << "Calling --ds (prefix): " << --ds << endl; // tests --operator
	cout << "Value after call: " << ds << endl; // displays results
	cout << "Calling ds-- (postfix): " << ds-- << endl; // tests operator--
	cout << "Value after call: " << ds << endl; // displays results
} // main()

