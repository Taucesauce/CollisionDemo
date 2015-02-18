#include "ParticleManager.h"

void ParticleManager<Circle>::newParticle()
{
	int x = ofRandom(0,ofGetWindowWidth());
	int y = ofRandom(150, ofGetWindowHeight());

	Circle circle = Circle(x, y);

	ObjectList.push_back(circle);
}

void ParticleManager<Circle>::draw(bool random)
{
	for(int x = 0; x < ObjectList.size(); x++)
	{
		if(random)
		{
			ofSetColor( ofColor(ofRandom( 0, 255 ), ofRandom( 0, 255 ), ofRandom( 0, 255 ) ));
			ofFill();
			ofCircle(ObjectList.at(x).position.x,ObjectList.at(x).position.y,ObjectList.at(x).radius);
		}
		else
		{
			ofCircle(ObjectList.at(x).position.x,ObjectList.at(x).position.y,ObjectList.at(x).radius);
		}
	}
}

void ParticleManager<Circle>::update(bool restitution)
{
	for(int x = 0; x < ObjectList.size(); x++)
	{
		for(int y = x+1; y < ObjectList.size(); y++)
		{
			bool collision = CollisonCheck(ObjectList.at(x), ObjectList.at(y));
			if(collision)
			{
				ofVec4f result = newVelocityCalc(ObjectList.at(x), ObjectList.at(y), restitution);
				ObjectList.at(x).velocity.x = result.w;
				ObjectList.at(x).velocity.y = result.x;
				ObjectList.at(y).velocity.x = result.y;
				ObjectList.at(y).velocity.y = result.z;
			}
		}
	}
	for(int x = 0; x < ObjectList.size();x++)
	{
		ObjectList.at(x).update(ObjectList.at(x).radius);
	}
}

void ParticleManager<Circle>::updateList(int listSize)
{
	if(ObjectList.size() < listSize)
	{
		for(int x = ObjectList.size(); x < listSize; x++)
		{
			this->newParticle();
		}
	}

	else
	{
		for(int x = ObjectList.size(); x > listSize; x--)
		{
			ObjectList.pop_back();
		}
	}
}
void ParticleManager<Circle>::drawComponents()
{
	for(int x = 0; x < ObjectList.size(); x++)
	{
		ofSetColor(0,230,0);
		ofFill();
		ofLine(ObjectList.at(x).position,(ObjectList.at(x).position + 10*ObjectList.at(x).velocity));
		ofSetColor(255,0,0);
		ofFill();
		ofLine(ObjectList.at(x).position,(ObjectList.at(x).position + ObjectList.at(x).radius));
	}
}

template<>
bool ParticleManager<Circle>::CollisonCheck(Circle object1, Circle object2)
{
	double xDistance = abs(object1.position.x - object2.position.x);
	double yDistance = abs(object1.position.y - object2.position.y);
	double totalDistance = sqrt(xDistance*xDistance + yDistance*yDistance);
	if(totalDistance <= (object1.radius + object2.radius))
		return true;

	else return false;
}

template<>
ofVec4f ParticleManager<Circle>::newVelocityCalc(Circle object1, Circle object2, bool elastic)
{
	int restitution = 1;
	if(elastic)
	{
		restitution = 0;
	}
	double movementAngle1 = object1.velocity.angle(ofVec2f(object1.position.x, object1.position.x + object1.radius));
	double movementAngle2 = object2.velocity.angle(ofVec2f(object2.position.x, object2.position.x + object2.radius));
	double collisionAngle = atan2((object1.position.y - object2.position.y), (object1.position.x - object2.position.x));

	object1.velocity.x = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / (object1.mass + object2.mass)) * cosf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object1.velocity.y = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / (object1.mass + object2.mass)) * sinf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * sinf(collisionAngle + (PI/2));

	object2.velocity.x = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object2.velocity.length() * cos(movementAngle1 - collisionAngle)) / (object2.mass + object2.mass)) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object2.velocity.y = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object2.velocity.length() * cos(movementAngle1 - collisionAngle)) / (object2.mass + object2.mass)) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));

	
	return ofVec4f(object1.velocity.x,object1.velocity.y,object2.velocity.x,object2.velocity.y);
}