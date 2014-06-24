//
//  movie.h

#ifndef movie_h
#define movie_h

#include "item.h"

class Movie : public Item {
    
public:
    
    Movie();
    Movie(const Movie&);
    ~Movie();

    virtual Movie* createEmptyInstance() const;
    virtual bool setData(string);   // data string comes from outside
    virtual void printMovie() const;

    virtual bool operator==(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    
protected:
    
    char movieCategory;     // F, D or C
    char mediaType;         // D for DVD

    string director;
    string title;
    string date;        // year or month and year
    
    List<Customer> borrowCustomers;
    
};

#endif
