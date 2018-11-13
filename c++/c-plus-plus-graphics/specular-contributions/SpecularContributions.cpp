/*	SpecularContributions.cpp
	
	This programs adds the specular contribution to the calculation of lighting intensity for
	an existing program, which displays a red square (made up of smaller squares) in the middle 
	of the screen, and which previously only computed the ambient and diffuse contributions.  The
	light in the scene comes from the front top right corner.

	@author: Dan Bonham
	@date: October 19th, 2015
*/


#include "stdafx.h"
#include <iostream> // input/output - debugging
#include <math.h> // used for color contribution calculations
#include "gl/glut.h" // glut header file
#include "vector3.h" // vector3 header - used for intersects, colors, normals

using namespace std; // sets namespace

// sets viewing position
vector3 viewer(0.0, 0.0, 100.0);

// sets surface normal of the wall - used for color contributions
vector3 wallNormal(0.0, 0.0, 1.0);

// colors used in the scene
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);

// sets lighting position
vector3 lightPosition(10, 10, 10);

// lighting elements cefficients
float ambient_coef = 0.3;
float diffuse_coef = 0.7;
float specular_coef = 0.3; // specular set to 1.0 - diffuse

int specularReflectionExponent = 2; // specular-reflection exponent

// initialize
void initialize() {
	// set background color
	glClearColor(0.5, 0.7, 0.5, 0.0);
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
	//vector3 reflect = unitVec.reflect(normal);
	vector3 reflectVec = reflect.normalize(); // normalize reflection vector

	// calculate viewer vector
	vector3 view = viewer.subtract(intersect);
	vector3 viewerVec = view.normalize(); // normalize viewer vector

	// calculate V dot R
	//vector3 viewerVec = viewer.normalize();
	float dotProd2 = viewerVec.dot(reflectVec);

	// calculate intensity
	float ambientContr = ambient_coef; // ambient contribution
	float diffuseContr = diffuse_coef * dotProd; // diffuse contribution
	float specularContr = specular_coef * pow(dotProd2, specularReflectionExponent); // specular contribution
	float intensity = ambientContr + diffuseContr + specularContr; // total intensity
	//float intensity = ambientContr + diffuseContr;

	if (intensity > 1.0) intensity = 1.0; // intensity cannot be greater than 1.0

	// calculate intensity of each of R, G, B
	float r = intensity * baseColor.x;
	float g = intensity * baseColor.y;
	float b = intensity * baseColor.z;

	return vector3(r,g,b); // returns color at current intersect
} // localColor()

// render
void render() {
	// render the square - loops create large rectangle through many smaller rectangles
	for (int m=-25; m<25; m++) {
		for(int n=-25; n<25; n++) {
			vector3 color = localColor(vector3(m,n,0), lightRed, wallNormal); // gets color for each rectangle

			glColor3f(color.x, color.y, color.z); // sets unique color for each rectangle

			glRecti(m, n, m+1, n+1); // draws each individual rectangle
		} // for(n)
	} // for (m)
} // render()

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

	//gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

	int windowHandle = glutCreateWindow("Calculate Specular Contribution"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)



