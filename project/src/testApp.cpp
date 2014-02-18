#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0, 0);
    ofDisableArbTex();
    light.enable();
    glEnable(GL_DEPTH_TEST);
    
    TCP.setup(12999);
    TCP.setMessageDelimiter("/r");
    
    ofEnableDepthTest();
    mypetals= new ofPetal(ofGetWidth(),ofGetHeight());
    lotus1 = new ofLotus(ofGetWidth(),ofGetHeight(),0.7,1.0,0.5);
    myglowry = new ofglowry(500,150,50);
    mybuddha = new ofBuddhaeyes(10,4,512,384,"buddhaeye.png");
    mygesture = new ofGesture();
    
    
 //   dampen = .4;
    
    state =0;
}

//--------------------------------------------------------------
void testApp::update(){
    
        mypetals->update();
    mygesture->update();
    
     if(mygesture->gs1check())
    {
        
        state=1;
        //ofLogNotice("heshi", ofToString(mygesture->gs1check()));
    }
    
    
    
    if(state==1)
    {
      lotus1->update(mygesture->gs2check());
        
        if(lotus1->condition()){
            mybuddha->update();
           // ofLogNotice("message", ofToString(msgTx));
            myglowry->update();
          /* if(sendflag==false)
           {
            msgTx="1[/p]";
               
            TCP.sendToAll(msgTx);
               sendflag=true;
           }
            if (angle> -0.5 && angle < 0.5) {
                count++;
            }
            ofLogNotice("count is", ofToString(count));
            if (count == 40) {
                //message format state[/p]x|y|z[/p]new_video
                msgTx = "1[/p]x|y|z[/p]1";
                TCP.sendToAll(msgTx);
                count = 0;
                ofLogNotice("count is", ofToString(count));
            }else{
                //msgTx = "1[/p]x|y|z[/p]0";
                //TCP.sendToAll(msgTx);
            }

        */
        }
        //ofLogNotice("stop", ofToString(lotus1->condition()));
    
        
    }
    
    
    
        
    

}

//--------------------------------------------------------------
void testApp::draw(){
    //mypetal1->drawWithModel();
    
 
    
    
    if(state == 0)
    {
    ofSetColor(255, 255, 255);
    mypetals->drawpetal();
        mygesture->drawfinger();
        
        
    }
    if(state == 1)
    {
        mypetals->clear();
        
     
        
        lotus1->drawWithModel();
      
        if(lotus1->condition())
        {
            
        ofPopMatrix();
        mybuddha->draw();
        myglowry->draw();
            mygesture->drawmainsphere();
        
        
        
        }

        
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
    
   // if(button == 0)
   // {
    //    state=1;
        
   // }
    
   // lastMouse = ofVec2f(x,y);
    

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

void testApp::exit()
{
    mygesture->clean();
    mybuddha->clean();
    mypetals->clear();
    myglowry->clean();
    
    free (mybuddha);
    free(mygesture);
    free(mypetals);
    free(myglowry);// let's close down Leap and kill the controller
}







