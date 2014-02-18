//
//  ofBuddhaeyes.h
//  project
//
//  Created by shengyi li on 2/7/2014.
//
//
#include "ofMain.h"
#include <string>
#ifndef project_ofBuddhaeyes_h
#define project_ofBuddhaeyes_h
class ofBuddhaeyes{
    
public:
    ofBuddhaeyes(float iT,int gp,int imgwidth, int imgheight, string nm);
    
    void setup();
    void update();
    void draw();
    void clean();
    ofMesh mesh;
    ofImage image;
    vector<ofVec3f> offsets;
    float intensityThreshold;
    int gap;
    int imagewidth;
    int imageheight;
    string name;
    
    
private:
    int w;
    int h;
    
    
    
    
    
};


#endif
