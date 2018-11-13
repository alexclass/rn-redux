/*	2DTransforms.cpp
	
	This program displays five identical houses in a semi-circle arc.
	The program has one routine to render each house. Each house is
	transformed (translated and rotated) to its desired orientation,
	before this routine is called to render it.

	

	@author: Dan Bonham
	@date: September 17th, 2015
*/

#include "stdafx.h"
#include "gl/glut.h" // glut header file

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color
	glColor3f(0.0, 0.0, 0.0); // sets the primitive color to black
}// initialize()

// render lower house - with anti-aliasing
void renderHouse() {
	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed for anti-aliasing
	glEnable(GL_BLEND); // needed for anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // sets blending specs

	// the triangle roof
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0, 2.75); // roof-point vertex
		glVertex2f(-0.55, 2.5); // left roof-base vertex
		glVertex2f(0.55, 2.5); // right roof-base vertex
	glEnd();

	// the square house body
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.4, 2.5); // top-left house body vertex
		glVertex2f(-0.4, 1.75); // bottom-left roof body vertex
		glVertex2f(0.4, 1.75); // bottom-right roof body vertex
		glVertex2f(0.4, 2.5); // top-right roof body vertex
	glEnd();

	glDisable(GL_LINE_SMOOTH); // disables anti-aliasing
}// renderUpperHouse()

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used with glClear
	glLoadIdentity(); // loads identity matrix

	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing specs

	// Sets location for first house and calls rendering routine
	glTranslatef(-2.0, -0.25, 0.0); // translates from origin
	glRotatef(45.0, 0.0, 0.0, 1.0); // rotates on z-axis from origin
	renderHouse(); // calls routine to render house at current position

	// Sets location for second house and calls rendering routine
	glTranslatef(1.0, -0.25, 0.0); // translates from position of previous house
	glRotatef(-22.5, 0.0, 0.0, 1.0); // rotates on z-axis from previous house
	renderHouse(); // calls routine to render house at current position

	// Sets location for third house and calls rendering routine
	glTranslatef(1.0, -0.25, 0.0); // translates from position of previous house
	glRotatef(-22.5, 0.0, 0.0, 1.0); // rotates on z-axis from previous house
	renderHouse(); // calls routine to render house at current position

	// Sets location for fourth house and calls rendering routine
	glTranslatef(1.0, -0.25, 0.0); // translates from position of previous house
	glRotatef(-22.5, 0.0, 0.0, 1.0); // rotates on z-axis from previous house
	renderHouse(); // calls routine to render house at current position

	// Sets location for fifth house and calls rendering routine
	glTranslatef(1.0, -0.25, 0.0); // translates from position of previous house
	glRotatef(-22.5, 0.0, 0.0, 1.0); // rotates on z-axis from previous house
	renderHouse(); // calls routine to render house at current position

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
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets front/depth buffers, RGB colour mode, depth buffer
		glutInitWindowSize(500, 500); // sets display window size
		glutInitWindowPosition(100, 100); // sets display window position

		int windowHandle = glutCreateWindow("2D Graphics Transformation"); // creates display window with specified title
		glutSetWindow(windowHandle); // sets display window to that created immediately above

		glutDisplayFunc(display); // assigns routine to display picture
		glutReshapeFunc(reshape); // assigns routine to handle display window size modifications

		initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop checking for input
}// main(int argc, char **argv)



