#include "Config.h"

namespace {
ofJson conf;
string configPath = ofFilePath().getUserHomeDir() + "/.config/animatron";
string appSupportPath = ofFilePath().getUserHomeDir() + "/.local/share/animatron";
}

//-------------------------------------------------------
void animatron::config::load() {
    // check if config directory exists
    ofDirectory configdir = ofDirectory(configPath);
    if(configdir.exists() == false) {
       ofLogWarning("config::setup")<<configPath<<" doesn't exist";
        // create directory if it doesn't
       configdir.create();
        // copy config-default.json to config directory
       ofFile defaultConfigFile(ofToDataPath("config-default.json"));
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

    print();
}

//-------------------------------------------------------
void animatron::config::print() {
    stringstream ss;
//    ss<<"====== CONFIG ======="<<endl;
//    ss<<"---------------------"<<endl;
    ss<<"config: "<<getConfigPath()<<endl;
    ss<<"appsupport: "<<getAppSupportPath()<<endl;
//    ss<<"---------------------"<<endl;
    ss<<"OSC listening on port: "<<getOscListenPort()<<endl;
    ss<<"OSC remote ip: "<<getOscRemoteIp()<<endl;
    ss<<"OSC remote port: "<<getOscRemotePort()<<endl;
//    ss<<"---------------------"<<endl;
    ss<<"MIDI-IN port: "<<getMidiInPort()<<endl;
    ofLogNotice()<<endl<<ss.str();
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
int animatron::config::getOscListenPort() {
    return conf["osc"]["port"];
}

//-------------------------------------------------------
string animatron::config::getOscRemoteIp() {
    return conf["osc"]["remote ip"];
}

//-------------------------------------------------------
int animatron::config::getOscRemotePort() {
    return conf["osc"]["remote port"];
}

//-------------------------------------------------------
int animatron::config::getMidiInPort() {
    return conf["midi"]["in port"];
}

//-------------------------------------------------------
string animatron::config::getMidiMapFilename() {
    return conf["midi"]["map file"];
}

//-------------------------------------------------------
string getMidiMapFilename();
