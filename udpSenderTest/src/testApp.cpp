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
    lastFrame=leap.getCurrentFrame();
    //udpConnection.SetEnableBroadcast(true);
    //udpConnection.SetReuseAddress(true);
    udpConnection.Create();
    udpConnection.Connect("127.0.0.1", 9999);
    //udpConnection.ConnectMcast("127.0.0.1", 9999);
    udpConnection.SetNonBlocking(true);
	

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
            angle = hands[i].rotationAngle(lastFrame);
            
            ofLogNotice("rotation ", "hand "+ ofToString(i) + " " + ofToString(angle));
            sp = leap.getMappedofPoint(hands[i].sphereCenter());
            r = hands[i].sphereRadius();
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            sphereNorm.push_back(pt0);
        }
        rad=hands[0].palmNormal().roll();
        angle=rad;
        if (spherePos.size()==2) {
            ofVec3f tp0 = spherePos[0]; ofVec3f tp1 = spherePos[1];
            float dis = tp0.distance(tp1);
            sphereSize.clear();
            sphereSize.push_back(dis);
        }

        
        //---------------------- state machine ----------------------------------
        if(phase1==true && phase2 == false && phase3==false && phase4 == false && phase5==false && phase6 == false && phase7 == false && (!fingerPos.empty()))
        {
            phase2 = true;
            state = 2;
        }
        
        if (phase2 == true && (sphereNorm.size()>=2)) {
            pt0 = sphereNorm[0];
            pt1 = sphereNorm[1];
            if (abs(abs(pt0.x)-abs(pt1.x))<0.04 && abs(abs(pt0.y)-abs(pt1.y))<0.04) {
                phase3 = true;
                phase2 = false;
                state= 3;
            }
        }
        
        if (hands.size()==2 && phase3) {
            phase3TwoHands=true;
        }
        
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
	leap.markFrameAsOld();	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.
    string message="";
    message=ofToString(state)+"[/p]"+ofToString(sp.x)+"|"+ofToString(sp.y)+"|"+ofToString(sp.z)+"[/p]"+ofToString(pt0.x)+"|"+ofToString(pt0.y)+"|"+ofToString(pt0.z)+"[/p]" + ofToString(r)+"[/p]" + ofToString(angle);
    ofLogNotice("message", message);
    int issend = udpConnection.Send(message.c_str(), message.size());
    ofLogNotice("is Send",ofToString(issend));
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
        ofLogNotice("phase 3 triggered position of sphere is", ofToString(pt.x) + " " + ofToString(pt.y) + " " + ofToString(pt.z));
        ofLogNotice("phase 3 triggered r of sphere is", ofToString(sphereSize[0]));
//        if (sphereSize[0] < 60) {
//            sphereSize[0] = sphereSize[0] * 0.5;
//        }else{
//            sphereSize[0] = sphereSize[0] * 1.5;
//        }
//        drawSphere(pt, sphereSize[0]);
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
void testApp::drawWithModel(){
    
    if(state==0)
    {
        
        
        // The leaf patrt start***********************************************//
        
        //leaf one
        
        ofVec3f position1 = model1.getPosition();
        
        //save the current view
        ofPushMatrix();
        
        //center ourselves there
        ofTranslate(position1);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(0.15,0.15,0.15);
        ofRotate(90,1,0,0);
        ofTranslate(-position1);
        //draw the model
        model1.drawFaces();
        //restore the view position
        
        ofPopMatrix();
        model1.setPosition(ofGetWidth()*0.5, ofGetHeight()*height1, 0);
        
        
        //leaf two
        ofVec3f position2 = model2.getPosition();
        //save the current view
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position2);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(0.3,0.3,0.3);
        ofRotate(60,1,0,0);
        ofTranslate(-position2);
        //draw the model
        model2.drawFaces();
        //restore the view position
        ofPopMatrix();
        model2.setPosition(ofGetWidth()*0.4, ofGetHeight()*height2, 0);
        
        
        ofVec3f position3 = model3.getPosition();
        
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position3);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(0.15,0.15,0.15);
        ofRotate(90,1,0,0);
        ofTranslate(-position3);
        //draw the model
        model3.drawFaces();
        //restore the view position
        ofPopMatrix();
        model3.setPosition(ofGetWidth()*0.3, ofGetHeight()*height3, 0);
        
        //leaf two
        ofVec3f position4 = model4.getPosition();
        //save the current view
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position4);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(0.1,0.1,0.1);
        ofRotate(60,1,0,0);
        ofTranslate(-position4);
        //draw the model
        model4.drawFaces();
        //restore the view position
        ofPopMatrix();
        model4.setPosition(ofGetWidth()*0.8, ofGetHeight()*height4, 0);
        
        ofVec3f position5 = model5.getPosition();
        //save the current view
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position5);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(0.1,0.1,0.1);
        ofRotate(120,1,0,0);
        ofTranslate(-position5);
        //draw the model
        model5.drawFaces();
        //restore the view position
        ofPopMatrix();
        model5.setPosition(ofGetWidth()*0.2, ofGetHeight()*height5, 0);
        
        ofVec3f position7 = circle.getPosition();
        //save the current view
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position7);
        //ofRotate(rdegree, 0, 1, 0);
        ofScale(radius,radius,radius);
        //ofRotate(120,1,0,0);
        ofTranslate(-position7);
        //draw the model
        circle.drawFaces();
        //restore the view position
        ofPopMatrix();
        circle.setPosition(ofGetWidth()*0.5, ofGetHeight()*0.85, 0);
        
        
        // The leaf patrt end***********************************************//
        
    }
    
    if(state==1)
    { 
        model1.clear();
        model2.clear();
        model3.clear();
        model4.clear();
        model5.clear();
        
        ofVec3f position6 = lotus.getPosition();
        //save the current view
        ofPushMatrix();
        //center ourselves there
        ofTranslate(position6);
        ofRotate(rdegree, 0, 1, 0);
        ofScale(1.3,1.3,1.3);
        ofTranslate(-position6);
        //draw the model
        lotus.drawFaces();
        //restore the view position
        ofPopMatrix();	
        lotus.setPosition(ofGetWidth()*0.5, ofGetHeight()*lotusheight, 0);
        
    }
    
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
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
