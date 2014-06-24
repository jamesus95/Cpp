#include "displayuser.h"

//---------- constructor/destructor ---------------------------------------
DisplayUser::DisplayUser(char instruction, int id) {
	this->instruction = instruction;
	this->id = id;
}

DisplayUser::~DisplayUser() {
	item = NULL;
	customer = NULL;
}

//---------- executer -----------------------------------------------------
bool DisplayUser::process(Inventory* inv) {
	cout << *customer << endl;
	customer->displayAllHistory();
	cout << endl;
	return true;
}

//---------- setter -------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------

void DisplayUser::setData(	istream& in, Inventory& inv,
							MovieFactory& mf, BinTree& cust) {
	setCustomer(in, cust);
}

void DisplayUser::setCustomer(istream& in, BinTree& cust) {
	
	int customerID = 0;
	in >> customerID;
	Customer target(customerID);	// empty instance with only id
	//Generic& targetRef = dynamic_cast<Generic&>(target);
	Generic* customerInStore = NULL;
	
	cust.retrieve(target, customerInStore);
	// pointer is now modified to point to the customer in our store
	if(customerInStore != NULL) {	// if found
		customer = static_cast<Customer*>(customerInStore);
	} else {
		customer = NULL;
	}
	// target goes out of scope and gets destroyed
}

//---------- initializer --------------------------------------------------
Transaction* DisplayUser::createEmptyInstance(int id) const {
	Transaction* trans = new DisplayUser('H', id);
	return trans;
}

//---------- getter -------------------------------------------------------
void DisplayUser::formatOutput(ostream& out) const {
	// out << "Printing history for user " << customer->getID() << endl;
}

ostream& operator << (ostream& out, const DisplayUser& transaction) {
	return out;
}