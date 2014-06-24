/**
@file node.h
@author James Murphree <murphs95@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
*/

#ifndef NODE_H
#define NODE_H

#include "data.h"

class Node {

public:
    Node(Data* data);
    Node(Data* data, Node* next);
    Node(const Node& orig);
    ~Node();

    Data* getData() const;
    Node* getNext() const;
    void setNext(Node* next);
    bool operator == (const Node& rightSide) const;
    bool operator != (const Node& rightSide) const;

private:
    Data* data;
    Node* next;

};


#endif