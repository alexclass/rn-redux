InheritanceBasics.cpp - creates a class hierarchy for simple geometry. Starts with a Point class to hold x and y values of a point. Overloads the << operator to print point values, and the + and – operators to add and subtract point coordinates.Creates a pure abstract base class Shape, which forms the basis of shapes. The Shape class contains abstract functions to calculate area and circumference of the shape, plus provides the coordinates (Points) of a rectangle that encloses the shape (a bounding box). These are overloaded by the derived classes. Creates a display() function that displays the name of the class, and all stored information about the class (including area, circumference, and bounding box). Builds a hierarchy by creating the Shape classes Circle, Square, and Triangle. For these derived classes, default constructors, and constructors whose arguments can initialize the shapes appropriately using the correct number of Point objects are created.  In main(), creates one instance each of the following: Circle (10, -5) with a radius of 23; Square (5, -5)(-10,7)(4,23)(-6,12); and Triangle(0,0)(10,10)(-15,15). Displays the information from each object.

- Program Purpose:
		Introduces the C++ concepts of class hierarchies, inheritance, abstract
		functions, composition, and other related topics.
- Compile (assuming GNU C++ compiler): g++ InheritanceBasics.cpp -o InheritanceBasics
- Execution: InheritanceBasics.exe
- Notes: No user input is necessary, everything for this program is hardcoded
- Classes: 
	- Point - holds x and y values of a point. Overloads the << operator to print 
				point values, and the + and – operators to add and subtract point 
				coordinates. 
	- Shape (base class) - forms the basis of shapes. Contains abstract functions 
				to calculate area and circumference of the shape, plus provides the 
				coordinates (Points) of a rectangle that encloses the shape (a bounding 
				box). These are overloaded by the derived classes. Creates a display() 
				function that displays the name of the class, and all stored information 
				about the class (including area, circumference, and bounding box).
	- Circle  (derived from Shape) - contains a default constructor and a constructor 
				whose arguments can initialize the circle appropriately using a Point 
				center and a radius.
	- Square (derived from Shape) - contains a default constructor and a constructor 
				whose arguments can initialize the square appropriately using four 
				Point vertices.
	- Triangle (derived from Shape) - contains a default constructor and a constructor 
				whose arguments can initialize the triangle appropriately using three 
				Point vertices.
- Variables:
	- x - int - Point class, used to store x-coordinate of a Point
	- y - int - Point class, used to store y-coordinate of a Point
	- center - Point - Circle class, used to store center Point of a circle
	- radius - int - Circle class, used to store the radius of a circle
	- pa - Point* - each derived Shape class, used to store bounding box of shape
	- vertices1 - Point - Square/Triangle class, used to store 1st Point of a shape
	- vertices2 - Point - Square/Triangle class, used to store 2nd Point of a shape
	- vertices3 - Point - Square/Triangle class, used to store 3rd Point of a shape
	- vertices4 - Point - Square class, used to store 4th Point of a square
	- minX - int - Square/Triangle class, used to store the minimum x-coordinate 
				among the points that make up the shape, used to determine bounding 
				box
	- maxX - int - Square/Triangle class, used to store the maximum x-coordinate 
				among the points that make up the shape, used to determine bounding 
				box
	- minY - int - Square/Trisngle class, used to store the minimum y-coordinate 
				among the points that make up the shape, used to determine bounding 
				box
	- maxY - int - Square/Triangle class, used to store the maximum x-coordinate 
				among the points that make up the shape, used to determine bounding box
	- s1 - Point - Square/Triangle class, used to store the difference between the 1st
			and 2nd vertices, used in calculating circumference
	- s2 - Point - Square/Triangle class, used to store the difference between the 2nd
				and 3rd vertices, used in calculating circumference
	- s3 - Point - Square/Triangle class, used to store the difference between the 3rd
				and 4th vertices, used in calculating circumference
	- s4 - Point - Square class, used to store the difference between the 4th
				and 1st vertices, used in calculating circumference

Test Plan
- Normal Case 1:
	- Runs program as constituted, without any alterations.
	- Should display output as required in program specification.
	- All testing built into program execution.
		- > This is a 6Circle
		- > It's area is: 1661.9
		- > It's circumference is: 144.513
		- > It's bounding box is: Point = (33, 18), Point = (33, -28), Point = (-13, -28), P
		- > oint = (-13, 18)
		- 
		- > This is a 6Square
		- > It's area is: 207
		- > It's circumference is: 68.4964
		- > It's bounding box is: Point = (5, 23), Point = (5, -5), Point = (-10, -5), Point
		- >  = (-10, 23)
		- 
		- > This is a 6Square
		- > It's area is: 2
		- > It's circumference is: 5.65685
		- > It's bounding box is: Point = (1, 1), Point = (1, -1), Point = (-1, -1), Point =
		- >  (-1, 1)
		- 
		- > This is a 8Triangle
		- > It's area is: 150
		- > It's circumference is: 60.8504
		- > It's bounding box is: Point = (10, 15), Point = (10, 0), Point = (-15, 0), Point
		- >  = (-15, 15)

**All output as expected

***As this program is completely hardcoded, there is no user input at all, there are no
further cases to test.  The above demonstrates that the program works as required.

Discussion:
		As this is an introductory program, much of the C++ functionality to 
		write an elegant program, with adequate error-handling, has not yet been
		introduced.  As such, this program is completely hard-coded and does not
		contain error-handling capabilities.
		The execution shows the results of al specuified calculations on the shapes
		specified in the program description.  All calculations are correct as when
		compared to manual calculations performed independent of the program.
		A second shape object is present, as the coordinates specified for the square
		in the program specifications does not actually form a square, to demonstrate
		that the required calculations do indeed work on an actual square.
		**In order for the area and circumference of a square to be calculated correctly,
		the coordinates of the shape must be entered in an order that forms a polygon
		without any crossing adges.
