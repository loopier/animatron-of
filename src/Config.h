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

int getOscPort();

int getMidiInPort();

}
}

#endif // CONFIG_H
