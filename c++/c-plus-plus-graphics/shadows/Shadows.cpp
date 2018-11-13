/*	Shadows.cpp
	
	This programs implements a recursive routine to produce a reflective effect, along with a
	proper shadow.  The implemented recursive method casts a ray from the ray source 
	to the scene. The ray either hits the wall (a non-reflective surface) or hits the floor (a 
	reflective surface). When it hits the wall, the method terminates the recursion and returns
	the local color of the wall. When the ray hits the floor, the method recursively invokes
	itself with the reflection ray, and calculates and return the mixed color.  The inclusion 
	test is implemented through an additional method - withinObject. The program hard-codes the 
	normal vector of the wall and the floor.  The program also checks whether each intersection 
	point in the recursion routine, when on the floor, can see the light source.  If it cannot, 
	the local color is mixed with the shadow color.

	@author: Dan Bonham
	@date: October 25th, 2015
*/

// headers necessary for the program
#include <iostream>
#include <algorithm>
#include <math.h>
#include "gl/glut.h"
#include "plane.h"

using namespace std; // sets namespace

// sets viewing angle
vector3 viewer(-40.0, 80.0, 160.0);

// defines floor settings
vector3 floorNormal(0.0, 1.0, 0.0);
plane   floorEquation(0.0, 4.0, 0.0, 0.0);
vector3 floorLimit1(-75.0, 0, -75.0);
vector3 floorLimit2(-75.0, 0, 75.0);
vector3 floorLimit3(75.0, 0, 75.0);
vector3 floorLimit4(75.0, 0, -75.0);

// defines wall settings
vector3 wallNormal(0.0, 0.0, 1.0);
plane   wall(0.0, 0.0, 4.0, 0.0);
vector3 wallLimit1(-25.0, 0.0, 0.0);
vector3 wallLimit2(-25.0, 50.0, 0.0);
vector3 wallLimit3(25.0, 50.0, 0.0);
vector3 wallLimit4(25.0, 0.0, 0.0);

// colors used in the program
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);
vector3 grey_white(0.9, 0.9, 0.9);

// lighting position
vector3 lightPosition(50, 50, 100);

// lighting elements used in the display calculations
float ambient_coef = 0.3;
float diffuse_coef = 0.7;
float reflect_coef = 0.4;
float local_coef   = 0.6;
float specular_coef = 0.3; // specular set to 1.0 - diffuse

int specularReflectionExponent = 100; // specular-reflection exponent

// initialize method
void initialize() {
	glClearColor(0.5, 0.7, 0.5, 0.0); // set background color

	// set the limits of the wall for inclusion testing
	wall.setP1(wallLimit1);
	wall.setP2(wallLimit2);
	wall.setP3(wallLimit3);
	wall.setP4(wallLimit4);

	// set the limits of the floor for inclusion testing
	floorEquation.setP1(floorLimit1);
	floorEquation.setP2(floorLimit2);
	floorEquation.setP3(floorLimit3);
	floorEquation.setP4(floorLimit4);
} // initialize()

// calculate local color - local color is intensity * base color
vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {
	// calculate unit vector
	vector3 origin = lightPosition.subtract(intersect);
	vector3 unitVec = origin.normalize(); // normalize unit vector

	// calculate dot product
	float dotProd = unitVec.dot(normal);

	// calculate reflection vector
	vector3 reflect = (normal.scalar(2*dotProd)).subtract(unitVec);
	vector3 reflectVec = reflect.normalize(); // normalize reflection vector

	// calculate viewer vector
	vector3 view = viewer.subtract(intersect);
	vector3 viewerVec = view.normalize(); // normalize viewer vector

	// calculate V dot R
	float dotProd2 = viewerVec.dot(reflectVec);

	// calculate intensity
	float ambientContr = ambient_coef; // ambient contribution
	float diffuseContr = diffuse_coef * dotProd; // diffuse contribution
	float specularContr = specular_coef * pow(dotProd2, specularReflectionExponent); // specular contribution
	float intensity = ambientContr + diffuseContr + specularContr; // total intensity

	if (intensity > 1.0) intensity = 1.0; // intensity cannot be greater than 1.0

	// calculate intensity of each of R, G, B
	float r = intensity * baseColor.x;
	float g = intensity * baseColor.y;
	float b = intensity * baseColor.z;

	return vector3(r,g,b); // returns color at current intersect
} // localColor()

