/*	MirrorRoom.cpp
	
	This programs implements a recursive routine to produce a mirror room with a cube in the middle -
	with each face of the cube a different color - through the use of reflective effects, along with
	proper shadows.  This is accomplished by adding complexity to the ray tracer, along with 
	additional planar objects to the scene. The implemented 
	recursive method casts a ray from the ray source to the scene. The ray either hits a reflective 
	surface (the floor or any of the three walls) or its hits the cube (a non- reflective surface). 
	When it hits the cube, the method terminates the recursion and returns the mixed color at the
	current pixel. When the ray hits a reflective surface, the method recursively invokes itself with 
	the reflection ray, until either the cube is hit or a ray has no intersections in the scene, and 
	calculates and return the mixed color at the original pixel.  The inclusion test is implemented 
	through an additional method - withinObject, and the program hard-codes the normal vectors of all 
	the planes in the scene.  The program also checks whether each intersection point in the recursion 
	routine can see the light source - if it cannot, a shadow color is assigned.

	@author: Dan Bonham
	@date: November 15th, 2015
*/

#include <iostream>
#include <algorithm>
#include <math.h>
#include "gl/glut.h"
#include "plane.h"

using namespace std;

vector3 viewer(-90.0, 150.0, 275.0); // viewer position

// floor characteristics - normal, plane equation, corners
vector3 floorNormal(0.0, 1.0, 0.0);
plane   floorEquation(0.0, 4.0, 0.0, 0.0);
vector3 floorLimit1(-100.0, 0, 100.0);
vector3 floorLimit2(100.0, 0, 100.0);
vector3 floorLimit3(100.0, 0, -100.0);
vector3 floorLimit4(-100.0, 0, -100.0);

// red face of cube - normal, plane equation, corners
vector3 redWallNormal(0.0, 0.0, 1.0);
plane redWall(0.0, 0.0, 4.0, -100.0);
vector3 redWallLimit1(-25.0, 50.0, 25.0);
vector3 redWallLimit2(-25.0, 0.0, 25.0);
vector3 redWallLimit3(25.0, 0.0, 25.0);
vector3 redWallLimit4(25.0, 50.0, 25.0);

// blue face of cube - normal, plane equation, corners
vector3 blueWallNormal(-1.0, 0.0, 0.0);
plane blueWall(4.0, 0.0, 0.0, 100.0);
vector3 blueWallLimit1(-25.0, 50.0, -25.0);
vector3 blueWallLimit2(-25.0, 0.0, -25.0);
vector3 blueWallLimit3(-25.0, 0.0, 25.0);
vector3 blueWallLimit4(-25.0, 50.0, 25.0);

// green face of cube - normal, plane equation, corners
vector3 greenWallNormal(1.0, 0.0, 0.0);
plane greenWall(4.0, 0.0, 0.0, -100.0);
vector3 greenWallLimit1(25.0, 50.0, 25.0);
vector3 greenWallLimit2(25.0, 0.0, 25.0);
vector3 greenWallLimit3(25.0, 0.0, -25.0);
vector3 greenWallLimit4(25.0, 50.0, -25.0);

// yellow face of cube - normal, plane equation, corners
vector3 yellowWallNormal(0.0, 0.0, -1.0);
plane yellowWall(0.0, 0.0, 4.0, 100.0);
vector3 yellowWallLimit1(25.0, 50.0, -25.0);
vector3 yellowWallLimit2(25.0, 0.0, -25.0);
vector3 yellowWallLimit3(-25.0, 0.0, -25.0);
vector3 yellowWallLimit4(-25.0, 50.0, -25.0);

// top face of cube - normal, plane equation, corners
vector3 topNormal(0.0, 1.0, 0.0);
plane   topEquation(0.0, 4.0, 0.0, -200.0);
vector3 topLimit1(-25.0, 50, -25.0);
vector3 topLimit2(-25.0, 50, 25.0);
vector3 topLimit3(25.0, 50, 25.0);
vector3 topLimit4(25.0, 50, -25.0);	

