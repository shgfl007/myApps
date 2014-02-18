//
//  LeapMotion.cpp
//  emptyExample
//
//  Created by Danning Lu on 13-11-2.
//
//

#include "LeapMotion.h"

LeapMotion::LeapMotion(){
}
//-----------------------------------------------------

LeapMotion::~LeapMotion(){
}
//-----------------------------------------------------

void LeapMotion::onInit(const Leap::Controller &controller){
    ofLogNotice("Initialized");
}

//-----------------------------------------------------
void LeapMotion::onConnect(const Leap::Controller &controller){
    ofLogNotice("Connected");
    
    //refresh background and frame
    controller.setPolicyFlags(Leap::Controller::POLICY_BACKGROUND_FRAMES);
}

//-----------------------------------------------------
void LeapMotion::onDisConnect(const Leap::Controller &controller){
    ofLogNotice("Disconnected");
}

//-----------------------------------------------------
void LeapMotion::onFrame(const Leap::Controller &controller){
    
    Leap::Frame frame = controller.frame();
    const Leap::GestureList gestureList = frame.gestures();
    
    //finger positions
    if (mutex.tryLock(2000)) {
        handList = frame.hands();
        fingers.clear();
        for (int cnt = 0; cnt < handList.count(); ++cnt) {
            Leap::FingerList tmpfingerList = handList[cnt].fingers();
            fingers.push_back(tmpfingerList);
        }
        
        mutex.unlock();
    }
}

//----------------------------------------------------
void LeapMotion::onExit(const Leap::Controller &controller){
    ofLogNotice("Exit");
}

//----------------------------------------------------
vector<Leap::FingerList> LeapMotion::getFingers(){
    vector<Leap::FingerList> tmp;
    
    mutex.lock();
    tmp = fingers;
    mutex.unlock();
    
    return tmp;
}