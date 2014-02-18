//
//  simpletest.h
//  project
//
//  Created by Apple on 13-12-17.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef project_simpletest_h
#define project_simpletest_h
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofsimple{
public:
    
    ofsimple(int getwidth, int getheight, float bline, float hscale, float wscale);
    void update();
    void drawWithModel();
    void clear();
    
    int width;
    int height;
    
    float pheight;
    
private:
    ofxAssimpModelLoader mypetal;
    int npetals;
    float speed=5.0;
    float x;
    float y;
    int z;
    float size;
    int  rotate;
    float line;
    ofVec3f position;
    
    
    
    
};



#endif
