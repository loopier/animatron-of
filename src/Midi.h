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

void logMessage(Message & msg);
}
}

#endif // MIDI_H
