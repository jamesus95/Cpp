//-------------------- Metadata --------------------
/**
 * @file        customer.cpp
 * Purpose:     Implementation file for the class Customer
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include "customer.h"
#include "transaction.h"

//------------------------------------------------ class basics

/**
 * @brief Default Constructor
 * @details id is supplied and neither assumed nor managed by this class
 *          or any other classes in this project.
 * 
 * @param id Integer value indicating the Customer's unique ID number.
 *           Take care in type-checking when doing comparison against a 
 *           length-4 string.
 */
Customer::Customer(int id) {
    this->id = id;
    firstName = "";
    lastName = "";
}

// not supported
Customer::Customer(const Customer& other) {
    if(this != &other) {    // potentially incorrect syntax
        this->id = other.id;
        this->firstName = other.firstName;
        this->lastName  = other.lastName;
    }
}

// properly overwrites sensitive data
Customer::~Customer() {
    this->id = -42;         // garbage data
    firstName = "Hello";
    lastName = "World";
    //rentedItems.clear();    // do not actually delete the items
    transactions.clear();   // or transactions, just de-reference them
}

//------------------------------------------------ getters

int Customer::getID() const {
    return this->id;
}

string Customer::getFirstName() const {
    return firstName;
}

string Customer::getLastName() const {
    return lastName;
}

// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// The operators make critical assumptions about the Generic& parameters
// actually being Customer instances. The typecasts do minimal type-checking
// and error handling. Use with extreme care.
// ----------------------------------------------------------------------------
bool Customer::operator < (const Generic& other) const {
	return id < static_cast<const Customer&>(other).id;
}

bool Customer::operator == (const Generic& other) const {
    return id == static_cast<const Customer&>(other).id;
}

// uses the STL vector's const iterator to traverse the list
void Customer::displayAllHistory() const {
    vector<Transaction*>::const_iterator it;
    for (it = transactions.begin(); it != transactions.end(); it++) {
        cout << *(*it) << endl;
    }
}

//------------------------------------------------ setters


// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------
void Customer::setData(istream& in) {
    in >> firstName >> lastName;  // assume data is well-formed
}

bool Customer::borrowItem(Item* item) {
    // rentedItems.insert(item);
	return true;
}

bool Customer::returnItem(Item* item) {
    // rentedItems.remove(item);
	return true;
}

// uses STL vector.push_back()
void Customer::addTransaction(Transaction* trans) {
	transactions.push_back(trans);
}

ostream& operator << (ostream& out, Customer& customer) {
    customer.formatOutput(out);
    return out;
}

void Customer::formatOutput(ostream& out) const {
    out << "Customer ID = " << id << " " 
        << firstName << " " << lastName;
}

#endif