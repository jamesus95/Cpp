//-------------------- Metadata --------------------
/**
 * @file        transactionfactory.cpp
 * Purpose:     Implementation file for the class TransactionFactory
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------


#include "transactionfactory.h"


TransactionFactory::TransactionFactory() {
    // 1. initialize
    for(int i = 0; i < TOTAL_TRANSACTION_TYPES; i++)
        origTransactions[i] = NULL;
    
    // 2. prepare the template instances
    origTransactions[hash('B')] = new Borrow('0', 0);
    origTransactions[hash('R')] = new Return('0', 0);
    origTransactions[hash('H')] = new DisplayUser('0', 0);
    origTransactions[hash('S')] = new DisplayInventory('0', 0);
    // add more here for extension
	
    currentID = 0;
}

TransactionFactory::TransactionFactory(TransactionFactory& other) {
    // not really necessary
}

TransactionFactory::~TransactionFactory() {
    for(int i = 0; i < TOTAL_TRANSACTION_TYPES; i++) {
        if(origTransactions[i] != NULL) {
            delete origTransactions[i];
            origTransactions[i] = NULL;
        }
    }
}

Transaction* TransactionFactory::createTransaction(string transCode) {
    if(transCode != "") {
        char code = transCode.c_str()[0];  // truncate the rest if existent
        
        // get the template object indicated by the code
        Transaction* temp = origTransactions[hash(code)];
        if(temp != NULL) {
            // clone the object of the type just found
            Transaction* newTrans = temp->createEmptyInstance(++currentID);
            itemHistory.push_back(newTrans);
            temp = NULL;
            return newTrans;
        } else return NULL;
    } else return NULL;
}

// Simple hashing routine. Only supports up to 26 subtypes for now.
int TransactionFactory::hash(char ch) const {
    return (int)(ch - 'A') % TOTAL_TRANSACTION_TYPES;
}
