//-------------------- Metadata --------------------
/**
 * @file item.h
 * Purpose:     Header file for the Item class
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
 * @class ITEM
 * Purpose:         Act as a generic item / product that is to be
 *              	exchanged between the Store and the Customer.
 *              	Can be extended with polymorphism.
 *
 * Inherit from:    Generic
 * Inherited by:    Movie (and other types if expansion is desired)
 *
 *///-------------------------------------------------
        
#ifndef ITEM_H
#define ITEM_H

using namespace std;

#include <string>
#include <string.h>		// for strcmp (a workaround for an unsolved bug)
#include "generic.h"

#define DEFAULT_MOVIE_QUANTITY 10

class Item : public Generic {
    
	friend ostream& operator << (ostream&, const Item&);

public:
    
	//--------- Constructor/Destructor ----------------------------------------
	Item(int = 0);
	virtual ~Item();

	//---------- Pure Virtual Functions ---------------------------------------
	/**
	 * @brief < operator
	 * @details overridden by inherited members with specific 
	 * less than comparison criteria
	 * 
	 * @param  Generic& : Generic to compare to
	 * @return bool : if they are equal or not
	 */
	virtual bool operator < (const Generic&) const = 0;
	
	/**
	 * @brief == operator
	 * @details overridden by inherited members with specific 
	 * comparison criteria
	 * 
	 * @param  Generic& : Generic to compare to
	 * @return bool : if they are equal or not
	 */
	virtual bool operator == (const Generic&) const = 0;
	
	/**
	 * @brief creates an empty Item instance
	 * @details overridden by inherited memebers to create specific instances
	 * returned as Item pointers
	 * 
	 * @param  int : Item ID
	 * @return Item* : a pointer pointint to the newly created instance
	 */
	virtual Item* createEmptyInstance(int) const = 0;
	
	/**
	 * @brief formats output and prints
	 * @details overridden by inherited memebers to print out formatted
	 * data to the ostream
	 * 
	 * @param  ostream& : output to write to
	 */
	virtual void formatOutput(ostream&) const = 0;
    
	/**
	 * @brief sets the items data
	 * @details overridden by inherited members to set the specific data of
	 * that member
	 * 
	 * @param  istream& : to get data from
	 */
    virtual void setData(istream&) = 0;
    
    /**
     * @brief parses the data out of a istream to set
     * @details overridden by inherited members to get data out of an istream.
     * Used in the creation of reference items in the TransactionFactory
     * DOES NOT FILL ALL DATA FIELDS
     * 
     * @param  istream& : to get data out of
     */
    virtual void parseTransactionData(istream&) = 0;

	//---------- Setters ------------------------------------------------------
	/**
	 * @brief Bulk add of quantity for this item.
	 * 
	 * @param newMovieCount The increment quantity.
	 * @pre   Increment quantity cannot be negative.
	 */
	void add(int);		// bulk increment of this item's quantity
	
	/**
	 * @brief Adjust the current count by 1.
	 * @details To be used for rental returns.
	 * @pre 	Fails if current quantity is to exceed total quantity
	 * @post	current quantity <= total quantity
	 * @return Success status.
	 */
	bool increment();	// increment this item's quantity by 1
	
	/**
	 * @brief Adjust the current count by 1.
	 * @details To be used for rental or sales.
	 * @pre 	Fails if current quantity == 0.
	 * @post 	current quantity >= 0
	 * @return Success status.
	 */
	bool decrement();	// decrement ....

	//---------- Getters ------------------------------------------------------
	/**
	 * @brief gets the Total number of Items
	 * @details gets the Total number of Items the store owns
	 * @return returns the number of total Items the store owns
	 */
	int getTotalCount();
	
	/**
	 * @brief gets the number of Items the store has in stock
	 * @details gets the number of Items the store has in stock
	 * at that time
	 * @return returns the number of total Items the store has
	 */
	int getCurrentCount();
	
	/**
	 * @brief Retrieve the item type to determine the type of this polymorphed
	 *        object.
	 * @details To be inherited as a flag of identity for polymorphed objects
	 *          that inherit from this class. The logic for 
	 *          interpreting the information that this routine returns is managed
	 *          externally.
	 * @return a `char` that indicates the type of the object.
	 */	
	char getType();

protected:
	char type;			// Type of item (Currently only Movie)
    int id;				// Unique ID given at creation
    int count;			// Number of Items in the store
	int totalCount;		// Number of Items owned by the store
};

#endif
