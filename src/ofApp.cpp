#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex();
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofBackground(0);

    cam.enableMouseInput();
    cam.enableOrtho();

    animatron::config::load();

    // setup MIDI
    midiin = animatron::midi::setup(
                animatron::config::getMidiInPort(),
                animatron::config::getMidiMapFilename(),
                this);
    midimap = animatron::midi::getMidiMap();

    // setup OSC mapper -----------------------------------------------------
    osc.setup(animatron::config::getOscListenPort(),
              animatron::config::getOscRemoteIp(),
              animatron::config::getOscRemotePort());
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::mapMessageToFunc);
    // app ------------------------------------------------------------------
    messageMap["/help"] = &ofApp::help;
    messageMap["/verbose"] = &ofApp::verbose;
    messageMap["/silent"] = &ofApp::silent;
    messageMap["/config"] = &ofApp::config;
    messageMap["/midiports"] = &ofApp::listMidiPorts;
    messageMap["/midiport"] = &ofApp::setMidiPort;
    messageMap["/midimap"] = &ofApp::setMidiMap;
    // 3d cam ---------------------------------------------------------------
    messageMap["/ortho"] = &ofApp::toggleOrthographicCamera;
    // node -----------------------------------------------------------------
    messageMap["/new"] = &ofApp::newNode;
    messageMap["/newat"] = &ofApp::newNodeAt;
    messageMap["/remove"] = &ofApp::removeNodes;
    messageMap["/list"] = &ofApp::listNodes;
    messageMap["/selected"] = &ofApp::listSelectedNodes;
    messageMap["/info"] = &ofApp::logNodeInfo;
    messageMap["/select"] = &ofApp::selectNode;
    messageMap["/deselect"] = &ofApp::deselectNode;
    messageMap["/move"] = &ofApp::moveNodes;
    messageMap["/moveto"] = &ofApp::moveNodesTo;
    messageMap["/rotate"] = &ofApp::rotateNodes;
    messageMap["/scale"] = &ofApp::scaleNodes;
    // image sequence -------------------------------------------------------
    messageMap["/sequence"] = &ofApp::addImageSequence;
    messageMap["/texture"] = &ofApp::setTexture;
    messageMap["/play"] = &ofApp::playNodes;
    messageMap["/playfrom"] = &ofApp::playNodesFromList;
    messageMap["/reverse"] = &ofApp::reverseNodes;
    messageMap["/pause"] = &ofApp::pauseNodes;
    messageMap["/stop"] = &ofApp::stopNodes;
    messageMap["/goto"] = &ofApp::gotoFrame;
    messageMap["/gotopct"] = &ofApp::gotoPercent;
    messageMap["/fps"] = &ofApp::setNodesFps;
    messageMap["/normfps"] = &ofApp::setNodesNormalizedFps;
    messageMap["/speed"] = &ofApp::setNodesSpeed;
    messageMap["/loop"] = &ofApp::loopNodes;
    messageMap["/noloop"] = &ofApp::noloopNodes;
    messageMap["/pingpong"] = &ofApp::pingpongNodes;
}

