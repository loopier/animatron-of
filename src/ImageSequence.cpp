#include "ImageSequence.h"

namespace  {
    animatron::image::ImageSequenceMap sequences;
    animatron::image::ImageSequencePlayerMap players;
}

//-------------------------------------------------------
//	instance methods
//-------------------------------------------------------
animatron::image::ImageSequencePlayer::ImageSequencePlayer() {

}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequencePlayer::getTextureForCurrentFrame() {
    return mSequence.getTextureForFrame(getCurrentFrameIndex());
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequencePlayer::getTextureForFrame(int index) {
    return mSequence.getTextureForFrame(index);
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequencePlayer::getTextureForTime(float time) {
    return mSequence.getTextureForTime(time);
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequencePlayer::getTextureForPercent(float percent) {
    return mSequence.getTextureForPercent(percent);
}

//-------------------------------------------------------
void animatron::image::ImageSequencePlayer::setFrameRate(float rate) {
    mSequence.setFrameRate(rate);
}

//-------------------------------------------------------
//	public interface
//-------------------------------------------------------
bool animatron::image::addSequence(string name) {
    return addSequence(name, name);
}

bool animatron::image::addSequence(string name, string path) {
    bool isSuccessful = false;
    ImageSequencePtr sequence;
    if (exists(name)) {
        ofLogWarning("image")<<"Sequence '"<<name<<"' already exists.  Skipping.";
        sequence = getImageSequenceByName(name);
        isSuccessful = true;
    } else {
        if(ofDirectory(path).exists()) {
            sequence = make_shared<ImageSequence>();
            sequences[name] = sequence;
            sequence->loadSequence(path);
            ofLogNotice("image")<<"Add sequence '"<<name<<"' from '"<<path<<"'";
            isSuccessful = true;
        } else {
            ofLogError("image")<<"Sequence not found: "<<path;
            isSuccessful = false;
        }
    }
    return isSuccessful;
}

//-------------------------------------------------------
bool animatron::image::addSequenceFromPath(string path) {
    return addSequence(ofFilePath().getFileName(path), path);
}

//-------------------------------------------------------
void animatron::image::playSequence(string name) {
    ImageSequencePlayerPtr sequence;
    if(exists(name)) {
        players[name]->play();
    }
}

//-------------------------------------------------------
bool animatron::image::exists(string name) {
    return players.count(name);
}

//-------------------------------------------------------
vector<string> animatron::image::getListOfSequences() {
    vector<string> names;
    for (auto seq : sequences) {
        names.push_back(seq.first);
    }
    return names;

}

//-------------------------------------------------------
vector<string> animatron::image::getListOfSequencePlayers() {
    vector<string> names;
    for (auto player : players) {
        names.push_back(player.first);
    }
    return names;
}

//-------------------------------------------------------
void animatron::image::printListOfSequences() {
    ofLogVerbose("image")<<"Sequences: ";
    for (auto item : sequences) {
        ofLogVerbose("image")<<"sequence: "<<item.first;
    }
}

//-------------------------------------------------------
void animatron::image::printListOfSequencePlayers() {
    ofLogVerbose("image")<<"Sequences: ";
    for (auto item : players) {
        ofLogVerbose("image")<<"player: "<<item.first;
    }
}

//-------------------------------------------------------
animatron::image::ImageSequencePtr animatron::image::getImageSequenceByName(string name) {
    ImageSequencePtr sequence;
    if (sequences.count(name)) {
        sequence = sequences[name];
    } else {
        ofLogWarning("imagesequence")<<"Sequence not found: "<<name;
        sequence = sequences["default"];
    }
    return sequence;
}

//-------------------------------------------------------
animatron::image::ImageSequencePlayerPtr animatron::image::getImageSequencePlayerByName(string name) {
    ImageSequencePlayerPtr player;
    if(exists(name)) {
        player = players[name];
    } else {
        ofLogWarning("imagesequence")<<"Player not found: "<<name;
        addSequence(name, name);
        player = players.find(name)->second;
    }
    return player;
}
