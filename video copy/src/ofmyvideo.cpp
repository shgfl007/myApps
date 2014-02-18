//
//  ofmyvideo.cpp
//  emptyExample
//
//  Created by shengyi li on 1/26/2014.
//
//

#include "ofmyvideo.h"
#include <string>
ofmyvideo::ofmyvideo(int x,int y ,string name)
{
    
    width = 256;
    height = 192;
    posx=x;
    posy=y;
    myplayer.loadMovie(name);
    
    
}

void ofmyvideo::play()
{
    
    myplayer.play();
    
    
}

void ofmyvideo::update()
{
    myplayer.update();
    
}


void ofmyvideo::draw()
{
    myplayer.draw(posx, posy, width, height);
}

void ofmyvideo::pause(bool pause)
{
    myplayer.setPaused(pause);
}