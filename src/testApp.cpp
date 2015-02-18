#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	Menu = OptionsPanel();
	Menu.setup();
	CircleManager = ParticleManager<Circle>();
	particleNum = Menu.numParticles;
	elastic = true;
	for(int x = 0; x < particleNum; x++)
	{
		CircleManager.newParticle();
	}

}

//--------------------------------------------------------------
void testApp::update(){
	CircleManager.updateList(Menu.numParticles);
	CircleManager.update(elastic);
}

//--------------------------------------------------------------
void testApp::draw(){
	Menu.draw();
	ofSetColor(Menu.circleColor);
	ofFill();
	CircleManager.draw(Menu.randomColor);
	if(Menu.drawBehaviorComponents)
	{
		CircleManager.drawComponents();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
