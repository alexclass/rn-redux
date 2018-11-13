# c-plus-plus-graphics
Simple C++ applications demonstrating the basics of rendering graphics.

All programs have been written as Win32 Console Application's using Microsoft Visual C++ and require the installation of GLUT (The OpenGL Utility Toolkit), which can be downloaded from:
https://www.opengl.org/resources/libraries/glut/

The repository includes the following solutions:

1. anti-aliasing: AntiAliasing.cpp and README.md - produces an output containing two houses, which are each a combination of a triangle and a rectangle, to demonstrate the result of anti-aliasing.

2. 2D-transforms: 2DTransforms.cpp and README.md - produces an output containing five identical houses, which have each been transformed to different desired orientations.

3. colouring-and-shading: ColouringAndShading.cpp and README.md - produces an output displaying a cube with various colours by setting the four vertices to red, green, blue, and yellow, respectively.

4. object-modeling: ObjectModeling.cpp and README.md - produces an output displaying a 3D house using a complex display list.

5. 3D-transforms: 3DTransforms.cpp and README.md - produces an output containing a 3D scene in which there are eight houses of varying shape and size spread over a ground surface, each of which have been transformed.

6. lighting-and-material: LightingAndMaterial.cpp and README.md - produces an output displaying a sphere whose lighting and surface material can be customized using a provided menu (accessed by a right-click).

7. specular-contributions: SpecularContributions.cpp, vector3.cpp, vector3.h, and README.md - produces an output which displays a red square, including a manual calculation of specular lighting.

8. loaded-texture: LoadedTexture.cpp, side.bmp, and README.md - produces an output containing a 3D scene, which includes a texture loaded as the background.

9. recursive-reflection: RecursiveReflection.cpp, vector3.cpp, plane.cpp, vector3.h, plane.h, and README.md - produces an output that includes reflection, implemented through a recursive ray tracing routine.

10. shadows: Shadows.cpp, vector3.cpp, plane.cpp, vector3.h, plane.h, and README.md - produces an output that takes shadows into account, implemented through recursive ray tracing.

11. mirror-room: MirrorRoom.cpp, vector3.cpp, plane.cpp, vector3.h, plane.h, and README.md - produces an output that contains a mirror room with  multi-colored cube in the middle, including all reflection and shadows.
