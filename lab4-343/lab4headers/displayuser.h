#ifndef DISPLAY_USER_H
#define DISPLAY_USER_H

#include "transaction.h"

class DisplayUser : public Transaction {

	friend ostream& operator << (ostream&, const DisplayUser&);

public:
	//---------- constructor/destructor ---------------------------------------
	/**
	 * @brief creates a DisplayUser transaction
	 * @details creates a DisplayUser with the given ID
	 * 
	 * @param char : transaction type character
	 * @param int : transaction ID
	 */
	DisplayUser(char, int);
	
	/**
	 * @brief destructor for DisplayUser
	 * @details destroys DisplayUser instance
	 */
	~DisplayUser();

	//---------- executer -----------------------------------------------------
	/**
	 * @brief processes the DisplayUser Transaction
	 * @details Displays the transaction history of the user contained
	 * in the transaction
	 * 
	 * @param  Inventory* : not used in DisplayUser Transaction
	 * @DisplayUser bool : if transaction was successful
	 */
	bool process(Inventory*);

	//---------- setter -------------------------------------------------------
	/**
	 * @brief sets the data for the DisplayUser transaction
	 * @details sets the Customer and Item in the DisplayUser Transaction
	 * 
	 * @param istream& : input to get data out of
	 * @param Inventory& : not used in DisplayUser
	 * @param MovieFactory& : not used in DisplayUser
	 * @param BinTree& : to search for Customer in
	 */
	void setData(istream&, Inventory&, MovieFactory&, BinTree&);
	
	/**
	 * @brief sets the DisplayUser Transactions Customer
	 * @details sets the DisplayUser Transactions Customer from the input
	 * 
	 * @param istream& : input to get data from
	 * @param BinTree& : to search for Customer in
	 */
	void setCustomer(istream&, BinTree&);

	//---------- initializer --------------------------------------------------
	/**
	 * @brief creates an Empty DisplayUser Transaction
	 * @details creates an Empty DisplayUser Transaction for generic Transaction 
	 * creation
	 * 
	 * @param  int : DisplayUser Transaction ID
	 * @DisplayUser Transaction* : Transaction pointer containing the new DisplayUser
	 */
	Transaction* createEmptyInstance(int) const;

	//---------- getter -------------------------------------------------------
	/**
	 * @brief formats the DisplayUser for printing
	 * @details formats the DisplayUser Transactions data and prints it to
	 * the input ostream
	 * 
	 * @param  osteram& : stream to output to
	 */
	void formatOutput(ostream&) const;

};

#endif