#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);
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
    
    
    cv=0;
    isConnected = tcpClient.setup("127.0.0.1", 11999);
    tcpClient.setMessageDelimiter("/r");
    
    connectTime = 0;
    deltaTime = 0;
    
    tcpClient.setVerbose(true);
    leap.open();
}

//--------------------------------------------------------------
void testApp::update(){

    for(int i=0; i<cv;i++)
    {
    
    if(myvideo[i]!=NULL)
    {
    
    myvideo[i]->update();
    }

    }
    if (isConnected) {
        if (tcpClient.send(msgTx)) {
            string str = tcpClient.receive();
            if (str.length()>0) {
                msgRx = str;
                ofLogNotice("message", msgRx);
                float x,y;
                vector<string> content = ofSplitString(msgRx, "[/p]");
                int state = atoi(content[0].c_str());
                string position = content[1];
                
            }
        }else if(!tcpClient.isConnected()){
            isConnected = false;
        }
    }else{
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
        if (deltaTime > 5000) {
            isConnected = tcpClient.setup("127.0.0.1", 11999);
            connectTime = ofGetElapsedTimeMillis();
        }
    }
    
    //if (state == 2) {
        vector<Hand> hands = leap.getLeapHands();
        if (!hands.empty()) {
            Vector norm = hands[0].palmNormal();
            Vector tmp = norm.normalized();
            string temp = hands[0].palmNormal().toString();
            ofLogNotice("norm is", temp);
            ofLogNotice("normalized", tmp.toString());
            //string direction = hands[0].direction().toString();
            //ofLogNotice("direction is", direction);
        }
     
   // }
    leap.markFrameAsOld();
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i=0; i<cv;i++)
    {
        
        if(myvideo[i]!=NULL)
        {
            
            myvideo[i]->draw();
        }
        
    }
   // int state = 1;
    
    //if(myvideo[0] == NULL)
    //{
    //    cout << "yes"<<endl;
        
    //}
    
    
   
    
    
        
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
    if(cv<numbofvideo && myvideo[cv] ==NULL)
    {
        myvideo[cv] = new ofmyvideo(xlist[cv],ylist[cv],pathlist[cv]);
        myvideo[cv]->play();
        cv++;
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