//-------------------- Metadata --------------------
/**
 * @file movie.cpp
 * Purpose:     Implementation file for the class Movie
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------

#ifndef MOVIE_CPP
#define MOVIE_CPP

#include "movie.h"

//--------- Constructor/Destructor ----------------------------------------
Movie::Movie(int id) : id(id) {}
Movie::~Movie() {}

//---------- getters ------------------------------------------------------

char Movie::getGenre() const {
	return genre;
}

ostream& operator << (ostream& out, const Movie& movie) {
    movie.formatOutput(out);
    return out;
}

/**
 * @brief Output helper. Formats a Generic Movie's standard output.
 * @details Used as a workaround operator<<'s incompatibility with inheritance
 * 
 * @param out Modified ostream&
 */
void Movie::formatOutput(ostream& out) const {
    out << formatTitle() << formatDirector() << year;
}

// 
string Movie::formatTitle() const {
	string spaceFiller = ".";
    string formattedTitle = title.substr(0, MAX_TITLE_LENGTH);
	for (int i = formattedTitle.length(); i < MAX_TITLE_LENGTH; i++) {
		formattedTitle += spaceFiller;
	}
	formattedTitle += spaceFiller;
	return formattedTitle;
}

string Movie::formatDirector() const {
    string spaceFiller = ".";
	string formattedDirector = director.substr(0, MAX_DIRECTOR_LENGTH);
	for (int i = formattedDirector.length(); i < MAX_DIRECTOR_LENGTH; i++) {
		formattedDirector += spaceFiller;
	}
	formattedDirector += spaceFiller;
	return formattedDirector;
}

string Movie::getHeader() const {
	return GENERIC_HEADER;
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
 * @details Uses the getter subroutines to parse the data one field at a time
 * 			The subroutines must be used in a correct order for a particular
 * 			data format.
 * 			The format for a generic Movie is:
 * 				Director, Movie Title, Year
 * 
 * @param in input stream containing the raw data
 */
void Movie::setData(istream& in) {
	//-------------------- temporary array to hold data read from the stream
	int size = MAX_STRING_SIZE;
	char* temp = new char[size];
	for(int i = 0; i < size; i++)
		temp[i] = ' ';		// initialize

	//--------------------- start reading and initializing fields
	this->mediaType = setMediaType(in);
	this->director = setDirector(in, temp, size);
	this->title = setMovieTitle(in, temp, size);
	this->year = setYear(in);

    delete[] temp; temp = NULL;
	
}

//------------------------------------------------ getMovieCode()
/**
 * @brief   Retrieves the character code from the input stream
 * @details Retrieves only the first space-delimited character from
 *          the input stream.
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 * 
 * @param in istream object containing the data to be parsed
 * @return a string of length 1 containing the code for the movie subtype
 */
string Movie::getMovieCode(istream& in) const {
    string code;
    in >> code;     // read one space-delimited token
    return code;    // assume that the token is the code
}

/**
 * @brief Retrieves the media format for the movie entry from the input
 *        stream.
 * @details Hard-coded for now. There is no parsing.
 * 
 * @param in input stream reference
 * @return a string containing the character "D" (for DVD)
 */
string Movie::setMediaType(istream& in) const {
    string s("D");  // hard-coded for now
    return s;
}

//------------------------------------------------ setDirector()
/**
 * @brief   Retrieves the full name of the director from the input stream
 * @details Retrieves the first comma-delimited string from the
 *          input stream and assume that it is the director's full name.
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 *          
 * @param in input stream reference
 * @param temp temporary array to hold the content being read
 * @param tempSize max size of this temp array
 * @return one string containing the director's full name
 */
string Movie::setDirector(istream& in, char* temp, int tempSize) const {
    char delim = ',';       // get all parts of a name
    in.getline(temp, tempSize, delim);
    string director = string(temp, getSizeOf(temp, tempSize));
    return director;
}

//------------------------------------------------ get size helper
/**
 * @brief Get size of the meaningful part of the c-string
 * @pre   Uses a double whitespace as the termination flag
 * 
 * @param c c-string to be investigated
 * @param max_size size of the c-string array
 * @return size of the content contained inside `c`
 */
int Movie::getSizeOf(char* c, int max_size) const {
    int i = 0;
    while(i < max_size - 1) {
        if(c[i] == ' ' && c[i+1] == ' ') break;     // double space terminate
        i++;
    }
    return i;
}


//------------------------------------------------ setMovieTitle()
/**
 * @brief   Retrieves the full title of the movie from the input stream
 * @details Retrieves the first comma-delimited string from the
 *          input stream and assume that it is the full title.
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 *          
 * @param in input stream reference
 * @param temp temporary array to hold the content being read
 * @param tempSize max size of this temp array
 * @return one string containing the full title of the movie
 */
string Movie::setMovieTitle(istream& in, char* temp, int tempSize) const {
    for (int i = 0; i < tempSize; i++)
        temp[i] = ' ';
    char delim = ',';
    in.getline(temp, tempSize, delim);
    string title = string(temp, getSizeOf(temp, tempSize));
    return title;
}

//------------------------------------------------ setYear()
/**
 * @brief   Retrieves the production year of a movie from the input stream
 * @pre     The input stream's cursor must be located directly in front
 *          of the content to be extracted. Use this subroutine (and others)
 *          in appropriate orders to ensure this assumption.
 *          
 * @param in input stream reference
 * @return one string containing the year
 */
string Movie::setYear(istream& in) const {
    string year; in >> year;
    return year;
}

// May not be needed because each genre's functionality
// is different. Declared to make compiler happy.
// void Movie::parseTransactionData(istream& in) {
// 
// }




#endif