//-------------------- Metadata --------------------
/**
 * @file drama.cpp
 * Purpose:     Implementation file for the class Drama
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#ifndef DRAMA_CPP
#define DRAMA_CPP

#include "drama.h"

//--------- Constructor/Destructor ----------------------------------------
Drama::Drama(int id) {
	this->genre = 'D';
	this->type = 'M';
	this->id = id;
	this->movieCategory = "D";
	// other quantities are presumed initialized thanks to the base classes'
	// constructors
}

Drama::~Drama() {}

//---------- getters ------------------------------------------------------

//--------------------------------------------- createEmptyInstance()
/**
 * @brief Clone-like routine to generate an empty copy of 
 *        the same type / class.
 * @details Used in the Factory design model to facilitate polymorphism.
 * 
 * @param id unique id of the item to be created. Managed externally.
 * @return Item pointer to an empty object of Drama type.
 */
Item* Drama::createEmptyInstance(int id) const {
	Item* d = new Drama(id);
	return d;
}


// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// The operators make critical assumptions about the Generic& parameters
// actually being Customer instances. The typecasts do minimal type-checking
// and error handling. Use with extreme care.
// ----------------------------------------------------------------------------

//---------------------------------------------- operator==
/**
 * @brief 	Just an overloaded operator
 * @details Compares by criteria: Movie.director, Movie.title
 * @pre 	Assume that the Generic reference is indeed a Drama type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * @warning The c-string comparison is a workaround for a weird bug wherein
 *          identical strings (at least visually) fails the equality test.
 * 
 * @param other Generic reference to (presumably) a Drama object.
 * @return  Equality comparison result
 */
bool Drama::operator == (const Generic& other) const {
	const Drama& d = static_cast<const Drama&>(other);

	// this check fails sometimes for no apparent reasons
	// return director == d.director && title == d.title;
	
	int i = strcmp(director.c_str(), d.director.c_str()) + 
			strcmp(title.c_str(), d.title.c_str());
	return i == 0;
}

//---------------------------------------------- operator<
/**
 * @brief 	Just an overloaded operator
 * @details Compares by criteria:
 * 				Movie.director, then
 * 				Movie.title
 * @pre 	Assume that the Generic reference is indeed a Drama type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * 
 * @param other Generic reference to (presumably) a Drama object.
 * @return  Less-than comparison result
 */
bool Drama::operator < (const Generic& other) const {
	const Drama& d = static_cast<const Drama&>(other);
	if (director == d.director)
		return title < d.title;
	else
		return director < d.director;
}

//---------- setters ------------------------------------------------------


// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------

//-------------------------------------------- setData()
/**
* @brief There is significant commonality between Movie's various genres
*        as far as this routine goes. Thus, they all inherit the common
*        functionality from Movie.setData()
*
* @param in input stream containing the raw data
*/
void Drama::setData(istream& in) {
	Movie::setData(in);
}

//---------------------------------------------- parseTransactionData()
/**
 * @brief Extract info from the input stream and parses it into the private
 *        fields.
 * @details Uses the getter subroutines to parse the data one field at a time
 * 			The subroutines must be used in a correct order for a particular
 * 			data format.
 * 			This routine is called when initializing the transactions.
 * 			The presumed format for input is:
 * 				director, movie title (both of which are comma-separated)
 * 
 * @param in extracted istream&
 */
void Drama::parseTransactionData(istream& in) {
	// temporary array to hold data read from the stream
	int size = MAX_STRING_SIZE;
	char* temp = new char[size];
	for(int i = 0; i < size; i++)
		temp[i] = ' ';		// initialize

	this->director = Movie::setDirector(in, temp, size);
	this->title = Movie::setMovieTitle(in, temp, size);

	delete[] temp; temp = NULL;
}

// -------- no overloaded behavior observed

// ostream& operator << (ostream& out, const Drama& movie) {
// 	movie.formatOutput(out);
// 	return out;
// }

// void Drama::formatOutput(ostream& out) const {
// 	out << "in Drama.formatOutput()";
// }

#endif