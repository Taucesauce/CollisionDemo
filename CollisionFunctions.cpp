#include "CollisionFunctions.h"

bool CollisionCheck(Circle object1, Circle object2)
{
	ofVec2f distance = object1.position - object2.position;
	if(distance.length() <= abs(object1.radius - object2.radius))
		return true;

	else return false;
}

void newVelocityCalc(Circle object1, Circle object2)
{
	double movementAngle1 = object1.velocity.angle(ofVec2f(object1.position.x, object1.position.x + object1.radius));
	double movementAngle2 = object2.velocity.angle(ofVec2f(object2.position.x, object2.position.x + object2.radius));
	double collisionAngle = atan2((object1.position.y - object2.position.y), (object1.position.x - object2.position.x));
	object1.velocity.x = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / 10) * cosf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object1.velocity.y = ((object1.velocity.length() * cosf(movementAngle1 - collisionAngle) * (object1.mass - object2.mass) + 2 * object2.mass * object2.velocity.length() * cos(movementAngle2 - collisionAngle)) / 10) * sinf(collisionAngle) + object1.velocity.length() * sinf(movementAngle1 - collisionAngle) * sinf(collisionAngle + (PI/2));
	object2.velocity.x = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object1.velocity.length() * cos(movementAngle1 - collisionAngle)) / 10) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));
	object2.velocity.y = ((object2.velocity.length() * cosf(movementAngle2 - collisionAngle) * (object2.mass - object1.mass) + 2 * object1.mass * object1.velocity.length() * cos(movementAngle1 - collisionAngle)) / 10) * cosf(collisionAngle) + object2.velocity.length() * sinf(movementAngle2 - collisionAngle) * cosf(collisionAngle + (PI/2));
}