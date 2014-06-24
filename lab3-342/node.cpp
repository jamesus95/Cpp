/**
@file node.cpp
@author James Murphree <murphs95@uw.edu>
@author Darren Hoehna <dhoehna@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
@brief Holds a pointer to the next node and a pointer to a data object
*/

#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"

/**
 *
 * @param data The data object to initialize
 * @pre data is a valid data object
 */
Node::Node(Data* data) : data(data), next(NULL) {}

/**
 *
 * @param data The Data object to initialize.
 * @param next The pointer to the next node.
 * @pre data is a valid data object.  next is not NULL.
 */
Node::Node(Data* data, Node* next) : data(data), next(next) {}

/**
 *
 * @param orig The Node object to copy.
 */
Node::Node(const Node& orig){
    this->data = orig.getData();
    this->next = orig.getNext();
}

/**
 * Deconstructor
 */
Node::~Node() {
    delete data;
    data = NULL;
    next = NULL;
}

/**
 *
 * @return The data object of this Node object.
 */
Data* Node::getData() const {return data;}

/**
 *
 * @return The pointer to the next Node object.
 */
Node* Node::getNext() const {return next;}

/**
 *
 * @param next The node for next to point to.
 */
void Node::setNext(Node* next) {this->next = next;}

/**
 *
 * @param rightSide The Node object to compare to.
 * @return True if the Nodes are equal, otherwise false.
 */
bool Node::operator == (const Node& rightSide) const {
    return (*data == *rightSide.data);
}

/**
 *
 * @param rightSide The Node object to compare to.
 * @return True if the Nodes are not equal, otherwise false.
 */
bool Node::operator != (const Node& rightSide) const {
    return (*data != *rightSide.data);
}


#endif