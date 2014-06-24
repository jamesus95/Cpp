#include "inventory.h"

Inventory::Inventory() {
	for (int i = 0; i < TOTAL_ITEM_TYPES; i++) {
		containers[i] = 0;
	}
	containers[hash('M')] = new MovieContainer();
}

Inventory::~Inventory() {
	delete containers[hash('M')];
}

Item* Inventory::get(Item* item) {
	char type = hash(item->getType());
	return (containers[(int)type])->get(item);
}

bool Inventory::add(Item* item) {
	char type = hash(item->getType());
	Item* target = containers[(int)type]->get(item);
	if (target != NULL) {
		target->add(INCREMENT_AMOUNT);
	}
	return target != NULL;
}

int Inventory::hash(char c) const {
	return (int)(c - 'A') % TOTAL_ITEM_TYPES;
}

void Inventory::printAll() const {
	for (int i = 0; i < TOTAL_ITEM_TYPES; i++) {
		if (containers[i] != NULL) {
			containers[i]->printAll();
		}
	}
}

bool Inventory::insert(Item* item) {
	char type = hash(item->getType());
	return (containers[(int)type])->add(item);
}

bool Inventory::remove(Item* item) {
	char type = hash(item->getType());
	return (containers[(int)type]->remove(item));
}