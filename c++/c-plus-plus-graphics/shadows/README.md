Shadows.cpp - produces an output that takes shadows into account, implemented through recursive ray tracing.

- Routines:
	- initialize() - called from main routine; sets the background colour and the limits of
				   both the floor and the wall - necessary for inclusion testing.
	- localColor() - called from rayTracer routine; used to color each individual rectangle that makes
				   up the display as a whole.  Allows for a lighting model which achieves semi-
				   realistic levels by using the intersect of each rectangle, the surface
				   normal of the rectangle, and the position of the light to calculate the ambient,
				   diffuse, and specular contributions at each unique position in the display.
	- withinObject() - called from rayTracer routine; is passed an intersection point and an
				   object plane, returns a boolean value specifying whether or not the given point is
				   within the given plane.
	- hasIntersection() - called from rayTracer routine; takes a ray's origin and direction and tests
				   to see whether the ray intersects any of the planes in the scene.  Returns a bool
				   value specifying the result.  Used by recursive routine as a control on recursion
				   - rays without intersection should not continue recursion.
	- rayTracer() - called from render routine; a recursive routine which is used to determine the color 
				   for each pixel in the display.  Incorporates intersection testing (which objects in 
				   the secene), reflection testing, and shadow testing to determine the correct color mix
				   at each pixel.
	- render() - called from display routine; activates anti-aliasing, before performing loop that contains
				   each pixel in the display.  At each pixel calls the recursive routine that determines
				   the display color of the pixel through ray tracing. Draws rectangle at each pixel 
				   position with color specified by ray tracing.
	- display(void) - assigned to glutDisplayFunc; sets glClear, gluLookAt, and
				   loads an identity matrix, before calling the render routine.  Makes a 
				   call to glutSwapBuffers before exiting.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
