/*	LightingAndMaterial.cpp
	
	This programs lights a sphere using OpenGL’s lighting features. It defines three 
	light sources originating from the top left corner, top right corner, and directly 
	behind the viewer. Each light source has the ability to shed a white, red, blue, 
	or green light, as selected by the user via a menu. In addition, three different 
	surface materials are available for selection for the sphere, as well as options 
	for choosing lighting elements, all via the menu. The menu system is activated by 
	clicking the right button of the mouse. The glutSolidSphere command is used to 
	generate the sphere.

	@author: Dan Bonham
	@date: October 17th, 2015
*/

#include "stdafx.h"
#include <stdlib.h> // standard library included for exit option
#include "gl/glut.h" // glut header

// lights
	GLfloat light_top_left[] = { -10.0, 10.0, 10.0, 0.0 }; // top right corner
	GLfloat light_top_right[] = { 10.0, 10.0, 10.0, 0.0 }; // top left corner
	GLfloat light_behind_viewer[] = { 0.0, 0.0, 10.0, 0.0 }; // behind viewer

	// different colored lights in the scene
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 }; // white light
	GLfloat green_light[] = {0.2, 1.0, 0.2, 1.0 }; // green light
	GLfloat red_light[] = { 1.0, 0.4, 0.4, 1.0 }; // red light
	GLfloat blue_light[] = { 0.2, 0.2, 1.0, 1.0 };	// blue light
	GLfloat black_light[] = { 0.0, 0.0, 0.0, 1.0 }; // black
	
	GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 }; // ambient light

// surface materials
	// gold
	GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };
	GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };
	GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };
	GLfloat gold_shininess[] = { 51.2 };

	// silver
	GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
	GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
	GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
	GLfloat silver_shininess[] = { 51.2 };

	// copper
	GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };
	GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };
	GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };
	GLfloat copper_shininess[] = { 51.2 };

// boolean flags used for light elements selection
	GLboolean diffuse = true; // holds whether diffuse element is active
	GLboolean specular = true; // holds whether specular element is active

// tracks current color of light - useful to track color when specular/diffuse are inactive
	GLfloat* light1Current = white_light; // holds current color setting of light 1
	GLfloat* light2Current = red_light; // holds current color setting of light 1
	GLfloat* light3Current = blue_light; // holds current color setting of light 3

// initialize
void initialize() {
	glClearColor(0.5, 0.7, 0.5, 0.0); // background colour

	glEnable(GL_DEPTH_TEST); // enable depth test
	glEnable(GL_LIGHTING); // enable lighting

	// initially enables the three lights in the scene
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// light 0 initial properties
	glLightfv(GL_LIGHT0, GL_POSITION, light_top_left); // sets to top left position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); // sets diffuse to white
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light); // sets specular to white

	// light 1 initial properties
	glLightfv(GL_LIGHT1, GL_POSITION, light_top_right); // sets to top right position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light); // sets diffuse to red
	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light); // sets specular to red

	// light 2 initial properties
	glLightfv(GL_LIGHT2, GL_POSITION, light_behind_viewer); // sets to behind viewer position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light); // sets diffuse to blue
	glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light); // sets specular to blue

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // sets ambient light

	// initial material settings for sphere are gold
	glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
} // initialize()



// render
void render() {
	glColor3f(0.75, 0.75, 0.75); // sets default color to grey

	glutSolidSphere(1.0, 64, 10); // generates sphere

	glPopMatrix(); // pops current matrix
} // render()

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing angle

	render(); // calls render routine

	glutSwapBuffers(); // interchanges front/back refresh buffers
} // display()



// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// color submenu for light 1
void light1ColorSubMenu(GLint option) {
	// switch handles user selection
	switch(option) {
		case 1: // turn light off
			glDisable(GL_LIGHT0);
			break;
		case 2: // sets color to white
			glEnable(GL_LIGHT0);
			light1Current = white_light; // stores current color setting
			break;
		case 3: // sets color to red
			glEnable(GL_LIGHT0);
			light1Current = red_light; // stores current color setting
			break;
		case 4: // sets color to blue
			glEnable(GL_LIGHT0);
			light1Current = blue_light; // stores current color setting
			break;
		case 5: // sets color to green
			glEnable(GL_LIGHT0);
			light1Current = green_light; // stores current color setting
	} // switch

	// adjusts light properties depending on current elements active
	if(diffuse && specular) { // all elements active (ambient, diffuse, specular)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Current);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light1Current);
	} else if (diffuse) // only diffuse and ambient active
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Current);

	glutPostRedisplay(); // redisplays
} // light1ColorSubMenu

// color submenu for light 2
void light2ColorSubMenu(GLint option) {
	// switch handles user selection
	switch(option) {
		case 1: // turn light off
			glDisable(GL_LIGHT1);
			break;
		case 2: // sets color to white
			glEnable(GL_LIGHT1);
			light2Current = white_light; // stores current color setting
			break;
		case 3: // sets color to red
			glEnable(GL_LIGHT1);
			light2Current = red_light; // stores current color setting
			break;
		case 4: // sets color to blue
			glEnable(GL_LIGHT1);
			light2Current = blue_light; // stores current color setting
			break;
		case 5: // sets color to green
			glEnable(GL_LIGHT1);
			light2Current = green_light; // stores current color setting
	} // switch

	// adjusts light properties depending on current elements active
	if(diffuse && specular) { // all elements active (ambient, diffuse, specular)
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Current);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light2Current);
	} else if (diffuse) // only diffuse and ambient active
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Current);

	glutPostRedisplay(); // redisplays
} // light2ColorSubMenu

// color submenu for light 2
void light3ColorSubMenu(GLint option) {

	// switch handles user selection
	switch(option) {
		case 1: // turn light off
			glDisable(GL_LIGHT2);
			break;
		case 2: // sets color to white
			glEnable(GL_LIGHT2);
			light3Current = white_light; // stores current color setting
			break;
		case 3: // sets color to red
			glEnable(GL_LIGHT2);
			light3Current = red_light; // stores current color setting
			break;
		case 4: // sets color to blue
			glEnable(GL_LIGHT2);
			light3Current = blue_light; // stores current color setting
			break;
		case 5: // sets color to green
			glEnable(GL_LIGHT2);
			light3Current = green_light; // stores current color setting
	} // switch

	// adjusts light properties depending on current elements active
	if(diffuse && specular) { // all elements active (ambient, diffuse, specular)
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light3Current);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light3Current);
	} else if (diffuse) // only diffuse and ambient active
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light3Current);

	glutPostRedisplay(); // redisplays
} // light3ColorSubMenu

// material submenu for sphere
void materialPropertiesSubMenu(GLint option) {

	// switch handles user selection
	switch(option) {
		case 1: // gold material selected
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
			render(); // calls render routine
			break;
		case 2: // silver material selected
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);
			render(); // calls render routine
			break;
		case 3: // copper material selected
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, copper_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, copper_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, copper_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, copper_shininess);
			render(); // calls render routine
	} // switch

	glutPostRedisplay(); // redisplays
} // materialsPropertiesSubMenu

