LoadedTexture.cpp -  - produces an output containing a 3D scene, which includes a texture loaded as the background.

- Routines:
	- makeImage() - called from initialize routine; responsible for loading the image file
				   and making the image that will be used for the texture in the scene.			   
	- initialize() - called from main routine; sets background colour to white, calls the 
				   makeImage routine, generates and binds the texture, and sets all necessary
				   texture parameters.
	- drawPicture() - called from display routine; enables texturing and then uses quads to
				   apply the texture, previously created, to the back wall of the scene and the
				   two side walls of the scene.  This is accomplished by attaching the 
				   appropriate texture coordinates to the corresponding vertices of each
				   quad.
	- displayHouse() - called from display routine; renders each house in the display
				   through the use of a complex display list (house), which contains
				   separate display lists (groung, body, and top), which build each 
				   part of the house.
	- display(void) - assigned to glutDisplayFunc; sets glClear, an identity
				   matrix, and gluLookAt.  Activates anti-aliasing and depth-testing.
				   Sets polygon mode to fill before building the ground portion of
				   the scene and successively calling the renderHouse routine, after 
				   appropriate individual transformations have been applied for each 
				   house, to create the scene.  Calls drawPicture routine to add
				   background texture, then flushes and swaps buffers before exit.
	- reshape(int w, int h) - assigned to glutReshapeFunc; handles changes in the
				   size of the display window by setting the viewport with the
				   height and width it accepts when called, and setting the frustum.
	- main(int argc, char **argv) - performs the main loop of the program.  Performs
				   all initializations - GLUT, display mode, display window specs -
				   and assigns routines to the glutDisplayFunc and glutReshapeFunc
				   before calling the initialize routine and then looping for any
				   input.
