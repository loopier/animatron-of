#include "ImageSequence.h"

namespace  {
    animatron::image::ImageSequencePlayerMap sequences;
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
bool animatron::image::addSequence(string name, string path) {
    bool success = false;
    ImageSequencePlayerPtr sequence;
    if (exists(name)) {
        ofLogWarning()<<"Sequence '"<<name<<"' already exists.  Skipping.";
        sequence = getByName(name);
        success = true;
    } else {
        if(ofDirectory(path).exists()) {
            sequence = make_shared<ImageSequencePlayer>(ImageSequencePlayer());
            sequences[name] = sequence;
            sequence->loadSequence(path);
            ofLogNotice()<<"Add sequence '"<<name<<"' from '"<<path<<"'";
            success = true;
        } else {
            ofLogError("image")<<"Sequence not found: "<<path;
            success = false;
        }
//        } else {
//            sequence->loadSequence(ofToDataPath("default"));
//        }
    }
    return success;
}

//-------------------------------------------------------
void animatron::image::playSequence(string name) {
    ImageSequencePlayerPtr sequence;
    if(exists(name)) {
        sequences[name]->play();
    }
}

//-------------------------------------------------------
bool animatron::image::exists(string name) {
    return sequences.count(name);
}

//-------------------------------------------------------
animatron::image::ImageSequencePlayerPtr animatron::image::getByName(string name) {
    ImageSequencePlayerPtr sequence;
    if(exists(name)) {
        sequence = sequences.find(name)->second;
    } else {
        ofLogVerbose()<<"Image sequence not found: "<<name;
//        addSequence(name, imgsPath+"default");
        addSequence(name, name);
        sequence = sequences.find(name)->second;
    }
    return sequence;
}
