//
//  ofglowry.cpp
//  project
//
//  Created by shengyi li on 1/27/2014.
//
//

#include "ofglowry.h"
#include <iostream>

ofglowry::ofglowry(int numb, float ballsize, float line)
{
    num = numb;
    radius = ballsize;
    linesize = line;
    ofLoadImage(texture, "dot.png");
	
	// load the shader
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/shader");
#else
    shader.load("shaders/shader");
#endif
    
    
}


void ofglowry::update()
{
    
    float theta1 = ofRandom(0, TWO_PI);
    float theta2 = ofRandom(0, TWO_PI);
    ofVec3f p;
    p.x = cos( theta1 ) * cos( theta2 );
    p.y = sin( theta1 );
    p.z = cos( theta1 ) * sin( theta2 );
    p  *= 800;
    addPoint(p.x, p.y, p.z);
    int total = (int)points.size();
    vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
    
    rotate+=0.2;
}


void ofglowry:: draw()
{
    
	glDepthMask(GL_FALSE);
	
	ofSetColor(255, 255, 255);
	
	// this makes everything look glowy :)
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();
    
	
	// bind the shader and camera
	// everything inside this function
	// will be effected by the shader/camera
	shader.begin();
   // ofPushMatrix();
    //ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.3, 0);
	camera.begin();
	
	// bind the texture so that when all the points
	// are drawn they are replace with our dot image
	
    ofPushMatrix();
    texture.bind();
    ofRotate(rotate,0,1,0);
	vbo.draw(GL_POINTS, 0, (int)points.size());
	texture.unbind();
    ofPopMatrix();
	
	camera.end();
	shader.end();
    
  
    
	//ofPopMatrix();
    
    
	ofDisablePointSprites();
	ofDisableBlendMode();
	
	// check to see if the points are
	// sizing to the right size
/*	ofEnableAlphaBlending();
	camera.begin();
	for (unsigned int i=0; i<points.size(); i++) {
		ofSetColor(255, 80);
		ofVec3f mid = points[i];
		mid.normalize();
		mid *= linesize;
		ofLine(points[i], mid);
	}
	camera.end();
    ofDisableAlphaBlending();*/
    glDepthMask(GL_TRUE);
    
}




void ofglowry::addPoint(float x, float y, float z) {
	ofVec3f p(x, y, z);
	points.push_back(p);
	
	// we are passing the size in as a normal x position
	float size = ofRandom(5, 50);
	sizes.push_back(ofVec3f(size));
}

void ofglowry::clean()
{
    vbo.clear();
    texture.clear();
    
    
}

