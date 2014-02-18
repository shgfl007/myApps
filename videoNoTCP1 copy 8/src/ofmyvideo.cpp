//
//  ofmyvideo.cpp
//  emptyExample
//
//  
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
    isDraw = true;
    
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

void ofmyvideo::close()
{
    isDraw = false;
    myplayer.close();
}

int ofmyvideo::getPosX()
{
    return posx;
}

int ofmyvideo::getPosY()
{
    return posy;
}