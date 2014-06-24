//-------------------- Metadata --------------------
/**
 * @file transaction.h
 * Purpose:     Header file for the class Transaction
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

//--------------- Class Description -----------------
/**
 * @class Transaction
 * Purpose:         Generic template for a specific operation
 * 					of the Store.
 *                  Transactions are interactions between
 *                  the Customer and the Store, including
 *                  (but is not limited to) 1) Borrow and/or
 *                  2) Return a Movie (and/or other items), 
 *                  3) display a user's profile, 4) display
 *                  the store's statuses.
 *                  
 *                  This class facilitates the Command OOP Design Pattern
 *                  as well as the Factory OOP Design Pattern.
 *                  
 *                  Since these Transactions are independent of both
 *                  the Customers and the Items they associate with,
 *                  additional information (such as timestamps) can 
 *                  be easily added.
 *
 * Inherit from:    <none> (potentially, it can inherit from Generic)
 * Inherited by:    Borrow, Return, DisplayUser, DisplayInventory
 *
 *///-------------------------------------------------

#ifndef transaction_h
#define transaction_h

#include "bintree.h"
#include "customer.h"
#include "item.h"
#include "movie.h"
#include "moviefactory.h"
#include "inventory.h"
#include <string>

using namespace std;

class Transaction {

	friend ostream& operator << (ostream&, const Transaction&);

public:
	//---------- constructor/destructor ---------------------------------------
	/**
	 * @brief Constructor for generic Transaction
	 * @details Constructs a blank transaction.  Should not be instantiated.
	 * 
	 * @param char : transaction type character
	 * @param int : transaction ID
	 */ 
	Transaction();
	
	/**
	 * @brief Virtual Destructor for Transaction
	 */
	virtual ~Transaction();

	//---------- pure virtual functions ---------------------------------------
	/**
	 * @brief processes the Transaction
	 * @details overridden by inherited members to process their specific
	 * transaction types
	 * 
	 * @param  inventory of items
	 * @return bool : whether or not the process was successful
	 */
	virtual bool process(Inventory*) = 0;
	
	/**
	 * @brief formats output for printing
	 * @details overridded by inherited members to print their specific
	 * transaction information
	 * 
	 * @param  ostream : for output to be written to
	 */
	virtual void formatOutput(ostream&) const = 0;
	
	/**
	 * @brief creates an empty instance of a transaction
	 * @details overwritten by inheritted members to create and return
	 * their specific transactions in a Transaction pointer
	 * 
	 * @param  int : ID of the transaction
	 * @return Transaction* : a pointer to the created Transaction
	 */
	virtual Transaction* createEmptyInstance(int) const = 0;
	
	/**
	 * @brief sets the data of the transaction
	 * @details Overridden by the inherited members to fill the transactions
	 * with the specific information they need to process
	 * 
	 * @param istream& : input stream to get data out of
	 * @param Inventory& : to search for Items in
	 * @param MovieFactory& : to create a Movie to reference
	 * @param BinTree& : to search for Customer in
	 */
	virtual void setData(istream&, Inventory&, MovieFactory&, BinTree&) = 0;

	//---------- getters ------------------------------------------------------
	/**
	 * @brief gets the Items of the Transaction
	 * @details gets the Item that the Transaction references
	 * @return Item* : Item pointer held by the Transaction
	 */
	virtual Item* getItem() const;
	
	/**
	 * @brief gets the Customer of the Transaction 
	 * @details gets the Customer that the Transaction regerences
	 * @return Customer* : Customer pointer held by the Transaction
	 */
	virtual Customer* getCustomer() const;
	
	/**
	 * @brief gets the Type of the Transaction
	 * @details gets the Char representing the Type of the Transaction
	 * @return char : Transaction Type
	 */
	char getTransactionType() const;
    
protected:
	Customer* customer;		// Customer associated with transaction
	Item* item;				// Item associated with the transaction
	char instruction;		// B (Borrow), R (Return),
							// H (Print Customer) or S (Print Store)
	int id;					// Unique ID given at creation

	// associate itself with the corresponding Customer instance
	void addTransactionToCustomer();

};

#endif
