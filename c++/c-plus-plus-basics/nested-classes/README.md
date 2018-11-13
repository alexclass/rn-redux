NestedClasses.cpp - Creates a Hen class. Inside this class, it nests a Nest class. Inside Nest, an Egg class is placed. Each class should have a display() member function. For each class, a constructor and a destructor is created that prints an appropriate message when called. In main(), an instance of each class is created using new, and a call to the display() function is made for each one. After display() is called, the storage is freed using delete.

- Program Purpose:
		Introduces the C++ concepts of classes, nested classes, constructors, destructors,
		and the deletion of clas objects.
- Compile (assuming GNU C++ compiler): g++ NestedClasses.cpp -o NestedClasses
- Execution: NestedClasses.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- Hen - contains a display() function, a constructor, and a destructor.  Also contains a nested class called Nest
	- Nest - contains a display() function, a constructor, and a destructor.  Also contains a nested class called Egg
	- Egg - contains a display() function, a constructor, and a destructor.
- Variables:
	- hen - Hen* - used to store a pointer to a dynamically created Hen object
	- nest - Hen::Nest* - used to store a pointer to a dynamically created Nest object
	- egg - Hen::Nest::Egg* - used to store a pointer to a dynamically created Egg object
  
Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations
	- Should display output as required in program specification
		- > Inside Hen constructor.
		- > Inside Nest constructor.
		- > Inside Egg constructor.
		- > Displaying instance of Hen class.
		- > Displaying instance of Nest class.
		- > Displaying instance of Egg class.
		- > Inside Hen deconstructor.
		- > Inside Nest deconstructor.
		- > Inside Egg deconstructor.

**All output as expected

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The program defines a Hen class, which has a nested Nest class, which in turn
		has a nested Egg class.
		Each of these classes have their own display() member function, as well as a 
		constructor and destructor, all of which display messages when called.
		In main, an instance of each object is created, displayed, and then deleted.
