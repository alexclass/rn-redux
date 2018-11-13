LightingAndMaterial.cpp - produces an output displaying a sphere whose lighting and surface material can be customized using a provided menu (accessed by a right-click).

- Routines:
	- initialize() - called from main routine; sets background colour, enables depth testing
				   /lighting/3 lights used in the scene, and sets the initial properties of
				   the 3 lights, along with the ambient lighting and the default material
				   used for the sphere (gold).
	- render() - called from display routine; sets the default primirive color to grey, 
				   builds the sphere, and then pops the current matrix.
	- display(void) - assigned to glutDisplayFunc; sets glClear, gluLookAt, and
				   loads an identity matrix, before calling the render routine.  Makes a 
				   call to glutSwapBuffers before exiting.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- light1ColorSubMenu(GLint option) - called from main, uses a switch to provide/select
				   light color options for the submenu.  Depending on the current light
				   settings (ambient, diffuse, specular) eithers stores the selection or
				   stores and sets the selected option for the scene.  Calls glutPostRedisplay
				   before exiting.
	- light2ColorSubMenu(GLint option) - see light1ColorSubMenu description.
	- light3ColorSubMenu(GLint option) - see light1ColorSubMenu description.
	- materialPropertiesSubMenu(GLint option) - called from main, uses a switch to provide/
				   select the sphere's material options for the submenu.  Depending on
				   the selection, updates the sphere material to either gold, silver, or
				   bronze.  Calls glutPostRedisplay before exiting.
	- lightElementsSubMenu(GLint option) - called from main, uses a switch to provide/display
				   the light element options for the submenu.  Updates the light properties
				   to reflect the user selection.  Calls glutPostRedisplay before exiting.
	- mainMenu(GLint option) - called from main, handles the main menu's exit selection, by
				   exiting the program.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   then assigns routines to the glutDisplayFunc and glutReshapeFunc,
				   creates the menu and all submenus and attaches the menu to the 
				   right mouse button, before calling the initialize routine and then 
				   looping for any input.
