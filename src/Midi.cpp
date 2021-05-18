#include "Midi.h"

namespace {
animatron::midi::MidiMapPtr midimap;
animatron::midi::MidiInPtr midiin;
}

//------------------------------------------------------------------------------------------
void animatron::midi::MidiMapper::setup(int port) {
    midiin.listInPorts();
    midiin.openPort(port);
    midiin.ignoreTypes(false, false, false);
    midiin.setVerbose(true);
    midiin.addListener(this);
    maxMidiMessages = 10;
}

//------------------------------------------------------------------------------------------
void animatron::midi::MidiMapper::newMidiMessage(Message & msg) {
    midiMessages.push_back(msg);

    // a queue of midi messages
    while(midiMessages.size() > maxMidiMessages) {
        midiMessages.erase(midiMessages.begin());
    }

    osc::Message oscmsg;

    // TODO: recursively convert MIDI map info to OSC message
    msg.getStatusString(msg.status);
    ofLogVerbose("midi")<<(*map)["note on"][0][0];

//    switch(msg.status) {
//        case MIDI_NOTE_OFF:
//            ofLogVerbose("midi")<<"Note Off";
//        case MIDI_NOTE_ON:
//            ofLogVerbose("midi")<<"NoteOn ch: "<<msg.channel<<" pitch: "<<msg.pitch<<" vel: "<<msg.velocity;
//            oscmsg.setAddress("/goto");
//            oscmsg.addInt32Arg(msg.pitch);
//            osc.sendMessage(oscmsg);
//        case MIDI_CONTROL_CHANGE:
//            ofLogVerbose("midi")<<"Control Change";
//        case MIDI_PROGRAM_CHANGE:
//            ofLogVerbose("midi")<<"Program Change";
//        case MIDI_PITCH_BEND:
//            ofLogVerbose("midi")<<"Pitch Bend";
//        case MIDI_AFTERTOUCH:
//            ofLogVerbose("midi")<<"Aftertouch";
//        case MIDI_POLY_AFTERTOUCH:
//            ofLogVerbose("midi")<<"Poly Aftertouch";
//        case MIDI_SYSEX:
//            ofLogVerbose("midi")<<"Sysex";
//        case MIDI_TIME_CODE:
//            ofLogVerbose("midi")<<"Time Code";
//        case MIDI_SONG_POS_POINTER:
//            ofLogVerbose("midi")<<"Song Pos";
//        case MIDI_SONG_SELECT:
//            ofLogVerbose("midi")<<"Song Select";
//        case MIDI_TUNE_REQUEST:
//            ofLogVerbose("midi")<<"Tune Request";
//        case MIDI_SYSEX_END:
//            ofLogVerbose("midi")<<"Sysex End";
//        case MIDI_TIME_CLOCK:
//            ofLogVerbose("midi")<<"Time Clock";
//        case MIDI_START:
//            ofLogVerbose("midi")<<"Start";
//        case MIDI_CONTINUE:
//            ofLogVerbose("midi")<<"Continue";
//        case MIDI_STOP:
//            ofLogVerbose("midi")<<"Stop";
//        case MIDI_ACTIVE_SENSING:
//            ofLogVerbose("midi")<<"Active Sensing";
//        case MIDI_SYSTEM_RESET:
//            ofLogVerbose("midi")<<"System Reset";
//        default:
//            ofLogVerbose("midi")<<"Unknown";
//    }

    // ofxMidiIn.verbose() works better than this
//    animatron::midi::logMessage(msg);
}

//------------------------------------------------------------------------------------------
void animatron::midi::MidiMapper::loadFunctionMap(string filename) {
//    map = make_shared<MidiMap>();
//    ofFile file(filename);
//    if(file.exists()) {
//        ofLogVerbose("midi")<<"Loading map: "<<filename;
//        file >> map;
//        ofLogVerbose("midi")<<map.dump();
//    } else {
//        ofLogError("midi")<<"Failed to load MIDI map.";
//        ofLogError("midi")<<"File not found: "<<filename;
//    }
}

