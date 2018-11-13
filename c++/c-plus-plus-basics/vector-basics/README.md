VectorBasics.cpp - introduces the C++ concept of the vector and demonstrates a few of its associated functions.

- Program Purpose:
		Introduces the C++ concept of the vector and demonstrates a few of its
		associated functions
- Compile (assuming GNU C++ compiler): g++ VectorBasics.cpp -o VectorBasics
- Execution: VectorBasics.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: None
- Variables:
  - vCounter - vector<float> - used to store loop counter values
  - vCounterSquared - vector<float> - used to store loop counter squared values
  - vSum - vector<float> - used to store sum of each element of previous vectors

Test Plan
- Normal Case 1:
  - Runs program as constituted, without any alterations
  - Should display output as required in program specification:
  - Creates three vector<float> objects. Fills the first two objects with 25 floating-point numbers using a for loop as follows:
	- fills the first vector object with the loop counter value
	- fills the second vector object with the loop counter value squared
	- a for loop adds the corresponding elements in the first two vectors, and puts the result in the corresponding element of the third vector
	- Displays all three vectors using the format “for counter; element + element = element”
		- > 0; 0 + 0 = 0
		- > 1; 1 + 1 = 2
		- > 2; 2 + 4 = 6
		- > 3; 3 + 9 = 12
		- > 4; 4 + 16 = 20
		- > 5; 5 + 25 = 30
		- > 6; 6 + 36 = 42
		- > 7; 7 + 49 = 56
		- > 8; 8 + 64 = 72
		- > 9; 9 + 81 = 90
		- > 10; 10 + 100 = 110
		- > 11; 11 + 121 = 132
		- > 12; 12 + 144 = 156
		- > 13; 13 + 169 = 182
		- > 14; 14 + 196 = 210
		- > 15; 15 + 225 = 240
		- > 16; 16 + 256 = 272
		- > 17; 17 + 289 = 306
		- > 18; 18 + 324 = 342
		- > 19; 19 + 361 = 380
		- > 20; 20 + 400 = 420
		- > 21; 21 + 441 = 462
		- > 22; 22 + 484 = 506
		- > 23; 23 + 529 = 552
		- > 24; 24 + 576 = 600
		- **All output as expected
***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrayes that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program populates the three vectors, as specified, in a single for loop.
		Following the population of the three vectors, a second for loop is used to
		display the results in the format specified.
