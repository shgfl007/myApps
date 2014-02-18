#pragma once

#include "ofMain.h"
#include "LeapMotion.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    LeapMotion leap;
    Leap::Controller leapController;
    ofCamera camera;
    void drawSphere(Leap::Vector vector, float radius);
    bool phase1, phase2, phase3, phase4, phase5, phase6, phase7 = false;
};
