ObjectModeling.cpp - produces an output displaying a 3D house using a complex display list.

- Routines:
	- initialize() - called from main routine; sets background colour to white.
	- renderHouse() - called from display routine; renders the house in the display
				   through the use of a complex display list (house), which contains
				   separate display lists (groung, body, and top), which build each 
				   part of the house.
	- display(void) - assigned to glutDisplayFunc; sets glClear, gluLookAt, and
				   glPolygonMode (wire frame) before calling the renderHouse routine.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
