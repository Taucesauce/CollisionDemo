#ifndef PARTICLEMANAGER_H
#define	PARTICLEMANGER_H

#include "ofMain.h"
#include "PhysObject.h"
#include "Circle.h"

//Class that handles each object type.
template <class PhysObject>
class ParticleManager
{
private:
	//List of the objects of the manager's type.
	vector<PhysObject> ObjectList;

public:
	//Declares Manager
	ParticleManager<PhysObject>(){}

	//Creates new object
	void newParticle();
	//Draws object
	void draw(bool random);
	//When menu box is checked, draws components of movement.
	void drawComponents();
	//Updates all particles in the list.
	void update(bool restitution);
	//Adjust the current size based on the menu number.
	void updateList(int listSize);

	//Object Collision functions
	bool CollisonCheck(Circle object1, Circle object2);
	ofVec4f newVelocityCalc(Circle object1, Circle object2, bool elastic);
};
#endif