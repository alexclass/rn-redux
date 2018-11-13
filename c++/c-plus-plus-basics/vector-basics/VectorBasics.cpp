/*
Title: VectorBasics.cpp
Description: Creates three vector<float> objects. Fills the first two objects with 25 
			 floating-point numbers using a for loop as follows:
				 - fills the first vector object with the loop counter value
				 - fills the second vector object with the loop counter value squared
				 - a for loop adds the corresponding elements in the first two vectors,
				   and puts the result in the corresponding element of the third vector
			 Displays all three vectors using the format “for counter; element + element
			 = element”
Date: January 23rd, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively through the use of "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
#include <vector> // Vector usage
using namespace std;

int main() {
	vector<float> vCounter; // to hold counter values
	vector<float> vCounterSquared; // to hold counter squared values
	vector<float> vSum; // to hold sum of first two vector element values
	for(int i = 0; i < 25; i++) { // used to populate three vectors
		vCounter.push_back(i); // adds counter value at current element
		vCounterSquared.push_back(i * i); // adds counter squared value at current element
		vSum.push_back(vCounter[i] + vCounterSquared[i]); // adds sum of first two vectors at corresponding element
	} // for(i)
	for(int i = 0; i < vCounter.size(); i++) // used to display contents of vectors
		cout << i << "; " << vCounter[i] << " + " << vCounterSquared[i] << " = " << vSum[i] << endl; // displays result
}
