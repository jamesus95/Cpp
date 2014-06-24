//
//  custdb.h

#ifndef CUSTOMER_DB_H
#define CUSTOMER_DB_H

#include "tree.h"
#include "customer.h"

class CustomerDB : public GenericDatabase {
    
public:
    
    CustomerDB();
    CustomerDB(const CustomerDB&);
    ~CustomerDB();

    bool insertCustomer(Customer*);

    Customer* findByID(int) const;
    Customer** findByLastName(string) const;
    void displayAll() const;

    
private:
    
    List customerTrees;
    int hash(char ch) const;
    
};


#endif
