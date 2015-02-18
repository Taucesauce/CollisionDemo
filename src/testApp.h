#pragma once

#include "Gui.h"
#include "ParticleManager.h"
#include "PhysObject.h"
#include "ofMain.h"

class testApp : public ofBaseApp{

	public:

		int particleNum;
		bool elastic;

		ParticleManager<Circle> CircleManager;
		OptionsPanel Menu;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
