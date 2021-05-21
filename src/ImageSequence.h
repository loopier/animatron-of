#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include "ofxImageSequencePlayback.h"

namespace animatron {
namespace image {

typedef ofxImageSequence ImageSequence;
typedef shared_ptr<ImageSequence> ImageSequencePtr;
typedef vector<ImageSequencePtr> ImageSequenceList;
typedef map<string, ImageSequencePtr> ImageSequenceMap;

// Extended the class instead of using
//  typedef ofxImageSequencePlayback ImageSequence;
// to expose some of the methods in ofxImageSequence that are not
// available in ofxImageSequencePlayback.  Why didn't the developer
// extend ofxImageSequence instead of using it as an instance variable?
//
// In ofxImageSequencePlayback there's no way get the textures.
// Textures are needed to use them as 3d mesh textures, binding
// them to 3d primitives.
class ImageSequencePlayer: public ofxImageSequencePlayback
{
public:
    ImageSequencePlayer();

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

typedef shared_ptr<ImageSequencePlayer>      ImageSequencePlayerPtr;
typedef vector<ImageSequencePlayerPtr>         ImageSequencePlayerList;
typedef map<string, ImageSequencePlayerPtr>    ImageSequencePlayerMap;

/// \brief Add the sequence NAME, with file from PATH.
/// \return BOOL If it has succeded loading the sequence.
bool addSequence(string name);
bool addSequence(string name, string path);
/// \brief Add a sequence with files from PATH named after the directory.
bool addSequenceFromPath(string path);
void playSequence(string name);
bool exists(string name);
/// \brief Return the list of available sequences.
vector<string> getListOfSequences();
vector<string> getListOfSequencePlayers();
void printListOfSequences();
void printListOfSequencePlayers();

/// \brief Return an image sequence
ImageSequencePtr getImageSequenceByName(string name);
/// \brief Return an image sequence player
ImageSequencePlayerPtr getImageSequencePlayerByName(string name);
}
}

#endif // IMAGESEQUENCE_H
