//-------------------- Metadata --------------------
/**
 * @file classic.cpp
 * Purpose:     Implementation file for the class Classic
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#ifndef CLASSIC_CPP
#define CLASSIC_CPP

#include "classic.h"

//--------- Constructor/Destructor ----------------------------------------
Classic::Classic(int id) {
	this->genre = 'C';
	this->type = 'M';
	this->id = id;
	// other quantities are also initialized thanks to the base classes'
	// constructors
}

Classic::~Classic() {}

//---------- getters ------------------------------------------------------

/**
 * @brief Clone-like routine to generate an empty copy of 
 *        the same type / class.
 * @details Used in the Factory design model to facilitate polymorphism.
 * 
 * @param id unique id of the item to be created. Managed externally.
 * @return Item pointer to an empty object of Classic type.
 */
Item* Classic::createEmptyInstance(int id) const {
	Item* c = new Classic(id);
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
 * @details Compares by criteria: Classic.actorName, Classic.month, Movie.year
 * @pre 	Assume that the Generic reference is indeed a Classic type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * 
 * @param other Generic reference to (presumably) a Classic object.
 * @return  Equality comparison result
 */
bool Classic::operator == (const Generic& other) const {
	const Classic& c = static_cast<const Classic&>(other);
	return month == c.month && 
		   year == c.year && 
		   actorName == c.actorName;
}

//---------------------------------------------- operator<
/**
 * @brief 	Just an overloaded operator
 * @details Compares by criteria:
 * 				Classic.actorName, then
 * 				Classic.month, then
 * 				Movie.year
 * @pre 	Assume that the Generic reference is indeed a Classic type object.
 * 			There is minimal type-checking done. Use with extreme care.
 * 
 * @param other Generic reference to (presumably) a Classic object.
 * @return  Less-than comparison result
 */
bool Classic::operator < (const Generic& other) const {
	const Classic& c = static_cast<const Classic&>(other);
	if (year == c.year) {
		if (month == c.month)
			return actorName < c.actorName;
		else
			return month < c.month;
	}
	else
		return year < c.year;
}

//------------------------------------------ getHeader()
/**
 * @brief Simple retriever of the display header for this type of object
 * @return a string containing the header (separated in columns) for
 *         display this type of object in a table.
 */
string Classic::getHeader() const {
	return CLASSIC_HEADER;
}

//---------- setters ------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------------------- Notes --------------------------------------
// Input parsing is extremely sensitive to syntax correctness.
// There is minimal checking and error handling going on.
// Use with extreme care.
// ----------------------------------------------------------------------------

//------------------------------------------------ setData()
/**
 * @brief Extract info from the input stream and parses it into the private
 *        fields.
 * @details  Uses the getter subroutines to parse the data one field at a time
 * 			The subroutines must be used in a correct order for a particular
 * 			data format.
 * 			This routine is called when initializing the store.
 * 			The format for a Classic Movie is:
 * 				Director, Movie Title, Actor's Name, Month, Year
 *
 * @param in input stream containing the raw data
 */
void Classic::setData(istream& in) {
	// temporary array to hold data read from the stream
	int size = MAX_STRING_SIZE;
	char* temp = new char[size];
	for (int i = 0; i < size; i++)
		temp[i] = ' ';		// initialize

	// start reading and initializing fields in order
	// movieCategory = getMovieCode(in);
	mediaType = Movie::setMediaType(in);
	director = Movie::setDirector(in, temp, size);
	title = Movie::setMovieTitle(in, temp, size);
	actorName = setClassicActor(in);
	month = setMonth(in);
	year = setYear(in);
	delete[] temp; temp = NULL;
}

//------------------------------------------------ setMonth()
/**
 * @brief   Retrieves the production month of a movie from the input stream
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 *
 * @param in input stream reference
 * @return one string containing the month
 */
string Classic::setMonth(istream& in) const {
	string month; in >> month;
	return month;
}

//------------------------------------------------ getActor()
/**
 * @brief   Retrieves a Classic Movie's main actor info from the input stream
 * @details Assume that actor's name consists of only 2 parts:
 *          first name and last name.
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 *
 * @param in input stream reference
 * @return one string containing the actor's full name
 */
string Classic::setClassicActor(istream& in) const {
	string fname; in >> fname;
	string lname; in >> lname;
	return fname + ' ' + lname;
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
 * 				month, year, classic actor name
 * 
 * @param in extracted istream&
 */
void Classic::parseTransactionData(istream& in) {
	this->month = setMonth(in);
	this->year = Movie::setYear(in);
	this->actorName = setClassicActor(in);
}

//-------------------------------------------------- output ------------------

ostream& operator << (ostream& out, const Classic& movie) {
	movie.formatOutput(out);
	return out;
}

void Classic::formatOutput(ostream& out) const {
	out << formatTitle() << formatDirector() << year;
	out << setw(MONTH_MAX_WIDTH);
	out << month;
	out << " " << actorName;
}

#endif