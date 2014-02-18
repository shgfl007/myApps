//
//  ofGesture.h
//  project
//
//  Created by shengyi li on 2/8/2014.
//
//

#ifndef project_ofGesture_h
#define project_ofGesture_h
#include "ofxLeapMotion.h"
#include "ofMain.h"
class ofGesture{
    
public:
    
    ofGesture();
    void update();
    void drawfinger();
    void drawmainsphere();
    bool gs1check();
    bool gs2check();
    bool grow;
    bool heshi;
    
    void drawSphere(ofVec3f vector, float radius);
    void drawRotatableSphere(ofVec3f vector, float radius, float angle);
    void clean();
    
private:
    
    vector <ofVec3f> fingerPos;
    vector <ofVec3f> spherePos;
    vector <Leap::Vector> sphereNorm;
    
    vector<Hand> hands;
    Leap::Vector pt0;
    Leap::Vector pt1;
    vector <float> sphereSize;
    float angle;
    ofxLeapMotion leap;
    
    
    ofVec3f pt;
    ofVec3f sp;
    
    
};


#endif
