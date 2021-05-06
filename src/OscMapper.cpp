#include "OscMapper.h"

animatron::osc::MessageMapper::MessageMapper() {

}

animatron::osc::MessageMapper::~MessageMapper() {

}

void animatron::osc::MessageMapper::setup() {
    osc.setup();
    ofAddListener(osc.newOscMessageEvent, this, &MessageMapper::mapMessageToFunc);

//    messageMap["/node/new"] =
}

//---------------------------------------------------------
void animatron::osc::MessageMapper::printMessage(animatron::osc::Message & msg)
{
    osc::printMessage(msg, "OSC:");
}

//---------------------------------------------------------
void animatron::osc::MessageMapper::mapMessageToFunc(animatron::osc::Message & msg)
{
    ofLogVerbose() << __PRETTY_FUNCTION__;
    // Look up the processor for this message address
    map<string, mappedFunc>::iterator iter = messageMap.find(msg.getAddress());
    if (iter != messageMap.end()) {
        (this->*(iter->second))(msg); // call the processor method for this message
        printMessage(msg);
    } else {
        ofLogWarning() << "Unhandled OSC message: " << msg.getAddress();
    }
}