// lights elements submenu
void lightElementsSubMenu(GLint option) {

	// handles user selection
	switch(option) {
		case 1: // only ambient option selected
			diffuse = false; // sets diffuse flag false
			specular = false; // sets specular flaf false

			// sets light 1 to reflect only ambient
			glLightfv(GL_LIGHT0, GL_DIFFUSE, black_light);
			glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);

			// sets light 2 to reflect only ambient
			glLightfv(GL_LIGHT1, GL_DIFFUSE, black_light);
			glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);

			// sets light 3 to reflect only ambient
			glLightfv(GL_LIGHT2, GL_DIFFUSE, black_light);
			glLightfv(GL_LIGHT2, GL_SPECULAR, black_light);

			break;
		case 2: // ambient and diffuse selected
			diffuse = true; // sets diffuse flag true
			specular = false; // sets specular flaf false

			// sets light 1 to reflect only ambient/diffuse
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Current);
			glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);

			// sets light 2 to reflect only ambient/diffuse
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Current);
			glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);

			// sets light 3 to reflect only ambient/diffuse
			glLightfv(GL_LIGHT2, GL_DIFFUSE, light3Current);
			glLightfv(GL_LIGHT2, GL_SPECULAR, black_light);

			break;
		case 3: // ambient, diffuse, and specular selected
			diffuse = true; // sets diffuse flag true
			specular = true; // sets specular flag true

			// sets light 1 to reflect ambient/diffuse/specular
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Current);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light1Current);

			// sets light 2 to reflect ambient/diffuse/specular
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light2Current);
			glLightfv(GL_LIGHT1, GL_SPECULAR, light2Current);

			// sets light 3 to reflect ambient/diffuse/specular
			glLightfv(GL_LIGHT2, GL_DIFFUSE, light3Current);
			glLightfv(GL_LIGHT2, GL_SPECULAR, light3Current);
	} // switch

	glutPostRedisplay(); // redisplays
} // lightElementsSubMenu

// main menu exit option
void mainMenu(GLint option) {
	
	// handles exit option on main menu
	if (option == 6)
		exit(0); // exits program
	glutPostRedisplay();
} // mainMenu

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Lighting Elements and Surface Materials"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	// all submenues for main menu
	GLint light1SubMenu;
	GLint light2SubMenu;
	GLint light3SubMenu;
	GLint materialSubMenu;
	GLint elementsSubMenu;

	initialize(); // calls initialize routine
	
	// sets light1SubMenu
	light1SubMenu = glutCreateMenu(light1ColorSubMenu);
		glutAddMenuEntry("Off", 1);
		glutAddMenuEntry("White Light", 2);
		glutAddMenuEntry("Red Light", 3);
		glutAddMenuEntry("Blue Light", 4);
		glutAddMenuEntry("Green Light", 5);
	
	// sets light2SubMenu
	light2SubMenu = glutCreateMenu(light2ColorSubMenu);
		glutAddMenuEntry("Off", 1);
		glutAddMenuEntry("White Light", 2);
		glutAddMenuEntry("Red Light", 3);
		glutAddMenuEntry("Blue Light", 4);
		glutAddMenuEntry("Green Light", 5);
	
	// sets light3SubMenu
	light3SubMenu = glutCreateMenu(light3ColorSubMenu);
		glutAddMenuEntry("Off", 1);
		glutAddMenuEntry("White Light", 2);
		glutAddMenuEntry("Red Light", 3);
		glutAddMenuEntry("Blue Light", 4);
		glutAddMenuEntry("Green Light", 5);

	// sets materialSubMenu
	materialSubMenu = glutCreateMenu(materialPropertiesSubMenu);
		glutAddMenuEntry("Gold", 1);
		glutAddMenuEntry("Silver", 2);
		glutAddMenuEntry("Copper", 3);

	// sets elementsSubMenu
	elementsSubMenu = glutCreateMenu(lightElementsSubMenu);
		glutAddMenuEntry("Ambient only", 1);
		glutAddMenuEntry("Ambient and Diffuse", 2);
		glutAddMenuEntry("Ambient, Diffuse, and Specular", 3);

	// creates main menu
	glutCreateMenu(mainMenu);
		glutAddSubMenu("Light 1", light1SubMenu);
		glutAddSubMenu("Light 2", light2SubMenu);
		glutAddSubMenu("Light 3", light3SubMenu);
		glutAddSubMenu("Material Properties", materialSubMenu);
		glutAddSubMenu("Light Elements", elementsSubMenu);
		glutAddMenuEntry("Quit", 6);

	glutAttachMenu(GLUT_RIGHT_BUTTON); // attaches menu to right mouse button

    glutMainLoop(); //  // displays initial graphics and puts program in infinite loop
} // main(int argc, char **argv)



