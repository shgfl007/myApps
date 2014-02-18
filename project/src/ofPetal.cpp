//
//  ofPetal.cpp
//  project
//
//  Created by Apple on 13-12-17.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ofPetal.h"



ofPetal::ofPetal(int _width, int _height)
{
    npetal=7;
    mysimple =new ofsimple*[npetal];
    pwidth[0]=0.1;
    pwidth[1]=0.3;
    pwidth[2]=0.5;
    pwidth[3]=0.6;
    pwidth[4]=0.7;
    pwidth[5]=0.8;
    pwidth[6]=0.9;

    
    pheight[0]=0.4;
    pheight[1]=0.2;
    pheight[2]=0.7;
    pheight[3]=0.3;
    pheight[4]=0.65;
    pheight[5]=0.4;
    pheight[6]=0.65;
    
    for(int i=0; i<npetal; i++)
        
    {
        
        mysimple[i] = new ofsimple(_width, _height,0.8,pheight[i],pwidth[i]); 
        
        
    }
    
    
    
}

void ofPetal::update()
{
    for(int i=0; i<npetal; i++)
    {
        mysimple[i]->update();
        
    }
    
}

void ofPetal::drawpetal()
{
    for(int i=0; i<npetal; i++)
    {
        mysimple[i]->drawWithModel();
        
    }
}

void ofPetal::clear(){
    
    for(int i=0; i<npetal; i++)
    {
        mysimple[i]->clear();
        
    }
    
}
