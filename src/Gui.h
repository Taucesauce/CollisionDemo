#ifndef GUI_H
#define GUI_H

#include "ofMain.h"
#include "ofxGui.h"

#include <string>

//Initializes GUI values and functions
class OptionsPanel
{
public:
	OptionsPanel();

	void update();
	void setup();
	void draw();

	ofxPanel panel;
	ofxSlider<int> numParticles;
	ofxToggle drawBehaviorComponents;
	ofxToggle randomColor;
	ofxColorSlider circleColor;
};
#endif