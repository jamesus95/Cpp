#include "displayinventory.h"

//---------- constructor/destructor ---------------------------------------
DisplayInventory::DisplayInventory(char instruction, int id) {
	this->instruction = instruction;
	this->id = id;
}

DisplayInventory::~DisplayInventory() {
	item = NULL;
	customer = NULL;
}

//---------- executer -----------------------------------------------------
bool DisplayInventory::process(Inventory* inv) {
	inv->printAll();
	return true;
}

//---------- setter -------------------------------------------------------
void DisplayInventory::setData(istream&, Inventory&, MovieFactory&, BinTree&) {
	// no data to parse
}

//---------- initializer --------------------------------------------------
Transaction* DisplayInventory::createEmptyInstance(int id) const {
	Transaction* trans = new DisplayInventory('S', id);
	return trans;
}

//---------- getter -------------------------------------------------------
void DisplayInventory::formatOutput(ostream& out) const {}

ostream& operator << (ostream& out, const DisplayInventory& transaction) {
	return out;
}


/*
<switch>	->	<first> <content> <end>
<first>		->	"case" <expr> "of"
<content>	->	<entry> | <entry> ; <content>
<entry>		->	<numberlist> : <statement>
<numberlist>->	<num> | <num> , <numberlist>
<end>		->	end
*/