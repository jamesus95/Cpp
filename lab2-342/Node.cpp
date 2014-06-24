/**
 * @file Node.cpp
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#include "Node.h"

// Constructors

// empty constructor
Node::Node() : nextNodePointer(NULL), dataObject(-1) {}

// data constructor
Node::Node(int dataObject) : nextNodePointer(NULL), dataObject(dataObject) {}

// data/pointer constructor
Node::Node(int dataObject, Node* nextNode) : nextNodePointer(nextNode), dataObject(dataObject) {}

// destructor
Node::~Node() {}

// Methods

// setItem
bool Node::setItem(int intToInsert) {
    bool success = true;
    dataObject = intToInsert;
    return success;
}

// getItem
int Node::getItem() {
    return dataObject;
}

// setNextNode
bool Node::setNextNode(Node* nextNode) {
    bool success = true;
    nextNodePointer = nextNode;
    return success;
}

// getNextNode
Node* Node::getNextNode() {
    return nextNodePointer;
}