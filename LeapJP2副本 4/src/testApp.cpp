#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    ofBackground(31);
    ofEnableLighting();
    light.setPosition(500, 300, 50);
    light.enable();
    
    glEnable(GL_DEPTH_TEST);
    state=0;
    
    leapController.addListener(leap);
    
}

//--------------------------------------------------------------
void testApp::update(){
    Leap::Vector pNormal;
    
    Leap::Frame frame = leapController.frame();
    Leap::HandList hands = frame.hands();
    
    Leap::Vector pt0;
    Leap::Vector pt1;
    
    if (!hands.isEmpty() && frame.id()>preId) {
        fingerPos.clear();
        sphereSize.clear();
        sphereNorm.clear();
        spherePos.clear();
        //ofLogNotice("hand detected");
        
        //----------------------------------- data collection ---------------------------------------------------------------------
        
        for (int i = 0; i<hands.count(); i++) {
            if (i>1) break;
            Leap::Hand tempHand = hands[i];
            Leap::FingerList tempfinger = tempHand.fingers();
            for (int j = 0; j <= tempfinger.count(); j++) {
                ofVec3f pt;
                Leap::Finger finger = hands[i].fingers()[j];
                Leap::Vector tempPT=finger.tipPosition();
                pt.x=tempPT.x;pt.y=tempPT.y;pt.z=tempPT.z;
                fingerPos.push_back(pt);
            }
            pt0 = tempHand.palmNormal();
            Leap::Vector center = tempHand.sphereCenter();
            ofVec3f sp; sp.x = center.x; sp.y = center.y; sp.z = center.z;
            float r = tempHand.sphereRadius();
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            sphereNorm.push_back(pt0);
            ofLogNotice("hand " +ofToString(i) + "normal", ofToString(pNormal.x) + " " + ofToString(pNormal.y) + " " + ofToString(pNormal.z));
           
        }
        
        //---------------------------------- state machine -----------------------------------------------------------------------
        if(phase1==true && phase2 == false && phase3==false && phase4 == false && phase5==false && phase6 == false && phase7 == false && (!fingerPos.empty()))
        {
            phase2 = true;
            state = 1;
        }
        
        if (phase2 == true && (sphereNorm.size()>=2)) {
            pt0 = sphereNorm[0];
            pt1 = sphereNorm[1];
            if (abs(abs(pt0.x)-abs(pt1.x))<0.04 && abs(abs(pt0.y)-abs(pt1.y))<0.04) {
                phase3 = true;
                phase2 = false;
            }
        }
        
    

    }
    ofLogNotice("phase1: ", ofToString(phase1));
    ofLogNotice("phase2: ", ofToString(phase2));
    ofLogNotice("phase3: ", ofToString(phase3));
    ofLogNotice("phase4: ", ofToString(phase4));
    ofLogNotice("phase5: ", ofToString(phase5));
    ofLogNotice("phase6: ", ofToString(phase6));
    ofLogNotice("phase7: ", ofToString(phase7));
    
    oldFrame = frame;
    preId = frame.id();

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    camera.begin();
    for (int i = 0; i < fingerPos.size(); i++) {
        ofVec3f pt;
        pt = fingerPos[i];
        drawSphere(pt, 10);
    }
    
    if (phase2 && (!spherePos.empty())) {
        ofVec3f temp = spherePos[0];
        temp.z = -90;
        drawSphere(temp, 20);
    }
    if (phase3 && (!sphereSize.empty())) {
        ofVec3f pt = ofVec3f(0,0);
        pt.z = -150;
        drawSphere(pt, sphereSize[0]);
    }
    camera.end();
}

//--------------------------------------------------------------
void testApp::drawSphere(ofVec3f vector, float radius){
    ofNoFill();
    ofPushMatrix();
    ofPoint point = ofPoint(vector.x, vector.y, vector.z);
    ofTranslate(point);
    ofRotateX(point.x);
    ofRotateY(point.y);
    ofRotateZ(point.z);
    ofSetColor(0xCC, 0, 0, 255);
    ofSphere(radius);
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void testApp::exit(){
    leapController.removeListener(leap);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}