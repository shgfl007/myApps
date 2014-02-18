//
//  ofLotus.h
//  project
//
//  Created by shengyi li on 1/17/2014.
//
//

#ifndef project_ofLotus_h
#define project_ofLotus_h
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
class ofLotus{
    
public:
    ofLotus(int getwidth, int getheight, float bline, float hscalse, float wscale);
    void update( bool grow);
    void drawWithModel();
    void clear();
    bool condition();
    
    int width;
    int height;
    
    float pheight;
    bool stop;
    
private:
    ofxAssimpModelLoader mylotus;
    float speed=-1.0;
    float x;
    float y;
    float z;
    float size;
    int rotate;
    float line;
    ofVec3f position;
    
};


#endif
