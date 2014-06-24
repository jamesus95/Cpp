//-------------------- Metadata --------------------
/**
 * @file        store.h
 * Purpose:     Header file for the class Store
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------


#ifndef STORE_H
#define STORE_H

#include "displayinventory.h"
#include "itemfactory.h"
#include "moviefactory.h"
#include "transactionfactory.h"
#include "transaction.h"
#include "customer.h"

#define CUSTOMER_FILE "data4customers.txt"
#define MOVIE_FILE "data4movies.txt"
#define TRANSACTION_FILE "data4commands.txt"

#include <fstream>
#include <iostream>

using namespace std;


//--------------- Class Description -----------------
/**
 * @class           Store
 * Purpose:         Provide initialization data for the databases, manage
 *                  data manipulation and run logic, utilizing the containers.
 *
 * Inherit from:    <none>
 * Inherited by:    <none>
 *
 *///-------------------------------------------------

class Store {

public:

	//------------------------------------------------ class basics
	Store();			// just initialize all the containers
	Store(Store&);		// not yet supported
	~Store();

	/**
	 * @brief equivalent to a main() routine.
	 * @details Calls more specialized routines to do the job. This method
	 *          only show the highest level of the flow of the program.
	 */
	void run();


private:

	//------------------------------------------------ the factories
	MovieFactory mf;
	TransactionFactory tf;

	//------------------------------------------------ the BIG containers
	Inventory inv;		/// contains all collections of all kinds of Items
	
	BinTree customers;

	// for our program, transactionQueue and transactionHistory
	// are identical. However, for a business logic that runs over time,
	// they may differ and there is enough merit to have both.
	vector<Transaction*> transactionQueue;		// unprocessed transactions
	vector<Transaction*> transactionHistory;    // all transactions

	/**
	 * @brief Call the individual initialization routines on the Customer,
	 *        the Items, and the Transactions.
	 */
	void initialize();

	/**
	 * @brief   initialize the Customer database using the data file.
	 *               
	 * @details read input data from the input stream and:
	 *               - instantiate customers
	 *               - initialize them
	 *               - insert them to collection
	 * 
	 * @param  in input stream to read from
	 */
	void addCustomers(istream&);
	
	// not used since we only have Movies to add
	void addItems(istream&);

	/**
	 * @brief   initialize the Movie database using the data file.
	 *               
	 * @details read input data from the input stream and:
	 *               - instantiate Movies
	 *               - initialize them
	 *               - insert them to the collections
	 * 
	 * @param  in input stream to read from
	 */
	void addMovies(istream&);

	/**
	 * @brief   initialize the Transaction database using the data file.
	 *               
	 * @details read input data from the input stream and:
	 *               - instantiate transactions
	 *               - initialize them
	 *               - insert them to collection
	 * 
	 * @param  in input stream to read from
	 */
	void addTransactions(istream&);

	/**
	 * @brief Progressively execute the Transactions from the queue
	 */
	void runBusiness();

	/**
	 * @brief Memory deallocation. Probably best not done here, but in the 
	 * factories instead.
	 */
	void cleanup();
};

#endif