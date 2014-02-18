#include "testApp.h"
#define RECONNECT_TIME 400

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(31);
    ofSetWindowShape(600, 600);
    ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();
    //camera.setOrientation(ofPoint(-20,0,0));
    
    glEnable(GL_DEPTH_TEST);
    state = 0;

	leap.open();
	//leap.setupGestures();   // we enable our gesture detection here
    //lastFrame=leap.getCurrentFrame();
    

	

}


//--------------------------------------------------------------
void testApp::update()
{
    
    
    
	//leap.updateGestures();  // check for gesture updates
    vector<Hand> hands = leap.getLeapHands();
    
    Leap::Frame frame;
    Leap::Vector pt0;
    Leap::Vector pt1;
    ofVec3f sp;
    float rad;
    float r;
    frame=leap.getCurrentFrame();
    if (leap.isFrameNew() && hands.size()) {
        fingerPos.clear();
        spherePos.clear();
        sphereSize.clear();
        sphereNorm.clear();
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        

        //---------------------- data collection ---------------------------------
        for (int i = 0; i < hands.size(); i++) {
            for (int j = 0; j<hands[i].fingers().count(); j++) {
                ofVec3f pt;
                
                const Finger &finger = hands[i].fingers()[j];
                pt = leap.getMappedofPoint(finger.tipPosition());
                fingerPos.push_back(pt);
            }
            pt0 = hands[i].palmNormal();
            //angle = hands[i].rotationAngle(lastFrame);
            //angle = pt0.roll();
            //ofLogNotice("rotation ", "hand "+ ofToString(i) + " " + ofToString(angle));
            sp = leap.getMappedofPoint(hands[i].sphereCenter());
            r = hands[i].sphereRadius();
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            sphereNorm.push_back(pt0);
            //hands[i].pointables();
        }
        if (hands.size()>1) {
            Leap::Vector handP1 = hands[0].palmPosition();
            Leap::Vector handP2 = hands[1].palmPosition();
            float dis01 = handP1.distanceTo(handP2);
            ofLogNotice("position of hand 1 is", ofToString(handP1));
            ofLogNotice("position of hand 2 is", ofToString(handP2));
            handP1.x = abs(handP1.x);handP1.y = abs(handP1.y);handP1.z = abs(handP1.z);
            handP2.x = abs(handP2.x);handP2.y = abs(handP2.y);handP2.z = abs(handP2.z);
            ofLogNotice("distance between hands is", ofToString(dis01));
            if (dis01<70 && dis01>30) {
                ofLogNotice("isBai", "1");
            }
        }
        
//        if (hands.size()>1) {
//            Leap::PointableList fingers01 = hands[0].pointables();
//            Leap::PointableList fingers02 = hands[1].pointables();
//            //if (fingers01.count()== fingers02.count() && fingers01.count()==5) {
////                for (int i = 0; i< fingers01.count(); i++) {
////                    float dis0 = fingers01[i].tipPosition().distanceTo(fingers02[i].tipPosition());
////                    ofLogNotice("distance between "+ ofToString(i), ofToString(dis0));
////                }
//            //}
//
//        }
        Leap::PointableList fingers01 = hands[0].pointables();
        
        rad=hands[0].palmNormal().roll();
        angle=rad;
        if (spherePos.size()==2) {
            ofVec3f tp0 = spherePos[0]; ofVec3f tp1 = spherePos[1];
            float dis = tp0.distance(tp1);
            sphereSize.clear();
            sphereSize.push_back(dis);
        }
//        string message="";
//        message=ofToString(state)+"[/p]"+ofToString(sp.x)+"|"+ofToString(sp.y)+"|"+ofToString(sp.z)+"[/p]"+ofToString(pt0.x)+"|"+ofToString(pt0.y)+"|"+ofToString(pt0.z)+"[/p]" + ofToString(r)+"[/p]" + ofToString(angle);
//        ofLogNotice("message", message);
//        int issend = TCP.sendToAll(message);
//        ofLogNotice("is Send",ofToString(issend));

        
        //---------------------- state machine ----------------------------------
//        if(phase1==true && phase2 == false && phase3==false && phase4 == false && phase5==false && phase6 == false && phase7 == false && (!fingerPos.empty()))
//        {
//            phase2 = true;
//            state = 2;
//            
//        }
//        
//        if (phase2 == true && (sphereNorm.size()>=2)) {
//            pt0 = sphereNorm[0];
//            pt1 = sphereNorm[1];
//            if (abs(abs(pt0.x)-abs(pt1.x))<0.04 && abs(abs(pt0.y)-abs(pt1.y))<0.04)
//            {
//                phase3 = true;
//                phase2 = false;
//                state= 3;
//
//            }
//        }
//        
//        if (hands.size()==2 && phase3) {
//            phase3TwoHands=true;
//        }
        //pt0 = sphereNorm[0];
        //pt1 = sphereNorm[1];
        ofVec3f pt00 = spherePos[0];
        ofVec3f pt01 = spherePos[1];
        //if (abs(abs(pt0.x)-abs(pt1.x))<0.04 && abs(abs(pt0.y)-abs(pt1.y))<0.04)
        //{
            phase3 = true;
            phase2 = false;
            state= 3;
            float dis = pt00.distance(pt01);

        //}
        
        
    }
//    ofLogNotice("phase1: ", ofToString(phase1));
//    ofLogNotice("phase2: ", ofToString(phase2));
//    ofLogNotice("phase3: ", ofToString(phase3));
//    ofLogNotice("phase4: ", ofToString(phase4));
//    ofLogNotice("phase5: ", ofToString(phase5));
//    ofLogNotice("phase6: ", ofToString(phase6));
//    ofLogNotice("phase7: ", ofToString(phase7));
//    ofLogNotice("rotation ", ofToString(rad));
    lastFrame=frame;
	leap.markFrameAsOld();
    


}


