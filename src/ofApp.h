#pragma once

#include "ofMain.h"
#include "Config.h"
#include "Node.h"
//#include "ImageSequence.h"
#include "Osc.h"
#include "Midi.h"

class ofApp : public ofBaseApp, public animatron::midi::MidiListener {

public:
    void setup();
    void update();
    void draw();
    void exit();

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

    /// \brief MIDI event receiver that maps MIDI messages to animator OSC controls
    void newMidiMessage(animatron::midi::Message & msg);

private:
    /// \brief osc interface list
    void help(const animatron::osc::Message & msg);
    /// \brief log everything
    void verbose(const animatron::osc::Message & msg);
    /// \brief only log important messages
    void silent(const animatron::osc::Message & msg);
    /// \brief print configuration to console
    void config(const animatron::osc::Message & msg);

    // MIDI -------------------------------------------------------------------
    /// \brief list available midi ports
    void listMidiPorts(const animatron::osc::Message & msg);
    void setMidiPort(const animatron::osc::Message & msg);
    void setMidiMap(const animatron::osc::Message & msg);

    // CAM ------------------------------------------------------------------
    void toggleOrthographicCamera(const animatron::osc::Message & msg);

    // NODES ------------------------------------------------------------------
    /// \brief list all the node names
    void listNodes(const animatron::osc::Message & msg);
    void listSelectedNodes(const animatron::osc::Message & msg);
    /// \brief select a node by name
    void selectNode(const animatron::osc::Message & msg);
    void deselectNode(const animatron::osc::Message & msg);
    void removeNodes(const animatron::osc::Message & msg);
    void moveNodes(const animatron::osc::Message & msg);
    void moveNodesTo(const animatron::osc::Message & msg);
    void rotateNodes(const animatron::osc::Message & msg);
    void scaleNodes(const animatron::osc::Message & msg);
    /// \brief create a new node with an image sequence attached to it
    void newNode(const animatron::osc::Message & msg);
    /// \brief create a new node with a name at a given position
    void newNodeAt(const animatron::osc::Message & msg);
    /// \brief log node info
    void logNodeInfo(const animatron::osc::Message & msg);

    // IMAGE SEQUENCE -------------------------------------------------------
    /// \brief add an image sequence to the list of resources
    /// An ImageSequencePlayer is needed to play them and a Node to display them.
    void addImageSequence(const animatron::osc::Message & msg);
    /// \brief load an image sequence to a node
    void setTexture(const animatron::osc::Message & msg);
//    void loadImageSequence(const animatron::osc::Message & msg);
    void playNodes(const animatron::osc::Message & msg);
    void playNodesFromList(const animatron::osc::Message & msg);
    void reverseNodes(const animatron::osc::Message & msg);
    void pauseNodes(const animatron::osc::Message & msg);
    void stopNodes(const animatron::osc::Message & msg);
    void gotoFrame(const animatron::osc::Message & msg);
    void gotoPercent(const animatron::osc::Message & msg);
    void setNodesFps(const animatron::osc::Message & msg);
    // values [0-1] multiplied by a value
    void setNodesNormalizedFps(const animatron::osc::Message & msg);
    void setNodesSpeed(const animatron::osc::Message & msg);
    void loopNodes(const animatron::osc::Message & msg);
    void noloopNodes(const animatron::osc::Message & msg);
    void pingpongNodes(const animatron::osc::Message & msg);

    /// \brief map OSC message to a function in the server
    void mapMessageToFunc(animatron::osc::Message & msg);

    typedef void (ofApp::* mappedFunc)(const animatron::osc::Message&);
    map<string, mappedFunc> messageMap;

    animatron::node::NodeMap nodes;
    animatron::osc::OscManager osc;
    animatron::midi::MidiMapper midiMapper;
    animatron::midi::MidiInPtr midiin;
    animatron::midi::MidiMapPtr midimap;
    animatron::midi::MessageList midiMessages;
    ofEasyCam cam;
};
