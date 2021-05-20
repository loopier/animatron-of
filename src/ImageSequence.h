#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include "ofxImageSequencePlayback.h"

namespace animatron {
namespace image {

// Extended the class instead of using
//  typedef ofxImageSequencePlayback ImageSequence;
// to expose some of the methods in ofxImageSequence that are not
// available in ofxImageSequencePlayback.  Why didn't the developer
// extend ofxImageSequence instead of using it as an instance variable?
//
// In ofxImageSequencePlayback there's no way get the textures.
// Textures are needed to use them as 3d mesh textures, binding
// them to 3d primitives.
class ImageSequence: public ofxImageSequencePlayback
{
public:
    ImageSequence();

    //returns the current frame
    ofTexture& getTextureForCurrentFrame();
    //returns a frame at a given index
    ofTexture& getTextureForFrame(int index);
    //returns a frame at a given time, used setFrameRate to set time
    ofTexture& getTextureForTime(float time);
    //returns a frame at a given time, used setFrameRate to set time
    ofTexture& getTextureForPercent(float percent);

    //
    void setFrameRate(float rate);
};

typedef shared_ptr<ImageSequence>      ImageSequencePtr;
typedef vector<ImageSequencePtr>         ImageSequenceList;
typedef map<string, ImageSequencePtr>    ImageSequenceMap;

/// \brief Add the sequence NAME, with file from PATH
/// \return BOOL If it has succeded loading the sequence
bool addSequence(string name, string path);
void playSequence(string name);
bool exists(string name);
ImageSequencePtr getByName(string name);
}
}

#endif // IMAGESEQUENCE_H