//--------------------------------------------------------------
void testApp::draw()
{

    float r;
    camera.begin();
    for (int i = 0; i < fingerPos.size(); i++) {
        ofVec3f pt;
        pt = fingerPos[i];
        drawSphere(pt, 10);
       
    }
    
   
    
    if (phase2 == true && (!spherePos.empty())) {
        ofVec3f temp = spherePos[0];
        temp.z = -90;
        drawSphere(temp, 20);
        ofLogNotice("phase 2 triggered position of sphere is", ofToString(temp.x) + " " + ofToString(temp.y) + " " + ofToString(temp.z));
    }
    if (phase3 == true  && (!sphereSize.empty())) {
        ofVec3f pt = ofVec3f(0, 0);
        pt.z = -150;
        //ofLogNotice("phase 3 triggered position of sphere is", ofToString(pt.x) + " " + ofToString(pt.y) + " " + ofToString(pt.z));
        //ofLogNotice("phase 3 triggered r of sphere is", ofToString(sphereSize[0]));

        drawRotatableSphere(pt, sphereSize[0]/3, angle);
//        if (phase3TwoHands) {
//            drawSphere(pt, sphereSize[0]/3);
//            r = sphereSize[0]/3;
//        }else
//        drawRotatableSphere(pt, r, angle);
    }
    /*for (int i = 0; i < spherePos.size(); i++) {
        drawSphere(spherePos[i], sphereSize[i]*0.8);
    }*/
    
    camera.end();
//    ofSetHexColor(0x000000);
//	ofRect(10, 60, ofGetWidth()-24, ofGetHeight() - 65 - 15);
//    
//	ofSetHexColor(0xDDDDDD);
    
	
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

//-----------------------------------------------------------------
void testApp::drawRotatableSphere(ofVec3f vector, float radius, float angle)
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
//--------------------------------------------------------------


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    int screenWidth = ofGetScreenWidth();
    int screenHeight = ofGetScreenHeight();
    switch (key) {
        case OF_KEY_RETURN:
            if (ofGetWindowMode() == OF_WINDOW) {
                ofSetWindowShape(screenWidth, screenHeight);
                ofSetWindowPosition(0, 0);
                ofLogNotice("key pressed","enter");
            }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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

//--------------------------------------------------------------
void testApp::exit()
{
    leap.close();  // let's close down Leap and kill the controller
}
