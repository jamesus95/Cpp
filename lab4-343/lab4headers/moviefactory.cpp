//-------------------- Metadata --------------------
/**
 * @file        moviefactory.cpp
 * Purpose:     Implementation file for the class MovieFactory
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#include "moviefactory.h"

//------------------------------------------------ class basics
/**
 * @brief   Constructor for MovieFactory
 * @details Creates the "template" instances and store them
 *          in the hash table.
 */
MovieFactory::MovieFactory() {
    // initialize everything with NULL
    for(int i = 0; i < MOVIE_TYPE_COUNT; i++)
        originalMovies[i] = NULL;
    // prepare template instances
    originalMovies[hash('C')] = new Classic();
    originalMovies[hash('F')] = new Comedy();
    originalMovies[hash('D')] = new Drama();
    // add more here for extension

    currentID = 0;
}

MovieFactory::MovieFactory(MovieFactory& other) {
    // not really necessary
}

/**
 * @brief   Destructor
 * @details Deletes the original copies.
 *          @TODO Also delete all the empty instances that the factory
 *                has ever created.
 */
MovieFactory::~MovieFactory() {
    for(int i = 0; i < MOVIE_TYPE_COUNT; i++) {
        if(originalMovies[i] != NULL) {
            delete originalMovies[i];
            originalMovies[i] = NULL;
        }
    }
}

Item* MovieFactory::createItem(string movieCode) {
    if(movieCode != "") {
        char code = movieCode.c_str()[0];  // truncate the rest if existent
        Movie* temp = originalMovies[hash(code)];
		if (temp != NULL) {
            Item* newMovie = temp->createEmptyInstance(++currentID);
            itemHistory.push_back(newMovie);
            temp = NULL;
            return newMovie;
        }
		else return NULL;
	} else return NULL;
}

// Simple hashing routine. Only supports up to 26 subtypes for now.
int MovieFactory::hash(char ch) const {
    return (int)(ch - 'A') % MOVIE_TYPE_COUNT;
}

void MovieFactory::addItemToHistory(Item* item) {
    itemHistory.push_back(item);
}