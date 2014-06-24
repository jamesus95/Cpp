//-------------------- Metadata --------------------
/**
 * @file        customer.h
 * Purpose:     Header file for the class Customer
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "item.h"
#include "generic.h"
#include <vector>


//--------------- Class Description -----------------
/**
 * @class           Customer
 * Purpose:         The purpose of a Customer is to be annoying and 
 *                  supply the Store with income.
 *                 
 *                  Specifically, they make requests to Borrow() 
 *                  and Rent() Movies (and other Items) that the
 *                  Store doesn't have.
 *
 * Inherit from:    Generic
 * Inherited by:    <none>
 *
 *///-------------------------------------------------

class Transaction;

using namespace std;

class Customer : public Generic {

friend ostream& operator << (ostream&, Customer&);
    
public:
    
    //------------------------------------------------ class basics
    
    /**
     * @brief   Default constructor
     * @param  id   specifies the id of the Customer
     */
    Customer(int);
    Customer(const Customer&);
    ~Customer();
    
    //------------------------------------------------ setData()

    /**
     * @brief   Read data from the input stream and initialize the private
     *          fields of this object.
     * @details Assumes data stream is well-formed. The expected format of
     *          the input is:
     *                nnnn abc xyz
     *          where nnnn is a 4-digit id number,
     *                abc is the Customer's first name,
     *                xyz is the Customer's last name
     * 
     * @param  in input data stream
     */
    void setData(istream&);

    /**
     * @brief   Places the processed transaction into the history collection.
     * @details This routine is called after the transaction is executed.
     *          Since we're adopting the OOP Command Design Pattern,
     *          transactions are objects foreign to the Customer class.
     * 
     * @param  transaction  Pointer to the transaction that is to be added.
     */
	void addTransaction(Transaction*);
    
    /**
     * @brief Modifies internal statuses to reflect the borrow transaction
     * @details This routine is called by the corresponding command object,
     *          i.e. a Borrow object.
     *          UPDATE June 06 2014: Due to laziness, we are not solving
     *          the circular dependency problem and instead opting to 
     *          discontinue this feature (which is not required).
     * 
     * @param  item     pointer to the item to be borrowed
     * @return Success status for the process
     */
    bool borrowItem(Item*);

    /**
     * @brief Modifies internal statuses to reflect the return transaction
     * @details This routine is called by the corresponding command object,
     *          i.e. a Return object.
     *          UPDATE June 06 2014: Due to laziness, we are not solving
     *          the circular dependency problem and instead opting to 
     *          discontinue this feature (which is not required).
     * 
     * @param  item     pointer to the item to be returned
     * @return Success status for the process
     */
    bool returnItem(Item*);
    

    // ---------- getters
    void displayAllHistory() const;
    int getID() const;
    string getFirstName() const;
    string getLastName() const;
    
	bool operator < (const Generic&) const;
    bool operator == (const Generic&) const;
    
private:

    /**
     * Simple private fields containing Customer's personal data.
     * The ids are provided from the input data; the program takes
     * no responsibility in managing this.
     * 
     * The program also identifies Customers by ID alone, so if the input
     * data screws this up (for instance, by having two unique Customers
     * with identical IDs), the error will simply not be handled, and 
     * undefined behaviors will take place.
     */
    string firstName, lastName;
    int id;
    
    /**
     * Collection of Items that the Customer is currently renting.
     * To be used for book-keeping purposes.
     */
    // vector<Item*> rentedItems;       // no longer supported
	
     /**
      * Collection of all the transactions that the Customer has
      * participated in. This serves book-keeping purposes as well
      * as legal interests.
      */
    vector<Transaction*> transactions;

    // ----------------------------------------------- helpers
    
    /**
     * @brief Helper function for operator<<.
     * @details Formats the output to display the Customer's:
     *              id
     *              first name
     *              last name
     *          in a space-delimited format.
     * 
     * @param out the ostream& to modify
     */
    void formatOutput(ostream&) const;

};

#endif
