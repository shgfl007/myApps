#pragma once

#include "ofMain.h"
#include "ofmyvideo.h"
#include "tcpReceiver.h"
#include "ofxLeapMotion.h"

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

    ofmyvideo **myvideo;
    int numbofvideo=16;
    int cv;
    string pathlist[16];
    int xlist[16]={0,256,512,768,0,256,512,768,0,256,512,768,0,256,512,768};
    int ylist[16]={192,0,192,0,384,192,384,192,0,384,0,384,576,576,576,576};
    //tcpReceiver *tcp;
    ofxTCPClient tcpClient;
    string msgTx, msgRx;
    
    float counter;
    int connectTime;
    int deltaTime;
    int state;
    string position;
    bool isConnected;
    
    ofxLeapMotion leap;
    bool istapped;
    
};
