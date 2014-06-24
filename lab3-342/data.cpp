/**
@file data.cpp
@author James Murphree <murphs95@uw.edu>
@author Darren Hoehna <dhoehna@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
@brief Holds the character and the corresponding index in which the
character appears.
*/

#ifndef DATA_CPP
#define DATA_CPP

#include "data.h"

/*Corresponds to \t, \n, \r, and  ' ' respectively.*/
//int const SPECIAL_CHARS[] = {9,10,13,32}; Do we need this?
int const NUM_SPECIAL_CHARS = 4;

enum specialChars {tab = 9, newLine = 10, carrigeReturn = 13, space = 32};

/**
 *
 * @param character The character to fill the Data object with.
 * @param space The space to fill the Data object with.
 * @pre space is a non-negative integer.
 */
Data::Data(char character, int space) : character(character), space(space) {}

/**
 * @param orig The Data object to copy.
 * @pre orig exists
 */
Data::Data(const Data& orig) {
    if(orig.isEmpty()) {
        this->character = EMPTY_CHARACTER;
        this->space = EMPTY_SPACE;
    }
    else {
        this->character = orig.getChar();
        this->space = orig.getSpace();
    }
}

/**
 * Default destructor
 */
Data::~Data() {}

/**
 *
 * @return A char representation of the character data member.
 * @pre character is a valid character.
 */
char Data::getChar() const {return character;}

/**
 *
 * @return An int representation of the space data member.
 * @pre space is valid.
 */
int Data::getSpace()const  {return space;}


/**
 *
 * @param character The character to insert
 * @param space The space to insert
 * @return True if the insertion was successful, otherwise false.
 * @pre space is a non-negative number.
 */
bool Data::insert(char character, int space) {
    if (this->isEmpty()) {
        this->character = character;
        this->space = space;
        return true;
    } else {
        return false;
    }
}

/**
 *
 * @return True if the remove is successful, otherwise false
 * @post This last node will be set to an empty state.
 */
bool Data::remove() {
    if (!this->isEmpty()) {
        this->character = '\0';
        this->space = -1;
        return true;
    } else {
        return false;
    }
}

/**
 * @param rightSide The Data object to compare
 * @return True if the objects are equal, otherwise false.
 */
bool Data::operator == (const Data& rightSide) const {
    return rightSide.character == character && rightSide.space == space;
}

/**
 *
 * @param rightSide The data object to compare.
 * @return True if the objects are not equal, otherwise false.
 */
bool Data::operator != (const Data& rightSide) const {
    return !(*this == rightSide);
}

/**
 *
 * @param rightSide The Data object to compare
 * @return True if the left side is greater than the right side
 * by space number.  otherwise false.
 */
bool Data::operator < (const Data& rightSide) const {
    return rightSide.space > space;
}

/**
 * @param output The stream to print to.
 * @param rightSide The Data object to print.
 * @return An ostream object
 */
std::ostream& operator<<(std::ostream& output, const Data& rightSide) {
    if ((static_cast<int>(rightSide.character) >= 0 &&
            static_cast<int>(rightSide.character) <= 32) ||
            (static_cast<int>(rightSide.character) >= 127 &&
            static_cast<int>(rightSide.character) <= 255)) {
        output << "(char#" << static_cast<int>(rightSide.character)
               << ", " << rightSide.space << ")";
        return output;
    }
    output << "(" << rightSide.character << ", " << rightSide.space << ")";
    return output;
}


/**
 *
 * @return True if the Data is empty, otherwise false.
 */
bool Data::isEmpty() const {
    return this->character == EMPTY_CHARACTER && this->space == EMPTY_SPACE;
}

#endif