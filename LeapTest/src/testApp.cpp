#include "testApp.h"


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
    
    
	//we need to call this for textures to work on models
    ofDisableArbTex();
	
	//this makes sure that the back of the model doesn't show through the front
	ofEnableDepthTest();
    
    
	//now we load our model
	model1.loadModel("3dmodel/leaf.obj");
    model2.loadModel("3dmodel/leaf.obj");
    model3.loadModel("3dmodel/leaf.obj");
    model4.loadModel("3dmodel/leaf.obj");
    model5.loadModel("3dmodel/leaf.obj");
    model6.loadModel("3dmodel/leaf.obj");
    model7.loadModel("3dmodel/leaf.obj");
    model8.loadModel("3dmodel/leaf.obj");
    model9.loadModel("3dmodel/leaf.obj");
    model10.loadModel("3dmodel/leaf.obj");
    lotus.loadModel("3dmodel/lotus.obj");
    circle.loadModel("3dmodel/circle.obj");
	model1.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.05, 0);
    model2.setPosition(ofGetWidth()*.4, ofGetHeight() * 0.3, 2);
    model3.setPosition(ofGetWidth()*.3, ofGetHeight() * 0.05, 4);
    model4.setPosition(ofGetWidth()*.8, ofGetHeight() * 0.2, 2);
    model5.setPosition(ofGetWidth()*.2, ofGetHeight() * 0.1, 3);
    model6.setPosition(ofGetWidth()*.75, ofGetHeight() * 0.7, 2);
    model7.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.8, 1);
    model8.setPosition(ofGetWidth()*.7, ofGetHeight() * 0.6, 3);
    model9.setPosition(ofGetWidth()*.55, ofGetHeight() * 0.1, 5);
    model10.setPosition(ofGetWidth()*.65, ofGetHeight() * 0.2, 2);
    lotus.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.5, 0);
    circle.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.5, 0);


}


//--------------------------------------------------------------
void testApp::update()
{
    //--------------------------- TimeLine & Motion Trace -----------------------
    int drop =0;
    if(height1 < 0.85)
    {height1 +=0.005;
    }
    else
    {
        height1 = 0.0;
        drop=1;
        
    }
    if(height2 < 0.85)
    {height2 +=0.005;}
    else
    {height2 = 0.0 ;}
    if(height3 < 0.85)
    {height3 +=0.005;}
    else
    {height3 = 0.0 ;}
    if(height4 < 0.85)
    {height4 +=0.005;}
    else
    {height4 = 0.0 ;}
    if(height5 < 0.85)
    {height5 +=0.005;}
    else
    {height5 = 0.0 ;}
    if(height6 < 0.85)
    {height6 +=0.005;}
    else
    {height6 = 0.0 ;}
    if(height7 < 0.85)
    {height7 +=0.005;}
    else
    {height7 = 0.0 ;}
    if(height8 < 0.85)
    {height8 +=0.005;}
    else
    {height8 = 0.0 ;}
    if(height9 < 0.85)
    {height9 +=0.005;}
    else
    {height9 = 0.0 ;}
    if(height10 < 0.85)
    {height10 +=0.005;
        //lotus.clear();
    }
    else
    {height10 = 0.0 ;}
    
    if(state==1)
    {
        if(lotusheight > 0.5 && grow==true)
        {
            
            lotusheight -=0.002;
        }
        
        
    }
    
    if(radius < 1.0 && drop == 1)
    {radius +=0.005;
        //lotus.clear();
    }
    else if(radius > 1.0)
    {radius = 0.001;
        drop=0;}
    
    
    
    
    rdegree += 5;

    
    
    
	//leap.updateGestures();  // check for gesture updates
    vector<Hand> hands = leap.getLeapHands();
    Leap::Vector pt0;
    Leap::Vector pt1;
    if (leap.isFrameNew() && hands.size()) {
        fingerPos.clear();
        spherePos.clear();
        sphereSize.clear();
        sphereNorm.clear();
        
        leap.setMappingX(-230, 230, -ofGetWidth(), ofGetWidth());
        leap.setMappingY(90, 490, -ofGetHeight(), ofGetHeight());
        leap.setMappingZ(-150, 150, -200, 200);
        

        //---------------------- data collection ---------------------------------
        for (int i = 0; i < hands.size(); i++) {
            for (int j = 0; j<hands[i].fingers().count(); j++) {
                ofVec3f pt;
                const Finger &finger = hands[i].fingers()[j];
                pt = leap.getMappedofPoint(finger.tipPosition());
                pt.y = -pt.y;
                fingerPos.push_back(pt);
            }
            pt0 = hands[i].palmNormal();
            ofVec3f sp = leap.getMappedofPoint(hands[i].sphereCenter());
            float r = hands[i].sphereRadius();
            if(!spherePos.empty() && phase2 == true)
            {ofVec3f temp = spherePos[0];
            if(temp.y < sp.y)
            {
                grow = false;
            }else
            {
                grow = true;
            }}
            ofLogNotice("is growing", ofToString(grow));
            spherePos.push_back(sp);
            sphereSize.push_back(r);
            sphereNorm.push_back(pt0);
        }
        
        //---------------------- state machine ----------------------------------
        if(phase1==true && phase2 == false && phase3==false && phase4 == false && phase5==false && phase6 == false && phase7 == false && (!fingerPos.empty()))
        {
            phase2 = true;
            state = 1;
        }
        
//        if (phase2 == true && (sphereNorm.size()>=2)) {
//            pt0 = sphereNorm[0];
//            pt1 = sphereNorm[1];
//            if (abs(abs(pt0.x)-abs(pt1.x))<0.04 && abs(abs(pt0.y)-abs(pt1.y))<0.04) {
//                phase3 = true;
//                phase2 = false;
//            }
//        }
        
    }
//    ofLogNotice("phase1: ", ofToString(phase1));
//    ofLogNotice("phase2: ", ofToString(phase2));
//    ofLogNotice("phase3: ", ofToString(phase3));
//    ofLogNotice("phase4: ", ofToString(phase4));
//    ofLogNotice("phase5: ", ofToString(phase5));
//    ofLogNotice("phase6: ", ofToString(phase6));
//    ofLogNotice("phase7: ", ofToString(phase7));
    
    
	leap.markFrameAsOld();	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new. 
}

