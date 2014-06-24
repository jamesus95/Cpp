
//  storemanager.h

#ifndef storemanager_h
#define storemanager_h

#include "inputmanager.h"
#include "moviedb.h"
#include "userdb.h"

class StoreManager {
   
public:

    void buildDatabases();
    void buildFactories();
        
    bool processTransaction(Transaction&);
    bool rent(Customer*, Movie*);
    bool collect(Customer*, Movie*);

    void displaySingleUserMovies(Customer*);
    
    void displayMovieDB();
    void displayUserDB();
    
private:
    
    MovieFactory* originalMovieTypes;
    UserFactory* originalUserTypes;
    MovieDB;
    UserDB;
    
    void buildMovieDB();
    void buildUserDB();
    void buildMovieFactory();
    void buildUserFactory();
};

#endif
