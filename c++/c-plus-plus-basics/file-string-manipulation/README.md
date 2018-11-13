FileStringManipulation.cpp - introduces the C++ concepts of file and string manipulation, including the use of getline().

- Program Purpose:
		Introduces the C++ concepts of file and string manipulation, including
		the use of getline().
- Compile (assuming GNU C++ compiler): g++ FileStringManipulation.cpp -o FileStringManipulation
- Execution: FileStringManipulation.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: None
- Variables:
	- aString - string array sized for 100 lines - used to store 100 lines
				  of file content
	- inputFile - ifstream - used to store the file to be opened and whose contents
					are read in and displayed

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification:
		- Creates an array of 100 string objects. Fills the array by opening a (text) 
		- file, and reading one line of the file into each string until the array is
	 	- filled. Displays the array using the format “line #: <string>”, where # is 
		- the actual line number, and <string> is the stored string.
		- > line 0: This is line 1
		- > line 1: This is line 2
		- > line 2: This is line 3
		- .
		- .
		- .
		- > line 77: This is line 78
		- > line 78: This is line 79
		- > line 79: This is line 80
		- > line 80: This is line 81
		- > line 81: This is line 82
		- > line 82: This is line 83
		- > line 83: This is line 84
		- > line 84: This is line 85
		- > line 85: This is line 86
		- > line 86: This is line 87
		- > line 87: This is line 88
		- > line 88: This is line 89
		- > line 89: This is line 90
		- > line 90: This is line 91
		- > line 91: This is line 92
		- > line 92: This is line 93
		- > line 93: This is line 94
		- > line 94: This is line 95
		- > line 95: This is line 96
		- > line 96: This is line 97
		- > line 97: This is line 98
		- > line 98: This is line 99
		- > line 99: This is line 100
		
**All output as expected (offset because array starts at 0)
***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program uses a for loop to populate the string array with 100 lines of
		content from the provided file.
		A second for lop is then used to display the contents of the array.
