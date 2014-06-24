#ifndef INVENTORY_H
#define INVENTORY_H

#define TOTAL_ITEM_TYPES 26
#define INCREMENT_AMOUNT 10

#include "itemcontainer.h"
#include "moviecontainer.h"
#include "item.h"

using namespace std;

class Inventory {

public:

    //------------------------------------------------ class basics
	Inventory();       // initialize the array
	~Inventory();

    //------------------------------------------------ public setters

    /**
     * @brief Puts the Item into the container
     * 
     * @param  item Item pointer
     * @return insertion success status
     */
	bool insert(Item*);

    /**
     * @brief Removes the Item from the container.
     *        NOT SUPPORTED
     * 
     * @param  item Item pointer to be inserted
     * @return removal success status (currently is a lie)
     */
    bool remove(Item*);

    /**
     * @brief Increment the quantity of the specified Item by a prefixed 
     *        amount.
     *        
     * @param  Item pointer to the object to be incremented
     * @return incrementation success status
     */
    bool add(Item*);

	/**
     * @brief retrieval routine
     * @details Takes in a "dummy" version of the target Item and searches
     *          for it in the container / collections
     * 
     * @param  item Item pointer to be retrieved
     * @return Pointer to the proper copy of the Item (stored in container)
     */
	Item* get(Item*);

    /**
     * @brief Display all containers of all kinds of Items
     */
	void printAll() const;

private:

    /**
     * Array containing all kinds of containers containing all kinds of Items.
     * To access the correct Item type, hash the correct Item.type code.
     */
	ItemContainer* containers[TOTAL_ITEM_TYPES];

    /**
     * @brief Hash function to access the desired Item collection via a `type`
     *        code (that the Item should contain)
     * 
     * @param  c a character containing the code of the Item's type
     * @return index of the Item-type's collection in the `containers` array
     */
	int hash(char) const;
};

#endif