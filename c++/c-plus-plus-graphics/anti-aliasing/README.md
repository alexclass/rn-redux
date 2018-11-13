AntiAliasing.cpp - produces an output containing two houses, which are each a combination of a triangle and a rectangle, to demonstrate the result of anti-aliasing.

- Routines:
	- initialize() - called from main routine; sets background colour to white and
				   primitive colour to black.
	- renderUpperHouse() - called from display routine; renders the house in the upper
				   part of the display, without using anti-aliasing.
	- renderLowerHouse() - called from display routine; renders the house in the lower
				   part of the display, using anti-aliasing.
	- display(void) - assigned to glutDisplayFunc; sets glClear, an identity
				   matrix, and gluLookAt before successively calling the renderUpperHouse
				   and renderLowerHouse routines.
				   Calls glutSwapBuffers before ending.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
