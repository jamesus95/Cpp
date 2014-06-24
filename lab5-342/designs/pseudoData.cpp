/**
 * This class holds 2 types of data: a string object and an integer, denoting
 * the frequency of occurrence of that string in a given text file.
 *
 * \version			1.2
 * \author 			James Murphree
 * \author 			Vu Dinh
 * \date 			March 2nd 2014
 * \copyright 		WTFPLv2.1
 * 
 */

class NodeData {	

	NodeData::NodeData() {
		create empty NodeData
	}

	NodeData::NodeData(string token) {
		create NodeData with passed in token and count 1
	}

	NodeData::NodeData(const NodeData& other) {
		create a new NodeData and copy members from other over
	}

	NodeData::~NodeData() {
		randomize contents and delete the NodeData
	}

	NodeData& NodeData::operator=(const NodeData& other) {
	    if(other does not refer to the same object as `this`) {
	    	copy = [make a copy of other]
	    	delete this (old resources)
	    	point this to copy (which holds new resources)
	    }
	    return *this;
	}

	// Comparision operators --------------------
	bool NodeData::operator==(const NodeData& rightSide) const {
	    if(token == token && count == count) 
	    	then return true;
	    else return false;
	}
	bool NodeData::operator<(const NodeData& rightSide) const {
	    // prioritize frequency over alphabetical order
	    if(count < rightSide.count)
	    	then return true;
	    else if(count == rightSide.count) {
	    	// now look at alphabetical order
	    	return token < rightSide.token;
	    }
	    else
	    	return false;
	}   
	bool NodeData::operator>(const NodeData& rightSide) const {
	    if not < and not ==
	    	then return true;
	    else return false;
	}

	// Mutate and Get ---------------------------------
	void NodeData::increaseCount() {count++;}
	void NodeData::decreaseCount() {count--;}

	int NodeData::getCount() const {return count;}
	string NodeData::getToken() const {return token;}

	ostream& operator<< (ostream& out, const NodeData& node) {
	    append the token and the count together to the ostream
	    return out;
	}

};