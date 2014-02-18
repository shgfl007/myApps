#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    //camera.setFov(60);
    //camera.setPosition(0, 200, ofGetWidth()/3);
    //camera.lookAt(ofVec3f(0, 200, 0));
    
    leapController.addListener(leap);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    //camera.begin();
    float r0 = 30;
    Leap::Vector ptp;
    Leap::Vector ptp0;
    Leap::Vector pNormal;
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    //ofSetColor(255, 255, 255);
   
    Leap::Frame frame = leapController.frame();
    Leap::HandList hands = frame.hands();
    
    if (!hands.isEmpty()) {
        //ofLogNotice("hand detected");
        int count = hands.count();
        for (int i = 0; i<count; i++) {
            if (i>1) break;
            Leap::Hand tempHand = hands[i];
            pNormal = tempHand.palmNormal();
            ofLogNotice("hand " +ofToString(i) + "normal", ofToString(pNormal.x) + " " + ofToString(pNormal.y) + " " + ofToString(pNormal.z));
            
        }
        Leap::Hand hand = hands[0];
        Leap::Hand hand1 = hands[1];
        double r = hand.sphereRadius();
        //ofLogNotice("r is" + ofToString(r));
        r0 = r * 5;
        ptp = hand1.palmNormal();
        ptp0 = hand.palmNormal();
        ofLogNotice("distance is ", ofToString(abs(ptp.x)-abs(pNormal.x)) + " " + ofToString(abs(ptp.y)-abs(pNormal.y)));
        
        if (abs(abs(ptp.x)-abs(pNormal.x))<0.4 && abs(abs(ptp.y)-abs(pNormal.y))<0.4) {
            phase1=false;
            ofLogNotice("phase 2 triggered", ofToString(phase1));
        }
    }
    
    if(phase1){
        ofSphere(ptp.x,-ptp.y,ptp.z, r0);
    }
    
    vector<Leap::FingerList> fingers = leap.getFingers();
    if (!fingers.empty()) {
        //ofLogNotice("finger detected");
        //ofBox(100, -200, 4, 40, 40, 40);
        phase1 = true;
        
        for (int cnt = 0; cnt < fingers.size(); cnt++) {
            for (int fingerNum = 0; fingerNum < fingers[cnt].count(); fingerNum++) {
                Leap::Vector pt = fingers[cnt][fingerNum].tipPosition();
                Leap::Vector vpt = fingers[cnt][fingerNum].tipVelocity();
                pt.x = pt.x*2;
                pt.y = (pt.y * -1)*2;
                pt.z = pt.z *2;
                //ofLogNotice("finger number is " + ofToString(cnt) + ofToString(fingerNum));
                //ofSphere(pt.x,pt.y,pt.z, 10);
                //ofBox(pt.x, pt.y, pt.z, 10, 10, 10);
                //ofLogNotice("position is " + ofToString(pt.x) + " " + ofToString(pt.y) + " " + ofToString(pt.z));
                //ofLogNotice("velocity is " + ofToString(vpt.x) + " " + ofToString(vpt.y) + " " + ofToString(vpt.z));
                drawSphere(pt, 10);
            }
        }
        Leap::Vector tpt = fingers[0][0].tipPosition();
 
        
        
    }
    ofPopMatrix();
    camera.end();
}

//--------------------------------------------------------------
void testApp::drawSphere(Leap::Vector vector, float radius){
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