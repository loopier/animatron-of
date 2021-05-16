#ifndef MIDI_H
#define MIDI_H

#include "ofMain.h"
#include "ofxMidi.h"

namespace animatron {
namespace midi {

typedef ofxMidiIn MidiIn;
typedef ofxMidiMessage Message;
typedef ofxMidiListener MidiListener;
typedef shared_ptr<MidiIn> MidiInPtr;
typedef vector<Message> MessageList;
typedef ofJson MidiMap;
typedef shared_ptr<MidiMap> MidiMapPtr;

MidiInPtr setup(int port);
void logMessage(Message & msg);
/// \brief Load a file with MIDI events mapped to Animatron functions
MidiMapPtr loadFunctionMap(string filename);
}
}

#endif // MIDI_H
