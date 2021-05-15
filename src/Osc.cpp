//
//  OscManager.cpp
//  clip
//
//  Created by roger on 11/08/2017.
//
//

#include "Osc.h"


//------------------------------------------------------------------------------------------
//      CLASS
//------------------------------------------------------------------------------------------

animatron::osc::OscManager::OscManager()
: listenPort(12345)
, remoteIp("localhost")
, remotePort(54321)
{
    ofLogVerbose() << __FUNCTION__ << ": Automatically listening to 'update' event";
    // automatically update without needing to call it from ofApp
    ofAddListener(ofEvents().update, this, &animatron::osc::OscManager::update);
    
    counterfortest=0;
}

animatron::osc::OscManager::~OscManager()
{
    ofRemoveListener(ofEvents().update, this, &animatron::osc::OscManager::update);
    ofLogVerbose() << __FUNCTION__ << ": OscManager object destroyed";
}

void animatron::osc::OscManager::setup(int newListenPort, string newRemoteIp, int newRemotePort)
{
    receiver.setup(newListenPort);
    ofLogNotice() << "OSC listening on port " << newListenPort;
    sender.setup(newRemoteIp, newRemotePort);
}

void animatron::osc::OscManager::setup(int port) {
    setup(port, remoteIp, remotePort);
}

void animatron::osc::OscManager::update()
{
    while (receiver.hasWaitingMessages()) {
        Message m;
        if (receiver.getNextMessage(m)) {
            printMessage(m);
            // notify all the listeners about this message and send it to them
            ofNotifyEvent(newOscMessageEvent, m, this);
        }
        
    }
    
    
}

void animatron::osc::OscManager::update(ofEventArgs& e)
{
    update();
}

void animatron::osc::OscManager::listenToPort(const int port)
{
    listenPort = port;
    ofLogVerbose() << __FUNCTION__ << ": Now listening to port " << listenPort;
}

void animatron::osc::OscManager::sendMessage(animatron::osc::Message& m)
{
    sender.sendMessage(m);
    printMessage(m, "Sent OSC:");
}

//------------------------------------------------------------------------------------------
//      INTERFACE FUNCTIONS
//------------------------------------------------------------------------------------------

void animatron::osc::printMessage(const animatron::osc::Message& m, const string& prepend, const ofLogLevel& loglevel)
{
    //    ofLogVerbose() << typeid(this).name() << "::" << __FUNCTION__;
    string msg = prepend;
    msg += animatron::osc::getPrintableMessage(m);
    
    ofLogVerbose()<<"osc: "<<msg;
}

string animatron::osc::getPrintableMessage(const animatron::osc::Message& m)
{
    string msg;
    msg = m.getAddress();
    msg += " \t";
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg += m.getArgTypeName(i);
        msg += ":";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg += m.getArgAsString(i);
        }
        else{
            msg += "unknown";
        }
        
//        msg += "\t";
        if(i < m.getNumArgs()-1) msg += ", ";
    }
    
    return msg;
}

string animatron::osc::getSimplifiedMessage(const animatron::osc::Message& m)
{
    string msg;
    msg = m.getAddress();
    msg += " \t";
    for(int i = 0; i < m.getNumArgs(); i++){
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//            msg += "\"" + m.getArgAsString(i) + "\"";
            msg += m.getArgAsString(i);
        }
        else{
            msg += "unknown";
        }
        
        msg += " ";
    }
    
    return msg;
}
