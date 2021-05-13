#include "Midi.h"

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
