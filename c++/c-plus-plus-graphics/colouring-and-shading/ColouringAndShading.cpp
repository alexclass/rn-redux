/*	ColouringandShading.cpp
	
	This program displays a cube with various colours by setting the four 
	vertices to red, green, blue, and yellow, respectively.

	@author: Dan Bonham
	@date: September 18th, 2015
*/

#include "stdafx.h"
#include "gl/glut.h" // glut header file

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color to white
	glColor3f(0.0, 0.0, 0.0); // sets the primitive color to black
}// initialize()

// render lower house - with anti-aliasing
void renderColourCube() {
	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed for anti-aliasing
	glEnable(GL_BLEND); // needed for anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // sets blending specs

	// the square house
	glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0); // sets current colour to green
		glVertex2f(-2.5, 2.5); // sets top-left (green) vertex
		glColor3f(1.0, 0.0, 0.0); // sets current colour to red
		glVertex2f(-2.5, -2.5); // sets bottom-left (red) vertex
		glColor3f(1.0, 1.0, 0.0); // sets current colour to yellow
		glVertex2f(2.5, -2.5); // sets bottom-right (yellow) vertex
		glColor3f(0.0, 0.0, 1.0); // sets current colour to blue
		glVertex2f(2.5, 2.5); // sets top-right (blue) vertex
	glEnd();

	glDisable(GL_LINE_SMOOTH); // disables anti-aliasing
}// renderUpperHouse()

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // sets what can be used with glClear
	glLoadIdentity(); // loads identity matrix
	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing

	renderColourCube(); // calls routine to display colour cube

	glutSwapBuffers(); // swaps front/depth buffers
}// display(void)

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport
	glMatrixMode(GL_PROJECTION); // sets projection mode
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets modelview mode
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // initializes GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets front/depth buffers, RGB colour scheme, depth buffer
	glutInitWindowSize(500, 500); // sets display window size
	glutInitWindowPosition(100, 100); // sets display window position

	int windowHandle = glutCreateWindow("Colouring and Shading"); // creates display window with title
	glutSetWindow(windowHandle); // sets display window to that created immediately above

	glutDisplayFunc(display); // sets routine that specifies picture for display window
	glutReshapeFunc(reshape); // sets routine to handle modifications to display window size

	initialize(); // calls initialization routine
	
	glutMainLoop(); // displays initial graphics and infinitely loops for interaction
}// main(int argc, char **argv)





