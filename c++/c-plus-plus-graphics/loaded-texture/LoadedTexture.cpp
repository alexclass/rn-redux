/*	LoadedTexture.cpp
	
	Adds a background texture to a program that produces an output containing a 3D 
	scene in which there are eight houses of varying shape and size spread over a 
	ground surface.  The eight houses are produced using translation, scaling, and 
	rotation performed on an initial protoype house.  Additionally, the ground portion 
	of the scene has been transformed to have an inverted z-axis to meet the specifications 
	of the program requirements.

	@author: Dan Bonham
	@date: October 20th, 2015
*/


#include "windows.h" // necessary for texture calculations
#include "gl/glut.h" // glut header file
#include "math.h" // necessary for texture calculations
#include <iostream> // necessary for I/O
#include <fstream> // necessary to load texture file
#include <string> // necessary for string manipulation

using namespace std; // sets namespace

// image
GLubyte *image;

GLubyte *l_texture;  // unsigned byte pointer for texture
BITMAPFILEHEADER fileheader; // used to hold bmp file header
BITMAPINFOHEADER infoheader; // used to hold bmp info header
RGBTRIPLE rgb; // used to hold RGB triple
GLuint texName; // texture name

// load and make image
void makeImage(void) {
	int i, j=0;
	FILE *l_file;
	string fn = "side.bmp";  // name of file used for texture
	const char *filename = fn.c_str();

	// open image file, return if error
	fopen_s(&l_file, filename, "rb");
	if (l_file == NULL) return;

	// read file header and header info
	fread(&fileheader, sizeof(fileheader), 1, l_file);
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	// allocate space for the image file
	l_texture = (GLubyte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

	// read da data
	j = 0;
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++) { 
		fread(&rgb, sizeof(rgb), 1, l_file); 
		l_texture[j+0] = (GLubyte) rgb.rgbtRed; // Red component
		l_texture[j+1] = (GLubyte) rgb.rgbtGreen; // Green component
		l_texture[j+2] = (GLubyte) rgb.rgbtBlue; // Blue component
		l_texture[j+3] = (GLubyte) 255; // Alpha value
		j += 4; // Go to the next position
	} // for(i)

	fclose(l_file); // Closes the file stream
} // makeImage(void)

// initialize
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // sets background color to white
	
	// image
	makeImage(); // calls makeImage routine
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage mode
	glGenTextures(1, &texName); // generates texture name
	glBindTexture(GL_TEXTURE_2D, texName); // binds texture to name

	// sets wrap and magnifying/minifying parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// set parameters for our 2D texture space
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		l_texture);
}// initialize()

// drawPicture routine
void drawPicture() {
	glEnable(GL_TEXTURE_2D); // enables texturing

	glBegin( GL_QUADS ); // sets texture on back wall
		glTexCoord2d(0.0,0.0); glVertex3f(-8.0, -0.1, 8.0); // bottom left
		glTexCoord2d(0.0,1.0); glVertex3f(-8.0, 16.0, 8.0); // top left
		glTexCoord2d(1.0,1.0); glVertex3f(8.0, 16.0, 8.0); // top right
		glTexCoord2d(1.0,0.0); glVertex3f(8.0, -0.1, 8.0); // bottom right
	glEnd();

	glBegin( GL_QUADS ); // sets texture on left wall
		glTexCoord2d(0.0,0.0); glVertex3f(-8.0, -0.1, -8.0); // front bottom
		glTexCoord2d(0.0,1.0); glVertex3f(-8.0, 16.0, -8.0); // front top
		glTexCoord2d(1.0,1.0); glVertex3f(-8.0, 16.0, 8.0); // back top
		glTexCoord2d(1.0,0.0); glVertex3f(-8.0, -0.1, 8.0); // back bottom
	glEnd();

	glBegin( GL_QUADS ); // sets texture on right wall
		glTexCoord2d(0.0,0.0); glVertex3f(8.0, -0.1, 8.0); // back bottom
		glTexCoord2d(0.0,1.0); glVertex3f(8.0, 16.0, 8.0); // back top
		glTexCoord2d(1.0,1.0); glVertex3f(8.0, 16.0, -8.0); // front top
		glTexCoord2d(1.0,0.0); glVertex3f(8.0, -0.1, -8.0); // front bottom
	glEnd();
} // drawPicture()

// renders the house prototype
void displayHouse() {
	// the ground section of the display
	GLuint ground = glGenLists(1); // assigns list identifier
	glNewList(ground, GL_COMPILE); // begins ground display list definition
		glColor3f(0.0, 1.0, 0.0); // sets colour to green
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
		glColor3f(1.0, 0.0, 0.0); // sets colour to red
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
		glColor3f(0.0, 0.0, 1.0); // sets colour to blue
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
		glTranslatef(0.0, 0.0, -1.0);
		glCallList(ground); // calls ground display list
		glPopMatrix(); // erases top matrix, moves previously copied to top

		glPushMatrix(); // copies top matrix and stores in second position
		//glTranslatef(0.0, 0.0, 2.0);
		glCallList(body); // calls body display list
		glPopMatrix(); // erases top matrix, moves previously copied to top

		glPushMatrix(); // copies top matrix and stores in second position
		//glTranslatef(0.0, 0.0, 2.0);
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
	gluLookAt(4.0, 4.0, -10.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0); // sets viewing angle (inverts z axis)

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
	displayHouse();// calls routine to render house

	// displays house at middle left of scene
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(-4.0, 0.0, 0.0); // translates 4 units left
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at middle right of scene
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(4.0, 0.0, 0.0); // translates 4 units right
	displayHouse();// calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back center of scene
	glPushMatrix(); // copies top matrix and stores in second position 
	glScalef(1.5, 1.0, 1.0); // increases width by 1.5
	glTranslatef(0.0, 0.0, 5.0); // translates 5 units back
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back left of scene
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(-4.0, 0.0, 4.0); // translates 4 units back and left
	glScalef(0.75, 0.75, 0.75); // reduces size to 0.75 in all directions
	glRotatef(45.0, 0.0, 1.0, 0.0); // rotates house 45 degrees around y axis
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at back right of display
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(5.0, 0.0, 5.0); // translates 5 units back and right
	glScalef(1.0, 2.0, 1.0); // increases height by factor of 2
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at front left of display
	glPushMatrix(); // copies top matrix and stores in second position 
	glTranslatef(-4.0, 0.0, -4.0); // translates 4 units left and forward
	glScalef(2.0, 1.0, 1.0); // increases width by factor of 2
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top

	// displays house at front right of display
	glPushMatrix(); // copies top matrix and stores in second position
	glTranslatef(3.0, 0.0, -4.0); // translates 3 units right and 4 forward
	glScalef(2.0, 1.0, 1.0); // increases width by factor of 2
	displayHouse(); // calls routine to render house
	glPopMatrix(); // erases top matrix, moves previously copied to top
	
	drawPicture(); // calls drawPicture routine

	glFlush(); // forces execution
	glutSwapBuffers(); //interchanges front/back refresh buffers
} // display()

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(1.0, -1.0, -1.0, 1.0, 1.5, 40.0); // sets frustum (accounts for inverted view)
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Loaded texture"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)







