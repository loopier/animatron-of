#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

//    animatron::NodePtr node;
//    node = make_shared<animatron::Node>();

    // setup OSC mapper
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &ofApp::mapMessageToFunc);

    messageMap["/nodes"] = &ofApp::listNodes;
    messageMap["/selected"] = &ofApp::listSelectedNodes;
    messageMap["/select"] = &ofApp::selectNode;
    messageMap["/deselect"] = &ofApp::deselectNode;
    messageMap["/remove"] = &ofApp::removeNodes;
    messageMap["/move"] = &ofApp::moveNodes;

    messageMap["/node/info"] = &ofApp::printNodeInfo;
    messageMap["/node/new"] = &ofApp::newNode;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    animatron::node::drawNodes();
}


//--------------------------------------------------------------
void ofApp::mapMessageToFunc(animatron::osc::Message & msg) {
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
//        animatron::osc::printMessage(msg);
    } else {
        ofLogError() << "Unhandled OSC message: " << msg.getAddress();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    animatron::node::print(name);
}

//--------------------------------------------------------------
void ofApp::deselectNode(const animatron::osc::Message & msg) {
    string name = msg.getArgAsString(0);
    animatron::node::deselect(name);
}

//--------------------------------------------------------------
void ofApp::removeNodes(const animatron::osc::Message & msg) {
    animatron::node::removeNodes();
}

//--------------------------------------------------------------
void ofApp::moveNodes(const animatron::osc::Message & msg) {
    animatron::node::moveNodes(msg.getArgAsFloat(0), msg.getArgAsFloat(1));
}

//--------------------------------------------------------------
void ofApp::newNode(const animatron::osc::Message & msg) {
    if(msg.getNumArgs() == 1) {
        animatron::node::create(msg.getArgAsString(0), ofRandom(1.0), ofRandom(1.0));
    } else if (msg.getNumArgs() == 3) {
        animatron::node::create(
                    msg.getArgAsString(0),
                    msg.getArgAsFloat(1),
                    msg.getArgAsFloat(2));
    } else {
        ofLogError() << "Please provide either 1 or 3 arguments.  Given: " << msg.getNumArgs();
    }
}

//--------------------------------------------------------------
void ofApp::printNodeInfo(const animatron::osc::Message & msg) {
    animatron::node::print(msg.getArgAsString(0));
}
