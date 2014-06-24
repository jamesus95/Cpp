/**
 * @file Node.h
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#ifndef NODE_H
#define	NODE_H

#include <iostream>
using namespace std;

class Node {
public:

    Node();
    Node(int dataObject);
    Node(int dataObject, Node* nextNode);

    /**
     * @description: sets the dataObject to intToInsert
     * @param intToInsert The unsigned integer to insert into he list.
     * @return True if the insertion was successful, otherwise false.
     */
    bool setItem(int intToInsert);
    bool setNextNode(Node* nextNode);
    int getItem();
    Node* getNextNode();

    virtual ~Node();

private:
    Node* nextNodePointer;
    int dataObject;
};

#endif