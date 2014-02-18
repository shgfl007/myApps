//
//  ofGesture.cpp
//  project
//
//  Created by shengyi li on 2/8/2014.
//
//

#include "ofGesture.h"


ofGesture::ofGesture()
{
    leap.open();
    heshi = false;
    grow = false;
    
}

void ofGesture::update()
{
     hands= leap.getLeapHands();
    float rad;
    if (leap.isFrameNew() && hands.size()) {
        fingerPos.clear();
        spherePos.clear();
        sphereSize.clear();
        sphereNorm.clear();
        
        leap.setMappingX(-230, 230, -ofGetWidth(), ofGetWidth());
        leap.setMappingY(90, 490, -ofGetHeight(), ofGetHeight());
        leap.setMappingZ(-150, 150, -200, 200);

    //------- data collection------
        for (int i = 0; i < hands.size(); i++) {
            for (int j = 0; j<hands[i].fingers().count(); j++) {
                
                const Finger &finger = hands[i].fingers()[j];
                pt = leap.getMappedofPoint(finger.tipPosition());
                pt.y = -pt.y;
                fingerPos.push_back(pt);
            }
            pt0 = hands[i].palmNormal();
            sp = leap.getMappedofPoint(hands[i].sphereCenter());
            float r = hands[i].sphereRadius();
            rad=hands[0].palmNormal().roll();
            angle=rad;
            if (spherePos.size()==2) {
                ofVec3f tp0 = spherePos[0]; ofVec3f tp1 = spherePos[1];
                float dis = tp0.distance(tp1);
                sphereSize.clear();
                sphereSize.push_back(dis);
            }
            
          
            
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            sphereNorm.push_back(pt0);
            
        }
        
    }
   
}

bool ofGesture::gs1check(){
    
    if(hands.size()>1){
        Leap::Vector handP1 = hands[0].palmPosition();
        Leap::Vector handP2 = hands[1].palmPosition();
        float dis01 = handP1.distanceTo(handP2);
        handP1.x = abs(handP1.x);handP1.y=abs(handP1.y);handP1.z=abs(handP1.z);
        handP2.x = abs(handP2.x);handP2.y=abs(handP2.y);handP2.z=abs(handP2.z);
        
        if(dis01<70 && dis01 >30)
        {
            heshi = true;
        }
        
    }

    return heshi;
    
}

bool ofGesture::gs2check(){
    
    if(!spherePos.empty())
    {
        ofVec3f temp1 = spherePos[0];
        if(temp1.y < sp.y)
        {
            grow = false;
        }else
        {
            grow = true;
        }
        
    }
    //ofLogNotice("is growing", ofToString(grow));

    return grow;
    
}

void ofGesture::drawfinger()
{
    for(int i =0; i < fingerPos.size(); i++)
    {
        
            ofVec3f pt;
            pt=fingerPos[i];
            drawSphere(pt,10);
        
    }
    
    
    
}

void ofGesture::drawmainsphere(){
    
    ofVec3f pt =ofVec3f(ofGetWidth()/2,ofGetWindowHeight()/2);
    pt.z=-150;
    
    
    drawRotatableSphere(pt,sphereSize[0], angle);
    
}





void ofGesture::drawSphere(ofVec3f vector, float radius){
    ofNoFill();
    ofPushMatrix();
    ofPoint point = ofPoint(vector.x, vector.y, vector.z);
    ofTranslate(point);
    ofRotateX(point.x);
    ofRotateY(point.y);
    ofRotateZ(point.z);
    //  ofSetColor(0xCC, 0, 0, 255);
    ofSphere(radius);
    ofPopMatrix();

}


void ofGesture::drawRotatableSphere(ofVec3f vector, float radius, float angle)
{
    ofNoFill();
    ofPushMatrix();
    ofPoint point = ofPoint(vector.x, vector.y, vector.z);
    ofTranslate(point);
    //float degrees = angle/3.14 * 180 *10;
    float degrees = ofRadToDeg(angle);
    ofRotate(degrees, 1, 1, 1);
    
    //    ofRotateX(point.x);
    //    ofRotateY(point.y);
    //    ofRotateZ(point.z);
    ofSetColor(0xCC, 0, 0, 255);
    ofSphere(radius);
    ofPopMatrix();
    
    
}

void ofGesture::clean()

{
    leap.close();
    fingerPos.clear();
   spherePos.clear();
    sphereNorm.clear();
    hands.clear();
sphereSize.clear();
   
}



