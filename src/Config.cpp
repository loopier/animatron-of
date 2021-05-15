#include "Config.h"

namespace {
ofJson conf;
string configPath = ofFilePath().getUserHomeDir() + "/.config/animatron";
string appSupportPath = ofFilePath().getUserHomeDir() + "/.local/share/animatron";
}

//-------------------------------------------------------
void animatron::config::setup() {
    // check if config directory exists
    ofDirectory configdir = ofDirectory(configPath);
    if(configdir.exists() == false) {
       ofLogWarning("config::setup")<<configPath<<" doesn't exist";
        // create directory if it doesn't
       configdir.create();
        // copy config_default.json to config directory
       ofFile defaultConfigFile(ofToDataPath("config_default.json"));
       defaultConfigFile.copyTo(configPath+"/config.json");
    } else {
       ofLogVerbose("config::setup")<<configPath<<" exists";
    }

    // check if app support directory exists
    ofDirectory appsuportdir = ofDirectory(appSupportPath);
    if(appsuportdir.exists() == false) {
        ofLogWarning("config::setup")<<appSupportPath<<" doesn't exist";
        appsuportdir.create();
    } else {
       ofLogVerbose("config::setup")<<appSupportPath<<" exists";
    }

    // load config file
    ofFile configFile(configPath+"/config.json");
    configFile >> conf;
}

//-------------------------------------------------------
string animatron::config::getConfigPath() {
    return configPath;
}

//-------------------------------------------------------
string animatron::config::getAppSupportPath() {
    return appSupportPath;
}

//-------------------------------------------------------
string animatron::config::getOscIp() {
    return conf["osc"]["server"]["ip"];
}

//-------------------------------------------------------
int animatron::config::getOscPort() {
    return conf["osc"]["server"]["port"];
}

//-------------------------------------------------------
int animatron::config::getMidiInPort() {
    return conf["midiin"]["port"];
}

