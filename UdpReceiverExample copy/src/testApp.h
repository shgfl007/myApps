#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{

	public:

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
        void drawSphere(ofVec3f vector, float radius);

		ofxUDPManager udpConnection;
		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;

		vector<ofPoint> stroke;
    
        vector <ofVec3f> fingerPos;
        vector<ofVec3f> spherePos;
        vector<ofVec3f> sphereNorm;
        vector <float> sphereSize;
        float angle;
        int state;
        ofCamera camera;
        ofLight light;
};

