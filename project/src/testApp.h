#pragma once

#include "ofMain.h"
#include "ofPetal.h"
#include "ofLotus.h"
#include "ofxNetwork.h"
#include "ofxLeapMotion.h"
#include "ofglowry.h"
#include "ofBuddhaeyes.h"
#include "ofGesture.h"

//#include "simpletest.h"
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
        void exit();
   
    //ofCamera camera;
    bool phase1 = true;
    bool phase2, phase3, phase4, phase5, phase6, phase7 = false;

    
    ofxTCPServer TCP;
    ofglowry *myglowry;
    ofBuddhaeyes *mybuddha;
    ofGesture *mygesture;
    
    ofQuaternion curRot;
	
    //a place to store the mouse position so we can measure incremental change
    ofVec2f lastMouse;
	
	//slows down the rotation 1 = 1 degree per pixel
	float dampen;
    
    
    bool sendflag = false;
    
        //ofPetal *mypetal1;
    
        ofPetal *mypetals;
        ofLight light;
        ofLotus *lotus1;
        int state;
        int petalno =7;
    
 
    ofEasyCam cam;
    
    
    string msgTx;
    string msgRx;
 //   int count = 0;
   // float angle;
       
		
};