//--------------------------------------------------------------
void ofApp::update(){
    animatron::node::updateNodes();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    glAlphaFunc(GL_GREATER,0.1f);
    glEnable(GL_ALPHA_TEST);
    ofEnableDepthTest();
    animatron::node::drawNodes();
    ofDisableDepthTest();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::exit(){
    animatron::midi::exit(this);
}

//--------------------------------------------------------------
void ofApp::mapMessageToFunc(animatron::osc::Message & msg) {
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
//        animatron::osc::logMessage(msg);
    } else {
        ofLogError() << "Unhandled OSC message: " << msg.getAddress();
    }
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(animatron::midi::Message & msg) {
    vector<animatron::osc::Message> oscmsgs = animatron::midi::getOscFromMidi(msg, midimap);
    for(auto oscmsg : oscmsgs) {
        mapMessageToFunc(oscmsg);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
      case 'o':
            cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::help(const animatron::osc::Message & msg) {
    vector<string> oscMessages;
    ofLog() << "------- OSC INTERFACE";
    for(const auto &item : messageMap) {
        oscMessages.push_back(item.first);
        ofLog() << item.first;
    }
}

//--------------------------------------------------------------
void ofApp::verbose(const animatron::osc::Message & msg) {
   ofSetLogLevel(OF_LOG_VERBOSE);
}

//--------------------------------------------------------------
void ofApp::silent(const animatron::osc::Message & msg) {
   ofSetLogLevel(OF_LOG_NOTICE);
}

//--------------------------------------------------------------
void ofApp::config(const animatron::osc::Message & msg) {
   animatron::config::print();
}

//--------------------------------------------------------------
void ofApp::listMidiPorts(const animatron::osc::Message & msg) {
    midiin->listInPorts();
}

//--------------------------------------------------------------
void ofApp::setMidiPort(const animatron::osc::Message & msg) {
    midiin->closePort();
    midiin->openPort(msg.getArgAsInt(0)); // by number
}

//--------------------------------------------------------------
void ofApp::setMidiMap(const animatron::osc::Message & msg) {
    midimap = animatron::midi::loadFunctionMap(msg.getArgAsString(0));
}

//--------------------------------------------------------------
void ofApp::listNodes(const animatron::osc::Message & msg) {
    animatron::node::listNodes();
}

//--------------------------------------------------------------
void ofApp::listSelectedNodes(const animatron::osc::Message & msg) {
    animatron::node::listSelectedNodes();
}

//--------------------------------------------------------------
void ofApp::selectNode(const animatron::osc::Message & msg) {
    string name = msg.getArgAsString(0);
    animatron::node::select(name);
    animatron::node::log(name);
}

//--------------------------------------------------------------
void ofApp::deselectNode(const animatron::osc::Message & msg) {
    string name = msg.getArgAsString(0);
    animatron::node::deselect(name);
}

//--------------------------------------------------------------
void ofApp::removeNodes(const animatron::osc::Message & msg) {
    ofLog() << "--- Nodes info\n";
    if(msg.getNumArgs() == 0) {
        animatron::node::removeNodes();
    } else {
        for(int i = 0; i < msg.getNumArgs(); i++) {
            animatron::node::remove(msg.getArgAsString(i));
        }
    }
}

//--------------------------------------------------------------
void ofApp::moveNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::moveNodes(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
    } else if(msg.getNumArgs() == 3) {
        animatron::node::move(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 2 or 3.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::moveNodesTo(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::moveNodesTo(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
    } else if(msg.getNumArgs() == 3) {
        animatron::node::moveTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 2 or 3.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::rotateNodes(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::rotateNodes(msg.getArgAsFloat(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::rotate(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::scaleNodes(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::scaleNodes(msg.getArgAsFloat(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::scale(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::setTexture(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::setNodesTexture(msg.getArgAsString(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(1));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::newNode(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::image::addSequenceFromPath(animatron::config::getAppSupportPath()+"/imgs/"+msg.getArgAsString(0));
        animatron::node::create(msg.getArgAsString(0));
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(0));
    } else if (msg.getNumArgs() == 2) {
        animatron::image::addSequenceFromPath(animatron::config::getAppSupportPath()+"/imgs/"+msg.getArgAsString(1));
        animatron::node::create(msg.getArgAsString(0));
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(1));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::newNodeAt(const animatron::osc::Message & msg) {
    if (msg.getNumArgs() == 3) {
        animatron::node::create(
                    msg.getArgAsString(0),
                    msg.getArgAsFloat(1),
                    msg.getArgAsFloat(2));
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(0));
    } else if (msg.getNumArgs() == 3) {
        animatron::node::create(
                    msg.getArgAsString(0),
                    msg.getArgAsFloat(1),
                    msg.getArgAsFloat(2));
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(3));
    } else {
        ofLogError("osc")<<"Wrong number of arguments.  Expected 3 or 4.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::logNodeInfo(const animatron::osc::Message & msg) {
    ofLog() << "--- Nodes info\n";
    if(msg.getNumArgs() == 0) {
        animatron::node::logNodes();
    } else {
        for(int i = 0; i < msg.getNumArgs(); i++) {
            animatron::node::log(msg.getArgAsString(i));
        }
    }
}

//--------------------------------------------------------------
void ofApp::toggleOrthographicCamera(const animatron::osc::Message & msg) {
    cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
}

//--------------------------------------------------------------
void ofApp::addImageSequence(const animatron::osc::Message & msg) {
    animatron::image::addSequenceFromPath(animatron::config::getAppSupportPath() + "/imgs/" + msg.getArgAsString(1));
}

//--------------------------------------------------------------
//void ofApp::loadImageSequence(const animatron::osc::Message & msg) {
//    // arg(0) is node name, arg(1) is sequence name
//    bool ok = animatron::image::addSequence(msg.getArgAsString(1), animatron::config::getAppSupportPath() + "/imgs/" + msg.getArgAsString(1));
//    if (ok) animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(1));
////    else animatron::node::setTexture(msg.getArgAsString(0), ofToDataPath("imgs/default"));
//}

//--------------------------------------------------------------
void ofApp::playNodes(const animatron::osc::Message & msg) {
    // TODO: change Nodes for Node (??)
    if(msg.getNumArgs() == 1) {
        animatron::node::play(msg.getArgAsString(0));
    } else {
        animatron::node::play();
    }
}

//--------------------------------------------------------------
void ofApp::playNodesFromList(const animatron::osc::Message & msg) {
   animatron::node::playFromList(msg.getArgAsInt(0), msg.getArgAsString(1));
}

//--------------------------------------------------------------
void ofApp::reverseNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::reverse(msg.getArgAsString(0));
    } else {
        animatron::node::reverse();
    }
}

//--------------------------------------------------------------
void ofApp::pauseNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::pause(msg.getArgAsString(0));
    } else {
        animatron::node::pause();
    }
}

//--------------------------------------------------------------
void ofApp::stopNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::stop(msg.getArgAsString(0));
    } else {
        animatron::node::stop();
    }
}

//--------------------------------------------------------------
void ofApp::gotoFrame(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::gotoFrame(msg.getArgAsString(0), msg.getArgAsInt(1));
    } else {
        animatron::node::gotoFrame(msg.getArgAsInt(0));
    }
}

//--------------------------------------------------------------
void ofApp::gotoPercent(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::gotoFrame(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        animatron::node::gotoFrame(msg.getArgAsFloat(0));
    }
}

//--------------------------------------------------------------
void ofApp::setNodesFps(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::setFps(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        animatron::node::setFps(msg.getArgAsFloat(0));
    }
}

//--------------------------------------------------------------
void ofApp::setNodesNormalizedFps(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 3) {
        animatron::node::setFps(msg.getArgAsString(0), msg.getArgAsFloat(1) * msg.getArgAsFloat(2));
    } else {
        animatron::node::setFps(msg.getArgAsFloat(0) * msg.getArgAsFloat(1));
    }
}

//--------------------------------------------------------------
void ofApp::setNodesSpeed(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::setFrameRate(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        animatron::node::setFrameRate(msg.getArgAsFloat(0));
    }
}

//--------------------------------------------------------------
void ofApp::loopNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::loop(msg.getArgAsString(0));
    } else {
        animatron::node::loop();
    }
}

//--------------------------------------------------------------
void ofApp::noloopNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::noloop(msg.getArgAsString(0));
    } else {
        animatron::node::noloop();
    }
}

//--------------------------------------------------------------
void ofApp::pingpongNodes(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::pingpong(msg.getArgAsString(0));
    } else {
        animatron::node::pingpong();
    }
}
