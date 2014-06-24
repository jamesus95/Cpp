//-----------------------------------------------------------------------------
// POLY.H
// Class for storing polynomials
// Author: James Murphree
//-----------------------------------------------------------------------------
// Poly class:  stores the information of a polynomial
//   included features:
//   -- Constructor for a single element of any exponent, a single constant
//		element, and a copy constructor
//	 -- Destructor
//	 -- +, -, * operators and their coresponding assignment operators
//	 -- Assignment operator (=)
//	 -- ==, != boolean operators
//	 -- <<, >> input/output operators
//	 -- getCoeff() for getting the coeff of an exponent
//	 -- setCoeff() for setting the coeff of an exponent
//
// Assumptions:
//   -- Contains only positive integer exponents
//	 -- Contains only integer coefficients
//	 -- Inputs are all integers
//-----------------------------------------------------------------------------

#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;

class Poly {

//------------------------------  <<  -----------------------------------------
//	Overloaded output operator for the Poly Class.  Outputs a formatted version
//	of the contained Poly.
//	PreConditions:	None
//	PostConditions:	Outputs the poly in the format Ax^z Bx^y ... Cx^2 Dx E
//					Where A, B, C, D, and E are constants and are printed with
//					a corresponding + or -
//					The exponents are ordered largest to smallest
//					And x^1 is represented as x AND x^0 is not displayed
//	Return:			ostream& for sequential outputs
friend ostream& operator << (ostream&, Poly&);

//------------------------------  >>  -----------------------------------------
//	Overloaded input operator for the Poly Class.  Inputs pairs of integers
//	representing coefficients and exponents into the polynomial.
//	PreConditions:	Input must be pairs of integers
//					Where the second of the pair must be 0 or greater
//					And the last pair must be -1 -1 denoting the end
//	PostConditions:	The integer pairs are added to the polynomial
//	Return:			istream& for sequential inputs
friend istream& operator >> (istream&, Poly&);

public:
//------------------------------  Constructor  --------------------------------
//	Constructs a Poly with input or default coefficient and exponent.
//	PreConditions:	takes in no inputs, a coefficient, or a coefficient and
//					an exponent
//	PostConditions:	creates a Poly without any elements, a Poly with the
//					input coefficient as the constant term, or a Poly with the
//					input coefficient in the input exponents term
//					If the input exponent is less than 0 it is set to 0
//	Parameters:		Coefficient, Exponent (can omit exponent or both)
Poly(int = 0, int = 0);

//------------------------------  Copy  ---------------------------------------
//	Constructs a Poly that is a copy of the passed in Poly.
//	PreConditions:	polyToCopy.poly points to an array in memory
//	PostConditions:	creates a Poly with all the elements contained in the
//					passed in Poly
Poly(const Poly&);

//------------------------------  Destructor ----------------------------------
//	Deletes the Poly.
//	PreConditions:	*this.poly points to an array in memory
//	PostConditions:	releases all the memory used by the Poly
~Poly();

//------------------------------  +  ------------------------------------------
//	Adds two Polys together.
//	PreConditions: 	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly consisting of the sum of all elements
//					from the two added together
Poly operator + (const Poly&) const;

//------------------------------  -  ------------------------------------------
//	Subtracts the second Poly from the first.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly consisting of the addition of the first
//					poly with the negative of the second
Poly operator - (const Poly&) const;

//------------------------------  *  ------------------------------------------
//	Multiplies the two Polys together.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly that is the product of the two
//					input Polys
Poly operator * (const Poly&) const;

//------------------------------  =  ------------------------------------------
//	Assigns THIS poly to values of another Poly
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	sets THIS Poly's values equal to the input Poly's
//	Return:			Returns THIS Poly for chaining operations
Poly& operator = (const Poly&);

//------------------------------  +=  -----------------------------------------
//	Assigns THIS poly to the sum of THIS Poly and another.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Adds the contents of the right side Poly to THIS Poly
//	Return:			Returns THIS Poly for chaining operations
Poly& operator += (const Poly&);

//------------------------------  -=  -----------------------------------------
//	Assigns THIS poly to the sum of THIS poly and the negative of another Poly
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Adds the negative contents of the right side Poly to THIS
//					Poly
//	Return:			Returns THIS Poly for chaining operations
Poly& operator -= (const Poly&);

//------------------------------  *=  -----------------------------------------
//	Assigns THIS poly to the product of THIS Poly and another.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Multiplies THIS Poly with the right side Poly and assigns
//					THIS Poly to the result
//	Return:			Returns THIS Poly for chaining operations
Poly& operator *= (const Poly&);

//------------------------------  ==  -----------------------------------------
//	Checks if two Polys are equivelant.
//	PreConditions:	right.poly points to an array in memory
//	PostConditions:	returns true if the Polys are equivelant
bool operator == (const Poly&) const;

//------------------------------  !=  -----------------------------------------
//	Checks if two Polys are not equivelant
//	PreConditions:	right.poly points to an array in memory
//	PostConditions:	returns true if the Polys are NOT equivelant
bool operator != (const Poly&) const;

//------------------------------  getCoeff  -----------------------------------
//	Gets the coefficient of the input exponent.
//	PreConditions:	None
//	PostConditions:	returns the coefficient for the input exponent or 0 if the
//					exponent is out of the array bounds
//	Parameters:		Exponent
int getCoeff(int) const;

//------------------------------  setCoeff  -----------------------------------
//	Sets the specified coefficient.
//	PreConditions:	input exponent is greater than -1
//	PostConditions:	Sets the coefficient of the input exponent to the 
//					input coefficient
//	Parameters:		Coefficient, Exponent
void setCoeff(int, int);

private:

int* poly;		// array of coefficients (indexes are exponents)
int size;		// size of array (NOT max polynomial term)

//------------------------------  zero  ---------------------------------------
//	Zeros out an array.
//	PreConditions:	input int pointer must point to an element in an array 
//					so that the int pointer plus the input size does not run
//					off the end of the array
//	PostConditions:	sets the indexes from a chunk of the input array from the 
//					input pointer to the input pointer plus the input size 
//					to zero
//	Parameters:		Array (can be a int* to any index), Size
void zero(int*, int);

//------------------------------  checkEmpty  ---------------------------------
//	Checks to see if the array contains all zeros.
//	PreConditions:	input int must be greater than -1 and less than size
//	PostConditions:	Checks if *this.poly contains only zeros starting at the
//					input index
bool checkEmpty(int) const;

//------------------------------  increaseSize  -------------------------------
//	Increases the size of *this.poly
//	PreConditions:	input size must be greater than *this.size
//	PostConditions:	creates a new array of input size and copies over values
//					from *this.poly and sets *this.poly to the new array
//					deletes old array
void increaseSize(int);

//------------------------------  add  ----------------------------------------
//	Adds the contents of the input Poly to THIS Poly
//	PreConditions:	None
//	PostConditions:	adds the coefficients from the input Poly to THIS Poly and
//					multiplies them by the input multiplier int
void add(const Poly&, int);

};

#endif