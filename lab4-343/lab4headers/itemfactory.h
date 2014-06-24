//-------------------- Metadata --------------------
/**
 * @file        itemfactory.h
 * Purpose:     Header file for the ItemFactory class
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
 * @class           ItemFactory
 * Purpose:         Generic inheritance template for 
 *                  the various item types' factories.
 *                  
 *                  A factory produces empty instances 
 *                  of various subtypes of the Object
 *                  type it exists to produce.
 *                  For instance, a MovieFactory would
 *                  produces subtypes of Movies (i.e. 
 *                  movie genres), given a particular
 *                  request.
 *                  
 * Inherit from:    <none>
 * Inherited by:    MovieFactory, (and more if desired)
 *
 *///-------------------------------------------------

#ifndef itemfactory_h
#define itemfactory_h

#define TOTAL_ITEM_TYPES 26	// 26 because of hashing implementation

#include "item.h"
#include <vector>

 using namespace std;

class ItemFactory {
    
public:

    //------------------------------------------------ createItem()
    /**
     * @brief Produces an instance of the requested sub-type.
     * @details The parameter indicates the subtype to be produced.
     *          The factory processes the param and creates an empty
     *          instance of that object type.
     * 
     * @param itemCode a string containing a code that indicates the
     *        subtype of item being requested.
     *        For Movies, it can be:
     *              'C' ----- Classic Movies
     *              'F' ----- Comedy Movies
     *              'D' ----- Drama Movies
     *              'S' ----- Sports
     *              ...
     *              
     * @return Generic Item pointer to the object of the correct 
     *         subtype (as indicated by the code).
     */
    virtual Item* createItem(string itemCode) = 0;

    
private:

    //------------------------------------------------ hash table
    /**
     * Hash table containing "templates" instances of the subtypes.
     * These are the Adams and Eves of each subtype.
     * They produce the empty copies via self-duplication ala
     * cell mitosis. The factory just needs to figure out which one
     * is the correct one to request duplication from.
     */
    Item* originalItems[TOTAL_ITEM_TYPES];

    //------------------------------------------------ item history
    /**
     * `itemHistory` contains pointers to all the Item instances
     * that this factory has produced. This serves easy management
     * of memory cleanup.
     */
    vector<Item*> itemHistory;

    int currentID;  /// Factories keep track of ids to assign to new instances

    // -----------------------------------------------------------------------
    
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
    int hash(char ch) const;  // maps movie code to correct constructor

protected:

    //------------------------------------------------ addItemToHistory()
    /**
     * @brief Append the newly created Item to a container for bookkeeping
     * @details We decided that it's easier to manage creation and deletion
     *          of objects if we do both in the same place.
     *          This is not yet implemented.
     * 
     * @param   item Item pointer to be appended
     */
    virtual void addItemToHistory(Item*) = 0;    
};

#endif
