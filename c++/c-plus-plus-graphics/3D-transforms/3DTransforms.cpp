/*	3DTransforms.cpp
	
	Produces an output containing a 3D scene in which there are eight houses of
	varying shape and size spread over a ground surface.  The eight houses are 
	produced using translation, scaling, and rotation performed on an initial
	protoype house.  Additionally, the ground portion of the scene has been 
	transformed to have an inverted z-axis to meet the specifications of the program
	requirements.

	@author: Dan Bonham
	@date: September 24th, 2015
*/

#include "stdafx.h"
#include "gl/glut.h" // glut header file

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color to white
	glColor3f(0.0, 0.0, 0.0); // sets default primitive colour to black
}// initialize()

// render the house in the display
void displayHouse() {
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
} // displayHouse()

// display registry
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix
	gluLookAt(3.0, 5.0, -12.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0); // sets viewing angle (inverts z axis)

	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed to activate anti-aliasing
	glEnable(GL_BLEND); // needed to activate anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // specifies blending specs

	glEnable(GL_DEPTH_TEST); // enables depth testing
	glDepthRange(0.0, 1.0); // inverted depth testing needed for inverted z-axis
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // sets polygon mode to front & back/fill

	// ground portion of the scene
	glPushMatrix(); // copies top matrix and stores in second position
	glBegin(GL_POLYGON); // begins definition of polygon representing the ground
		glColor3f(1.0, 0.0, 0.0); // sets color to red - easy ID of correct front-left position
		glVertex3f(-8.0, -0.1, -8.0); // front-left corner
		glColor3f(1.0, 1.0, 1.0); // sets color to white
		glVertex3f(8.0, -0.1, -8.0); // front-right corner
		glColor3f(0.0, 0.0, 1.0); // sets color to blue - easy ID of correct far-right position
		glVertex3f(8.0, -0.1, 8.0); // far-right corner
		glColor3f(1.0, 1.0, 1.0); // sets color to white
		glVertex3f(-8.0, -0.1, 8.0); // far-left corner
	glEnd(); // ends definition of ground
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at center of scene
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse();// calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at middle left of scene
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	glTranslatef(-4.0, 0.0, 0.0); // translates 4 units left
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at middle right of scene
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	glTranslatef(4.0, 0.0, 0.0); // translates 4 units right
	displayHouse();// calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back center of scene
	glPushMatrix(); // copies top matrix and stores in second position
	glScalef(1.5, 1.0, 1.0); // increases width by 1.5
	glTranslatef(0.0, 0.0, 5.0); // translates 5 units back
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back left of scene
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(-4.0, 0.0, 4.0); // translates 4 units back and left
	glScalef(0.75, 0.75, 0.75); // reduces size to 0.75 in all directions
	glRotatef(45.0, 0.0, 1.0, 0.0); // rotates house 45 degrees around y axis
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back right of display
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(5.0, 0.0, 5.0); // translates 5 units back and right
	glScalef(1.0, 2.0, 1.0); // increases height by factor of 2
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at front left of display
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(-4.0, 0.0, -4.0); // translates 4 units left and forward
	glScalef(2.0, 1.0, 1.0); // increases width by factor of 2
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at front right of display
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(3.0, 0.0, -4.0); // translates 3 units right and 4 forward
	glScalef(2.0, 1.0, 1.0); // increases width by factor of 2
	glTranslatef(1.0, 0.0, 0.0); // accounts for z inversion compared to original house model
	glRotatef(180.0, 0.0, 1.0, 0.0); // accounts for z inversion compared to original house model
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top
} // display()

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(1.0, -1.0, -1.0, 1.0, 1.5, 40.0); // sets frustum (alters x, accounts for inverted z view)
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // sets single buffer, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("3D Transformation and Projection"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)





