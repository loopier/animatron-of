#ifndef OSCMAPPER_H
#define OSCMAPPER_H

#include "ofMain.h"
#include "Osc.h"
#include "types.h"

namespace animatron {
namespace osc {

typedef ofxOscMessage Message;

class MessageMapper
{
public:
    MessageMapper();
    ~MessageMapper();

    void setup();
private:
    void printMessage(Message & msg);
    void mapMessageToFunc(Message & msg);

    typedef void (MessageMapper::* mappedFunc)(const Message&);

    map<string, mappedFunc> messageMap;
    OscManager osc;
};

}
}

#endif // OSCMAPPER_H
