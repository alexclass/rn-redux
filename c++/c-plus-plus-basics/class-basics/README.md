ClassBasics.cpp - creates a Text class that contains a string object to hold the text of a file. Gives it two constructors: a default constructor, and a constructor that takes a string argument that is the name of the file to open. When the second constructor is used, the file is opened and the contents of the file read into the string member object. A member function contents() returns the string so that it can be displayed. In main(), a file is opened using Text, and displays the contents.

- Program Purpose:
		Introduces the C++ concepts of classes, multiple constructors, member data and member 
		functions, and the use of a class to perform file manipulation.
- Compile (assuming GNU C++ compiler): g++ ClassBasics.cpp -o ClassBasics
- Execution: ClassBasics.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- Text - contains a string variable - fileInput - which stores the file that the class
			   will manipulate.  Also contains a contents() member function, a default constructor, 
			   and a constructor that accepts a string argument (name of file to be manipulated).
- Variables:
	- fileInput - string - member data from Text class, used to store name of file the 
				class will manipulate
	- inFile - ifstream  - in Text constructor, used to open/manipulate specified file
	- line - string - in Text constructor, used to read contents of the file and store it in
			   the Text member data fileInput
	- text - instance of Text class - used to store an instance of the Text class
	- contents - string - in main, holds the contents returned by the contents() member
			   function of the Text class

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification (reads DVDRentalList.txt file)
		- > Addicted R 1.75 Drama New 2.99 In-stock N/A N/A 48295730
		- > Predestination R 1.6 Action New 2.99 Rented BonhamD 02/15/2015 93681304
		- > Fury R 2.2 Action New 2.99 In-stock N/A N/A 73591279
		- > Lucy R 1.5 Action New 2.99 Rented SmithJ 02/17/2015 98765498
		- > Boyhood R 2.8 Drama New 2.99 Rented DoeJ 02/16/2015 78912843
		- > Laggies R 1.7 Comedy New 2.99 Rented BrownS 02/12/2015 45678765
		- > Alexander PG 1.4 Family New 2.99 In-stock N/A N/A 43564728
		- > Brave PG 1.6 Family Standard 1.99 Rented BrowningK 02/19/2015 32123465
		- > Dracula R 1.5 Action Standard 1.99 In-stock N/A N/A 87980934
		- > Divergent PG-13 2.3 Adventure Standard 1.99 Rented HanningL 02/18/2015 65676567

**All output as expected

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program defines a Text class, which is used to open, read, and store
		the contents of a specified file.
		In main, an instance of the Text class is created and used to display the 
		contents of a hardcoded file, "DVDRentalList.txt".
