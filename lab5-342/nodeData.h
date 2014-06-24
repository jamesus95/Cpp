/**
 * @file nodeData.h
 * Purpose: header files and includes for the nodeData.cpp file
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef NODE_DATA_H
#define NODE_DATA_H

#include <iostream>
#include <string>

using namespace std;

class NodeData {

    // output operator --------------------------
	friend ostream& operator << (ostream& out, const NodeData& node);

public:

    // constructor/destructor -------------------
	NodeData(string someString = "", int frequency = 1);
	NodeData(const NodeData& other);
	~NodeData();
    
    // setter operator --------------------------
    NodeData& operator = (const NodeData&); 

    // comparision operators --------------------
    bool operator == (const NodeData& rightSide) const;
    bool operator != (const NodeData& rightSide) const;
    bool operator < (const NodeData& rightSide) const;   
    bool operator > (const NodeData& rightSide) const;
    
    // setters ----------------------------------
    void increaseCount();
    void decreaseCount();

    // getters ----------------------------------
    int getCount() const;
    string getToken() const;    


private:

    // fields -----------------------------------
	string token;
	int count;

};

#include "nodeData.cpp"

#endif