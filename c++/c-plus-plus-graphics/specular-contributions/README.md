SpecularContributions.cpp - produces an output which displays a red square, including a manual calculation of specular lighting.

- Routines:
	- initialize() - called from main routine; sets background colour.
	- localColor() - called from render routine; used to color each individual rectangle that makes
				   up the larger rectangle in the display.  Allows for a lighting model which 
				   achieves semi-realistic levels by using the intersect of each rectangle, the surface
				   normal of the rectangle, and the position of the light to calculate the ambient,
				   diffuse, and specular contributions at each unique position in the larger rectangle.
	- render() - called from display routine; two four loops are used to create a large red rectangle,
				   consisting of many smaller rectangles which are each coloured individually.  These
				   smaller rectangles allow for a semi-accurate lighting model.  Each rectangle is 
				   colored by calling the localColor routine.
	- display(void) - assigned to glutDisplayFunc; sets glClear, gluLookAt, before calling 
				   the renderHouse routine.  Swaps buffers before exiting.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
