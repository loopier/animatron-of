#include "Node.h"

namespace {
// anonymous namespace to hold local variables
animatron::node::NodeMap nodes;
vector<string> selectedNodes;
map<string, animatron::image::ImageSequencePtr> textures;
}

//-------------------------------------------------------
animatron::node::NodeMap animatron::node::getNodes() {
    return nodes;
}

//-------------------------------------------------------
void animatron::node::drawNodes() {
    for (const auto &item : nodes) {
        if(image::exists(item.first)) {
//            ofLogVerbose()<<"Drawing nodes with texture";
            image::getByName(item.first)->getTextureForCurrentFrame().bind();
            item.second->draw();
            image::getByName(item.first)->getTextureForCurrentFrame().unbind();
        } else {
//            ofLogVerbose()<<"Drawing empty nodes";
            item.second->draw();
        }
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
        node = nodes.find(name)->second;
    } else {
        ofLogVerbose() << "Node not found.  Creating new: " << name;
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
        node = create(name, 0.0, 0.0);
    }
    return node;
}

//-------------------------------------------------------
animatron::node::NodePtr animatron::node::create(string name, float x, float y) {
    NodePtr node;
    if (exists(name)) {
        node = getByName(name);
    } else {
        node = make_shared<Node>(Node());
        nodes[name] = node;
        node->setPosition(x * ofGetWidth(), y * ofGetHeight(), float(0.0));
//        ofLogVerbose()<<"node pos: "<<node->getPosition();
//        ofLogVerbose()<<"x: "<<x<<" y: "<<y;
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
        move(node, x, y);
        ofLogVerbose()<<"moving "<<node<<" to "<<x<<", "<<y;
    }
}

//-------------------------------------------------------
void animatron::node::moveNodesTo(float x, float y) {
    for(auto node : selectedNodes) {
        moveTo(node, x, y);
        ofLogVerbose()<<"moving "<<node<<" to "<<x<<", "<<y;
    }
}

//-------------------------------------------------------
void animatron::node::move(string name, float x, float y) {
    getByName(name)->move(x * ofGetWidth(),y * ofGetHeight(), 0);
}

//-------------------------------------------------------
void animatron::node::moveTo(string name, float x, float y) {
    getByName(name)->setPosition(x * ofGetWidth(), y * ofGetHeight(), 0);
}

//-------------------------------------------------------
void animatron::node::rotateNodes(float a) {
    for(auto node : selectedNodes) {
        getByName(node)->rollRad(a);
    }
}

//-------------------------------------------------------
void animatron::node::rotate(string name, float a) {
    getByName(name)->rollRad(a);
}

//-------------------------------------------------------
void animatron::node::scaleNodes(float s) {
    for(auto node : selectedNodes) {
        getByName(node)->setScale(s);
    }
}

//-------------------------------------------------------
void animatron::node::scale(string name, float s) {
    getByName(name)->setScale(s);
}

//-------------------------------------------------------
void animatron::node::setNodesTexture(string textureName) {
    for(auto node : selectedNodes) {
        setTexture(node, textureName);
    }
}

//-------------------------------------------------------
void animatron::node::setTexture(string nodeName, string textureName) {
    ofLogVerbose() << "Setting texture: '"<<textureName<<"' to node '"<<nodeName<<"'";
    textures[nodeName] = image::getByName(textureName);
}

//-------------------------------------------------------
void animatron::node::select(string name) {
    if(exists(name) == false) {
        ofLogError() << "Can't select a node that doesn't exist";
        return;
    }
    ofLogVerbose() << "Added to selection: " << name;
    selectedNodes.push_back(name);
    listSelectedNodes();
}

//-------------------------------------------------------
void animatron::node::deselect(string name) {
    ofLogVerbose() << "Removed from selection: " << name;
    vector<string>::iterator it;
    it = std::find(selectedNodes.begin(), selectedNodes.end(), name);
    if(it != selectedNodes.end()) selectedNodes.erase(it);
    listSelectedNodes();
}

//-------------------------------------------------------
void animatron::node::logNodes() {
    for(auto node : selectedNodes) {
        log(node);
    }
}

//-------------------------------------------------------
void animatron::node::log(string name) {
    if(exists(name)) {
        string info = "\n --- node info ---\n";
        info += name + "\n";
        info += ofToString(getByName(name)->getPosition());
        ofLog() << info;
    } else {
        ofLog() << "Node not found: " << name;
    }
}
