#pragma once

#include "ofMain.h"
#include "ofmyvideo.h"
#include "tcpReceiver.h"
#include "ofxLeapMotion.h"
#include "ofxAssimpModelLoader.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();

    ofmyvideo **myvideo;
    vector<ofmyvideo> videoList;
    int numbofvideo=16;
    int cv;
    string pathlist[16];
    int xlist[16]={0,256,512,768,0,256,512,768,0,256,512,768,0,256,512,768};
    int ylist[16]={192,0,192,0,384,192,384,192,0,384,0,384,576,576,576,576};
    ofxTCPClient tcpClient;
    string msgTx, msgRx;
    
    float counter;
    int connectTime;
    int deltaTime;
    int state;
    string position;
    bool isConnected;
    
    ofxLeapMotion leap;
    bool pause = false;
    
    ofCamera camera;
    ofLight light;
    
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
    float radius;
    int rdegree = 0;
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
    int isNewVideo = 0;
    int count = 0;
    bool isSend = false;
    bool isFirstTime = true;
};
