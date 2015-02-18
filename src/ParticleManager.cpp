#include "ParticleManager.h"

//Method used to generate a new instance of a circle object 
//and push it onto the list to be drawn.

void ParticleManager<Circle>::newParticle()
{
	//Picks a random point on the app window.
	int x = ofRandom(0,ofGetWindowWidth());
	int y = ofRandom(150, ofGetWindowHeight());

	//Creates a new circle object at that point.
	Circle circle = Circle(x, y);

	//Pushes the new circle
	ObjectList.push_back(circle);
}

//Iterates through the list of objects and draws each one.
void ParticleManager<Circle>::draw(bool random)
{
	//For loop for iteration through list.
	for(int x = 0; x < ObjectList.size(); x++)
	{
		//Checks for the "Disco Time" condition.
		if(random)
		{
			//FLASHY COLORS!
			ofSetColor( ofColor(ofRandom( 0, 255 ), ofRandom( 0, 255 ), ofRandom( 0, 255 ) ));
			ofFill();
			ofCircle(ObjectList.at(x).position.x,ObjectList.at(x).position.y,ObjectList.at(x).radius);
		}
		//Draws a circle using the objects' attributes.
		else
		{
			ofCircle(ObjectList.at(x).position.x,ObjectList.at(x).position.y,ObjectList.at(x).radius);
		}
	}
}

//Iterates through the list and calculates position after a frame passes.
void ParticleManager<Circle>::update(bool restitution)
{
	//Double for loop for checking a collision between each object in the application.
	//**Could be streamlined by checking specific divisions of the window, implement later.** 
	for(int x = 0; x < ObjectList.size(); x++)
	{
		for(int y = x+1; y < ObjectList.size(); y++)
		{
			//Determines if two objects overlap
			bool collision = CollisonCheck(ObjectList.at(x), ObjectList.at(y));
			//Calculates new velocity after collision #IhavenoideahowIcodedthat
			if(collision)
			{
				//Seriously though, there should be a much better (and more accurate) way of getting that to work. USE PHYSICS. hahah
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

//Matches the list size with the number of objects currently in the app.
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

//Method used for drawing the lines representing current motion of an object.
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
	//If the total distance between two objects (Circles for now) is less than the sum of their radii,
	//they must be overlapping, and therefore have collided this frame.
	double xDistance = abs(object1.position.x - object2.position.x);
	double yDistance = abs(object1.position.y - object2.position.y);
	double totalDistance = sqrt(xDistance*xDistance + yDistance*yDistance);
	if(totalDistance <= (object1.radius + object2.radius))
		return true;

	else return false;
}

//#yoloswag 
template<>
//Elasticity sold separately.
ofVec4f ParticleManager<Circle>::newVelocityCalc(Circle object1, Circle object2, bool elastic)
{
	double movementAngle1 = object1.velocity.angle(ofVec2f(object1.position.x, object1.position.x + object1.radius));
	double movementAngle2 = object2.velocity.angle(ofVec2f(object2.position.x, object2.position.x + object2.radius));
	double collisionAngle = atan2((object1.position.y - object2.position.y), (object1.position.x - object2.position.x));

	object1.velocity.x = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / (object1.mass + object2.mass)) * cosf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object1.velocity.y = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / (object1.mass + object2.mass)) * sinf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * sinf(collisionAngle + (PI/2));

	object2.velocity.x = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object2.velocity.length() * cos(movementAngle1 - collisionAngle)) / (object2.mass + object2.mass)) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object2.velocity.y = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object2.velocity.length() * cos(movementAngle1 - collisionAngle)) / (object2.mass + object2.mass)) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));

	
	return ofVec4f(object1.velocity.x,object1.velocity.y,object2.velocity.x,object2.velocity.y);
}