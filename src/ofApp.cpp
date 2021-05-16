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
    midiIn = animatron::midi::setup(animatron::config::getMidiInPort());
    // add ofApp as a listener
    midiIn->addListener(this);
    midiMap = animatron::midi::loadFunctionMap("midi-interface_default.json");

    // setup OSC mapper
//    osc.setup(animatron::config::getOscPort());
    osc.setup(animatron::config::getOscListenPort(),
              animatron::config::getOscRemoteIp(),
              animatron::config::getOscRemotePort());
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::mapMessageToFunc);
    // app
    messageMap["/help"] = &ofApp::help;
    messageMap["/verbose"] = &ofApp::verbose;
    messageMap["/silent"] = &ofApp::silent;
    messageMap["/config"] = &ofApp::config;
    messageMap["/midiports"] = &ofApp::listMidiPorts;
    messageMap["/midiport"] = &ofApp::setMidiPort;
    // node
    messageMap["/new"] = &ofApp::newNode;
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
    messageMap["/settexture"] = &ofApp::setTexture;
    // 3d cam
    messageMap["/ortho"] = &ofApp::toggleOrthographicCamera;
    // image sequence
    messageMap["/animation"] = &ofApp::loadImageSequence;
    messageMap["/play"] = &ofApp::playNodes;
    messageMap["/reverse"] = &ofApp::reverseNodes;
    messageMap["/pause"] = &ofApp::pauseNodes;
    messageMap["/stop"] = &ofApp::stopNodes;
    messageMap["/goto"] = &ofApp::gotoFrame;
    messageMap["/fps"] = &ofApp::setNodesFps;
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
    midiIn->closePort();
    midiIn->removeListener(this);
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
    midiMessages.push_back(msg);

    // a queue of midi messages
    while(midiMessages.size() > maxMidiMessages) {
        midiMessages.erase(midiMessages.begin());
    }

    animatron::osc::Message oscmsg;

    // TODO: recursively convert MIDI map info to OSC message
    msg.getStatusString(msg.status);
    ofLogVerbose("midi")<<(*midiMap)["note on"][0][0];

//    switch(msg.status) {
//        case MIDI_NOTE_OFF:
//            ofLogVerbose("midi")<<"Note Off";
//        case MIDI_NOTE_ON:
//            ofLogVerbose("midi")<<"NoteOn ch: "<<msg.channel<<" pitch: "<<msg.pitch<<" vel: "<<msg.velocity;
//            oscmsg.setAddress("/goto");
//            oscmsg.addInt32Arg(msg.pitch);
//            osc.sendMessage(oscmsg);
//        case MIDI_CONTROL_CHANGE:
//            ofLogVerbose("midi")<<"Control Change";
//        case MIDI_PROGRAM_CHANGE:
//            ofLogVerbose("midi")<<"Program Change";
//        case MIDI_PITCH_BEND:
//            ofLogVerbose("midi")<<"Pitch Bend";
//        case MIDI_AFTERTOUCH:
//            ofLogVerbose("midi")<<"Aftertouch";
//        case MIDI_POLY_AFTERTOUCH:
//            ofLogVerbose("midi")<<"Poly Aftertouch";
//        case MIDI_SYSEX:
//            ofLogVerbose("midi")<<"Sysex";
//        case MIDI_TIME_CODE:
//            ofLogVerbose("midi")<<"Time Code";
//        case MIDI_SONG_POS_POINTER:
//            ofLogVerbose("midi")<<"Song Pos";
//        case MIDI_SONG_SELECT:
//            ofLogVerbose("midi")<<"Song Select";
//        case MIDI_TUNE_REQUEST:
//            ofLogVerbose("midi")<<"Tune Request";
//        case MIDI_SYSEX_END:
//            ofLogVerbose("midi")<<"Sysex End";
//        case MIDI_TIME_CLOCK:
//            ofLogVerbose("midi")<<"Time Clock";
//        case MIDI_START:
//            ofLogVerbose("midi")<<"Start";
//        case MIDI_CONTINUE:
//            ofLogVerbose("midi")<<"Continue";
//        case MIDI_STOP:
//            ofLogVerbose("midi")<<"Stop";
//        case MIDI_ACTIVE_SENSING:
//            ofLogVerbose("midi")<<"Active Sensing";
//        case MIDI_SYSTEM_RESET:
//            ofLogVerbose("midi")<<"System Reset";
//        default:
//            ofLogVerbose("midi")<<"Unknown";
//    }

    // ofxMidiIn.verbose() works better than this
//    animatron::midi::logMessage(msg);
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
    midiIn->listInPorts();
}

//--------------------------------------------------------------
void ofApp::setMidiPort(const animatron::osc::Message & msg) {
    midiIn->closePort();
    midiIn->openPort(msg.getArgAsInt(0)); // by number
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
        ofLogError()<<"Wrong number of arguments.  Expected 2 or 3.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::moveNodesTo(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::moveNodesTo(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
    } else if(msg.getNumArgs() == 3) {
        animatron::node::moveTo(msg.getArgAsString(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
    } else {
        ofLogError()<<"Wrong number of arguments.  Expected 2 or 3.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::rotateNodes(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::rotateNodes(msg.getArgAsFloat(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::rotate(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        ofLogError()<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::scaleNodes(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::scaleNodes(msg.getArgAsFloat(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::scale(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        ofLogError()<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::setTexture(const animatron::osc::Message &msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::setNodesTexture(msg.getArgAsString(0));
    } else if(msg.getNumArgs() == 2) {
        animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(1));
    } else {
        ofLogError()<<"Wrong number of arguments.  Expected 1 or 2.  Given: "<<msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::newNode(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
//        animatron::node::create(msg.getArgAsString(0), ofRandom(1.0), ofRandom(1.0));
        animatron::node::create(msg.getArgAsString(0));
    } else if (msg.getNumArgs() == 3) {
        animatron::node::create(
                    msg.getArgAsString(0),
                    msg.getArgAsFloat(1),
                    msg.getArgAsFloat(2));
    } else {
        ofLogError()<<"Wrong number of arguments.  Expected 1 or 3.  Given: "<<msg.getNumArgs();
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
void ofApp::loadImageSequence(const animatron::osc::Message & msg) {
//    animatron::image::addSequence(msg.getArgAsString(0), msg.getArgAsString(1));
    animatron::node::setTexture(msg.getArgAsString(0), msg.getArgAsString(1));
}

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
void ofApp::setNodesFps(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 2) {
        animatron::node::setFps(msg.getArgAsString(0), msg.getArgAsFloat(1));
    } else {
        animatron::node::setFps(msg.getArgAsFloat(0));
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
