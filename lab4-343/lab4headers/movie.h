//-------------------- Metadata --------------------
/**
 * @file movie.h
 * Purpose:     Header file for the class Movie
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------
        
//--------------- Class Description -----------------
/**
 * @class Movie
 * Purpose:         Generic Movie template for various 
 *                  movie genres to extend from.
 *                  This class facilitates the Factory OOP Design Pattern.
 *
 * Inherit from:    Item      
 * Inherited by:    Classic, Comedy, Drama (and more if desired)
 *
 *///-------------------------------------------------

#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"
#include <string>

using namespace std;

#define MAX_TITLE_LENGTH 20
#define MAX_DIRECTOR_LENGTH 16
#define MAX_STRING_SIZE 256
#define GENERIC_HEADER "TITLE                DIRECTOR         YEAR"

class Movie : public Item {
    
	friend ostream& operator << (ostream&, const Movie&);

public:
    
    //---------- constructors/destructor --------------------------------------
    /**
     * @brief movie constructor
     * 
     * @param  int : ID
     */
    Movie(int = 0);

    /**
     * @brief movie copy constructor
     * 
     * @param  const Movie& : Movie to copy
     */
    Movie(const Movie&);

    /**
     * @brief virtual destructor
     */
    virtual ~Movie();

    //---------- pure virtual functions ---------------------------------------
    /**
     * @brief creates an empty Item instance
     * @details overridden by inherited memebers to create specific instances
     * returned as Item pointers
     * 
     * @param  int : Item ID
     * @return Item* : a pointer pointint to the newly created instance
     */
    virtual Item* createEmptyInstance(int) const = 0;    // similar to clone()
	
    /**
     * @brief == operator
     * @details overridden by inherited members with specific 
     * comparison criteria
     * 
     * @param  Generic& : Generic to compare to
     * @return bool : if they are equal or not
     */
    virtual bool operator == (const Generic&) const = 0;
	
    /**
     * @brief < operator
     * @details overridden by inherited members with specific 
     * less than comparison criteria
     * 
     * @param  Generic& : Generic to compare to
     * @return bool : if they are equal or not
     */
    virtual bool operator < (const Generic&) const = 0;

    /**
     * @brief parses the data out of a istream to set
     * @details overridden by inherited members to get data out of an istream.
     * Used in the creation of reference items in the TransactionFactory
     * DOES NOT FILL ALL DATA FIELDS
     * 
     * @param  istream& : to get data out of
     */
    virtual void parseTransactionData(istream&) = 0;
	
	//---------- getters ------------------------------------------------------
    /**
     * @brief gets the Genre
     * @details gets the Genre of the Movie
     * @return char : Genre char
     */
    virtual char getGenre() const;          // similar to Item.getType() 
	
    /**
     * @brief gets the header to print in the DisplayInventory Transaction
     * @return string : header
     */
    virtual string getHeader() const;
	
    // int hash(char) const;                   // may not be necessary
	
    /**
     * @brief Output helper. Formats a Generic Movie's standard output.
     * @details Used as a workaround operator<<'s incompatibility with inheritance
     *  
     * @param out Modified ostream&
     */
    virtual void formatOutput(ostream&) const;

    //---------- setters ------------------------------------------------------
    /**
     * @brief Extract info from the input stream and parses it into the private
     *        fields.
     * @details Uses the getter subroutines to parse the data one field at a time
     *          The subroutines must be used in a correct order for a particular
     *          data format.
     *          The format for a generic Movie is:
     *              Director, Movie Title, Year
     * 
     * @param in input stream containing the raw data
     */
    virtual void setData(istream&);    // populate Movie's private fields

protected:
    int id;
    string movieCategory;   // F (Comedy), D (Drama) or C (Classic)
    string mediaType;       // D (DVD)
    string director;
    string title;
    string year;
	char genre;             // F (Comedy), D (Drama) or C (Classic)

    //---------- getter helpers -----------------------------------------------
    /**
     * @brief Get size of the meaningful part of the c-string
     * @pre   Uses a double whitespace as the termination flag
     * 
     * @param c c-string to be investigated
     * @param max_size size of the c-string array
     * @return size of the content contained inside `c`
     */
    int getSizeOf(char*, int) const;    // determine size of c-string

    //---------- input routines -----------------------------------------------
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
    string getMovieCode(istream&) const;
    
    /**
     * @brief Retrieves the media format for the movie entry from the input
     *        stream.
     * @details Hard-coded for now. There is no parsing.
     * 
     * @param in input stream reference
     * @return a string containing the character "D" (for DVD)
     */
    string setMediaType(istream&) const;  // hard-coded for now
    
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
    string setDirector(istream&, char*, int) const;

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
    string setMovieTitle(istream&, char*, int) const;
    
    /**
     * @brief   Retrieves the production year of a movie from the input stream
     * @pre     The input stream's cursor must be located directly in front
     *          of the content to be extracted. Use this subroutine (and others)
     *          in appropriate orders to ensure this assumption.
     *          
     * @param in input stream reference
     * @return one string containing the year
     */
    string setYear(istream& in) const;
	
	//---------- formatting functions for output operator ---------------------
	
    /**
     * @brief Format the Movie's title to be properly displayed in
     *        a table, on a letter-sized paper, without modification to
     *        the data.
     * @details truncate the title if it's too long and pad the 
     *          empty space with a filler character for ease of view.
     */
    string formatTitle() const;

    /**
     * @brief Format the Movie's author to be properly displayed in
     *        a table, on a letter-sized paper, without modifying internal
     *        data.
     * @details truncate the Author's name if it's too long and pad the 
     *          empty space with a filler character for ease of view.
     */
	string formatDirector() const;
	
};

#endif
