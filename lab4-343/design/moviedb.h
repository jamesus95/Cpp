//
//  moviedb.h

#ifndef MOVIE_DB_H
#define MOVIE_DB_H

#include "tree.h"
#include "movie.h"

class MovieDB : public GenericDatabase {
    
public:
    
    MovieDB();
    MovieDB(const MovieDB&);
    ~MovieDB();
    
    void increaseCopies(Movie*, int);
    void decreaseCopies(Movie*, int);
    
    Movie* findByID(int) const;
    Movie** findByTitle(string) const;
    
    virtual bool operator==(const MovieDB& ) const;
    virtual bool operator<(const MovieDB& ) const;
    virtual MovieDB* createMovie();
    
    // bool rent(Movie*, Customer*);        // fits better in Manager
    // bool collect(Movie*, Customer*);
    
    void printAllMovies() const;
    void printRentedMovies(Customer*) const;
    
private:
    
    List movieTreeList;
    int movieStock[];

    int hash(char ch) const;     // movieStock hash function

    void setCopies(int, int);
    
};


#endif
