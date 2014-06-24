#ifndef RETURN_H
#define RETURN_H

#include "transaction.h"

class Return : public Transaction {

	friend ostream& operator << (ostream&, const Return&);

public:
	//---------- constructor/destructor ---------------------------------------
	/**
	 * @brief creates a Return transaction
	 * @details creates a Return with the given ID
	 * 
	 * @param char : transaction type character
	 * @param int : transaction ID
	 */
	Return(char, int);
	/**
	 * @brief destructor for Return
	 * @details destroys Return instance
	 */
	~Return();

	//---------- executer -----------------------------------------------------
	/**
	 * @brief processes the Return Transaction
	 * @details makes the the customer contained in the Transaction Return 
	 * the Movie contained in the Transaction
	 * 
	 * @param  Inventory* : not used in Return Transaction
	 * @return bool : if transaction was successful
	 */
	bool process(Inventory*);

	//---------- setter -------------------------------------------------------
	/**
	 * @brief sets the data for the Return transaction
	 * @details sets the Customer and Item in the Return Transaction
	 * 
	 * @param istream& : input to get data out of
	 * @param Inventory& : to search for Item in
	 * @param MovieFactory& : to create reference Movie from
	 * @param BinTree& : to search for Customer in
	 */
	void setData(istream&, Inventory&, MovieFactory&, BinTree&);
	
	/**
	 * @brief sets the Return Transactions Customer
	 * @details sets the Return Transactions Customer from the input
	 * 
	 * @param istream& : input to get data from
	 * @param BinTree& : to search for Customer in
	 */
	void setCustomer(istream&, BinTree&);
	
	/**
	 * @brief sets the Return Transactions Item
	 * @details sets the Return Transactions Item from the input
	 * 
	 * @param istream& : input to get data from
	 * @param Inventory& : to search for Item in
	 * @param MovieFactory& : to create reference Movie to search for
	 */
	void setItem(istream&, Inventory&, MovieFactory&);

	//---------- initializer --------------------------------------------------
	/**
	 * @brief creates an Empty Return Transaction
	 * @details creates an Empty Return Transaction for generic Transaction 
	 * creation
	 * 
	 * @param  int : Return Transaction ID
	 * @return Transaction* : Transaction pointer containing the new Return
	 */
	Transaction* createEmptyInstance(int) const;

	//---------- getter -------------------------------------------------------
	/**
	 * @brief formats the Return for printing
	 * @details formats the Return Transactions data and prints it to
	 * the input ostream
	 * 
	 * @param  osteram& : stream to output to
	 */
	void formatOutput(ostream&) const;

};

#endif