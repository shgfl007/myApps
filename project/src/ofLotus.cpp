//
//  ofLotus.cpp
//  project
//
//  Created by shengyi li on 1/17/2014.
//
//

#include "ofLotus.h"
#include <iostream>


ofLotus::ofLotus(int getwidth, int getheight, float bline, float hscale, float wscale)
{
    width = getwidth;
    height = getheight;
    line = bline*getheight;
    x = width * wscale;
    y = height * hscale;
    z = ofRandom(10,0);
    rotate = 0;
    size = 1.3;
    mylotus.loadModel("3dmodel/lotus.obj");
    mylotus.setPosition(x, y, z);
    stop = false;
    
}

void ofLotus::update(bool grow)
{
    if(y > line && grow==true)
    {
        y+=speed;
        
    }
    else if(y < line)
    {
        
        y=y;
        stop =true;
    }
    rotate+=5;
}

void ofLotus::drawWithModel()

{
    //glDepthMask(GL_FALSE);
    position = mylotus.getPosition();
    ofPushMatrix();
    ofTranslate(position);
    ofRotate(rotate, 0, 1, 0);
    ofScale(size,size,size);
    ofTranslate(-position);
    mylotus.drawFaces();
    ofPopMatrix();
    mylotus.setPosition(x, y, z);
    
}

void ofLotus::clear()
{
    
    mylotus.clear();
    
}
bool ofLotus::condition(){
    
    return stop;
}


