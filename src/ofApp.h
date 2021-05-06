#pragma once

#include "ofMain.h"
#include "types.h"
#include "Node.h"
#include "Osc.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    /// \brief osc interface list
    void help(const animatron::osc::Message & msg);
    /// \brief log everything
    void verbose(const animatron::osc::Message & msg);
    /// \brief only log important messages
    void silent(const animatron::osc::Message & msg);
    /// \brief list all the node names
    void listNodes(const animatron::osc::Message & msg);
    void listSelectedNodes(const animatron::osc::Message & msg);
    /// \brief select a node by name
    void selectNode(const animatron::osc::Message & msg);
    void deselectNode(const animatron::osc::Message & msg);
    void removeNodes(const animatron::osc::Message & msg);
    void moveNodes(const animatron::osc::Message & msg);
    void moveNodesTo(const animatron::osc::Message & msg);

    /// \brief create a new node with a name
    void newNode(const animatron::osc::Message & msg);

    /// \brief log node info
    void logNodeInfo(const animatron::osc::Message & msg);

    /// \brief map OSC message to a function in the server
    void mapMessageToFunc(animatron::osc::Message & msg);

    typedef void (ofApp::* mappedFunc)(const animatron::osc::Message&);
    map<string, mappedFunc> messageMap;

    animatron::node::NodeMap nodes;
    animatron::osc::OscManager osc;
};
