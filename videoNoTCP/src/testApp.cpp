#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    state=0;
    ofSetFrameRate(60);
    ofDisableArbTex();
	ofEnableDepthTest();
    ofBackground(31);
    ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();
    //--------------------------------Load Video Clips ------------------------
    pathlist[0]="movies/1.mov";
    pathlist[1]="movies/2.mov";
    pathlist[2]="movies/3.mov";
    pathlist[3]="movies/1.mov";
    pathlist[4]="movies/2.mov";
    pathlist[5]="movies/3.mov";
    pathlist[6]="movies/1.mov";
    pathlist[7]="movies/2.mov";
    pathlist[8]="movies/3.mov";
    pathlist[9]="movies/1.mov";
    pathlist[10]="movies/2.mov";
    pathlist[11]="movies/3.mov";
    pathlist[12]="movies/1.mov";
    pathlist[13]="movies/2.mov";
    pathlist[14]="movies/3.mov";
    pathlist[15]="movies/1.mov";
    myvideo = new ofmyvideo*[numbofvideo];
    cv=0;//count = 0;
    
    //------------------------------- Load 3D Models --------------------------
//    model1.loadModel("3dmodel/leaf.obj");
//    model2.loadModel("3dmodel/leaf.obj");
//    model3.loadModel("3dmodel/leaf.obj");
//    model4.loadModel("3dmodel/leaf.obj");
//    model5.loadModel("3dmodel/leaf.obj");
//    model6.loadModel("3dmodel/leaf.obj");
//    model7.loadModel("3dmodel/leaf.obj");
//    model8.loadModel("3dmodel/leaf.obj");
//    model9.loadModel("3dmodel/leaf.obj");
//    model10.loadModel("3dmodel/leaf.obj");
//    lotus.loadModel("3dmodel/lotus.obj");
//    circle.loadModel("3dmodel/circle.obj");
//    model1.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.05, 0);
//    model2.setPosition(ofGetWidth()*.4, ofGetHeight() * 0.3, 2);
//    model3.setPosition(ofGetWidth()*.3, ofGetHeight() * 0.05, 4);
//    model4.setPosition(ofGetWidth()*.8, ofGetHeight() * 0.2, 2);
//    model5.setPosition(ofGetWidth()*.2, ofGetHeight() * 0.1, 3);
//    model6.setPosition(ofGetWidth()*.75, ofGetHeight() * 0.7, 2);
//    model7.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.8, 1);
//    model8.setPosition(ofGetWidth()*.7, ofGetHeight() * 0.6, 3);
//    model9.setPosition(ofGetWidth()*.55, ofGetHeight() * 0.1, 5);
//    model10.setPosition(ofGetWidth()*.65, ofGetHeight() * 0.2, 2);
//    lotus.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.5, 0);
//    circle.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.5, 0);
    
    
    //----------------------------- TCP -----------------------------------------
//    isConnected = tcpClient.setup("169.254.236.103", 12999);
//    tcpClient.setMessageDelimiter("/r");
//    
//    connectTime = 0;
//    deltaTime = 0;
//    
//    tcpClient.setVerbose(true);
    
    //---------------------------- Leap -----------------------------------------
    leap.open();
}

