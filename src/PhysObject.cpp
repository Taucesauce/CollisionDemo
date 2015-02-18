#include "PhysObject.h"

void PhysObject::update(int radius)
{
	if((this->position.x + radius) >= ofGetWindowWidth())
	{
		this->velocity.x *= -1;
		/*this->position.x = 0 + radius;*/
	}
	if((this->position.x - radius) <= 0)
	{
		this->velocity.x *= -1;
		/*this->position.x = ofGetWindowWidth() - radius;*/
	}
	if((this->position.y - radius) <= 0)
	{
		this->velocity.y *= -1;
		/*this->position.y = ofGetWindowHeight() - radius;*/
	}
	if((this->position.y + radius) >= ofGetWindowHeight())
	{
		this->velocity.y *= -1;
		/*this->position.y = 0 + radius;*/
	}

	this->position += this->velocity;
}