//-------------------- Metadata --------------------
/**
 * @file generic.h
 * Purpose:     Header file for the `generic data` class
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
 * @class GENERIC
 * Purpose:         Generic data object to be inherited from for polymorphism.
 *                  This class was created solely for the purpose of re-using
 *                  data structures.
 *                  
 *                  Derived classes from Generic assumes that the overloaded
 *                  operators / routines are used correctly. There is
 *                  a minimal amount of type-checking done.
 *
 * Inherit from:    <none>      
 * Inherited by:    Item, Customer
 *
 *///-------------------------------------------------
        
#ifndef GENERIC_H
#define GENERIC_H

#include <iostream>

using namespace std;

class Generic {

	/**
	 * @brief friend ostream << operator
	 * @details outputs the generic to the ostream
	 * 
	 * @param ostream& : to output to
	 * @param Generic& : to output
	 */
	friend ostream& operator << (ostream&, const Generic&);

public:
	/**
	 * @brief virtual destructor
	 */
	virtual ~Generic();

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
	 * @brief formats the generic for output
	 * @details formats the generic and outputs it to the given
	 * ostream
	 * 
	 * @param  ostream& : for output the generic
	 */
	virtual void formatOutput(ostream&) const = 0;    // operator<< helper

};

#endif