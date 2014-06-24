//-------------------- Metadata --------------------
/**
 * @file comedy.cpp
 * Purpose:     Implementation file for the class Comedy
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------


#ifndef COMEDY_CPP
#define COMEDY_CPP

#include "comedy.h"


//--------- Constructor/Destructor ----------------------------------------
Comedy::Comedy(int id) {
	this->genre = 'F';
	this->type = 'M';
	this->id = id;
	this->movieCategory = "F";	// may not currently be used
	// other quantities are also initialized thanks to the base classes'
	// constructors
}

Comedy::~Comedy() {}

//---------- getters ------------------------------------------------------

//--------------------------------------------- createEmptyInstance()
/**
 * @brief Clone-like routine to generate an empty copy of 
 *        the same type / class.
 * @details Used in the Factory design model to facilitate polymorphism.
 * 
 * @param id unique id of the item to be created. Managed externally.
 * @return Item pointer to an empty object of Comedy type.
 */
Item* Comedy::createEmptyInstance(int id) const {
	Item* c = new Comedy(id);
	return c;
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
 * @details Compares by criteria: Movie.title, Movie.year
 * @pre 	Assume that the Generic reference is indeed a Comedy type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * 
 * @param other Generic reference to (presumably) a Comedy object.
 * @return  Equality comparison result
 */
bool Comedy::operator == (const Generic& other) const {
	// that's a bold cast, Cotton, let's see if it pays off for him
	const Comedy& c = static_cast<const Comedy&>(other);
	int i = strcmp(title.c_str(), c.title.c_str()) + strcmp(year.c_str(), c.year.c_str());
	return i == 0;
}
	
//---------------------------------------------- operator<
/**
 * @brief 	Just an overloaded operator
 * @details Compares by criteria:
 * 				Movie.title, then
 * 				Movie.year
 * @pre 	Assume that the Generic reference is indeed a Comedy type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * 
 * @param other Generic reference to (presumably) a Comedy object.
 * @return  Less-than comparison result
 */
bool Comedy::operator < (const Generic& other) const {
	const Comedy& c = static_cast<const Comedy&>(other);
	if (title == c.title)
		return year < c.year;
	else
		return title < c.title;
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
void Comedy::setData(istream& in) {
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
 * 				movie title (ended with a ','), year
 * 
 * @param in extracted istream&
 */
void Comedy::parseTransactionData(istream& in) {
	// temporary array to hold data read from the stream
	int size = MAX_STRING_SIZE;
	char* temp = new char[size];
	for(int i = 0; i < size; i++)
		temp[i] = ' ';		// initialize

	this->title = Movie::setMovieTitle(in, temp, size);
	this->year = Movie::setYear(in);

	delete[] temp; temp = NULL;
}


// -------- no overloaded behavior observed, so these are
// -------- neither declared nor defined
// -------- We're not sure which approach is the "best practice" when it comes
// -------- to functionalities that are not overloaded.

// ostream& operator << (ostream& out, const Comedy& movie) {
// 	movie.formatOutput(out);
// 	return out;
// }

// void Comedy::formatOutput(ostream& out) const {
// 	out << "in Comedy.formatOutput()";
// }

#endif