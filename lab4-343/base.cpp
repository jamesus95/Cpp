#include <iostream>

#ifndef BASE
#define BASE

using namespace std;

class Base {

friend ostream& operator<<(ostream& out, const Base& b) {
    b.print(out);
    return out;
}	

public:
	int id;

	Base() : id(0) {}

	virtual bool operator<(Base& other) {
		return (id < other.id);
	}

	virtual bool operator==(Base& other) {
		return (id == other.id);
	}
	
	virtual void setID(int newID) {
		id = newID;
	}

	virtual void print(ostream& out) const {
		out << "\tBase, id: " << id << endl;
	}

};

#endif