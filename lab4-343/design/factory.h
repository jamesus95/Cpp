
#ifndef itemfactory_h
#define itemfactory_h

#define ITEM_TYPES 3

class ItemFactory {
    
public:
    
    MovieFactory();
    MovieFactory(MovieFactory&);
    ~MovieFactory();
    
    Movie* createMovie(char movieCode) const;
    
    
private:
    
    Movie* originalMovies[MOVIE_TYPES];   // instances of each movie
    int hash(char ch) const;    // maps movie code to correct constructor
    
};

#endif
