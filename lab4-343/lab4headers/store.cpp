
/**
 * @mainpage Movie Store
 * 
 * @section Introduction
 * This project implements the logic for a Rental Movie Store. The Store 
 * allows the Customers to borrow and return Movies. Additionally, it can 
 * display the transaction history of a particular user, and it can display
 * its current inventory.
 * 
 * Apart from these functionalities, the project is designed and implemented
 * in such a way that additional functionalities can easily be added.
 * More movie genres than Classic, Comedy, and Drama can be added to the Store.
 * The Store can also carry new types of Items aside from just Movies.
 * Additional transactions regarding the old data or new ones do not interfere
 * with the operations of the old transactions, respecting the Open-Closed
 * principle.
 * 
 * Even new features that aren't just simple additions of existing stuff are
 * also easy to add, e.g. time-related routines.
 * 
 * @section Assumptions
 * This project, given the size, makes HUGE assumptions about the data file's
 * syntactical correctness. There are various checks for the content of the
 * data, but close to none for the form.
 * 
 * Invalid formats in data files cause undefined behaviors.
 * 
 * @section Notes
 * @warning The whole store does not support the remove() functionality yet.
 * This is because we're reusing the old BinTree data structure which did not
 * (and still does not) support removal of items.
 */

#include "store.h"

#include <cassert>
#include <ctype.h>



//------------------------------------------------ class basics

Store::Store() {}

Store::Store(Store& other) {} // not yet supported

Store::~Store() {}

//------------------------------------------------ main routine

void Store::run() {
    // initializing business
    initialize();
    // data loaded, run transactions now
    runBusiness();
    // 5pm. Clean up
    cleanup();
}

void Store::initialize() {
	ifstream customerFile;
	customerFile.open(CUSTOMER_FILE, ifstream::in);
	string YEAH;
    if (!customerFile.is_open()) {
       cout << "Customer File could not be opened." << endl;
    } else { 
        addCustomers(customerFile);
        // getline(customerFile, YEAH);
        // cout << "YEAH! " << YEAH << endl; 
    }
	customerFile.close();

    ifstream movieFile;
	movieFile.open(MOVIE_FILE, ifstream::in);
    if (!movieFile.is_open()) {
       cout << "Movie File could not be opened." << endl;
    } else {
		addMovies(movieFile);
        // getline(movieFile, YEAH);
        // cout << "YEAH! " << YEAH << endl; 
	}

    ifstream transactionFile;
	transactionFile.open(TRANSACTION_FILE, ifstream::in);
    if (!transactionFile.is_open()) {
       cout << "Transaction File could not be opened." << endl;
    } else { 
        addTransactions(transactionFile); 
        // getline(transactionFile, YEAH);
        // cout << "YEAH! " << YEAH << endl;
    }

    customerFile.close();
    movieFile.close();
    transactionFile.close();
}

void Store::addCustomers(istream& in) {
    int id = 0;
    Customer* current;
	for (;;) {
		in >> id;
		if (in.eof()) break;
		current = new Customer(id);
		current->setData(in);
		this->customers.insert(current);
	}
}

void Store::addMovies(istream& in) {
    string movieCode = "";
    Item* current;
	for (;;) {
		in >> movieCode;
		if (in.eof()) break;
		current = mf.createItem(movieCode);
		if (current != NULL) {
			current->setData(in);  // read movie data in
			this->inv.insert(current);
		} else {
			getline(in, movieCode);
		}
	}
}

void Store::addTransactions(istream& in) {
    string transCode = "";
    Transaction* current;
	for (;;) {
		in >> transCode;
		if (in.eof()) break;
		current = tf.createTransaction(transCode);
        
        if(current == NULL) {
            char p = in.peek();
            if (isalpha(p)) {
                // CHILL!
            } else {
                string dummy;
                getline(in, dummy);    
            }
            
        }
		if (current != NULL) {
			current->setData(in, inv, mf, customers);  // read movie data in
			// check the current transaction's validity
            if(transCode == "B" || transCode == "R") {
                if(current->getItem() == NULL || current->getCustomer() == NULL) {
                    delete current;
                    current = NULL;
                }
            } else if (transCode == "H") {
                if(current->getCustomer() == NULL) {
                    delete current;
                    current = NULL;
                }
            } 
            if (current != NULL) {
                this->transactionQueue.push_back(current);
            }
		}
	}
}

void Store::runBusiness() {
	vector<Transaction*>::iterator cur = transactionQueue.begin();
	vector<Transaction*>::iterator end = transactionQueue.end();
    while (cur != end) {
		(*cur)->process(&inv);
		cur++;
	}
	// transactionQueue.clear();
}

void Store::cleanup() {
    while (!transactionQueue.empty()) {
        transactionQueue.pop_back();
    }
}