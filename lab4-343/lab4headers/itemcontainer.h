/**
 * @class ItemContainer
 * Manages multiple subinventories of items via a hashing routine.
 */

#ifndef ITEM_CONTAINER_H
#define ITEM_CONTAINER_H

#include "bintree.h"
#include "item.h"

#define ITEM_TYPE_COUNT 1

class ItemContainer {
private:
    
    //SubInventory* subInventories;      // hash table of subInvs

public:

    //------------------------------------------------ class basics
    ItemContainer();
    ItemContainer(const ItemContainer&);
    virtual ~ItemContainer();

    //------------------------------------------------ getters
	virtual Item* get(Item*);

    //------------------------------------------------ setters
	virtual bool add(Item*);
	virtual bool remove(Item*);

	virtual void printAll() const;

protected:
	char type;
	BinTree* types;

	virtual int hash(char c) const;

};

#endif