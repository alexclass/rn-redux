InlineFunctions.cpp - creates a const whose value is determined at runtime by reading the time when the program starts. In a separate function, creates two arrays of 10 000 doubles. Initializes the first array with sequential integral values starting with 100, and initializes the second array with the same numbers, but in reverse order.  Loops through both arrays using a single loop, multiplying the corresponding array elements from each array together, and displays the result. Reads the time when the program completes the multiplication, then computes and displays the elapsed time. Uses inline functions.

- Program Purpose:
		Introduces the C++ concepts of inline functions, consts, the ctime library and 
		its functions, and timing the execution of a program.
- Compile (assuming GNU C++ compiler): g++ InlineFunctions.cpp -o InlineFunctions
- Execution: InlineFunctions.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- ExecutionTime - contains all variables/functions (defined below) necessary for the program
- Variables:
	- sequentialArray - double array - used in ExecutionTime class to store
					10,000 sequential values starting with 100
	- reverseArray - double array - used in the ExecutionTime class to store 10,000
					numbers in reverse order from 10,099 and down
	- startTime - const time_t  - used in ExecutionTime class to store the time the program begins
	- endTime - time_t - used in ExecutionTime class to store the time the program completes
					its computation

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification
		- > result[0]: 1.0099e+006
		- > result[1]: 1.0199e+006
		- > result[2]: 1.02989e+006
		- .
		- .
		- .
		- > result[9978]: 1.21944e+006
		- > result[9979]: 1.20948e+006
		- > result[9980]: 1.19952e+006
		- > result[9981]: 1.18956e+006
		- > result[9982]: 1.17959e+006
		- > result[9983]: 1.16963e+006
		- > result[9984]: 1.15966e+006
		- > result[9985]: 1.14969e+006
		- > result[9986]: 1.13972e+006
		- > result[9987]: 1.12974e+006
		- > result[9988]: 1.11977e+006
		- > result[9989]: 1.10979e+006
		- > result[9990]: 1.09981e+006
		- > result[9991]: 1.08983e+006
		- > result[9992]: 1.07984e+006
		- > result[9993]: 1.06986e+006
		- > result[9994]: 1.05987e+006
		- > result[9995]: 1.04988e+006
		- > result[9996]: 1.03989e+006
		- > result[9997]: 1.02989e+006
		- > result[9998]: 1.0199e+006
		- > result[9999]: 1.0099e+006
		- > Elapsed time = 4 seconds.

**All output as expected, however, there as no difference in terms of execution
		between this program using inline functions, and the program which
		did not use inline functions.  This was not as I expected at all.

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program defines several inline functions: (1) getEndTime() to return a time_t value that 
		reflects the time the method was called, (2) createArrays() to create two arrays
		of 10,000 doubles whose elements are each multiplied together and the result
		displayed, (3) performCalculation which calculates the product of each of the array
		elements, and (4) timeDifference() which takes two time_t values and returns the
		difference between the two times.
		In main, a const value is determined at runtime which reflects the time that the 
		program starts, the createArrays() method is then called to perform its required
		computations.  After this method returns, the program determines the time that
		the computations completed and then calculates and displays the total length of time
		the program took to execute.