// withinObject - calculates whether a point is within a plane
bool withinObject(vector3 point, plane object) {
	// tests the point against the plane bounaries
	if ( (point.x <= (max(max(object.p1x, object.p2x), max(object.p3x, object.p4x)) + .1)) && 
		 (point.x >= (min(min(object.p1x, object.p2x), min(object.p3x, object.p4x)) - .1)) &&
		 (point.y <= (max(max(object.p1y, object.p2y), max(object.p3y, object.p4y)) + .1)) && 
		 (point.y >= (min(min(object.p1y, object.p2y), min(object.p3y, object.p4y)) - .1)) &&
		 (point.z <= (max(max(object.p1z, object.p2z), max(object.p3z, object.p4z)) + .1)) && 
		 (point.z >= (min(min(object.p1z, object.p2z), min(object.p3z, object.p4z)) - .1)) )
		return true; // returns true if point is within plane
	else
		return false; // returns false if point is not within the plane
} // withinObject()

bool hasIntersection (vector3 origin, vector3 dir) {
	// Use the Incident Ray to find the nearest intersection
	vector3 fInt = floorEquation.intersect(origin, origin.add(dir)); // floor intersection
	vector3 wInt = wall.intersect(origin, origin.add(dir)); // wall intersection

	// checks whether given ry has an intersection in the scene
	if( (withinObject(wInt, wall) ) || (withinObject(fInt, floorEquation) ) )
		return true; // returns true if ray has intersection with plane in scene
	else
		return false; // returns false when no intersections
} //hasIntersection()

// rayTracer - recursive routine that is used to display scene
vector3 rayTracer(vector3 origin, vector3 dir, int cumulativeCalls) {
	// checks whether current ray requires further processing
	if ( (!hasIntersection(origin, dir)) || (cumulativeCalls > 1)  ) {
		return vector3(0.5, 0.7, 0.5); // returns background color
	} else { // additional data needed for current ray
		// Use the Incident Ray to find the nearest intersection
		vector3 fInt = floorEquation.intersect(origin, origin.add(dir)); // floor plane intersection
		vector3 wInt = wall.intersect(origin, origin.add(dir)); // wall plane intersection

		// tests for the ray's nearest intersection in the scene
		if( withinObject(wInt, wall) ) { // checks wall
			return localColor(wInt, lightRed, wallNormal); // gets local color at intersection point
		} else { // floor
			vector3 lColor =  localColor(fInt, grey, floorNormal); // gets local color at intersection point

			// Cast a ray from the intersection to the light sources
			vector3 lightRay = lightPosition.subtract(fInt);
			vector3 rayNorm = lightRay.normalize();

			// Find if there is any intersection point in between floor and light
			wInt = wall.intersect(fInt, fInt.add(rayNorm));
			if( (withinObject(wInt, wall)) ) { // tests for shadow
				lColor = lColor.scalar(ambient_coef);  // alters lColor to shadowed version
			} // if 

			vector3 reflectiveRay = dir.reflect(floorNormal); // Calculate reflective ray
			rayNorm = reflectiveRay.normalize(); // normalize reflective ray
		
			vector3 rColor = rayTracer(fInt, rayNorm, cumulativeCalls + 1); // Call Recursive Ray Tracer to get reflective color
			lColor = lColor.scalar(local_coef).add(rColor.scalar(reflect_coef)); // mixes local and reflection color

			return lColor; // returns color of current rectangle
		} // else
	} // else
} // colourContribution()

// render
void render() {
	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed to activate anti-aliasing
	glEnable(GL_BLEND); // needed to activate anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // specifies blending specifications

	// loops through each pixel in the display
	for (int m=-250; m<250; m++) {
		for(int n=-250; n<250; n++) {
			vector3 intersect = vector3(m, n, 0); // gets current intersect
			vector3 direction = intersect.subtract(viewer); // gets direction from viewer to intersect
			vector3 color = rayTracer(viewer, direction, 0); // gets color for current intersect

			glColor3f(color.x, color.y, color.z); // sets current color to that specified
			glRecti(m, n, m+1, n+1); // draws rectangle at current intersect
		} // for(n)
	} // for(m)
} // render

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

//	gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing angle

	render(); // calls render routine

	glutSwapBuffers(); //interchanges front/back refresh buffers
}// display(void)

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 250.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)


// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Shadows"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)


