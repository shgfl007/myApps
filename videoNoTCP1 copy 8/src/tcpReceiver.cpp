//
//  tcpReceiver.cpp
//  emptyExample
//
//  Created by Danning Lu on 2014-01-27.
//
//

#include "tcpReceiver.h"
#include <string>


//tcpReceiver::tcpReceiver(string ip, int port)
//{
//    msgTx = "";
//    msgRx = "";
//    isConnected =tcpClient.setup(string ip, int port);
//    tcpClient.setMessageDelimiter("/r");
//    
//    connectTime = 0;
//    deltaTime = 0;
//    tcpClient.setVerbose(true);
//}
//
//void tcpReceiver::splitMsg()
//{
//    if(isConnected){
//        if (tcpClient.send(msgTx)) {
//            string str = tcpClient.receive();
//            if (str.length()>0) {
//                msgRx = str;
//                ofLogNotice("message", msgRx);
//                vector<string> content = ofSplitString(msgRx, "[/p]");
//                state = atoi(content[0].c_str());
//                position = content[1];
//            }
//        }
//    }
//}
//
//int tcpReceiver::getState()
//{
//    return state;
//}
//
//string tcpReceiver::getPosition()
//{
//    return position;
//}



