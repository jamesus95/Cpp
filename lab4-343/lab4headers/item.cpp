//-------------------- Metadata --------------------
/**
 * @file item.cpp
 * Purpose:     Implementation of the Item class
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------
        

#ifndef ITEM_CPP
#define ITEM_CPP

#include "item.h"

//--------- Constructor/Destructor ----------------------------------------
Item::Item(int id) {
    this->id = id;
    this->count = 10;
    this->totalCount = 10;
}

Item::~Item() {}

//---------- getters ------------------------------------------------------

/**
 * @brief Retrieve the item type to determine the type of this polymorphed
 *        object.
 * @details To be inherited as a flag of identity for polymorphed objects
 *          that inherit from this class. The logic for 
 *          interpreting the information that this routine returns is managed
 *          externally.
 * @return a `char` that indicates the type of the object.
 */	
char Item::getType() {
	return type;
}

//-----------------------------------------------------------------------------
int Item::getTotalCount() {
	return totalCount;
}

int Item::getCurrentCount() {
	return count;
}

//-----------------------------------------------------------------------------
ostream& operator << (ostream& out, const Item& item) {
	item.formatOutput(out);
	return out;
}

//---------- setters ------------------------------------------------------

/**
 * @brief Bulk add of quantity for this item.
 * 
 * @param newMovieCount The increment quantity.
 * @pre   Increment quantity cannot be negative.
 */
void Item::add(int newMovieCount) {
	if(newMovieCount >= 0) {
		totalCount += newMovieCount;
		count += newMovieCount;	
	}
}

/**
 * @brief Adjust the current count by 1.
 * @details To be used for rental returns.
 * @pre 	Fails if current quantity is to exceed total quantity
 * @post	current quantity <= total quantity
 * @return Success status.
 */
bool Item::increment() {
	if (count >= totalCount) {
		return false;
	} else {
		count++;
		return true;
	}
}

/**
 * @brief Adjust the current count by 1.
 * @details To be used for rental or sales.
 * @pre 	Fails if current quantity == 0.
 * @post 	current quantity >= 0
 * @return Success status.
 */
bool Item::decrement() {
	if (count <= 0) {
		return false;
	} else {
		count--;
		return true;
	}
}

#endif