// back wall characteristics - normal, plane equation, corners
vector3 backWallNormal(0.0, 0.0, 1.0);
plane backWall(0.0, 0.0, 4.0, 400.0);
vector3 backWallLimit1(-100.0, 150.0, -100.0);
vector3 backWallLimit2(-100.0, 0.0, -100.0);
vector3 backWallLimit3(100.0, 0.0, -100.0);
vector3 backWallLimit4(100.0, 150.0, -100.0);

// left mirror wall characteristics - normal, plane equation, corners
vector3 leftWallNormal(1.0, 0.0, 0.0);
plane leftWall(4.0, 0.0, 0.0, 400.0);
vector3 leftWallLimit1(-100.0, 150.0, 100.0);
vector3 leftWallLimit2(-100.0, 0.0, 100.0);
vector3 leftWallLimit3(-100.0, 0.0, -100.0);
vector3 leftWallLimit4(-100.0, 150.0, -100.0);

// right mirror wall characteristics - normal, plane equation, corners
vector3 rightWallNormal(-1.0, 0.0, 0.0);
plane rightWall(4.0, 0.0, 0.0, -400.0);
vector3 rightWallLimit1(100.0, 150.0, -100.0);
vector3 rightWallLimit2(100.0, 0.0, -100.0);
vector3 rightWallLimit3(100.0, 0.0, 100.0);
vector3 rightWallLimit4(100.0, 150.0, 100.0);

// colors usd in the scene
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);
vector3 lightBlue(0.1, 0.1, 0.75);
vector3 lightGreen(0.1, 0.75, 0.1);
vector3 lightYellow(0.75, 0.75, 0.1);
vector3 cyan(0.1, 0.75, 0.75);
vector3 white(1.0, 1.0, 1.0);
vector3 grey_dark(0.2, 0.2, 0.2);
vector3 black(0.0, 0.0, 0.0);

// lighting positions
vector3 light1Position(75, 150, 150);
vector3 light2Position(-75, 150, -150);

// lighting elements - used in lighting calculations
float ambient_coef = 0.2;
float diffuse_coef = 0.6;//0.7
float reflect_coef = 0.3;//0.4
float local_coef   = 0.5;//0.6
float specular_coef = 0.4; // specular set to 1.0 - diffuse
int specularReflectionExponent = 8; // specular-reflection exponent

// arrays used in the ray tracer - hold characteristics of the different planar surfaces
plane planes[] = { floorEquation, redWall, blueWall, greenWall, yellowWall, leftWall, rightWall, backWall, floorEquation, topEquation }; // plane equations
vector3 colors[] = { white, lightRed, lightBlue, lightGreen, lightYellow, grey, grey, grey, black, cyan }; // colors
vector3 normals[] = { floorNormal, redWallNormal, blueWallNormal, greenWallNormal, yellowWallNormal, leftWallNormal, rightWallNormal, backWallNormal, floorNormal, topNormal }; // normals

// vector used to hold intersection points - used in ray tracer (avoids some redundant calculations)
vector3 fInt(0.0, 0.0, 0.0); // floor/ray intersection
vector3 rwInt(0.0, 0.0, 0.0); // red face of cube/ray intersection
vector3 bwInt(0.0, 0.0, 0.0); // blue face of cube/ray intersection
vector3 gwInt(0.0, 0.0, 0.0); // green face of cube/ray intersection
vector3 ywInt(0.0, 0.0, 0.0); // yellow face of cube/ray intersection
vector3 topInt(0.0, 0.0, 0.0); // top face of cube/ray intersection
vector3 rightInt(0.0, 0.0, 0.0); // right mirror wall/ray intersection
vector3 leftInt(0.0, 0.0, 0.0); // left mirror wall/ray intersection
vector3 backInt(0.0, 0.0, 0.0); // back mirror wall/ray intersection

