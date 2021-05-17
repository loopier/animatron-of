#ifndef CONFIG_H
#define CONFIG_H

#include "ofMain.h"
#include "ofxJSON.h"

namespace animatron {
namespace config {

void load();
void print();

string getConfigPath();
string getAppSupportPath();

int getOscListenPort();
string getOscRemoteIp();
int getOscRemotePort();

int getMidiInPort();
string getMidiMapFilename();

}
}

#endif // CONFIG_H
