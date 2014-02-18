//
//  tcpReceiver.h
//  emptyExample
//
//  Created by Danning Lu on 2014-01-27.
//
//

#ifndef __emptyExample__tcpReceiver__
#define __emptyExample__tcpReceiver__

#include <iostream>
#include "ofMain.h"
#include "ofxNetwork.h"

class tcpReceiver{
    
public:
    tcpReceiver();
    void setIP(string ip);
    void setPort(int port);
    tcpReceiver(string ip, int port);
    int getState();
    string getPosition();
    void readMsg();
    bool isConnected;
    void splitMsg();
    
private:
    
    ofxTCPClient tcpClient;
    string msgTx, msgRx;
    
    float counter;
    int connectTime;
    int deltaTime;
    int state;
    string position;
    
    
    
};


#endif /* defined(__emptyExample__tcpReceiver__) */
