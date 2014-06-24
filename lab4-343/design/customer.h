//
//  customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "item.h"

class Customer : public Item {
    
public:
    
    Customer(std::string);
    Customer();
    ~Customer();
    
    // --------- setters
    virtual void setData(string);       // local logic to parse data
    bool borrowMovie(Movie*);
    bool returnMovie(Movie*);
    void addTransaction();              

    // ---------- getters
    void displayAllHistory() const;
    int getCustomerID() const;
    string getFirstName() const;
    string getLastName() const;
    Customer* createEmptyInstance() const;
    
    virtual bool operator==(const Customer&) const;
    virtual bool operator!=(const Customer&) const;
    
private:
    string firstName, lastName;
    int customerID;
    
    List<Movie> rentedMovies;
	List<int> transactionIDs;
    
};

#endif
