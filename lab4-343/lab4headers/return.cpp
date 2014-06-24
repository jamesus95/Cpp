#include "return.h"

//---------- constructor/destructor ---------------------------------------
Return::Return(char instruction, int id) {
	this->instruction = instruction;
	this-> id = id;
}

Return::~Return() {
	item = NULL;
	customer = NULL;
}

//---------- executer -----------------------------------------------------
bool Return::process(Inventory* inv) {
	//check customer has item
	bool checkin = item->increment();
	if (checkin) {
		customer->returnItem(item);
	}
	Transaction::addTransactionToCustomer();
	return checkin;
}

//---------- setter -------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------

void Return::setData(	istream& in, Inventory& inv, MovieFactory& mf,
						BinTree& cust) {
	setCustomer(in, cust);
	setItem(in, inv, mf);
}

void Return::setItem(istream& in, Inventory& inv, MovieFactory& mf) {
	// assume that items can only be movies
	string mediaCode = "z";
	string movieCode = "Z";
	in >> mediaCode >> movieCode;
	Item* target = mf.createItem(movieCode);
	if(target != NULL) {
		target->parseTransactionData(in);
		Item* movieInStore = NULL;

		movieInStore = inv.get(target);		// modify movieInStore
		if(movieInStore != NULL) {
			item = movieInStore;
		} else {
			item = NULL;
		}
		delete target;
	} else {
		in.ignore(256, '\n');		// consume the rest of the bad data
	}
}

void Return::setCustomer(istream& in, BinTree& cust) {
	int customerID = 0;
	in >> customerID;
	Customer target(customerID);	// empty instance with only id
	Generic* customerInStore = NULL;
	Generic& genTarget = static_cast<Generic&>(target);
	cust.retrieve(genTarget, customerInStore);
	// pointer is now modified to point to the customer in our store
	if(customerInStore != NULL) {	// if found
		customer = static_cast<Customer*>(customerInStore);
	} else {	
		customer = NULL;
	}
	// target goes out of scope and gets destroyed
}


//---------- initializer --------------------------------------------------
Transaction* Return::createEmptyInstance(int id) const {
	Transaction* trans = new Return('R', id);
	return trans;
}

//---------- getter -------------------------------------------------------
void Return::formatOutput(ostream& out) const {
	if(this->item != NULL)
		out << "DVD Return " << *item;
	else { out << ""; }
}

ostream& operator << (ostream& out, const Return& transaction) {
	transaction.formatOutput(out);
	return out;
}