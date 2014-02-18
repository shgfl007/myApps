//
//  ofmyvideo.h
//  emptyExample
//
//  
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
    void close();
    int getPosX();
    int getPosY();
    bool isDraw;
    
    int width;
    int height;
private:
    int posx;
    int posy;
    ofVideoPlayer myplayer;
    
    
    
    
    
    
    
};



#endif
