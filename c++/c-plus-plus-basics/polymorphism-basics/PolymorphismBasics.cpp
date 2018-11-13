/*
Title: PolymorphismBasics.cpp
Description: Creates an inheritance hierarchy of Rodent: Mouse, Gerbil, Hamster, etc. 
	     In the base class, provides methods that are common to all Rodents, and 
	     refines these in the derived classes to perform different behaviours 
	     depending on the specific type of Rodent. Rodent is created as a pure 
	     abstract base class. Creates an array of pointers (10) to Rodent, and fills 
	     it with different specific types of Rodents. Calls the base class methods, 
	     and displays the results.
Date: March 28th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively using information from "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
using namespace std;

class Rodent { // pure abstract base class
public:
	virtual void species() const = 0; // refined in each subtype to display correct species
	virtual void eats() const = 0; // refined in each subtype to display correct food
	virtual void hygiene() const = 0; // refined in each subtype to display correct hygiene
	virtual void personality() const = 0; // refined in each subtype to display correct personality
	virtual void trait() const = 0; // refined in each subtype to display correct traits
};

class Mouse : public Rodent { // subtype of Rodent
public:
	void species() const { // refines base class method to display subtype species
		cout << "I am a Mouse" << endl;
	}
	void eats() const { // refines base class method to display subtype food
		cout << "I eat cheese" << endl;
	}
	void hygiene() const { // refines base class method to display subtype hygiene
		cout << "I am smelly" << endl;
	}
	void personality() const { // refines base class method to display subtype personality
		cout << "I am social" << endl;
	}
	void trait() const { // refines base class method to display subtype traits
		cout << "I am smart" << endl;
	}
};

class Gerbil : public Rodent { // subtype of Rodent
public:
	void species() const { // refines base class method to display subtype species
		cout << "I am a Gerbil" << endl;
	}
	void eats() const { // refines base class method to display subtype food
		cout << "I eat almonds" << endl;
	}
	void hygiene() const { // refines base class method to display subtype hygiene
		cout << "I am fairly clean" << endl;
	}
	void personality() const { // refines base class method to display subtype personality
		cout << "I am skittish" << endl;
	}
	void trait() const {
		cout << "I am hyperactive" << endl;
	}
};

class Hamster : public Rodent { // subtype of Rodent
public:
	void species() const { // refines base class method to display subtype species
		cout << "I am a Hamster" << endl;
	}
	void eats() const { // refines base class method to display subtype food
		cout << "I eat seeds" << endl;
	}
	void hygiene() const { // refines base class method to display subtype hygiene
		cout << "I am dirty" << endl;
	}
	void personality() const { // refines base class method to display subtype personality
		cout << "I am tempermental" << endl;
	}
	void trait() const { // refines base class method to display subtype traits
		cout << "I am docile" << endl;
	}
};

int main() {
	// array of 10 pointers to Rodent, filled with the different subtypes
	Rodent* rp[] = { new Mouse, new Gerbil, new Hamster,
					 new Mouse, new Gerbil, new Hamster,
					 new Mouse, new Gerbil, new Hamster,
					 new Mouse};
	// loops through array and tests calls each base class method
	for(int i = 0; i < 10; i++) {
		rp[i]->species();
		rp[i]->eats();
		rp[i]->hygiene();
		rp[i]->personality();
		rp[i]->trait();
		cout << endl;
	}
} // main