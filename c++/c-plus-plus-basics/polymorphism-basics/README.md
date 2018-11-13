PolymorphismBasics.cpp - creates an inheritance hierarchy of Rodent: Mouse, Gerbil, Hamster, etc. In the base class, provides methods that are common to all Rodents, and refines these in the derived classes to perform different behaviours depending on the specific type of Rodent. Rodent is created as a pure abstract base class. Creates an array of pointers (10) to Rodent, and fills it with different specific types of Rodents. Calls the base class methods, and displays the results.

- Program Purpose:
		Introduces the C++ concepts of class hierarchies, inheritance, abstract
		functions, and polymorphism.
- Compile (assuming GNU C++ compiler): g++ PolymorphismBasics.cpp -o PolymorphismBasics
- Execution: PolymorphismBasics.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- Rodent - a pure abstract base class, which provides methods that are common to
				all subtypes of Rodents.
	- Mouse - derived from Rodent, refines each class from the base class to perform
				behaviours specific to a Mouse.
	- Gerbil - derived from Rodent, refines each class from the base class to perform
				behaviours specific to a Gerbil.
	- Hamster - derived from Rodent, refines each class from the base class to perform
				behaviours specific to a Hamster.
- Variables:
	- rp[] - Rodent* - an array of Rodent pointers which is populated with the three
			   different subtypes of Rodent to demonstrate polymorphism.

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations.
	- Should display output as required in program specification.
	- All testing built into program execution.
		- > I am a Mouse
		- > I eat cheese
		- > I am smelly
		- > I am social
		- > I am smart
		- > 
		- > I am a Gerbil
		- > I eat almonds
		- > I am fairly clean
		- > I am skittish
		- > I am hyperactive
		- 
		- > I am a Hamster
		- > I eat seeds
		- > I am dirty
		- > I am tempermental
		- > I am docile
		- > 
		- > I am a Mouse
		- > I eat cheese
		- > I am smelly
		- > I am social
		- > I am smart
		- > 
		- > I am a Gerbil
		- > I eat almonds
		- > I am fairly clean
		- > I am skittish
		- > I am hyperactive
		- > 
		- > I am a Hamster
		- > I eat seeds
		- > I am dirty
		- > I am tempermental
		- > I am docile
		- > 
		- > I am a Mouse
		- > I eat cheese
		- > I am smelly
		- > I am social
		- > I am smart
		- > 
		- > I am a Gerbil
		- > I eat almonds
		- > I am fairly clean
		- > I am skittish
		- > I am hyperactive
		- > 
		- > I am a Hamster
		- > I eat seeds
		- > I am dirty
		- > I am tempermental
		- > I am docile
		- > 
		- > I am a Mouse
		- > I eat cheese
		- > I am smelly
		- > I am social
		- > I am smart
		
**All output as expected

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The execution shows that although the pointers in the array are of type Rodent,
		the correct methods are called polymorphically based on the subtype created
		in each element of the array.
