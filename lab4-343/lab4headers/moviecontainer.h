//-------------------- Metadata --------------------
/**
 * @file        moviecontainer.h
 * Purpose:     Header file for the class MovieContainer
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------


#ifndef MOVIE_CONTAINER_H
#define MOVIE_CONTAINER_H

#include "itemcontainer.h"
#include "movie.h"

using namespace std;

//--------------- Class Description ------------------
/**
 * @class           MovieContainer
 * Purpose:         Acts as an aggregation point for the 
 *                  various subtypes of Movie.
 *                  Movie objects are stored in separate
 *                  collections, which are contained and
 *                  managed in this MovieContainer.
 *                  
 *                  To get to the desired collection of Movie
 *                  subtype quickly, a hash table is provided by 
 *                  the MovieContainer.
 *
 * Inherit from:    ItemContainer
 * Inherited by:    <none>
 *
 *///-------------------------------------------------

class MovieContainer : public ItemContainer {

protected:

    //------------------------------------------------ fields
    char type;              /// the type of Item that this container
    BinTree* types;         /// collections of Item objects
	
    //------------------------------------------------ internal logic
    int hash(char) const;  

public:

    //------------------------------------------------ class basics
    MovieContainer();           /// initialize the collections
    MovieContainer(const MovieContainer&);
    ~MovieContainer();          /// Deallocate the collections

	//------------------------------------------------ getters
	
    /**
     * @brief Retrieval routine.
     * @details Searches for the requested Item in the container.
     *          This routine accepts a "dummy" copy of the Item
     *          that needs to be searched for. This "dummy" copy 
     *          contains just enough data to facilitate the lookup.
     *          
     *          For instance, using the "dummy" copy:
     *                  TYPE :      'D'
     *                  TITLE:      "Romeo and Juliet"
     *                  YEAR :      1968
     *                  DIRECTOR:   ---
     *          MovieContainer will find and return the movie:
     *                  TYPE :      'D'
     *                  TITLE:      "Romeo and Juliet"
     *                  YEAR :      "1968"
     *                  DIRECTOR:   "Franco Zeffirelli"
     *                  
     * 
     * @param  item the "dummy" item to facilitate look-up
     * @return Pointer to the actual copy of the Item desired.
     */
    Item* get(Item*);
	void printAll() const;

	//------------------------------------------------ setters
	bool add(Item*);
	bool remove(Item*);

};

#endif