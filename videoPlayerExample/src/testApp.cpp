#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(254,254,254);
	ofSetVerticalSync(true);
	frameByframe = false;
    isdraw = true;
	// Uncomment this to show movies with alpha channels
	// fingerMovie.setPixelFormat(OF_PIXELS_RGBA);
    
	fingerMovie.loadMovie("movies/fingers.mov");
    //fingerMovie.loadMovie("movies/ar.mov");
    movieH = fingerMovie.getHeight();
    movieW = fingerMovie.getWidth();
    ratio = movieW/movieH;
	fingerMovie.play();
    size = ofRandom(100, 400);
    size = 300;
}

//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetHexColor(0xFFFFFF);
    if (isdraw) {
        fingerMovie.draw(x0,y0,size*ratio,size);
        fingerMovie.update();
    }
    
    ofSetHexColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    
    int nChannels = fingerMovie.getPixelsRef().getNumChannels();
    
    // let's move through the "RGB(A)" char array
    // using the red pixel to control the size of a circle.
    for (int i = 4; i < 320; i+=8){
        for (int j = 4; j < 240; j+=8){
            unsigned char r = pixels[(j * 320 + i)*nChannels];
            float val = 1 - ((float)r / 255.0f);
            ofCircle(400 + i,20+j,10*val);
        }
    }
//
//
//    ofSetHexColor(0x000000);
//	ofDrawBitmapString("press f to change",20,320);
//    if(frameByframe) ofSetHexColor(0xCCCCCC);
//    ofDrawBitmapString("mouse speed position",20,340);
//    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
//    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
//    ofSetHexColor(0x000000);
//
//    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
//    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
//    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);
//    fingerMovie.setLoopState(OF_LOOP_NORMAL);
//    if(fingerMovie.getIsMovieDone()){
//        ofSetHexColor(0xFF0000);
//        ofDrawBitmapString("end of movie",20,440);
//    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
//    switch(key){
//        case 'f':
//            frameByframe=!frameByframe;
//            fingerMovie.setPaused(frameByframe);
//        break;
//        case OF_KEY_LEFT:
//            fingerMovie.previousFrame();
//        break;
//        case OF_KEY_RIGHT:
//            fingerMovie.nextFrame();
//        break;
//        case '0':
//            fingerMovie.firstFrame();
//        break;
//    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
//	if(!frameByframe){
//        int width = ofGetWidth();
//        float pct = (float)x / (float)width;
//        float speed = (2 * pct - 1) * 5.0f;
//        fingerMovie.setSpeed(speed);
//	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
//	if(!frameByframe){
//        int width = ofGetWidth();
//        float pct = (float)x / (float)width;
//        fingerMovie.setPosition(pct);
//	}
    //x0 = x; y0 = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//	if(!frameByframe){
//        fingerMovie.setPaused(true);
    
    fingerMovie.close();
    isdraw = false;
//	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
//	if(!frameByframe){
//        fingerMovie.setPaused(false);
//	}
    
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
