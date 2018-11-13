TemplateBasics.cpp - uses the Standard C++ Library vector as an underlying implementation to create a Set template class that accepts only one of each type of object that is put into it. Makes a nested iterator class that supports the “end sentinel” concept. Includes test code in main(), using both the program Set template class and the Standard C++ Library set template to verify that the behaviour is correct.

- Program Purpose:
		Introduces the C++ concepts templates, iterators, nested iterators, and end sentinels.
- Compile (assuming GNU C++ compiler): g++ TemplateBasics.cpp -o TemplateBasics
- Execution: TemplateBasics.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- Set - template <class T> - Uses the Standard C++ Library vector as an underlying 
			 implementation, a class that accepts only one of each type of object that 
			 you put into it.
	- iterator - nested in Set class, used to traverse the objects in a Set, supports
			 the "end sentinel" concept.
- Variables:
	- v - vector<T> - in Set, used to store the collection of objects
	- s - Set& - in iterator, used to store the Set reference the iterator works on
	- index - int - in iterator, used to store current position in the set while being
			manipulated by the iterator

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations.
	- Should display output as required in program specification.
	- All testing built into program execution.
		- > Custom Set Empty: 1
		- > Library Set Empty: 1
		- > Custom Set Size: 0
		- > Library Set Size: 0
		- > Custom Set Empty: 0
		- > Library Set Empty: 0
		- > Custom Set Size: 10
		- > Library Set Size: 10
		- > Custom Set Size (after redundant insert attempt): 10
		- > Library Set Size (after redundant insert attempt): 10
		- > Custom set: 0
		- > Custom set: 1
		- > Custom set: 2
		- > Custom set: 3
		- > Custom set: 4
		- > Custom set: 5
		- > Custom set: 6
		- > Custom set: 8
		- > Custom set: 9
		- > Library set: 0
		- > Library set: 1
		- > Library set: 2
		- > Library set: 3
		- > Library set: 4
		- > Library set: 5
		- > Library set: 6
		- > Library set: 8
		- > Library set: 9
		- > Custom set: 5
		- > Custom set: 6
		- > Custom set: 8
		- > Custom set: 9

**All output as expected

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The execution tests each of the methods built in to the custom Set class and 
		compares the results of each with the set class from the C++ library.
		Furthermore, the nested iterator is tested for required functionality.
