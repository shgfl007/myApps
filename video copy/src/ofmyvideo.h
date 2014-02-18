//
//  ofmyvideo.h
//  emptyExample
//
//  Created by shengyi li on 1/26/2014.
//
//

#ifndef emptyExample_ofmyvideo_h
#define emptyExample_ofmyvideo_h
#include "ofMain.h"
#include <string>

class ofmyvideo{
    
public:
    ofmyvideo(int x, int y, string name);
    
    void update();
    void draw();
    void clear();
    void play();
    void pause(bool pause);
    
    int width;
    int height;
private:
    int posx;
    int posy;
    ofVideoPlayer myplayer;
    
    
    
    
    
    
    
};



#endif
