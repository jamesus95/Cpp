//-------------------- Metadata --------------------
/**
 * @file        transactionfactory.h
 * Purpose:     Header file for the class TransactionFactory
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------


#ifndef TRANSACTION_FACTORY_H
#define TRANSACTION_FACTORY_H

#define TOTAL_TRANSACTION_TYPES 26	// 26 because of hashing implementation

#include "transaction.h"
#include "borrow.h"
#include "return.h"
#include "displayuser.h"
#include "displayinventory.h"


//--------------- Class Description -----------------
/**
 * @class           TransactionFactory
 * Purpose:         Act as a centralized generator for various
 *                  Transaction subtypes. E.g. Borrow, Return,
 *                  Display User, Display Inventory
 *                  
 *                  Given a code, the TransactionFactory will return
 *                  an empty instance of the Transaction subtype
 *                  indicated by that code (NULL if the subtype
 *                  is not supported).
 *
 * Inherit from:    ItemFactory (not really necessary)
 * Inherited by:    <none>
 *
 *///-------------------------------------------------

class TransactionFactory {
    
public:

    //------------------------------------------------ class basics
    
    /**
     * @brief Default constructor.
     * @details Defines the logic for the hash table. Extend the class
     * by adding logic to this routine.
     */
    TransactionFactory();
    
    TransactionFactory(TransactionFactory&);
    
    /**
     * @brief Default destructor.
     * @details Manages the destruction of the template objects.
     *          @todo also destroy all the empty instances that this
     *          factory creates and releases into the wild world
     */
    ~TransactionFactory();

    //------------------------------------------------ createItem()
    /**
     * @brief Creates an empty instance of the subtype
     *        indicated by the transCode
     * 
     * @param transCode a string containing the code for the transaction
     *                  that is requested from the outside
     * @return Item pointer to the newly created transaction instance
     */
    virtual Transaction* createTransaction(string);
    
private:
    
	//------------------------------------------------ hash table
    /**
     * Hash table containing "templates" instances of the Movie genres.
     * See itemfactory.h for details.
     */
    Transaction* origTransactions[TOTAL_TRANSACTION_TYPES];
    
    //------------------------------------------------ item history
    /**
     * `itemHistory` contains pointers to all the Item instances
     * that this factory has produced.
     */
    vector<Transaction*> itemHistory;

    int currentID;  /// Factories keep track of ids to assign to new instances

    //------------------------------------------------ hash()
    /**
     * @brief   Hash function. Maps a char to an array index.
     * @details Maps an object subtype code into an index to access a
     *          template of that subtype.
     * 
     * @param ch a character indicating the subtype of the Item to be cloned.
     * @return array index corresponding to a template instance of
     *         the desired item subtype
     */
    int hash(char ch) const;

};

#endif
