DynamicStorage.cpp - introduces the C++ concepts of dynamic creation of storage, deleting that storage, and shows the required memory for different types.

- Program Purpose:
		Introduces the C++ concepts of dynamic creation of storage, deleting that
		storage, and shows the required memory for the different types
- Compile (assuming GNU C++ compiler): g++ DynamicStorage.cpp -o DynamicStorage
- Execution: DynamicStorage.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: None
- Variables:
	- size - int - used to store a single int value that is the size for the arrays
	- ip - int* - used to store a pointer to a single int value
	- lp - long* - used to store a pointer to a single long value
	- ca - char* - used to store a pointer to a char array with 100 elements
	- fa - float* - used to store a pointer to a float array with 100 elements

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification
	- Dynamically creates pieces of storage of the following types using new: int, long, an array of 100 chars, and an array of 100 floats. Prints the addresses and values of these using the format: “type @ <address>= <value>”. After printing all the addresses and values, frees the storage using delete. Fills the char array using copies of the lowercase and uppercase alphabet (a-z, A-Z), and fills the float array using sequential numbers starting with 101.
		- > int @ <5772088> = <59>
		- > long @ <5772136> = <123456>
		- > charArray[0] @ <5770984> = \<a\>
		- > charArray[1] @ <5770985> = \<b\>
		- > charArray[2] @ <5770986> = \<c\>
		- > charArray[3] @ <5770987> = \<d\>
		- > charArray[4] @ <5770988> = \<e\>
		- > charArray[5] @ <5770989> = \<f\>
		- > charArray[6] @ <5770990> = \<g\>
		- > charArray[7] @ <5770991> = \<h\>
		- > charArray[8] @ <5770992> = \<i\>
		- > charArray[9] @ <5770993> = \<j\>
		- > .
		- > .
		- > .
		- > charArray[90] @ <5771074> = \<M\>
		- > charArray[91] @ <5771075> = \<N\>
		- > charArray[92] @ <5771076> = \<O\>
		- > charArray[93] @ <5771077> = \<P\>
		- > charArray[94] @ <5771078> = \<Q\>
		- > charArray[95] @ <5771079> = \<R\>
		- > charArray[96] @ <5771080> = \<S\>
		- > charArray[97] @ <5771081> = \<T\>
		- > charArray[98] @ <5771082> = \<U\>
		- > charArray[99] @ <5771083> = \<V\>
		- > floatArray[0]  @ <5771096> = <101>
		- > floatArray[1]  @ <5771100> = <102>
		- > floatArray[2]  @ <5771104> = <103>
		- > floatArray[3]  @ <5771108> = <104>
		- > floatArray[4]  @ <5771112> = <105>
		- > floatArray[5]  @ <5771116> = <106>
		- > floatArray[6]  @ <5771120> = <107>
		- > floatArray[7]  @ <5771124> = <108>
		- > floatArray[8]  @ <5771128> = <109>
		- > floatArray[9]  @ <5771132> = <110>
		- > .
		- > .
		- > .
		- > floatArray[90]  @ <5771456> = <191>
		- > floatArray[91]  @ <5771460> = <192>
		- > floatArray[92]  @ <5771464> = <193>
		- > floatArray[93]  @ <5771468> = <194>
		- > floatArray[94]  @ <5771472> = <195>
		- > floatArray[95]  @ <5771476> = <196>
		- > floatArray[96]  @ <5771480> = <197>
		- > floatArray[97]  @ <5771484> = <198>
		- > floatArray[98]  @ <5771488> = <199>
		- > floatArray[99]  @ <5771492> = <200>

**All output as expected
***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program creates an int, a long, an array of 100 chars, and an array of
		100 floats and displays the address and value for each data element.
		The char array is fileed with alternating copies of the lowercase and
		uppercase alphabet, while the float array contains sequential numbers from
		101 to 200.
		After all required information has been displayed, all data is deleted.
