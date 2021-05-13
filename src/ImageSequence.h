#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include "ofxImageSequencePlayback.h"

namespace animatron {
namespace image {

// Extended the class instead of using
//  typedef ofxImageSequencePlayback ImageSequence;
// because in the original there's no way get the textures.
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
};

typedef shared_ptr<ImageSequence>      ImageSequencePtr;
typedef vector<ImageSequencePtr>         ImageSequenceList;
typedef map<string, ImageSequencePtr>    ImageSequenceMap;

void addSequence(string name, string path);
void playSequence(string name);
bool exists(string name);
ImageSequencePtr getByName(string name);
}
}

#endif // IMAGESEQUENCE_H
