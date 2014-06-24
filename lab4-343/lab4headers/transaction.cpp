//-------------------- Metadata --------------------
/**
 * @file transaction.cpp
 * Purpose:     Implementation file for the class Transaction
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#include "transaction.h"

//---------- constructor/destructor ---------------------------------------
Transaction::Transaction() {}

Transaction::~Transaction() {}

//---------- getters ------------------------------------------------------
Item* Transaction::getItem() const {
	return item;
}

Customer* Transaction::getCustomer() const {
    return customer;
}

char Transaction::getTransactionType() const {
    return instruction;
}

ostream& operator << (ostream& out, const Transaction& transaction) {
	transaction.formatOutput(out);
	return out;
}

//---------- setters ------------------------------------------------------
void Transaction::addTransactionToCustomer() {
	customer->addTransaction(this);
}