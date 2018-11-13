2DTransforms.cpp - produces an output containing five identical houses, which have each been transformed to different desired orientations.

- Routines:
	- initialize() - called from main routine; sets background colour to white and
				   primitive colour to black.
	- renderHouse() - called from display routine; activates anti-aliasing
				   before rendering a house at the current position.
				   De-activates anti-aliasing before ending.
	- display(void) - assigned to glutDisplayFunc; sets glClear, an identity
				   matrix, and gluLookAt. Performs five consecutive transformations
				   - a translation followed by a rotation - in combination with calls
				   to renderHouse to display the required scene.
				   Calls glutSwapBuffers before ending.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
