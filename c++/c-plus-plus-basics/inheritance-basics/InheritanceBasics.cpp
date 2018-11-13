// reference used: http://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object
// reference used: http://www.cplusplus.com/reference/cmath/sqrt/
// reference used: http://stackoverflow.com/questions/9424173/c-find-the-smallest-amongst-3-numbers

/*
Title: InheritanceBasics.cpp
Description: Creates a class hierarchy for simple geometry. Starts with a Point class to 
	     hold x and y values of a point. Overloads the << operator to print point 
	     values, and the + and – operators to add and subtract point coordinates.
	     Creates a pure abstract base class Shape, which forms the basis of shapes. 
	     The Shape class contains abstract functions to calculate area and circumference 
	     of the shape, plus provides the coordinates (Points) of a rectangle that 
	     encloses the shape (a bounding box). These are overloaded by the derived 
	     classes. Creates a display() function that displays the name of the class, 
	     and all stored information about the class (including area, circumference, 
	     and bounding box). Builds a hierarchy by creating the Shape classes Circle, 
	     Square, and Triangle. For these derived classes, default constructors, and 
	     constructors whose arguments can initialize the shapes appropriately using 
	     the correct number of Point objects are created.  In main(), creates one 
	     instance each of the following: Circle (10, -5) with a radius of 23; Square 
	     (5, -5)(-10,7)(4,23)(-6,12); and Triangle(0,0)(10,10)(-15,15). Displays the 
	     information from each object.
Date: March 28th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written using information from "Thinking in C++" by Bruce Eckel
#include <iostream> // Stream declarations
#include <typeinfo> // in order to use typeid to determine class type
#include <math.h> // for various mathematical functions used
#include <algorithm> // for mathematical functions used
using namespace std;

class Point {
	int x; // x-coordinate of the point
	int y; // y-coordinate of the point
public:
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) {} // constructor with specified coords
	friend ostream& operator<<(ostream& os, Point p) { // overloaded operator prints point
		return os << "Point = (" << p.x << ", " << p.y << ")";
	}
	const Point operator+(const Point& right) const { // overloaded operator allows addition
		return Point(x + right.x, y + right.y);
	}
	const Point operator-(const Point& right) const { // overloaded operator allows subtraction
		return Point(x - right.x, y - right.y);
	}
	int getX() const { return x; } // accessor method for x
	int getY() const { return y; } // accessor method for y
};

class Shape {
public:
	virtual double area() const = 0; // overloaded by derived classes
	virtual double circumference() const = 0; // overloaded by derived classes
	virtual Point* coordinates() const = 0; // overloaded by derived classes
	//virtual void display() const = 0;
	void display() const { // Displays all information of given shape
		cout << "This is a " << typeid(*this).name() << endl;
		cout << "It's area is: " << area() << endl;
		cout << "It's circumference is: " << circumference() << endl;
		Point* pa = coordinates();
		cout << "It's bounding box is: " << pa[0] << ", " << pa[1] << ", " << pa[2] << ", " << pa[3] << endl;
		cout << endl;
	}
};

class Circle : public Shape {
	Point center; // center point of circle
	int radius; // radius of circle
public:
	Circle() : center(0, 0), radius(10) {} // default constructor
	Circle(Point p, int r) : center(p), radius(r) {} // constructor with specified info
	double area() const { //calculates/returns area of a circle
		return 3.1415926535897 * (radius * radius);
	}
	double circumference() const { // calculates/returns circumference of a circle
		return 2 * 3.1415926535897 * radius;
	}
	Point* coordinates() const { // calculates/returns bounding box of circle
		Point* pa = new Point[4];
		pa[0] = center + Point(radius, radius);
		pa[1] = center + Point(radius, -radius);
		pa[2] = center - Point(radius, radius);
		pa[3] = center - Point(radius, -radius);
		return pa;
	}
	/*void display() const {
		cout << "This is the Circle class" << endl;
		cout << "It's center point is: " << center << endl;
		cout << "It's radius is: " << radius << endl;
		cout << "It's area is: " << area() << endl;
		cout << "It's circumference is: " << circumference() << endl;
		Point* pa = coordinates();
		cout << "It's bounding box is: " << pa[0] << ", " << pa[1] << ", " << pa[2] << ", " << pa[3] << endl;
		cout << endl;
	}*/
};