//--------------------------------------------------------------
void testApp::update(){
    int drop =0;
    //------------------------------ animation ----------------------------------
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
    
    if(radius < 1.0 && drop == 1)
    {radius +=0.005;
        //lotus.clear();
    }
    else if(radius > 1.0)
    {radius = 0.001;
        drop=0;}
    rdegree += 5;
    
    
    //---------------------------- TCP communication ----------------------------
//    if (cv == numbofvideo) {
//        msgTx = "1[/p]1"; //serial_number_of_client[/p]is_all_video_triggered
//    }else{
//        msgTx = "1[/p]0"; 
//    }
//    if (isConnected) {
//        if (tcpClient.send(msgTx)) {
//            //message format state[/p]x|y|z[/p]new_video
//            string str = tcpClient.receive();
//            if (str.length()>0) {
//                msgRx = str;
//                ofLogNotice("message", msgRx);
//                float x,y;
//                vector<string> content = ofSplitString(msgRx, "[/p]");
//                state = atoi(content[0].c_str());
//                
//                if (msgRx.length()>5) {
//                    string position = content[1];
//                    if (content.size()>=3) {
//                        isNewVideo = atoi(content[2].c_str());
//                    }
//                    
//                }
//                
//            }
//        }else if(!tcpClient.isConnected()){
//            isConnected = false;
//        }
//    }else{
//        deltaTime = ofGetElapsedTimeMillis() - connectTime;
//        if (deltaTime > 5000) {
//            isConnected = tcpClient.setup("169.254.236.103", 12999);
//            connectTime = ofGetElapsedTimeMillis();
//        }
//    }
    
    //----------------------------- Video Clips update ---------------------------
//    if (state == 1 && isNewVideo == 1) {
//        if(cv<numbofvideo && myvideo[cv] ==NULL)
//        {
//            myvideo[cv] = new ofmyvideo(xlist[cv],ylist[cv],pathlist[cv]);
//            myvideo[cv]->play();
//            cv++;
//        }
//        isNewVideo = 0;
//    }
    
    if (state == 1) {
        for(int i=0; i<cv;i++)
        {
            
            if(myvideo[i]!=NULL)
            {
                
                myvideo[i]->update();
            }
            
        }
    }
    if (cv==numbofvideo) {
        state=2;
        
    }
    if (state == 2) {
        videoList.clear();
        for(int i=0; i<cv;i++)
        {
            
            if(myvideo[i]!=NULL && myvideo[i]->isDraw)
            {
                
                myvideo[i]->update();
                videoList.push_back(*myvideo[i]);
            }
            
        }
        ofLogNotice("count is", ofToString(videoList.size()));
//        if (count == 0) {
//            state=3;
//            ofLogNotice("state is", "3");
//        }
    }
  
    //--------------------------- Leap Data Collection ----------------------------
    //if (state == 2) {
    vector<Hand> hands = leap.getLeapHands();
    if (!hands.empty()) {
        Vector norm = hands[0].palmNormal();
        
        float rad = norm.angleTo(norm.forward());
        string temp = hands[0].palmNormal().toString();
        //ofLogNotice("norm is", temp);
        float angle = ofRadToDeg(rad);
        //ofLogNotice("angle is", ofToString(angle));
        if (angle<40 && angle > 10) {
            pause = true;
        }else{
            pause = false;
        }
    }
    for(int i=0; i<cv;i++)
    {
        
        if(myvideo[i]!=NULL)
        {
            
            myvideo[i]->pause(pause);
        }
        
    }
    
    // }
    leap.markFrameAsOld();
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    if (state==0) {
        //drawWithModel();
    }else if(state ==1){
        for(int i=0; i<cv;i++)
        {
        
            if(myvideo[i]!=NULL)
            {
                
                myvideo[i]->draw();
            }
        
        }
    }else if (state == 2)
    {
        //count = 0;
        for(int i=0; i<cv;i++)
        {
            
            if(myvideo[i]!=NULL && myvideo[i]->isDraw)
            {
                
                myvideo[i]->draw();
                //count++;
            }
            
        }
    }
    // int state = 1;
    
    //if(myvideo[0] == NULL)
    //{
    //    cout << "yes"<<endl;
    
    //}
    
    
    
    
    
    
}
//--------------------------------------------------------------
//void testApp::drawWithModel(){
//    //leaf one
//    
//    ofVec3f position1 = model1.getPosition();
//    
//    //save the current view
//    ofPushMatrix();
//    
//    //center ourselves there
//    ofTranslate(position1);
//    ofRotate(rdegree, 0, 1, 0);
//    ofScale(0.15,0.15,0.15);
//    ofRotate(90,1,0,0);
//    ofTranslate(-position1);
//    //draw the model
//    model1.drawFaces();
//    //restore the view position
//    
//    ofPopMatrix();
//    model1.setPosition(ofGetWidth()*0.5, ofGetHeight()*height1, 0);
//    
//    
//    //leaf two
//    ofVec3f position2 = model2.getPosition();
//    //save the current view
//    ofPushMatrix();
//    //center ourselves there
//    ofTranslate(position2);
//    ofRotate(rdegree, 0, 1, 0);
//    ofScale(0.3,0.3,0.3);
//    ofRotate(60,1,0,0);
//    ofTranslate(-position2);
//    //draw the model
//    model2.drawFaces();
//    //restore the view position
//    ofPopMatrix();
//    model2.setPosition(ofGetWidth()*0.4, ofGetHeight()*height2, 0);
//    
//    
//    ofVec3f position3 = model3.getPosition();
//    
//    ofPushMatrix();
//    //center ourselves there
//    ofTranslate(position3);
//    ofRotate(rdegree, 0, 1, 0);
//    ofScale(0.15,0.15,0.15);
//    ofRotate(90,1,0,0);
//    ofTranslate(-position3);
//    //draw the model
//    model3.drawFaces();
//    //restore the view position
//    ofPopMatrix();
//    model3.setPosition(ofGetWidth()*0.3, ofGetHeight()*height3, 0);
//    
//    //leaf two
//    ofVec3f position4 = model4.getPosition();
//    //save the current view
//    ofPushMatrix();
//    //center ourselves there
//    ofTranslate(position4);
//    ofRotate(rdegree, 0, 1, 0);
//    ofScale(0.1,0.1,0.1);
//    ofRotate(60,1,0,0);
//    ofTranslate(-position4);
//    //draw the model
//    model4.drawFaces();
//    //restore the view position
//    ofPopMatrix();
//    model4.setPosition(ofGetWidth()*0.8, ofGetHeight()*height4, 0);
//    
//    ofVec3f position5 = model5.getPosition();
//    //save the current view
//    ofPushMatrix();
//    //center ourselves there
//    ofTranslate(position5);
//    ofRotate(rdegree, 0, 1, 0);
//    ofScale(0.1,0.1,0.1);
//    ofRotate(120,1,0,0);
//    ofTranslate(-position5);
//    //draw the model
//    model5.drawFaces();
//    //restore the view position
//    ofPopMatrix();
//    model5.setPosition(ofGetWidth()*0.2, ofGetHeight()*height5, 0);
//    
//    ofVec3f position7 = circle.getPosition();
//    //save the current view
//    ofPushMatrix();
//    //center ourselves there
//    ofTranslate(position7);
//    //ofRotate(rdegree, 0, 1, 0);
//    ofScale(radius,radius,radius);
//    //ofRotate(120,1,0,0);
//    ofTranslate(-position7);
//    //draw the model
//    circle.drawFaces();
//    //restore the view position
//    ofPopMatrix();
//    circle.setPosition(ofGetWidth()*0.5, ofGetHeight()*0.85, 0);
//    
//
//}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    if (state==2) {
        for (int i = 0; i<cv; i++) {
            if (myvideo[i]->getPosX()<=x && (myvideo[i]->getPosX()+myvideo[i]->width)>=x && myvideo[i]->getPosY() <= y && (myvideo[i]->getPosY()+myvideo[i]->height)>=y) {
                myvideo[i]->close();
                count--;
                ofLogNotice("decrease count", ofToString(count));
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(state == 0) state=1;
    else if(state==1&&cv<numbofvideo && myvideo[cv] ==NULL)
    {
        myvideo[cv] = new ofmyvideo(xlist[cv],ylist[cv],pathlist[cv]);
        myvideo[cv]->play();
        cv++;count++;
    }
    
    
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
void testApp::exit(){
    leap.close();
}