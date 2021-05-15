#include "Midi.h"

animatron::midi::MidiInPtr animatron::midi::setup(int port) {
    MidiInPtr midiIn = make_shared<MidiIn>();
    // open port
    midiIn->listInPorts();
//    midiIn->openVirtualPort("ofxMidiIn Input"); // open a virtual port
//    midiIn->openPort("SuperCollider:out0 129:4"); // by name
    midiIn->openPort(port); // by number
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn->ignoreTypes(false, false, false);
    // print received messages to the console
    midiIn->setVerbose(true);
   return midiIn;
}

void animatron::midi::logMessage(Message & msg) {
    stringstream tx;
    tx<<"status: "<<msg.status<<endl;
    tx<<"ch: "<<msg.channel<<endl;
    tx<<"pitch: "<<msg.pitch<<endl;
    tx<<"value: "<<msg.channel<<endl;
    tx<<"vel: "<<msg.velocity<<endl;
    tx<<"ctl: "<<msg.control<<endl;
    ofLogVerbose()<<tx.str();
}