class Square : public Shape {
	Point vertices1; // 1st coordinate of square
	Point vertices2; // 2nd coordinate of square
	Point vertices3; // 3rd coordinate of square
	Point vertices4; // 4th coordinate of square
public:
	// default constructor
	Square() : vertices1(-1,0), vertices2(0,1), vertices3(1,0), vertices4(0,-1) {}
	// constructor with specified coordinates
	Square(Point v1, Point v2, Point v3, Point v4) : vertices1(v1), vertices2(v2), vertices3(v3), vertices4(v4) {}
	double area() const { // calculates/returns area of square
		return abs(((vertices1.getX()*vertices2.getY() - vertices1.getY()*vertices2.getX()) +
					(vertices2.getX()*vertices3.getY() - vertices2.getY()*vertices3.getX()) +
					(vertices3.getX()*vertices4.getY() - vertices3.getY()*vertices4.getX()) +
					(vertices4.getX()*vertices1.getY() - vertices4.getY()*vertices1.getX())) / 2);
	}
	double circumference() const { // calculates/returns circumference of square
		Point s1 = vertices1 - vertices2; // difference between vertices
		Point s2 = vertices2 - vertices3; // difference between vertices
		Point s3 = vertices3 - vertices4; // difference between vertices
		Point s4 = vertices4 - vertices1; // difference between vertices
		return sqrt(pow(s1.getX(),2) + pow(s1.getY(),2)) + sqrt(pow(s2.getX(),2) + pow(s2.getY(),2)) +
			   sqrt(pow(s3.getX(),2) + pow(s3.getY(),2)) + sqrt(pow(s4.getX(),2) + pow(s4.getY(),2));
	}
	Point* coordinates() const { // calculates/returns bounding box of square
		// determines max/min of all points for both x and y coordinates
		int minX = min(min(min(vertices1.getX(), vertices2.getX()), vertices3.getX()), vertices4.getX());
		int maxX = max(max(max(vertices1.getX(), vertices2.getX()), vertices3.getX()), vertices4.getX());
		int minY = min(min(min(vertices1.getY(), vertices2.getY()), vertices3.getY()), vertices4.getY());
		int maxY = max(max(max(vertices1.getY(), vertices2.getY()), vertices3.getY()), vertices4.getY());
		// determines bounding box
		Point* pa = new Point[4];
		pa[0] = Point(maxX, maxY);
		pa[1] = Point(maxX, minY);
		pa[2] = Point(minX, minY);
		pa[3] = Point(minX, maxY);
		return pa;
	}
	/*void display() const {
		cout << "This is the Square class" << endl;
		cout << "It's vertices are: " << vertices1 << ", " << vertices2 << ", " << vertices3 << ", " << vertices4 << endl;
		cout << "It's area is: " << area() << endl;
		cout << "It's circumference is: " << circumference() << endl;
		Point* pa = coordinates();
		cout << "It's bounding box is: " << pa[0] << ", " << pa[1] << ", " << pa[2] << ", " << pa[3] << endl;
		cout << endl;
	}*/
};

class Triangle : public Shape {
	Point vertices1; // 1st coordinate of triangle
	Point vertices2; // 2nd coordinate of triangle
	Point vertices3; // 3rd coordinate of triangle
public:
	// default constructor
	Triangle() : vertices1(0, 1), vertices2(1, -1), vertices3(-1, -1) {}
	// constructor with specified coordinates
	Triangle(Point v1, Point v2, Point v3) : vertices1(v1), vertices2(v2), vertices3(v3) {}
	double area() const { // calculates/returns area of triangle
		Point s1 = vertices1 - vertices3; // difference between points
		Point s2 = vertices2 - vertices3; // difference between points
		return (s1.getX() * s2.getY() - s1.getY() * s2.getX()) / 2;
	}
	double circumference() const { // calculates/returns circumference of triangle
		Point s1 = vertices1 - vertices2; // difference between points
		Point s2 = vertices2 - vertices3; // difference between points
		Point s3 = vertices3 - vertices1; // difference between points
		return sqrt(pow(s1.getX(),2) + pow(s1.getY(),2)) + sqrt(pow(s2.getX(),2) + pow(s2.getY(),2)) +
			   sqrt(pow(s3.getX(),2) + pow(s3.getY(),2));
	}
	Point* coordinates() const { // calculates/returns bounding box of triangle
		// determines max/min of all points for both x and y coordinates
		int minX = min(min(vertices1.getX(), vertices2.getX()), vertices3.getX());
		int maxX = max(max(vertices1.getX(), vertices2.getX()), vertices3.getX());
		int minY = min(min(vertices1.getY(), vertices2.getY()), vertices3.getY());
		int maxY = max(max(vertices1.getY(), vertices2.getY()), vertices3.getY());
		// determines bounding box
		Point* pa = new Point[4];
		pa[0] = Point(maxX, maxY);
		pa[1] = Point(maxX, minY);
		pa[2] = Point(minX, minY);
		pa[3] = Point(minX, maxY);
		return pa;
	}
	/*void display() const {
		cout << "This is the Triangle class" << endl;
		cout << "It's vertices are: " << vertices1 << ", " << vertices2 << ", " << vertices3 << endl;
		cout << "It's area is: " << area() << endl;
		cout << "It's circumference is: " << circumference() << endl;
		Point* pa = coordinates();
		cout << "It's bounding box is: " << pa[0] << ", " << pa[1] << ", " << pa[2] << ", " << pa[3] << endl;
		cout << endl;
	}*/
};

int main() {
	Circle circle(Point(10, -5), 23); // creates circle specified in requirements
	circle.display(); // displays circle info
	// Points must be passed in clockwise order to negate crossing
	Square square(Point(5,-5), Point(-10,7), Point(-6,12), Point(4,23)); // creates specified square
	square.display(); // displays square
	Square square2; // creates default square for further testing
	square2.display(); // displays square
	Triangle triangle(Point(0,0), Point(10,10), Point(-15,15)); // creates specified triangle
	triangle.display(); // displays triangle
}