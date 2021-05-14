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
void animatron::node::updateNodes() {
    for (const auto &item : textures) {
        item.second->update();
    }
}

//-------------------------------------------------------
void animatron::node::drawNodes() {
    for (const auto &item : nodes) {
        // check if node has a texture assigned
        if(textures.count(item.first)) {
            textures[item.first]->getTextureForCurrentFrame().bind();
            item.second->draw();
            textures[item.first]->getTextureForCurrentFrame().unbind();
//            item.second->drawWireframe();
        } else {
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
    // FIX: this is supposed to create different copies of the ImageSequence objects, not
    //		just of the pointers, but 'play' seems to affect all instances of the same
    //		type of ImageSequence.
    ofLogVerbose() << "Setting texture: '"<<textureName<<"' to node '"<<nodeName<<"'";
//    textures[nodeName] = make_shared<image::ImageSequence>(image::ImageSequence(*image::getByName(textureName)));
//    textures[nodeName] = make_shared<image::ImageSequence>(image::ImageSequence());
//    *textures[nodeName] = *image::getByName(textureName);
//    textures[nodeName] = make_shared<image::ImageSequence>(*image::getByName(textureName));
    image::ImageSequencePtr original = image::getByName(textureName);
    textures[nodeName] = make_shared<image::ImageSequence>(image::ImageSequence());
    *textures[nodeName] = *original;
    getByName(nodeName)->resizeToTexture(textures[nodeName]->getTextureForFrame(0));
//    ofLogVerbose()<<"textures["<<nodeName<<"] = "<<typeid(textures[nodeName]).name();
    // print memory allocations
    ofLogVerbose()<<"original mem addr: "<<original.get();
    ofLogVerbose()<<"node mem addr:     "<<textures[nodeName].get();
//    printf("(%p, %p)\n", textures[nodeName].get(), image::getByName(textureName).get());
}

void animatron::node::play(string name) {
    ofLogVerbose()<<"play: "<<name;
//    ofLogVerbose()<<"node exists: "<<name<<" "<<exists(name);
//    ofLogVerbose()<<"img exists: "<<name<<" "<<image::exists(name);
//    ofLogVerbose()<<"texture exists: "<<textures.count(name);
    if(textures.count(name) > 0) {
        textures[name]->play();
//        textures[name]->setShouldLoop(true);
//        ofLogVerbose()<<"playing: "<<textures[name]->isPlaying();
    }
}

//------------------------------------------------------
void animatron::node::play() {
    for(auto name : selectedNodes) {
        play(name);
    }
}

//------------------------------------------------------
void animatron::node::reverse(string name) {
    ofLogVerbose()<<"reverse: "<<name;
    if (textures.count(name)) {
        textures[name]->reverse();
    }
}

//------------------------------------------------------
void animatron::node::reverse() {
    for(auto name : selectedNodes) {
        reverse(name);
    }
}

//------------------------------------------------------
void animatron::node::pause(string name) {
    ofLogVerbose()<<"pause: "<<name;
    if (textures.count(name)) {
        textures[name]->pause();
    }
}

//------------------------------------------------------
void animatron::node::pause() {
    for(auto name : selectedNodes) {
        pause(name);
    }
}

//------------------------------------------------------
void animatron::node::stop(string name) {
    ofLogVerbose()<<"stop: "<<name;
    if (textures.count(name)) {
        textures[name]->stop();
    }
}

//------------------------------------------------------
void animatron::node::stop() {
    for(auto name : selectedNodes) {
        stop(name);
    }
}

//------------------------------------------------------
void animatron::node::gotoFrame(string name, int frame) {
    ofLogVerbose()<<"goto: "<<frame<<" in: "<<name;
    if (textures.count(name)) {
        textures[name]->setCurrentFrameIndex(frame);
    }
}

//------------------------------------------------------
void animatron::node::gotoFrame(int frame) {
    for(auto name : selectedNodes) {
        gotoFrame(name, frame);
    }

}

//------------------------------------------------------
void animatron::node::setFps(string name, float fps) {
    ofLogVerbose()<<"set fps: "<<fps<<" in: "<<name;
    if (textures.count(name)) {
        textures[name]->setFPS(fps);
    }
}

//------------------------------------------------------
void animatron::node::setFps(float fps) {
    for(auto name : selectedNodes) {
        setFps(name, fps);
    }

}

//------------------------------------------------------
void animatron::node::loop(string name) {
    ofLogVerbose()<<"loop: "<<name;
    if (textures.count(name)) {
        textures[name]->setShouldLoop(true);
    }
}

//------------------------------------------------------
void animatron::node::loop() {
    for(auto name : selectedNodes) {
        loop(name);
    }

}

//------------------------------------------------------
void animatron::node::noloop(string name) {
    ofLogVerbose()<<"loop: "<<name;
    if (textures.count(name)) {
        textures[name]->setShouldLoop(false);
        textures[name]->setShouldPingPong(false);
    }
}

//------------------------------------------------------
void animatron::node::noloop() {
    for(auto name : selectedNodes) {
        noloop(name);
    }

}

//------------------------------------------------------
void animatron::node::pingpong(string name) {
    ofLogVerbose()<<"pingpong: "<<name;
    if (textures.count(name)) {
        textures[name]->setShouldPingPong(true);
    }
}

//------------------------------------------------------
void animatron::node::pingpong() {
    for(auto name : selectedNodes) {
        pingpong(name);
    }

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
