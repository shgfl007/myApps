#pragma once

#include "ofMain.h"
#include "ofMath.h"
#include "ofxLeapMotion.h"
#include "ofxAssimpModelLoader.h"


class testApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();
	
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
		
	ofxLeapMotion leap;
    ofCamera camera;
    void drawSphere(ofVec3f vector, float radius);
    void drawRotatableSphere(ofVec3f vector, float radius, float angle);
    bool phase1 = true;
    bool phase2, phase3, phase4, phase5, phase6, phase7,phase3TwoHands = false;
    ofLight light;
    Leap::Frame lastFrame;
    float angle;
    vector <ofVec3f> fingerPos;
    vector<ofVec3f> spherePos;
    vector<Leap::Vector> sphereNorm;
    vector <float> sphereSize;
    
    ofxAssimpModelLoader model1;
    ofxAssimpModelLoader model2;
    ofxAssimpModelLoader model3;
    ofxAssimpModelLoader model4;
    ofxAssimpModelLoader model5;
    ofxAssimpModelLoader model6;
    ofxAssimpModelLoader model7;
    ofxAssimpModelLoader model8;
    ofxAssimpModelLoader model9;
    ofxAssimpModelLoader model10;
    ofxAssimpModelLoader lotus;
    ofxAssimpModelLoader circle;
    int state;
    float radius;
    
    
    void drawWithModel();
    float height1 = 0.05;
    float height2 = 0.3;
    float height3 = 0.5;
    float height4 = 0.8;
    float height5 = 0.2;
    float height6 = 0.7;
    float height7 = 0.8;
    float height8 = 0.6;
    float height9 = 0.1;
    float height10 = 0.2;
    float lotusheight = 1.0;
    int rdegree = 0;

};
