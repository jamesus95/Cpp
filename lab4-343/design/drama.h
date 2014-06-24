//
//  drama.h
//  lab4

#ifndef drama_h
#define drama_h

#include "movie.h"

class Drama : public Movie {
    
public:
    
    Drama();
    ~Drama();
    Drama(const Drama&);
    
    virtual Movie* createEmptyInstance() const;    
    virtual void setData(string);
    virtual printMovie() const;

    virtual bool operator==(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    
private:
    
};




#endif
