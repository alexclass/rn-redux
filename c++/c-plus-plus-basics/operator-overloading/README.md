OperatorOverloading.cpp - creates a simple class (DoStuff) containing an int, and overloads the operator+ as a member function. Also, provides a print() member function that takes an ostream& as an argument and prints to that ostream&. Adds a binary operator- and operator+ to the class as member functions. Allows use of the objects in complex expressions such as a + b – c. Adds the operator++ and operator--, both prefix and postfix versions. Overloads the << operator to provide the same functionality as the print() member function.

- Program Purpose:
		Introduces the C++ concept of operator overloading.
- Compile (assuming GNU C++ compiler): g++ OperatorOverloading.cpp -o OperatorOverloading
- Execution: OperatorOverloading.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- DoStuff - contains all necessary elements to fulfill the program description
- Variables:
	- i - int - used to store the int that is operated on by all the member functions

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations.
	- Should display output as required in program specification.
	- All testing built into program execution - all overloaded operators inherently tested and correct execution confirmed in output.
	- Output in file "OpOv.txt" also confirms print() method working.
	-Console:
		- > Initial value of ds: [i] = 0
		- > In unary operator+
		- > After unary operator+ (has no effect): [i] = 0
		- > After binary operator+ 5 (ds = ds + 5): [i] = 5
		- > After binary operator- 2 (ds = ds - 2): [i] = 3
		- > After testing complex expression (ds = ds[3] + ds2[2] - ds3[4]: [i] = 1
		- > Calling ++ds (prefix): [i] = 2
		- > Value after call: [i] = 2
		- > Calling ds++ (postfix): [i] = 2
		- > Value after call: [i] = 3
		- > Calling --ds (prefix): [i] = 2
		- > Value after call: [i] = 2
		- > Calling ds-- (postfix): [i] = 2
		- > Value after call: [i] = 1

**All output as expected
		- "OpOv.txt":
		- > i = 0

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program defines several overloaded operators on a simple class which contains
		a single int data member.  The overloaded operators are all defined as member functions,
		except for the "operator<<" which is a friend function.
		Each of the overloaded operators performs its computations on the int data member
		of the DoStuff class.
