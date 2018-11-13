WordsInFile.cpp - opens a file, counts the # of whitespace-separated words in that file, and displays the result.

- Program Purpose:
		Introduces C++ concepts such as opening a file, using a while loop, getting
		input from the opened file, and counting.
- Compile (assuming GNU C++ compiler): g++ WordsInFile.cpp -o WordsInFile
- Execution: WordsInFile.exe
- Notes: No user input required, everything necessary for this program is hardcoded
- Classes: None
- Variables:
	- inputFile - ifstream - used to store the file to be opened and whose words
					are counted
	- word - string - used to store each whitespace-separated word as they are 
					read in from the file
	- count - int - used to store the # of whitespace-separated words in the file

Test Plan
- Normal Case 1:
	- Hard codes the file "13File.txt" to be opened/counted
	- Should open correctly and count 13 words
		- > The total # of whitespace-separated words in the file is 13
- Normal Case 2:
	- Hard codes the file "80File.txt" to be opened/counted
	- Should open correctly and count 80 words
		- > The total # of whitespace-separated words in the file is 80
- Normal Case 3:
	- Hard codes the file "WCFile.txt" to be opened/counted
	- Should open correctly and count 404 words
		- > The total # of whitespace-separated words in the file is 404
- Limit Data Case (empty file):
	- Hard codes the file "Empty.txt" to be opened/counted
	- The file is empty, contains zero words, but should be handled correctly
		- > The total # of whitespace-separated words in the file is 0
- Abnormal Data Case (non-existant file):
	- Hard codes the file "Phantom.txt" to be opened/counted
	- The file doesn't exist, program should display that there are 0 words
		- > The total # of whitespace-separated words in the file is 0

Discussion:
		As this is meant to introduce a few basics, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program attempts to open the provided (hard-coded) file, and proceeds
		to count the number of whitespace-separated words in the file via a while
		loop.
		If the file is not valid, the program simply displays that the number of 
		words in the file is 0.
