#ifndef NODE_H
#define NODE_H

#include "ofMain.h"
#include "types.h"
#include "ImageSequence.h"

namespace animatron {
namespace node {

typedef ofPlanePrimitive Node;
typedef shared_ptr<Node>      NodePtr;
typedef vector<NodePtr>         NodeList;
typedef map<string, NodePtr>    NodeMap;


/////////// PUBLIC INTERFACE ////////////////////////////
NodeMap getNodes();
void updateNodes();
void drawNodes();

vector<string> listNodes();
vector<string> listSelectedNodes();

///
/// \brief check if a nod is in the list
/// \param name
/// \return
///
bool exists(string & name);

/// \brief get a node by it's name
NodePtr getByName(string & name);

/// \brief create a new node
/// \param name
/// \return a pointer to the node
NodePtr create(string name);
NodePtr create(string name, float x, float y);

/// \brief remove selected nodes
void removeNodes();
/// \brief remove node by name
void remove(string name);

/// \brief move selected nodes
void moveNodes(float x, float y);
/// \brief move selected nodes to a position
void moveNodesTo(float x, float y);
/// \brief move node by name
void move(string name, float x, float y);
void moveTo(string name, float x, float y);

void rotateNodes(float a);
void rotate(string name, float a);

void scaleNodes(float s);
void scale(string name, float s);

void select(string name);
void deselect(string name);

/// \brief Attach a texture to a node
void setNodesTexture(string textureName);
void setTexture(string nodeName, string textureName);

void play(string name);
void play();
void reverse(string name);
void reverse();
void pause(string name);
void pause();
void stop(string name);
void stop();
void gotoFrame(string name, int frame);
void gotoFrame(int frame);
void setFps(string name, float fps);
void setFps(float fps);
void loop(string name);
void loop();
void noloop(string name);
void noloop();
void pingpong(string name);
void pingpong();

/// \brief Prints node's values
void logNodes();
void log(string name);

}
}

#endif // NODE_H
