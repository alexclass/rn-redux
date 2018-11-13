/*
Title: NestedClasses.cpp
Description: Creates a Hen class. Inside this class, it nest a Nest class. Inside Nest, 
	     an Egg class is placed. Each class should has a display() member function. 
	     For each class, a constructor and a destructor is created that prints an 
	     appropriate message when called. In main(), an instance of each class is created
	     using new, and a call to the display() function is made for each one. After 
	     display() is called, the storage is freed using delete.
Date: February 16th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively using information from "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
using namespace std;

class Hen {
public:
	void display(); // member function
	Hen(); // constructor
	~Hen(); // destructor

	class Nest { // Nested class
	public:
		void display(); // member function
		Nest(); // constructor
		~Nest(); // destructor

		class Egg { // Nested class
		public:
			void display(); // member function
			Egg(); // constructor
			~Egg(); // destructor
		}; // Egg
	}; // Nest
}; // Hen

void Hen::display() { // definition of member function
	cout << "Displaying instance of Hen class." << endl;
}

Hen::Hen() { // definition of constructor
	cout << "Inside Hen constructor." << endl;
}

Hen::~Hen() { // definition of deconstructor
	cout << "Inside Hen deconstructor." << endl;
}

void Hen::Nest::display() { // definition of member function
	cout << "Displaying instance of Nest class." << endl;
}

Hen::Nest::Nest() { // definition of constructor
	cout << "Inside Nest constructor." << endl;
}

Hen::Nest::~Nest() { // definition of deconstructor
	cout << "Inside Nest deconstructor." << endl;
}

void Hen::Nest::Egg::display() { // definition of member function
	cout << "Displaying instance of Egg class." << endl;
}

Hen::Nest::Egg::Egg() { // definition of constructor
	cout << "Inside Egg constructor." << endl;
}

Hen::Nest::Egg::~Egg() { // definition of deconstructor
	cout << "Inside Egg deconstructor." << endl;
}

int main() {
	Hen* hen = new Hen(); // dynamic creation of Hen
	Hen::Nest* nest = new Hen::Nest(); // dynamic creation of Nest
	Hen::Nest::Egg* egg = new Hen::Nest::Egg(); // dynamic creation of Egg
	hen->display(); // calls hen member function
	nest->display(); // calls nest member function
	egg->display(); // calls egg member function
	delete hen; // deletes hen - calls deconstructor
	delete nest; // deletes nest - calls deconstructor
	delete egg; // deletes egg - calls deconstructor
} // main