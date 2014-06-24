#ifndef DISPLAY_INVENTORY_H
#define DISPLAY_INVENTORY_H

#include "transaction.h"

class DisplayInventory : public Transaction {

	friend ostream& operator << (ostream&, const DisplayInventory&);

public:
	//---------- constructor/destructor ---------------------------------------
	/**
	 * @brief creates a DisplayInventory transaction
	 * @details creates a DisplayInventory transaction with given 
	 * transaction char and ID
	 * 
	 * @param char : character representing the transaction
	 * @param int : transaction ID
	 */
	DisplayInventory(char, int);
	
	/**
	 * @brief Destructor for DisplayInventory Transaction
	 */
	~DisplayInventory();

	//---------- executer -----------------------------------------------------
	/**
	 * @brief Processes the DisplayInventory Transaction
	 * @details Displays all the Items in the Inventory
	 * 
	 * @param  Inventory* : inventory to display all items from
	 * @return bool : if the transaction was successful or not
	 */
	bool process(Inventory*);

	//---------- setter -------------------------------------------------------
	/**
	 * @brief Sets the data in DisplayInventory Transaction
	 * @details Doesn't do anything because no data needs to be held by the 
	 * DisplayInventory Transaction
	 * 
	 * @param istream& : input to get data from
	 * @param Inventory& : not used
	 * @param MovieFactory& : not used
	 * @param BinTree& : not used
	 */
	void setData(istream&, Inventory&, MovieFactory&, BinTree&);

	//---------- initializer --------------------------------------------------
	/**
	 * @brief creates an empty DisplayInventory
	 * @details creates an empty DisplayInventory Transaction for generic
	 * Transaction creation
	 * 
	 * @param  int : Transaction ID
	 * @return Transaction* : pointer to the newly created DisplayInventory
	 * Transaction
	 */
	Transaction* createEmptyInstance(int) const;

	//---------- getter -------------------------------------------------------
	/**
	 * @brief formats the DisplayInventory for printing
	 * @details formats the DisplayInventory Transactions data and prints it to
	 * the input ostream
	 * 
	 * @param  osteram& : stream to output toc
	 */
	void formatOutput(ostream&) const;

};

#endif