//--------------------------------------------------------------
void testApp::draw()
{
//     /* Leap iGesture Key
//     --------------------------------
//     1 = Screen Tap
//     2 = Key Tap
//     3 = Swipe Right
//     4 = Swipe Left
//     5 = Swipe Down
//     6 = Swipe Up
//     7 = Swipe Forward
//     8 = Swipe Backward (towards yourself)
//     9 = Circle Left (counter-clockwise)
//     10 = Circle Right (clockwise)
//     --------------------------------
//     */
//    
//    string msg;
//    
//    switch (leap.iGestures)
//    {
//        case 1:
//            msg = "Screen Tap";
//            break;
//            
//        case 2:
//            msg = "Key Tap";
//            break;
//            
//        case 3:
//            msg = "Swipe Right";
//            break;
//            
//        case 4:
//            msg = "Swipe Left";
//            break;
//            
//        case 5:
//            msg = "Swipe Down";
//            break;
//            
//        case 6:
//            msg = "Swipe Up";
//            break;
//            
//        case 7:
//            msg = "Swipe Forward";
//            break;
//            
//        case 8:
//            msg = "Swipe Backwards";
//            break;
//            
//        case 9:
//            msg = "Circle Left";
//            break;
//            
//        case 10:
//            msg = "Circle Right";
//            break;
//            
//        default:
//            msg = "Waiting for hand movement...";
//            break;
//    }
//    
//    ofDrawBitmapString(msg, 20, 20);  // let's draw our message to the screen
    //camera.begin();
    for (int i = 0; i < fingerPos.size(); i++) {
        ofVec3f pt;
        pt = fingerPos[i];
        drawSphere(pt, 10);
    }
    
    ofSetColor(255, 255, 255, 255);
	
    
	//first let's just draw the model with the model object
	drawWithModel();
    
    if (phase2 == true && (!spherePos.empty())) {
        ofVec3f temp = spherePos[0];
        //temp.z = -50;
        //drawSphere(temp, 20);
        ofLogNotice("phase 2 triggered position of sphere is", ofToString(temp.x) + " " + ofToString(temp.y) + " " + ofToString(temp.z));
    }
    /*if (phase3 == true  && (!sphereSize.empty())) {
        ofVec3f pt = ofVec3f(-21, -80);
        pt.z = -150;
        ofLogNotice("phase 3 triggered position of sphere is", ofToString(pt.x) + " " + ofToString(pt.y) + " " + ofToString(pt.z));
        ofLogNotice("phase 3 triggered r of sphere is", ofToString(sphereSize[0]));
        drawSphere(pt, sphereSize[0]);
    }*/
    /*for (int i = 0; i < spherePos.size(); i++) {
        drawSphere(spherePos[i], sphereSize[i]*0.8);
    }*/
    
    //camera.end();
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
