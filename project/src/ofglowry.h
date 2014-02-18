//
//  ofglowry.h
//  project
//
//  Created by shengyi li on 1/27/2014.
//
//

#include "ofMain.h"
#ifndef project_ofglowry_h
#define project_ofglowry_h
class ofglowry{
 
public:
    ofglowry(int pointnumb, float ballsize, float line);
    
    void setup();
    void update();
    void draw();
    void clean();
    
    void addPoint(float x, float y, float z);
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    ofVbo vbo;
    ofShader shader;
    ofEasyCam camera;
    ofTexture texture;
    
    
    int num;
    float radius;
    float linesize;
    
float rotate;
private:
    
    
    
};


#endif
