//-------------------- Metadata --------------------
/**
 * @file classic.h
 * Purpose:     Header file for the class Classic (a Movie genre/subtype)
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
 * @class Classic
 * Purpose:         One of the actual data objects, 
 *                  containing the input files' data.
 *                  This class facilitates the Factory OOP Design Pattern.
 *
 * Inherit from:    Movie
 * Inherited by:    <none>  (not set up to be inherited)
 *
 *///-------------------------------------------------


#ifndef CLASSIC_H
#define CLASSIC_H

#include "movie.h"
#include <iomanip>      // for setw()
#include <iostream>

using namespace std;

#define MONTH_MAX_WIDTH 3
#define CLASSIC_HEADER "TITLE                DIRECTOR         YEAR MO YEAR"

class Classic : public Movie {

	friend ostream& operator << (ostream&, const Classic&);

public:
    
	//---------- constructors/destructor --------------------------------------
    Classic(int = 0);
    ~Classic();
    Classic(const Classic&);
    
	//---------- getters ------------------------------------------------------
    /**
     * @brief Clone-like routine to generate an empty copy of 
     *        the same type / class.
     * @details Used in the Factory design model to facilitate polymorphism.    
     * 
     * @param id unique id of the item to be created. Managed externally.
     * @return Item pointer to an empty object of Classic type.
     */
    Item* createEmptyInstance(int) const;
	
    /**
     * @brief   Just an overloaded operator
     * @details Compares by criteria: Classic.actorName, Classic.month, Movie.year
     * @pre     Assume that the Generic reference is indeed a Classic type object.
     *          There is minimal type-checking done. Use with extreme care.
     * 
     * @param other Generic reference to (presumably) a Classic object.
     * @return  Equality comparison result
     */
    bool operator == (const Generic&) const;
	
    /**
     * @brief   Just an overloaded operator
     * @details Compares by criteria:
     *              Classic.actorName, then
     *              Classic.month, then
     *              Movie.year
     * @pre     Assume that the Generic reference is indeed a Classic type object.
     *          There is minimal type-checking done. Use with extreme care.
     * 
     * @param other Generic reference to (presumably) a Classic object.
     * @return  Less-than comparison result
     */
    bool operator < (const Generic&) const;
	
    /**
     * @brief Simple retriever of the display header for this type of object
     * @return a string containing the header (separated in columns) for
     *         display this type of object in a table.
     */
    string getHeader() const;

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
     * @details  Uses the getter subroutines to parse the data one field at a time
     *          The subroutines must be used in a correct order for a particular
     *          data format.
     *          This routine is called when initializing the store.
     *          The format for a Classic Movie is:
     *              Director, Movie Title, Actor's Name, Month, Year
     *
     * @param in input stream containing the raw data
     */
    void setData(istream&);

    /**
     * @brief Extract info from the input stream and parses it into the private
     *        fields.
     * @details Uses the getter subroutines to parse the data one field at a time
     *          The subroutines must be used in a correct order for a particular
     *          data format.
     *          This routine is called when initializing the transactions.
     *          The presumed format for input is:
     *              month, year, classic actor name
     * 
     * @param in extracted istream&
     */
    void parseTransactionData(istream&);
    
private:
    
    // fields inherited from Movie not listed

    //---------- unique fileds and getters for classic movies -----------------
    string month;
    string actorName;

    /**
     * @brief   Retrieves the production month of a movie from the input stream
     * @pre     The input stream's cursor must be located directly in front
     *          of the content to be extracted. Use this subroutine (and others)
     *          in appropriate orders to ensure this assumption.
     *
     * @param in input stream reference
     * @return one string containing the month
     */
    string setMonth(istream&) const;

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
    string setClassicActor(istream&) const;
};

#endif
