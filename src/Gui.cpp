#include "Gui.h"
#include <iostream>

OptionsPanel::OptionsPanel()
{

}

void OptionsPanel::setup()
{
	panel.setup("Options Menu");
	panel.add(drawBehaviorComponents.setup("Draw Mechanics",false));
	panel.add(randomColor.setup("DISCO FEVER!", false));
	panel.add(numParticles.setup("Number of Particles", 5, 2, 50));
	panel.add(circleColor.setup("Circle Color",ofColor(255,0,255),ofColor(0,0),ofColor(255,255)));
}

void OptionsPanel::draw()
{
	panel.draw();
}