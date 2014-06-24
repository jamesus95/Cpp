//-------------------- Metadata --------------------
/**
 * @file borrow.cpp
 * Purpose:     Implementation file for the class Borrow
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#include "borrow.h"

//---------- constructor/destructor ---------------------------------------

Borrow::Borrow(char instruction, int id) {
	this->instruction = instruction;
	this->id = id;
	this->item = NULL; this->customer = NULL;
}

Borrow::~Borrow() {
	item = NULL;
	customer = NULL;
	this->instruction = ' ';
	this->id = 0;
}

//---------- executer -----------------------------------------------------

//----------------------------------------- process()
/**
 * @brief Execute the Borrow process for a Movie and a Customer
 * @details This can only be called after the initialization
 * of this Transaction, via the method setData(), has finished.
 * 
 * @param inv Pointer to the Inventory holding the data of the Store. Some
 *            Transactions (not this one) requires access to it.
 * @return Transaction success status
 */
bool Borrow::process(Inventory* inv) {
	bool checkout = item->decrement();
	if (checkout) {
		customer->borrowItem(item);
	}
	Transaction::addTransactionToCustomer();
	return checkout;
}

//---------- setter -------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------


//---------------------------------------- setData()
void Borrow::setData(	istream& in, Inventory& inv, MovieFactory& mf,
						BinTree& cust) {
	setCustomer(in, cust);
	setItem(in, inv, mf);
}

//----------------------------------------- setItem()
void Borrow::setItem(istream& in, Inventory& inv, MovieFactory& mf) {
	// assume that items can only be movies
	string mediaCode = "Z"; string movieCode = "Z";
	in >> mediaCode >> movieCode;
	Item* target = mf.createItem(movieCode);
	item = NULL;
	
	if(target != NULL && mediaCode.c_str()[0] == 'D') {
		target->parseTransactionData(in);
		Item* movieInStore = NULL;
		movieInStore = inv.get(target);		// modify movieInStore

		if(movieInStore != NULL) {
			item = movieInStore;
		} else {item = NULL;}
		delete target;
	} else {
		in.ignore(256, '\n');		// consume the rest of the bad data
	}
}

//------------------------------------------------ setCustomer()
void Borrow::setCustomer(istream& in, BinTree& cust) {
	int customerID = 0;
	in >> customerID;
	Customer target(customerID);	// empty instance with only id
	Generic* customerInStore = NULL;
	
	cust.retrieve(target, customerInStore);
	// pointer is now modified to point to the customer in our store
	if(customerInStore != NULL) {	// if found
		// down-cast and store reference
		customer = dynamic_cast<Customer*>(customerInStore);
	} else {
		customer = NULL;
	}
	// target goes out of scope and gets destroyed
}

//---------- initializer --------------------------------------------------
Transaction* Borrow::createEmptyInstance(int id) const {
	Transaction* trans = new Borrow('B', id);
	return trans;
}

//---------- getter -------------------------------------------------------
void Borrow::formatOutput(ostream& out) const {
	if(this->item != NULL)	{
		out << "DVD Borrow " << *item;
	}
	else { out << ""; }
}

ostream& operator << (ostream& out, const Borrow& transaction) {
	transaction.formatOutput(out);
	return out;
}