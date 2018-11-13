/*	ObjectModeling.cpp
	
	Produces the display of a 3D house using a complex display list.  The entire object 
	has three components: the ground (green), the body (red), and the top (blue).  The 
	ground is a simple rectangle, the body is a cube consisting of six squares, and the 
	top is a pyramid consisting of four triangles. Rendering of the pyramid’s base (a square) 
	is not included.  The local coordinates of the far-left-lower and near-right-upper 
	corners of the body are {0,0,0}, and {1,1,1}, respectively. The coordinates of the 
	far-left and near-right corners of the pyramid are {-0.2, 1.0, -0.2} and {1.2, 1.0, 1.2}, 
	respectively. The coordinate of the tip of the pyramid is {0.5, 1.5, 0.5}. The far-left 
	and near-right corners of the ground are at {-1.0, 0.0, -0.5} and {2.0, 0.0, 2.5}, 
	respectively.  The command glPolygonMode sets the polygon as wire frame, while the 
	command gluLookAt is used to set the proper view of the object.

	@author: Dan Bonham
	@date: September 22nd, 2015
*/

#include "stdafx.h"
#include "gl/glut.h" // glut header file

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color
}// initialize()

// render the house in the display
void renderHouse() {
	// the ground section of the display
	GLuint ground = glGenLists(1); // assigns list identifier
	glNewList(ground, GL_COMPILE); // begins ground display list definition
		glColor3f(0.0, 0.8, 0.0); // sets colour to green
		glBegin(GL_POLYGON); // begins output primitive (ground) definition
			glVertex3f(-1.0, 0.0, -0.5); // far-left corner
			glVertex3f(-1.0, 0.0, 2.5); // near-left corner
			glVertex3f(2.0, 0.0, 2.5); // near-right corner
			glVertex3f(2.0, 0.0, -0.5); // far-right corner
		glEnd(); // ends output primitive (ground) definition
	glEndList(); // ends ground display list definition

	// the body section of the house
	GLuint body = glGenLists(1); // assigns list identifier
	glNewList(body, GL_COMPILE); // begins body display list definition
		glColor3f(0.8, 0.0, 0.0); // sets colour to red
		typedef GLint vertex3 [3]; // defines a data type - three int vertex
		vertex3 pt[8] = { {0, 0, 0}, {1, 0, 0},
						  {0, 0, 1}, {1, 0, 1},
						  {0, 1, 0}, {1, 1, 0},
						  {0, 1, 1}, {1, 1, 1} }; // assigns the 8 body vertices to array
		glEnableClientState(GL_VERTEX_ARRAY); // activates vertex-array feature of OpenGL
		glVertexPointer(3, GL_INT, 0, pt); // specifies location/data format for vertex coords
		GLubyte vertIndex[] = {6, 2, 3, 7, 5, 1, 0, 4, 7, 3, 1, 5,
							   4, 0, 2, 6, 2, 0, 1, 3, 7, 5, 4, 6}; // sets vertex order for display
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex); // displays body portion of house
	glEndList(); // ends body display list definition

	// the top section of the house
	GLuint top = glGenLists(1); // assigns list identifier
	glNewList(top, GL_COMPILE); // begins top display list definition
		glColor3f(0.0, 0.0, 0.8); // sets colour to blue
		typedef GLfloat vertices3 [3]; // defines data type - three float vertex
		vertices3 pts[5] = { {0.5, 1.5, 0.5}, {-0.2, 1.0, -0.2},
						   {-0.2, 1.0, 1.2}, {1.2, 1.0, 1.2},
						   {1.2, 1.0, -0.2} }; // assigns 5 top vertices to array
		glVertexPointer(3, GL_FLOAT, 0, pts); // specifies location/data format for vertex coords
		GLubyte vertsIndex[] = {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1}; // sets vertex order for display
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, vertsIndex); // displays top portion of house
	glEndList(); // ends top display list definition
	
	// complex display list to display scene
	GLuint house = glGenLists(1); // assigns list identifier
	glNewList(house, GL_COMPILE); // begins house display list definition
		glPushMatrix(); // copies top matrix and stores in second position
		glCallList(ground); // calls ground display list
		glPopMatrix(); // erases top matrix, moves previously copied to top

		glPushMatrix(); // copies top matrix and stores in second position
		glCallList(body); // calls body display list
		glPopMatrix(); // erases top matrix, moves previously copied to top

		glPushMatrix(); // copies top matrix and stores in second position
		glCallList(top); // calls top display list
		glPopMatrix(); // erases top matrix, moves previously copied to top
	glEndList(); // ends house display list definition

	glCallList(house); // calls house - complex display list

	glFlush(); // forces execution of functions
}

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

	gluLookAt(3.75, 3.5, 7.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing angle

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // sets polygon mode to front & back/wireframe
	renderHouse(); // calls renderHouse routine

	glutSwapBuffers(); //interchanges front/back refresh buffers
}// display(void)

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Object Modeling"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)






