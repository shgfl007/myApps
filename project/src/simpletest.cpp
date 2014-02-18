//
//  simpletest.cpp
//  project
//
//  Created by Apple on 13-12-17.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "simpletest.h"

ofsimple::ofsimple(int _getwidth, int _getheight, float _bline, float _hscale, float _wscale )
{
    width=_getwidth;
    height=_getheight;
    line = _bline*_getheight;
    x= width * _wscale;
    y= height * _hscale;
    z = ofRandom(10,0);
    rotate=ofRandom(360.0, 0.0);
    size = ofRandom(0.3, 0.15);

    mypetal.loadModel("3dmodel/leaf.obj");
    mypetal.setPosition(x, y, z);
    
   
    
}

void ofsimple::update()
{
    if(y < line)
    {
        y+=speed;
        
    }
    else
    {
        y=0.0;
        
        
    }
    
    rotate+=5;
    
    
}

void ofsimple::drawWithModel()
{
    position =mypetal.getPosition();
    ofPushMatrix();
    ofTranslate(position);
    ofRotate(rotate, 0, 1, 0);
    ofScale(size,size,size);
    ofRotate(90, 1, 0, 0);
    ofTranslate(-position);
    


    mypetal.drawFaces();
    ofPopMatrix();
    mypetal.setPosition(x, y, z);
   
    
    
}

void ofsimple::clear()
{
    mypetal.clear();
}






