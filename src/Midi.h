#ifndef MIDI_H
#define MIDI_H

#include "ofMain.h"
#include "ofxMidi.h"
#include "Osc.h"

namespace animatron {
namespace midi {

typedef ofxMidiIn MidiIn;
typedef ofxMidiMessage Message;
typedef ofxMidiListener MidiListener;
typedef shared_ptr<MidiIn> MidiInPtr;
typedef vector<Message> MessageList;
typedef ofJson MidiMap;
typedef shared_ptr<MidiMap> MidiMapPtr;
class MidiMapper;
typedef shared_ptr<MidiMapper> MidiMapperPtr;

class MidiMapper: public MidiListener {
public:
    void setup(int port);
    void newMidiMessage(Message & msg);
    void loadFunctionMap(string filename);
    void setMap(MidiMapPtr newmap);
    MidiMapPtr getMap();
private:
    osc::Sender osc;
    MidiIn midiin;
    MidiMapPtr map;
    MessageList midiMessages;
    int maxMidiMessages;
};

MidiInPtr setup(int port, string midimapfilename, MidiListener *listener);
void exit(MidiListener * listener);
void logMessage(Message & msg);
/// \brief Load a file with MIDI events mapped to Animatron functions
MidiMapPtr loadFunctionMap(string filename);
MidiMapPtr getMidiMap();
vector<osc::Message> getOscFromMidi(Message & msg);
}
}

#endif // MIDI_H
