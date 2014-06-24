//
//  comedy.h
//  lab4

#ifndef comedy_h
#define comedy_h

#include "movie.h"

class Comedy : public Movie {
    
public:
    
    Comedy();
    ~Comedy();
    Comedy(const Comedy&);

    virtual Movie* createEmptyInstance() const;    
    virtual void setData(string);
    virtual printMovie() const;

    virtual bool operator==(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    
private:
    
};

#endif