// initialize routine
void initialize() {
	// set background color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// set the limits of the floor
	floorEquation.setP1(floorLimit1);
	floorEquation.setP2(floorLimit2);
	floorEquation.setP3(floorLimit3);
	floorEquation.setP4(floorLimit4);

	// set the limits of the red cube face
	redWall.setP1(redWallLimit1);
	redWall.setP2(redWallLimit2);
	redWall.setP3(redWallLimit3);
	redWall.setP4(redWallLimit4);

	// set the limits of the blue cube face
	blueWall.setP1(blueWallLimit1);
	blueWall.setP2(blueWallLimit2);
	blueWall.setP3(blueWallLimit3);
	blueWall.setP4(blueWallLimit4);

	// set the limits of the green cube face
	greenWall.setP1(greenWallLimit1);
	greenWall.setP2(greenWallLimit2);
	greenWall.setP3(greenWallLimit3);
	greenWall.setP4(greenWallLimit4);

	// set the limits of the yellow cube face
	yellowWall.setP1(yellowWallLimit1);
	yellowWall.setP2(yellowWallLimit2);
	yellowWall.setP3(yellowWallLimit3);
	yellowWall.setP4(yellowWallLimit4);

	// set the limits of the left mirror wal
	leftWall.setP1(leftWallLimit1);
	leftWall.setP2(leftWallLimit2);
	leftWall.setP3(leftWallLimit3);
	leftWall.setP4(leftWallLimit4);

	// set the limits of the right mirror wall
	rightWall.setP1(rightWallLimit1);
	rightWall.setP2(rightWallLimit2);
	rightWall.setP3(rightWallLimit3);
	rightWall.setP4(rightWallLimit4);

	// set the limits of the back mirror wall
	backWall.setP1(backWallLimit1);
	backWall.setP2(backWallLimit2);
	backWall.setP3(backWallLimit3);
	backWall.setP4(backWallLimit4);

	// set the limits of the top cube face
	topEquation.setP1(topLimit1);
	topEquation.setP2(topLimit2);
	topEquation.setP3(topLimit3);
	topEquation.setP4(topLimit4);
} // initialize()

// calculate local color - local color is intensity * base color
vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal, vector3 lightPosition) {
	// calculate unit vector
	vector3 origin = lightPosition.subtract(intersect);
	vector3 unitVec = origin.normalize(); // normalize unit vector

	float dotProd = unitVec.dot(normal); // calculate dot product

	// calculate reflection vector
	vector3 reflect = (normal.scalar(2*dotProd)).subtract(unitVec);
	vector3 reflectVec = reflect.normalize(); // normalize reflection vector

	// calculate viewer vector
	vector3 view = viewer.subtract(intersect);
	vector3 viewerVec = view.normalize(); // normalize viewer vector

	// calculate V dot R
	float dotProd2 = viewerVec.dot(reflectVec);

	// calculate intensity
	float ambientContr = ambient_coef; // ambient contribution
	float diffuseContr = diffuse_coef * dotProd; // diffuse contribution
	float specularContr = specular_coef * pow(dotProd2, specularReflectionExponent); // specular contribution
	float intensity = ambientContr + diffuseContr + specularContr; // total intensity
	//float intensity = ambientContr + diffuseContr; // does not include specular

	if (intensity > 1.0) intensity = 1.0; // intensity cannot be greater than 1.0

	// calculate intensity of each of R, G, B
	float r = intensity * baseColor.x;
	float g = intensity * baseColor.y;
	float b = intensity * baseColor.z;

	return vector3(r,g,b); // returns color at current intersect
} // localColor()

