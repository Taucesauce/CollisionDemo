#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H

#include "ofMain.h"


//Foundation class for all objects being rendered in the application.
class PhysObject
{
public:

	//Object's current position vector
	ofVec2f position;
	//Object's current velocity vector
	ofVec2f velocity;
	//Object's mass
	float mass;

	//Calculates the particle's position/velocity in the following frame.
	void update(int radius);
};
#endif