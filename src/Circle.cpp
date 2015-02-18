#include "Circle.h"
//Circle Shape constructor
Circle::Circle(int x, int y)
{
	this->position = ofVec2f(x, y);
	this->velocity = this->position*(1/ofGetFrameRate());
	this->radius = ofRandom(10,15);
	this->mass = 2;
}