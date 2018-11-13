/*
Title: PrimeNumbers.cpp
Description: Uses two nested for loops and the modulus operator (%) to detect and print
			 the prime numbers from 1 to 10,000. Displays all the primes found.
Date: January 23rd, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
using namespace std;

int main() {
	bool prime; // used to flag numbers that are prime
	for(int i = 2; i < 10000; i++) { // iterates from 2 to 1000 to test for primes
		prime = true; // initially sets prime true
		for(int j = 2; j < i; j++) { // loops from 2 to current number to check for divisibility
			if(i % j == 0) // a modulus of 0 means the number isn't prime
				prime = false; // sets bool to false as number isn't prime
		} // for(j)
		if(prime)
			cout << i << " is prime." << endl; // displays a number if found to be prime
	} // for(i)
} ///:~