//-------------------- Metadata --------------------
/**
 * @file        moviefactory.h
 * Purpose:     Header file for the class MovieFactory
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

//--------------- Class Description -----------------
/**
 * @class           MovieFactory
 * Purpose:         Act as a centralized generator for various
 *                  Movie subtypes (Classic, Comedy, Drama).
 *                  
 *                  Given a code, the MovieFactory will return
 *                  an empty instance of the Movie subtype
 *                  indicated by that code (NULL if the subtype
 *                  is not supported).
 *
 * Inherit from:    ItemFactory (even though it doesn't really need to)
 * Inherited by:    <none>
 *
 *///-------------------------------------------------

#ifndef MOVIE_FACTORY_H
#define MOVIE_FACTORY_H

#define MOVIE_TYPE_COUNT 26  // 26 because of current hashing implementation

#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "itemfactory.h"

class MovieFactory : public ItemFactory {
    
public:
    
    //------------------------------------------------ class basics
    MovieFactory();                 // standard constructor
    MovieFactory(MovieFactory&);    
    ~MovieFactory();                // @TODO: destroy all created instances

    /**
     * @brief   Creates an empty instance of the genre indicated by the movieCode
     * 
     * @param movieCode a string containing the code for the movie genre
     *                  that is requested from the outside.
     * @return Item pointer to the newly created Movie genre instance
     */
    Item* createItem(string);
    
    
private:
    
    //------------------------------------------------ hash table
    /**
     * Hash table containing "templates" instances of the Movie genres.
     * See itemfactory.h for details.
     */
    Movie* originalMovies[MOVIE_TYPE_COUNT];   // instances of each movie

    //------------------------------------------------ item history
    /**
     * `itemHistory` contains pointers to all the Item instances
     * that this factory has produced.
     */
    vector<Item*> itemHistory;

    int currentID; /// Factories keep track of ids to assign to new instances

    //------------------------------------------------ hash()
    /**
     * @brief   Hash function. Maps a char to an array index.
     * @details Maps an object subtype code into an index to access a
     *          template of that subtype.
     * 
     * @param ch a character indicating the subtype of the Item to be cloned.
     * @return array index corresponding to a template instance of
     *         the desired item subtype
     */
    int hash(char ch) const;
    void addItemToHistory(Item*);

};

#endif
