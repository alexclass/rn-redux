DisplayOnPrompt.cpp - opens a (text) file, and displays the contents of that file one line at a time. After a line has been displayed, the program waits for the user to press the '<enter>' key before displaying the next line in the file.

- Program Purpose:
		Introduces C++ concepts such as the getline() function, getting input from the 
		user, and how to pause and wait for input
- Compile (assuming GNU C++ compiler): g++ DisplayOnPrompt.cpp -o DisplayOnPrompt
- Execution: DisplayOnPrompt.exe
- Notes: Only user input necessary is prompting for the next line of file content by 
		pressing <enter>.  Everything else necessary for this program is hardcoded
- Classes: None
- Variables:
  - inputFile - ifstream - used to store the file to be opened and whose contents
					are read in and displayed
  - line - string - used to store and display each line of contents from the file 
					as they are read in

Test Plan
- Normal Case 1:
	- Hard codes the file "80File.txt" to be opened/read-in/displayed
	- Should open correctly and display contents line by line as prompted by user
		- > This is the first line of the file. (press enter for next line)
		- > This is the second line of the file. (press enter for next line)
		- > This is the third line of the file. (press enter for next line)
		- > This is the fourth line of the file. (press enter for next line)
		- > This is the fifth line of the file. (press enter for next line)
		- > This is the sixth line of the file. (press enter for next line)
		- > This is the seventh line of the file. (press enter for next line)
		- > This is the eighth line of the file. (press enter for next line)
		- > This is the ninth line of the file. (press enter for next line)
		- > This is the tenth line of the file. (press enter for next line)
		- **All displayed correctly, prompt worked as expected
- Normal Case 2:
	- Hard codes the file "13File.txt" to be opened/read-in/displayed
	- Should open correctly and display contents line by line as prompted by user
		- > There are numerous words found in this file. (press enter for next line)
		- > (press enter for next line)
		- > The total number is 13. (press enter for next line)
		- **All displayed correctly, prompt worked as expected
- Normal Case 3:
	- Hard codes the file "WCFile.txt" to be opened/read-in/displayed
	- Should open correctly and display contents line by line as prompted by user
		- > This is line 1 (press enter for next line)
		- > This is line 2 (press enter for next line)
		- > This is line 3 (press enter for next line)
		- > This is line 4 (press enter for next line)
		- > This is line 5 (press enter for next line)
		- > This is line 6 (press enter for next line)
		- > This is line 7 (press enter for next line)
		- > This is line 8 (press enter for next line)
		- > This is line 9 (press enter for next line)
		- > This is line 10 (press enter for next line)
		- .
		- .
		- .
		- > This is line 101 (press enter for next line)
		- **All displayed correctly, prompt worked as expected
- Limit Data Case (empty file):
	- Hard codes the file "Empty.txt" to be opened/read-in/displayed
	- The file is empty, contains zero words, but should be handled correctly
		- > (press enter for next line)
		- **Works correctly, as do while loop is used to show program response
- Abnormal Data Case (non-existant file):
	- Hard codes the file "Phantom.txt" to be opened/read-in/displayed
	- The file doesn't exist, program should prompt once to show empty response
		- > (press enter for next line)
		- **Works correctly, as do while loop is used to show program response

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program attempts to open the provided (hard-coded) file, and proceeds
		to read in and display the contents line by line as prompted by the user
		via a do-while loop.
		If the file is not valid, the program simply displays an empty line followed
		by a single prompt to illustrate the program is running/responsive.