// withinObject() - determines if a given intersection point is within an objects boundaries
bool withinObject(vector3 point, plane object) {
		if ( (-0.1 < point.y) && (point.y < 150.1) && (-100.1 < point.z) && (point.z < 100.1) && (-100.1 < point.x) && (point.x < 100.1) && 
			 (point.y <= (max(max(object.p1y, object.p2y), max(object.p3y, object.p4y)) + .1)) && 
			 (point.y >= (min(min(object.p1y, object.p2y), min(object.p3y, object.p4y)) - .1)) &&
			 (point.z <= (max(max(object.p1z, object.p2z), max(object.p3z, object.p4z)) + .1)) && 
			 (point.z >= (min(min(object.p1z, object.p2z), min(object.p3z, object.p4z)) - .1)) &&
			 (point.x <= (max(max(object.p1x, object.p2x), max(object.p3x, object.p4x)) + .1)) && 
			 (point.x >= (min(min(object.p1x, object.p2x), min(object.p3x, object.p4x)) - .1)) )
			return true; // returns true when intersection is present
		else
			return false; // returns false when the ray does not intersect object
} // withinObject()

// hasIntersection() - determines if a given ray intersects any of the objects in the scene
bool hasIntersection (vector3 origin, vector3 dir) {
	// gets intersection point for each object plane
	fInt = floorEquation.intersect(origin, origin.add(dir));
	rwInt = redWall.intersect(origin, origin.add(dir));
	bwInt = blueWall.intersect(origin, origin.add(dir));
	gwInt = greenWall.intersect(origin, origin.add(dir));
	ywInt = yellowWall.intersect(origin, origin.add(dir));
	topInt = topEquation.intersect(origin, origin.add(dir));
	rightInt = rightWall.intersect(origin, origin.add(dir));
	leftInt = leftWall.intersect(origin, origin.add(dir));
	backInt = backWall.intersect(origin, origin.add(dir));

	// determines whether any intersection point is within an object's boundaries
	if( (withinObject(fInt, floorEquation) ) ||
		(withinObject(backInt, backWall) ) ||
		(withinObject(leftInt, leftWall) ) ||
		(withinObject(rightInt, rightWall) ) ||
		(withinObject(rwInt, redWall) ) ||
		(withinObject(bwInt, blueWall) ) ||
		(withinObject(gwInt, greenWall) ) ||
		(withinObject(ywInt, yellowWall) ) ||
		(withinObject(topInt, topEquation) ) )
		return true; // returns true when intersection present
	else
		return false; // returns false when no intersection present
} //hasIntersection()

