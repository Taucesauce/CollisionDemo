//Used to build the circle object specific to the Physobject class.
//Adds a radius variable and shape-specific constructor.

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofVec2f.h"
#include "PhysObject.h"

class Circle : public PhysObject
{
public:
	//Object's radius member
	float radius;

	Circle(int x, int y);
};
#endif