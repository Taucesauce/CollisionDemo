#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofVec2f.h"
#include "PhysObject.h"

class Circle : public PhysObject
{
public:
	float radius;

	Circle(int x, int y);
};
#endif