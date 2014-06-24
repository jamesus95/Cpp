//-------------------- Metadata --------------------
/**
 * @file drama.h
 * Purpose:     Header file for the class Drama
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
 * @class Drama
 * Purpose:         One of the actual data objects, 
 *                  containing the input files' data.
 *                  This class facilitates the Factory OOP Design Pattern.
 *
 * Inherit from:    Movie      
 * Inherited by:    <none>
 *
 *///-------------------------------------------------


#ifndef drama_h
#define drama_h

#include "movie.h"

using namespace std;

class Drama : public Movie {
    
	// friend ostream& operator << (ostream&, const Drama&);

public:
    //---------- constructors/destructor --------------------------------------
    Drama(int = 0);
    ~Drama();
    Drama(const Drama&);
    
    //---------- getters ------------------------------------------------------
    /**
     * @brief Clone-like routine to generate an empty copy of 
     *        the same type / class.
     * @details Used in the Factory design model to facilitate polymorphism.
     * 
     * @param id unique id of the item to be created. Managed externally.
     * @return Item pointer to an empty object of Drama type.
     */
    Item* createEmptyInstance(int) const;

    /**
     * @brief   Just an overloaded operator
     * @details Compares by criteria: Movie.director, Movie.title
     * @pre     Assume that the Generic reference is indeed a Drama type object.
     *          There is minimal type-checking done. Use with extreme care.
     * @warning The c-string comparison is a workaround for a weird bug wherein
     *          identical strings (at least visually) fails the equality test.
     * 
     * @param other Generic reference to (presumably) a Drama object.
     * @return  Equality comparison result
     */
	bool operator == (const Generic&) const;

    /**
     * @brief   Just an overloaded operator
     * @details Compares by criteria:
     *              Movie.director, then
     *              Movie.title
     * @pre     Assume that the Generic reference is indeed a Drama type object.
     *          There is minimal type-checking done. Use with extreme care.
     * 
     * @param other Generic reference to (presumably) a Drama object.
     * @return  Less-than comparison result
     */
	bool operator < (const Generic&) const;
    // virtual void formatOutput(ostream&) const;

    //---------- setters ------------------------------------------------------
    /**
    * @brief There is significant commonality between Movie's various genres
    *        as far as this routine goes. Thus, they all inherit the common
    *        functionality from Movie.setData()
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
     *              director, movie title (both of which are comma-separated)
     * 
     * @param in extracted istream&
     */
    void parseTransactionData(istream&);
    
};

#endif
