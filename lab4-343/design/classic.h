//
//  classic.h
//  lab4

#ifndef classic_h
#define classic_h

#include "movie.h"

class Classic : public Movie {
    
public:
    
    Classic();
    ~Classic();
    Classic(const Classic&);
    
    virtual Movie* createEmptyInstance() const;    
    virtual void setData(string);
    virtual printMovie() const;

    virtual bool operator==(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    
private:
    
    string year;            // release date
    string actorName;       // major actor
    
};

#endif
