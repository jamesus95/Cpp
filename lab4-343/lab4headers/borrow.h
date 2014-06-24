//-------------------- Metadata --------------------
/**
 * @file borrow.h
 * Purpose:     Header file for class Borrow
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
  * @class Borrow
  * Purpose:         Contains the logic for the Borrow routine, 
  *                  as well as references to objects and data it
  *                  needs to perform the rental process.
  *                  This routine is a class instead of a function
  *                  for extensibility, following the 
  *                  OOP Command Design Pattern.
  *
  * Inherit from:    Transaction
  * Inherited by:    <none>
  *
  *///-------------------------------------------------

#ifndef BORROW_H
#define BORROW_H

#include "transaction.h"

class Borrow : public Transaction {

	friend ostream& operator << (ostream&, const Borrow&);

public:
	
	//---------- constructor/destructor ---------------------------------------
	/**
	 * @brief creates a borrow transaction
	 * @details creates a borrow with the given ID
	 * 
	 * @param char : transaction type character
	 * @param int : transaction ID
	 */
	Borrow(char, int);

	/**
	 * @brief destructor for Borrow
	 * @details destroys Borrow instance
	 */
	~Borrow();

	//---------- executer -----------------------------------------------------
	/**
	 * @brief processes the Borrow Transaction
	 * @details makes the the customer contained in the Transaction borrow 
	 * the Movie contained in the Transaction
	 * 
	 * @param  Inventory* : not used in Borrow Transaction
	 * @return bool : if transaction was successful
	 */
	bool process(Inventory*);	// logic for the Borrow routine

	//---------- setter -------------------------------------------------------
	/**
	 * @brief sets the data for the borrow transaction
	 * @details sets the Customer and Item in the Borrow Transaction
	 * 
	 * @param istream& : input to get data out of
	 * @param Inventory& : to search for Item in
	 * @param MovieFactory& : to create reference Movie from
	 * @param BinTree& : to search for Customer in
	 */
	void setData(istream&, Inventory&, MovieFactory&, BinTree&);
	
	/**
	 * @brief sets the Borrow Transactions Customer
	 * @details sets the Borrow Transactions Customer from the input
	 * 
	 * @param istream& : input to get data from
	 * @param BinTree& : to search for Customer in
	 */
	void setCustomer(istream&, BinTree&);

	/**
	 * @brief sets the Borrow Transactions Item
	 * @details sets the Borrow Transactions Item from the input
	 * 
	 * @param istream& : input to get data from
	 * @param Inventory& : to search for Item in
	 * @param MovieFactory& : to create reference Movie to search for
	 */
	void setItem(istream&, Inventory&, MovieFactory&);

	//---------- initializer --------------------------------------------------
	/**
	 * @brief creates an Empty Borrow Transaction
	 * @details creates an Empty Borrow Transaction for generic Transaction 
	 * creation
	 * 
	 * @param  int : Borrow Transaction ID
	 * @return Transaction* : Transaction pointer containing the new Borrow
	 */
	Transaction* createEmptyInstance(int) const;

	//---------- getter -------------------------------------------------------
	/**
	 * @brief formats the Borrow for printing
	 * @details formats the Borrow Transactions data and prints it to
	 * the input ostream
	 * 
	 * @param  osteram& : stream to output to
	 */
	void formatOutput(ostream&) const;

};

#endif