/**
* @class ItemContainer
* Manages multiple subinventories of items via a hashing routine.
*/

#ifndef ITEM_CONTAINER_CPP
#define ITEM_CONTAINER_CPP

#include "itemcontainer.h"

ItemContainer::ItemContainer() {
	// type = 'I';
 //    types = new BinTree[ITEM_TYPE_COUNT];   // initialize all the trees
}

ItemContainer::ItemContainer(const ItemContainer&) {

}

ItemContainer::~ItemContainer() {
	// delete[] types;
	// types = NULL;
}

//------------------------------------------------ getters

Item* ItemContainer::get(Item* item) {
	Generic* find;
	Generic* target = static_cast<Generic*>(item);
	types[hash('A')].retrieve(*target, find);
	return static_cast<Item*>(find);
}

// Put new stuff in
bool ItemContainer::add(Item* item) {
	return types[hash('A')].insert(item);
}

int ItemContainer::hash(char c) const {
	return 0;
}

void ItemContainer::printAll() const {
	// for (int i = 0; i < ITEM_TYPE_COUNT; i++) {
	// 	// Generic** items = new Generic*[types[i].size()];
	// 	// types[i].bstreeToArray(items);
	// 	// for (int j = 0; j < types[i].size(); j++) {
	// 	// 	// Need formatting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!s
	// 	// 	cout << *items[j] << endl;
	// 	// }
	// 	// delete[] items;

	// 	cout << static_cast<Item*>(types[i].getRoot()->getData())->getHeader() << endl;
	// 	cout << types[i] << endl;
	// }
}

bool ItemContainer::remove(Item* item) {
	return types[hash('A')].remove(static_cast<Generic&>(*item));
}


#endif