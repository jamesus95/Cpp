/**
 * This class defines the Node class to be used in a Threaded 
 * Binary Search Tree.
 *
 * \version         1.1
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "nodeData.h"

using namespace std;

class Node {

	friend ostream& operator<< (ostream& out, const Node& node);

public:
	Node(string token);
	Node(string token, Node* left, Node* right);
	Node(string token, Node* left, Node* right, bool rightThread);
	Node(const Node& other);
	~Node();

	void setLeft(Node* left);
	void setRight(Node* right, bool rightThread = false);
	void setThreadStatus(bool threadStatus);

	Node* getLeft() const;
	Node* getRight() const;
	NodeData* getData() const;
	bool isThreaded() const;

private:
	NodeData* data;
	Node* left;
	Node* right;

	// experimental
	// bool leftThread;		NO LEFT THREAD!
	bool isThread;
};

#include "node.cpp"

#endif
