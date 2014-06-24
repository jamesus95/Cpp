/**
 * @file node.h
 * Purpose: header files and includes for the node.cpp file
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "nodeData.h"

using namespace std;

class Node {

	// output operator --------------------------
	friend ostream& operator<< (ostream& out, const Node& node);

public:
	// constructors / destructors
	Node(string token, int frequency = 1);

	Node(	string token, int frequency, Node* left, Node* right,
			bool leftThreadStatus, bool rightThreadStatus		);
	Node(const Node& other);
	~Node();

	// setters ----------------------------------
	void setLeft(Node* left, bool leftThreadStatus);
	void setRight(Node* right, bool rightThreadStatus);

	// getters ----------------------------------
	Node* getLeft() const;
	Node* getRight() const;
	NodeData* getData() const;
	bool isLeftThreaded() const;
	bool isRightThreaded() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;
	bool isLeaf() const;

	// comparision operators --------------------
	bool operator == (const Node& other) const;
	bool operator != (const Node& other) const;

private:

	// fields -----------------------------------
	NodeData* data;
	Node* left;
	Node* right;
	bool leftThread;
	bool rightThread;

};

#include "node.cpp"

#endif
