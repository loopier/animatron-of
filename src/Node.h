#ifndef NODE_H
#define NODE_H

#include "ofMain.h"
#include "types.h"

namespace animatron {
namespace node {

typedef shared_ptr<ofNode>      NodePtr;
typedef vector<NodePtr>         NodeList;
typedef map<string, NodePtr>    NodeMap;

/////////// PUBLIC INTERFACE ////////////////////////////
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

/// \brief Prints node's values
void logNodes();
void log(string name);

}
}

#endif // NODE_H
