#ifndef CONFIG_H
#define CONFIG_H

#include "ofMain.h"
#include "ofxJSON.h"

namespace animatron {
namespace config {

void setup();

string getConfigPath();
string getAppSupportPath();

string getOscIp();
int getOscPort();

int getMidiInPort();

}
}

#endif // CONFIG_H
