#include "ImageSequence.h"

namespace  {
    animatron::image::ImageSequenceMap sequences;
}

//-------------------------------------------------------
//	instance methods
//-------------------------------------------------------
animatron::image::ImageSequence::ImageSequence() {

}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequence::getTextureForCurrentFrame() {
    return mSequence.getTextureForFrame(getCurrentFrameIndex());
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequence::getTextureForFrame(int index) {
    return mSequence.getTextureForFrame(index);
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequence::getTextureForTime(float time) {
    return mSequence.getTextureForTime(time);
}

//-------------------------------------------------------
ofTexture& animatron::image::ImageSequence::getTextureForPercent(float percent) {
    return mSequence.getTextureForPercent(percent);
}

//-------------------------------------------------------
//	public interface
//-------------------------------------------------------
void animatron::image::addSequence(string name, string path) {
    ImageSequencePtr sequence;
    if (exists(name)) {
        ofLogWarning()<<"Sequence '"<<name<<"' already exists.  Skipping.";
        sequence = getByName(name);
    } else {
        sequence = make_shared<ImageSequence>(ImageSequence());
        sequences[name] = sequence;
        sequence->loadSequence(path);
        ofLogNotice()<<"Created new image sequence '"<<name<<"' from '"<<path<<"'";
    }
}

//-------------------------------------------------------
void animatron::image::playSequence(string name) {
    ImageSequencePtr sequence;
    if(exists(name)) {
        sequences[name]->play();
    }
}

//-------------------------------------------------------
bool animatron::image::exists(string name) {
    return sequences.count(name);
}

//-------------------------------------------------------
animatron::image::ImageSequencePtr animatron::image::getByName(string name) {
    ImageSequencePtr sequence;
    if(exists(name)) {
        sequence = sequences.find(name)->second;
    } else {
        ofLogVerbose()<<"Asking for a sequence that doesn't exists.  Skipping.";
    }
    return sequence;
}