// rayTracer() - determines the color at each pixel in the display
vector3 rayTracer(vector3 origin, vector3 dir, int cumulativeCalls) {
	// test if need to continue recursion
	if ( /*(cumulativeCalls > 5) || */(!hasIntersection(origin, dir)) ) { // recursion can end
		return vector3(0.0, 0.0, 0.0); // returns black - background or reflective ray gone out of room
	} else { // recursion continues
		float minDistance = 100000; // used to determine nearest intersection
		float testDistance; // distance at test intersection
		int intIndex = 0; // will be set to object that ray intersects with
		bool reflective = false; // determines whether intersection is with a reflective surface
		vector3 intersection(0.0, 0.0, 0.0); // will hold current intersection

		// determines nearest ray/object intersection - sets array index to appropriate, 
		// resets distance variable, sets intersection variable
		if( withinObject(topInt, topEquation) && (!(withinObject(origin, topEquation)) || cumulativeCalls == 0) && ((testDistance = origin.distance(topInt)) < minDistance) ) { // top cube face
			intIndex = 9;
			minDistance = testDistance;
			intersection = topInt;
		} // end(top cube face)
		
		if( withinObject(rwInt, redWall) && (!(withinObject(origin, redWall))  || cumulativeCalls == 0) && ((testDistance = origin.distance(rwInt)) < minDistance) ) { // red cube face
			intIndex = 1;
			minDistance = testDistance;
			intersection = rwInt;
		} // end(red cube face)
		
		if( withinObject(bwInt, blueWall) && (!(withinObject(origin, blueWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(bwInt)) < minDistance) ) { // blue cube face
			intIndex = 2;
			minDistance = testDistance;
			intersection = bwInt;
		} // end(blue cube face)
		
		if( withinObject(gwInt, greenWall) && (!(withinObject(origin, greenWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(gwInt)) < minDistance) ) { // green cube face
			intIndex = 3;
			minDistance = testDistance;
			intersection = gwInt;
		} // end(green cube face)
		
		if( withinObject(ywInt, yellowWall) && (!(withinObject(origin, yellowWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(ywInt)) < minDistance) ) { // yellow cube face
			intIndex = 4;
			minDistance = testDistance;
			intersection = ywInt;
			// cout << " yellow " << endl;
		} // end(yellow cube face)
		
		if( (fInt.y < 1) && withinObject(fInt, floorEquation) && (!(withinObject(origin, floorEquation)) || cumulativeCalls == 0) && ((testDistance = origin.distance(fInt)) < minDistance) ) { // floor
			if ( (((int)ceil(fInt.x / 10) + (int)ceil((fInt.z) / 10)) % 2) == 0 ) // used to create a checkered floor
				intIndex = 0; // white tile
			else
				intIndex = 8; // black tile
			minDistance = testDistance;
			intersection = fInt;
			reflective = true;
		} // end(floor)
		
		if( withinObject(leftInt, leftWall) && (!(withinObject(origin, leftWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(leftInt)) < minDistance) ) { // left wall
			intIndex = 5;
			minDistance = testDistance;
			intersection = leftInt;
			reflective = true;
		} // end(left wall)
		
		if( withinObject(rightInt, rightWall) && (!(withinObject(origin, rightWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(rightInt)) < minDistance) ) { // right wall
			intIndex = 6;
			minDistance = testDistance;
			intersection = rightInt;
			reflective = true;
		} // end(right wall)
		
		if( withinObject(backInt, backWall) && (!(withinObject(origin, backWall)) || cumulativeCalls == 0) && ((testDistance = origin.distance(backInt)) < minDistance) ) { // back wall
			intIndex = 7;
			minDistance = testDistance;
			intersection = backInt;
			reflective = true;
		} // end(back wall)

		vector3 light1Color(0.0, 0.0, 0.0); // will store color contribution from first light source
		vector3 light2Color(0.0, 0.0, 0.0); // will store color contribution from second light source
		for (int i = 0; i < 2; i++ ) { // loops for each light source
			vector3 lightPosition(0.0, 0.0, 0.0); // will hold different light positions
			if ( i == 0 ) lightPosition = light1Position; else lightPosition = light2Position; // gets each light position for calculations

			// Cast a ray from the intersection to the light sources
			vector3 lightRay = lightPosition.subtract(intersection);
			vector3 rayNorm = lightRay.normalize();

			vector3 currentInt(0.0, 0.0, 0.0);
		
			bool shadow = false; // holds variable that determines whether current point is within shadow
			// determines whether current point is within a shadow - if so, sets bool variable to true
			if( (withinObject((currentInt = topEquation.intersect(intersection, intersection.add(rayNorm))), topEquation)) && !(withinObject(intersection, topEquation)) && (lightPosition.distance(currentInt) < lightPosition.distance(intersection)) ) {
				shadow = true;
			} else if( (withinObject((currentInt = redWall.intersect(intersection, intersection.add(rayNorm))), redWall)) && !(withinObject(intersection, redWall)) && (lightPosition.distance(currentInt) < lightPosition.distance(intersection)) ) {
				shadow = true;
			} else if( (withinObject((currentInt = blueWall.intersect(intersection, intersection.add(rayNorm))), blueWall)) && !(withinObject(intersection, blueWall)) && (lightPosition.distance(currentInt) < lightPosition.distance(intersection)) ) {
				shadow = true;
			} else if( (withinObject((currentInt = greenWall.intersect(intersection, intersection.add(rayNorm))), greenWall)) && !(withinObject(intersection, greenWall)) && (lightPosition.distance(currentInt) < lightPosition.distance(intersection)) ) {
				shadow = true;
			} else if( (withinObject((currentInt = yellowWall.intersect(intersection, intersection.add(rayNorm))), yellowWall)) && !(withinObject(intersection, yellowWall)) && (lightPosition.distance(currentInt) < lightPosition.distance(intersection)) ) {
				shadow = true;
			} // else if

			vector3 lColor =  localColor(intersection, colors[intIndex], normals[intIndex], lightPosition); // get local color
			
			// If intersection exists
			if ( shadow ) { // Calculate lighting intensity with shadow
				lColor = lColor.scalar(ambient_coef); // sets local color to shadowed version
			} // end if
					
			if ( reflective ) { // If the object at the intersection point is reflective
				vector3 reflectiveRay = dir.reflect(normals[intIndex]); // Calculate reflective ray
				rayNorm = reflectiveRay.normalize(); // normalize reflective ray
				vector3 rColor = rayTracer(intersection, rayNorm, cumulativeCalls + 1); // Call Recursive Ray Tracer to get reflective color
				lColor = lColor.scalar(local_coef).add(rColor.scalar(reflect_coef)); // ***Color per light source = (Local color * local color contribution percentage) + (Reflective color * reflective color contribution percentage)
			} // Endif
			
			if (i == 0) light1Color = lColor; else light2Color = lColor; // gets color contribution from each light source
		} // end for

		// ***Add all colors per light source to get color at the intersection point
		float r = light1Color.x + light2Color.x;
		float g = light1Color.y + light2Color.y;
		float b = light1Color.z + light2Color.z;

		return vector3(r, g, b); // Return color at the intersection point
	} // else
} // rayTracer()

// render
void render() {
	// activate anti-aliasing
	glEnable(GL_LINE_SMOOTH); // needed to activate anti-aliasing
	glEnable(GL_BLEND); // needed to activate anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // specifies blending specifications

	// loops through each pixel in the display
	for (int m=-300; m<300; m++) {
		for(int n=-300; n<300; n++) {
			vector3 intersect = vector3(m, n, 0); // gets current intersect
			vector3 direction = intersect.subtract(viewer); // gets direction from viewer to intersect
			vector3 color = rayTracer(viewer, direction, 0); // gets color for current intersect

			glColor3f(color.x, color.y, color.z); // sets current color to that specified
			glRecti(m, n, m+1, n+1); // draws rectangle at current intersect
		} // for(n)
	} // for(m)
} // render

// display registry
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // specifies what can be used
	glLoadIdentity(); // loads identity matrix

//	gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // sets viewing angle

	render(); // calls render routine

	glutSwapBuffers(); //interchanges front/back refresh buffers
}// display(void)

// reshape registry
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); // sets viewport size and position
	glMatrixMode(GL_PROJECTION); // sets projection mode - designates matrix for projection transformation
	glLoadIdentity(); // loads identity matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 650.0); // sets frustum
	glMatrixMode(GL_MODELVIEW); // sets current matrix to modelview
}// reshape(int w, int h)

// Main program
void main(int argc, char **argv) {
	glutInit(&argc, argv); // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets two buffers, RGB colour mode, depth buffer operations
	glutInitWindowSize(500, 500); // sets window size
	glutInitWindowPosition(100, 100); // sets window position

	int windowHandle = glutCreateWindow("Mirror Room"); // creates window with specified title
	glutSetWindow(windowHandle); // sets window to that previously created

	glutDisplayFunc(display); // sets routine to display picture in window
	glutReshapeFunc(reshape); // sets routine to handle change in display-window dimensions

	initialize(); // calls initialize routine
	
	glutMainLoop(); // displays initial graphics and puts program in infinite loop
}// main(int argc, char **argv)









