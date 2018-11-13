3DTransforms.cpp - produces an output containing a 3D scene in which there are eight houses of varying shape and size spread over a ground surface, each of which have been transformed.

- Routines:
	- initialize() - called from main routine; sets background colour to white and
				   primitive colour to black.
	- displayHouse() - called from display routine; renders each house in the display
				   through the use of a complex display list (house), which contains
				   separate display lists (groung, body, and top), which build each 
				   part of the house.
	- display(void) - assigned to glutDisplayFunc; sets glClear, an identity
				   matrix, and gluLookAt.  Activates anti-aliasing and depth-testing.
				   Sets polygon mode to fill before building the ground portion of
				   the scene and successively calling the renderHouse routine, after 
				   appropriate individual transformations have been applied for each 
				   house, to create the scene.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
