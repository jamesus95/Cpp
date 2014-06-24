/**
 * This class holds 2 types of data: a string object and an integer, denoting
 * the frequency of occurrence of that string in a given text file.
 *
 * \version         1.2
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#ifndef NODE_DATA_H
#define NODE_DATA_H

#include <iostream>
#include <string>

using namespace std;

class NodeData {

	friend ostream& operator<< (ostream& out, const NodeData& node);

public:
	NodeData(string someString = ""); // default to null string
	NodeData(const NodeData& other);
	~NodeData();
    
    NodeData& operator=(const NodeData&); 

    // Comparision operators --------------------
    bool operator== (const NodeData& rightSide) const;
    bool operator!= (const NodeData& rightSide) const;
    bool operator< (const NodeData& rightSide) const;   
    bool operator> (const NodeData& rightSide) const;
    
    // Mutate and Get ----------------------------
    void increaseCount();
    void decreaseCount();
    int getCount() const;
    string getToken() const;    


private:
	string token;
	int count;

};

#include "nodeData.cpp"

#endif