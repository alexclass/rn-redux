PrimeNumbers.cpp - uses two nested for loops and the modulus operator (%) to detect and print the prime numbers from 1 to 10,000. Displays all the primes found.

- Program Purpose:
		Introduces the C++ concepts of boolean variables, nested for loops, and
		the modulus operator
- Compile (assuming GNU C++ compiler): g++ PrimeNumbers.cpp -o PrimeNumbers
- Execution: PrimeNumbers.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: None
- Variables:
  - prime - boolean - used to flag prime numbers inside nested for loops

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification
		- > 2 is prime.
		- > 3 is prime.
		- > 5 is prime.
		- .
		- .
		- .
		- > 9787 is prime.
		- > 9791 is prime.
		- > 9803 is prime.
		- > 9811 is prime.
		- > 9817 is prime.
		- > 9829 is prime.
		- > 9833 is prime.
		- > 9839 is prime.
		- > 9851 is prime.
		- > 9857 is prime.
		- > 9859 is prime.
		- > 9871 is prime.
		- > 9883 is prime.
		- > 9887 is prime.
		- > 9901 is prime.
		- > 9907 is prime.
		- > 9923 is prime.
		- > 9929 is prime.
		- > 9931 is prime.
		- > 9941 is prime.
		- > 9949 is prime.
		- > 9967 is prime.
		- > 9973 is prime.

**All output as expected
***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program used nested for loops, an if statement, and a boolean variable to
		flag and display all the prime numbers up to 10,000.