//------------------------------------------------------------------------------------------
void animatron::midi::MidiMapper::setMap(animatron::midi::MidiMapPtr newmap) {
    map = newmap;
}

//------------------------------------------------------------------------------------------
animatron::midi::MidiMapPtr animatron::midi::MidiMapper::getMap() {
    return map;
}

//------------------------------------------------------------------------------------------
// PUBLIC INTERFACE
//------------------------------------------------------------------------------------------
animatron::midi::MidiInPtr animatron::midi::setup(int port, string midimapfilename, MidiListener * listener) {
    midiin = make_shared<MidiIn>();
    midiin->listInPorts();
    midiin->openPort(port);
    midiin->ignoreTypes(false, false, false);
    midiin->setVerbose(true);
    midiin->addListener(listener);
    midimap = loadFunctionMap(midimapfilename);
    midimap->dump();
    return midiin;
}

//------------------------------------------------------------------------------------------
void animatron::midi::exit(animatron::midi::MidiListener * listener) {
    midiin->closePort();
    midiin->removeListener(listener);
}

//------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------
animatron::midi::MidiMapPtr animatron::midi::loadFunctionMap(string filename) {
    MidiMapPtr midimap = make_shared<MidiMap>();
    ofFile file(filename);
    if(file.exists()) {
        ofLogVerbose("midi")<<"Loading map: "<<filename;
        file >> *midimap;
        ofLogVerbose("midi")<<midimap->dump();
    } else {
        ofLogError("midi")<<"Failed to load MIDI map.";
        ofLogError("midi")<<"File not found: "<<filename;
    }
    return midimap;
}

//------------------------------------------------------------------------------------------
void animatron::midi::setMidiMap(string filename) {
    midimap = loadFunctionMap(filename);
}

//------------------------------------------------------------------------------------------
animatron::midi::MidiMapPtr animatron::midi::getMidiMap() {
    return midimap;
}

vector<animatron::osc::Message> animatron::midi::getOscFromMidi(animatron::midi::Message & msg, animatron::midi::MidiMapPtr map) {
//    midiMessages.push_back(msg);

//    // a queue of midi messages
//    while(midiMessages.size() > maxMidiMessages) {
//        midiMessages.erase(midiMessages.begin());
//    }
    ofLogVerbose("midi")<<"Converting midi msg to lowercase: "<<msg.getStatusString(msg.status);
    string status = ofToLower(msg.getStatusString(msg.status));
    vector<osc::Message> oscmsgs;
    ofLogVerbose("midi")<<(*map)[status];
    for(auto & item : (*map)[status]) {
        animatron::osc::Message oscmsg;
        oscmsg.setAddress(item["cmd"][0]);
        float min = (item["min"].is_null()) ? 0.0 : float(item["min"]);
        float max = (item["max"].is_null()) ? 1.0 : float(item["max"]);
        for (auto arg : vector<ofJson>(item["cmd"].begin() + 1, item["cmd"].end())) {
            if(arg.is_string()) {
                // channel, pitch, velocity, control, value, detlatime
                if(arg == "channel") oscmsg.addFloatArg(ofMap(msg.channel, 0,127, min, max));
                else if(arg == "pitch") oscmsg.addFloatArg(ofMap(msg.pitch, 0,127, min, max));
                else if(arg == "velocity") oscmsg.addFloatArg(ofMap(msg.velocity, 0,127, min, max));
                else if(arg == "control") oscmsg.addFloatArg(ofMap(msg.control, 0,127, min, max));
                else if(arg == "value") oscmsg.addFloatArg(ofMap(msg.value, 0,127, min, max));
                else if(arg == "deltatime") oscmsg.addFloatArg(ofMap(msg.deltatime, 0,127, min, max));
                else oscmsg.addStringArg(arg);
            } else if (arg.is_number()) {
                oscmsg.addFloatArg(arg);
            }
        }

        ofLogVerbose("midi")<<"Converted '"<<item<<"' to osc: "<<oscmsg<<" min: "<<min<<" max: "<<max;
        oscmsgs.push_back(oscmsg);
    }
    return oscmsgs;
}
