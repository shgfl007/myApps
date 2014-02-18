//
//  ofBuddhaeyes.cpp
//  project
//
//  Created by shengyi li on 2/7/2014.
//
//

#include "ofBuddhaeyes.h"
#include <string>

ofBuddhaeyes::ofBuddhaeyes(float iT,int gp,int imgwidth, int imgheight, string nm)
{
    intensityThreshold = iT;
    gap = gp;
    imagewidth = imgwidth;
    imageheight = imgheight;
    name = nm;
    image.loadImage(name);
    image.resize(imagewidth,imageheight);;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    w = image.getWidth();
    h = image.getHeight();
    for (int x=0; x<w; x+=gap) {
        for (int y=0; y<h; y+= gap ){
            ofColor c = image.getColor(x, y);
            // ofColor temp;
            
            // temp.r = c.r +200;
            //temp.g = c.g +200;
            //temp.b = c.b + 200;
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(2*x, 2*y, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                
                // And add this line:
                // It will create a ofVec3f with 3 random values
                // These will allow us to move the x, y and z coordinates of each vertex independently
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    ofEnableDepthTest();
	glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
	glPointSize(5);
    
    
}

void ofBuddhaeyes::update()
{
    
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
    
    
}


void ofBuddhaeyes::draw(){
    
    mesh.draw();

}

void ofBuddhaeyes::clean(){
    
    mesh.clear();
    image.clear();
    
}








