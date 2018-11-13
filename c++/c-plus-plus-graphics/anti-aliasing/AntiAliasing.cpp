/*	AntiAliasing.cpp
	
	Produces an output containing two houses, which are each a combination of
	a triangle and a rectangle.  Each house is rendered in its own separate 
	routine.  The lower house in the output is drawn using an anti-aliasing
	technique, while the upper house does not make use of anti-aliasing.

	@author: Dan Bonham
	@date: September 17th, 2015
*/

#include "StdAfx.h"
#include "gl/glut.h" // glut header file

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color
	glColor3f(0.0, 0.0, 0.0); // sets the primitive color to black
}// initialize()


// render upper house - no anti-aliasing
void renderUpperHouse() {
	// the triangle roof
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.825, 4.3); // top-point vertex of roof
		glVertex2f(-2.575, 2.8); // left-base vertex of roof
		glVertex2f(1.425, 3.8); // right-base vertex of roof
	glEnd();

	// the square house body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-2.075, 2.925); // top-left vertex of body
		glVertex2f(-1.325, -0.075); // bottom-left vertex of body
		glVertex2f(1.675, 0.675); // bottom-right vertex of body
		glVertex2f(0.925, 3.675); // top-right vertex of body
	glEnd();
}// renderUpperHouse()

// render lower house - with anti-aliasing
void renderLowerHouse() {
	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed to activate anti-aliasing
	glEnable(GL_BLEND); // needed to activate anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // specifies blending specifications

	// the triangle roof
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.375, -0.5); // top-point vertex of roof
		glVertex2f(-1.375, -2.0); // left-base vertex of roof
		glVertex2f(2.625, -1.0); // right-base vertex of roof
	glEnd();

	// the square house body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.875, -1.875); // top-left vertex of body
		glVertex2f(-0.125, -4.875); // bottom-left vertex of body
		glVertex2f(2.875, -4.125); // bottom-right vertex of body
		glVertex2f(2.125, -1.125); // top-right vertex of body
	glEnd();

	glDisable(GL_LINE_SMOOTH); // disables anti-aliasing
}// renderUpperHouse()

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // viewing

	renderUpperHouse(); // renders house without anti-aliasing
	renderLowerHouse(); // renders house with anti-aliasing

	glutSwapBuffers(); //interchanges front/back refresh buffers
}// display(void)

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Anti-Aliasing"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)

