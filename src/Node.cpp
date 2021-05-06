#include "Node.h"

animatron::node::Node::Node() {
    ofLogError() << "This method must not be called. " << __PRETTY_FUNCTION__ << ". All nodes must have a name.";
}

animatron::node::Node::Node(string & name)
: name(name)
, pos(ofGetWidth() / 2, ofGetHeight() / 2) {
    ofLogVerbose() << "Creating node: " << name;
}

animatron::node::Node::Node(string & name, float x, float y)
: name(name)
, pos(x, y) {
    ofLogVerbose() << "Creating node: " << name;
}

animatron::node::Node::~Node() {
    ofLogVerbose() << "Destroying node: " << name;
}

void animatron::node::Node::setName(string & newName) {
    ofLogVerbose() << "Setting node name from: " << name << "\n to: " << newName;
    name = newName;
}

string animatron::node::Node::getName() const {
    return name;
}

void animatron::node::Node::setPosition(animatron::Point & p) {
    ofLogVerbose() << "Setting node postion from: " << pos << "\n to: " << p;
    pos = p;
}

void animatron::node::Node::setPosition(float x, float y) {
    ofLogVerbose() << "Setting node postion from: " << pos << "\n to: " << x << " " << y;
    pos = Point(x,y);
}

animatron::Point animatron::node::Node::getPosition() const {
    return pos;
}

string animatron::node::Node::print() {
   string info = "---- " + name + "\n";
   info += "name: " + name + "\n";
   info += "pos: " + ofToString(pos) + "\n";
   ofLog() << info;
   return info;
}

void animatron::node::Node::draw() {
    float radius = 50;
    ofNoFill();
    ofPushMatrix();
    ofTranslate(pos);
    ofDrawCircle(0,0, radius);
    ofDrawLine( -radius * 2, 0, + radius * 2, 0);
    ofDrawLine( 0, -radius * 2, 0, + radius * 2);
    ofPopMatrix();
}


/////////// PUBLIC INTERFACE ////////////////////////////

namespace {

animatron::node::NodeMap nodes;
vector<string> selectedNodes;

}

//-------------------------------------------------------
void animatron::node::drawNodes() {
    for (const auto &item : nodes) {
        item.second->draw();
    }
}

//-------------------------------------------------------
vector<string> animatron::node::listNodes() {
    vector<string> names;
    for (const auto &item : nodes) {
        ofLog() << item.first;
        names.push_back(item.first);
    }
    return names;
}

//-------------------------------------------------------
vector<string> animatron::node::listSelectedNodes() {
    for (const auto &name : selectedNodes) {
        ofLog() << name;
    }
    return selectedNodes;
}

//-------------------------------------------------------
bool animatron::node::exists(string & name) {
    return nodes.count(name);
}

//-------------------------------------------------------
animatron::node::NodePtr animatron::node::getByName(string & name) {
    NodePtr node;
    if(exists(name)) {
        ofLogVerbose() << "Existing node: " << name;
        node = nodes.find(name)->second;
    } else {
        ofLogVerbose() << "Asking for a node that didn't exist.  Creating new: " << name;
        node = create(name);
    }
    return node;
}

//-------------------------------------------------------
animatron::node::NodePtr animatron::node::create(string name) {
    NodePtr node;
    if (exists(name)) {
        node = getByName(name);
    } else {
        node = create(name, 0.5, 0.5);
    }
    return node;
}

//-------------------------------------------------------
animatron::node::NodePtr animatron::node::create(string name, float x, float y) {
    NodePtr node;
    if (exists(name)) {
        node = getByName(name);
    } else {
        node = make_shared<Node>(name, x * ofGetWidth(), y * ofGetHeight());
        nodes[name] = node;
    }
    return node;
}

//-------------------------------------------------------
void animatron::node::removeNodes() {
    for(auto node : selectedNodes) {
        remove(node);
    }
}

//-------------------------------------------------------
void animatron::node::remove(string name) {
    if(exists(name) == false) return;
    deselect(name);
    nodes.erase(name);
}

//-------------------------------------------------------
void animatron::node::moveNodes(float x, float y) {
    for(auto node : selectedNodes) {
        nodes[node]->setPosition(x * ofGetWidth(), y * ofGetHeight());
    }
}

//-------------------------------------------------------
void animatron::node::move(string name, float x, float y) {
    getByName(name)->setPosition(x,y);
}

//-------------------------------------------------------
void animatron::node::select(string name) {
    selectedNodes.push_back(name);
}

//-------------------------------------------------------
void animatron::node::deselect(string name) {
    vector<string>::iterator it;
    it = std::find(selectedNodes.begin(), selectedNodes.end(), name);
    if(it != selectedNodes.end()) selectedNodes.erase(it);
}

//-------------------------------------------------------
void animatron::node::print(string name) {
    if(exists(name)) {
        getByName(name)->print();
    } else {
        ofLog() << "Node not found: " << name;
    }
}
