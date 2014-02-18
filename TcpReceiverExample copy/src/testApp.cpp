#include "testApp.h"
#define RECONNECT_TIME 400
string message;

//--------------------------------------------------------------
void testApp::setup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(31);
    ofSetWindowShape(600, 600);
    ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();

    typed = false;
    pos = 0;
    msgTx = "";
    msgRx = "";
    weConnected = tcpClient.setup("127.0.0.1", 11999);
    tcpClient.setMessageDelimiter("/r");
    
    connectTime = 0;
    deltaTime = 0;
    
    tcpClient.setVerbose(true);
    
    
}

//--------------------------------------------------------------
void testApp::update(){

    if (weConnected) {
        if (tcpClient.send(msgTx)) {
            string str = tcpClient.receive();
            if (str.length()>0) {
                msgRx = str;
                ofLogNotice("message", msgRx);
                float x,y;
                vector<string> content = ofSplitString(msgRx,"[/p]");
                int state=atoi(content[0].c_str());
                string position = content[1];
                vector<string> tempP = ofSplitString(position, "|");
                ofVec3f pt = ofVec3f(atof(tempP[0].c_str()),atof(tempP[1].c_str()),atof(tempP[2].c_str()));
                string norm = content[2];
                vector<string> tempN = ofSplitString(norm, "|");
                ofVec3f n = ofVec3f(atof(tempN[0].c_str()),atof(tempN[1].c_str()),atof(tempN[2].c_str()));
                float r = atof(content[3].c_str());
                angle = atof(content[4].c_str());
                ofLogNotice("state is", ofToString(state));
                ofLogNotice("position is", ofToString(pt.x)+" "+ofToString(pt.y)+" "+ofToString(pt.z));
                ofLogNotice("norm is", ofToString(n.x)+" "+ofToString(n.y)+" "+ofToString(n.z));
                ofLogNotice("r is", ofToString(r));
                ofLogNotice("angle is", ofToString(angle));
                
                spherePos.clear();
                sphereSize.clear();
                sphereNorm.clear();
                sphereSize.push_back(r);
                spherePos.push_back(pt);
                sphereNorm.push_back(n);

            }

        }else if (!tcpClient.isConnected()){
            weConnected = false;
        }
    }else{
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
        
		if( deltaTime > 5000 ){
			weConnected = tcpClient.setup("127.0.0.1", 11999);
			connectTime = ofGetElapsedTimeMillis();
		}
        
    }
    


}

//--------------------------------------------------------------
void testApp::draw(){
    camera.begin();
    
    if (!sphereSize.empty() && !spherePos.empty()) {
        drawSphere(spherePos[0], sphereSize[0]);
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
