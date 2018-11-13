ColouringAndShading.cpp - produces an output displaying a cube with various colours by setting the four vertices to red, green, blue, and yellow, respectively.

- Routines:
	- initialize() - called from main routine; sets background colour to white and
				   primitive colour to black.
	- renderColourCube() - called from display routine; activates anti-aliasing
				   before rendering the colour cube with specified attributes.
				   De-activates anti-aliasing before ending.
	- display(void) - assigned to glutDisplayFunc; sets glClear, an identity
				   matrix, and gluLookAt before calling renderColourCube routine.
				   Calls glutSwapBuffers before ending.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
