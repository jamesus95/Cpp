//-----------------------------------------------------------------------------
// POLY.CPP
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

#ifndef POLY_CPP
#define POLY_CPP

#include "poly.h"

//------------------------------  Constructor  --------------------------------
//	Constructs a Poly with input or default coefficient and exponent.
//	PreConditions:	takes in no inputs, a coefficient, or a coefficient and
//					an exponent
//	PostConditions:	creates a Poly without any elements, a Poly with the
//					input coefficient as the constant term, or a Poly with the
//					input coefficient in the input exponents term
//					If the input exponent is less than 0 it is set to 0
//	Parameters:		Coefficient, Exponent (can omit exponent or both)
Poly::Poly(int coeff, int exp) {
	if (exp < 0) {
		exp = 0;
		coeff = 0;
	}
	size = exp + 1;
	poly = new int[size];
	zero(poly, size);
	poly[exp] = coeff;
}

//------------------------------  Copy  ---------------------------------------
//	Constructs a Poly that is a copy of the passed in Poly.
//	PreConditions:	polyToCopy.poly points to an array in memory
//	PostConditions:	creates a Poly with all the elements contained in the
//					passed in Poly
Poly::Poly(const Poly& other) {
	size = other.size;
	poly = new int[size];
	zero(poly, size);
	for (int i = 0; i < size; i++) {
		poly[i] = other.poly[i];
	}
}

//------------------------------  Destructor ----------------------------------
//	Deletes the Poly.
//	PreConditions:	*this.poly points to an array in memory
//	PostConditions:	releases all the memory used by the Poly
Poly::~Poly() {
	zero(poly, size);
	delete[] poly;
	poly = NULL;
}

//------------------------------  increaseSize  -------------------------------
//	Increases the size of *this.poly
//	PreConditions:	input size must be greater than *this.size
//	PostConditions:	creates a new array of input size and copies over values
//					from *this.poly and sets *this.poly to the new array
//					deletes old array
void Poly::increaseSize(int size) {
	if (size > this->size) {
		int* temp = new int[size];
		zero(temp, size);
		for (int i = 0; i < this->size; i++) {
			temp[i] = poly[i];
		}
		zero(poly, this->size);
		delete[] poly;
		poly = temp;
		temp = NULL;
		this->size = size;
	}
}

//------------------------------  zero  ---------------------------------------
//	Zeros out an array.
//	PreConditions:	input int pointer must point to an element in an array 
//					so that the int pointer plus the input size does not run
//					off the end of the array
//	PostConditions:	sets the indexes from a chunk of the input array from the 
//					input pointer to the input pointer plus the input size 
//					to zero
//	Parameters:		Array (can be a int* to any index), Size
void Poly::zero(int* array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
}

//------------------------------  +  ------------------------------------------
//	Adds two Polys together.
//	PreConditions: 	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly consisting of the sum of all elements
//					from the two added together
Poly Poly::operator + (const Poly& rightSide) const {
	Poly temp = Poly(*this);
	temp.add(rightSide, 1);
	return temp;
}

//------------------------------  -  ------------------------------------------
//	Subtracts the second Poly from the first.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly consisting of the addition of the first
//					poly with the negative of the second
Poly Poly::operator - (const Poly& rightSide) const {
	Poly temp = Poly(*this);
	temp.add(rightSide, -1);
	return temp;
}

//------------------------------  add  ----------------------------------------
//	Adds the contents of the input Poly to THIS Poly
//	PreConditions:	None
//	PostConditions:	adds the coefficients from the input Poly to THIS Poly and
//					multiplies them by the input multiplier int
void Poly::add(const Poly& other, int multiplier) {
	if (other.size > size)
		increaseSize(other.size);
	for (int i = 0; i < other.size; i++) {
		poly[i] += (multiplier * other.poly[i]);
	}
}

//------------------------------  *  ------------------------------------------
//	Multiplies the two Polys together.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	creates a new Poly that is the product of the two
//					input Polys
Poly Poly::operator * (const Poly& rightSide) const {
	Poly temp = Poly();
	for (int i = 0; i < size; i++) {	// loop through first Poly
		if (poly[i] != 0) {
			for (int j = 0; j < rightSide.size; j++) {
				if (rightSide.poly[j] != 0) {	
					temp.setCoeff(poly[i] * rightSide.poly[j] + temp.getCoeff(i + j), i + j);
				}
			}
		}
	}
	return temp;
}

//------------------------------  =  ------------------------------------------
//	Assigns THIS poly to values of another Poly
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	sets THIS Poly's values equal to the input Poly's
//	Return:			Returns THIS Poly for chaining operations
Poly& Poly::operator = (const Poly& rightSide) {
	if (this != &rightSide) {
		if (size < rightSide.size)
			increaseSize(rightSide.size);
		for (int i = 0; i < rightSide.size; i++) {
			this->poly[i] = rightSide.poly[i];
		}
	}
	return *this;
}

//------------------------------  +=  -----------------------------------------
//	Assigns THIS poly to the sum of THIS Poly and another.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Adds the contents of the right side Poly to THIS Poly
//	Return:			Returns THIS Poly for chaining operations
Poly& Poly::operator += (const Poly& rightSide) {
	this->add(rightSide, 1);
	return *this;
}

//------------------------------  -=  -----------------------------------------
//	Assigns THIS poly to the sum of THIS poly and the negative of another Poly
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Adds the negative contents of the right side Poly to THIS
//					Poly
//	Return:			Returns THIS Poly for chaining operations
Poly& Poly::operator -= (const Poly& rightSide) {
	this->add(rightSide, -1);
	return *this;
}

//------------------------------  *=  -----------------------------------------
//	Assigns THIS poly to the product of THIS Poly and another.
//	PreConditions:	right.poly points to an array in memory 
//	PostConditions:	Multiplies THIS Poly with the right side Poly and assigns
//					THIS Poly to the result
//	Return:			Returns THIS Poly for chaining operations
Poly& Poly::operator *= (const Poly& rightSide) {
	// Simpler than trying to augment THIS Poly because multiplication doesn't
	// retain previous values like addition/subtraction do
	// AKA: Readability > Efficiency
	*this = *this * rightSide;
	return *this;
}

//------------------------------  ==  -----------------------------------------
//	Checks if two Polys are equivelant.
//	PreConditions:	right.poly points to an array in memory
//	PostConditions:	returns true if the Polys are equivelant
bool Poly::operator == (const Poly& rightSide) const {
	int size = (this->size < rightSide.size ? this->size : rightSide.size);
	for (int i = 0; i < size; i++) {
		if (poly[i] != rightSide.poly[i])
			return false;
	}
	if (this->size == rightSide.size) {
		return true;
	} else if (this->size == size) {
		return rightSide.checkEmpty(size);
	} else {
		return this->checkEmpty(size);
	}
}

//------------------------------  checkEmpty  ---------------------------------
//	Checks to see if the array contains all zeros.
//	PreConditions:	input int must be greater than -1 and less than size
//	PostConditions:	Checks if *this.poly contains only zeros starting at the
//					input index
bool Poly::checkEmpty(int startIndex) const {
	for (int i = startIndex; i < size; i++) {
		if (poly[i] != 0)
			return false;
	}
	return true;
}

//------------------------------  !=  -----------------------------------------
//	Checks if two Polys are not equivelant
//	PreConditions:	right.poly points to an array in memory
//	PostConditions:	returns true if the Polys are NOT equivelant
bool Poly::operator != (const Poly& rightSide) const {
	return !(*this == rightSide);
}

//------------------------------  getCoeff  -----------------------------------
//	Gets the coefficient of the input exponent.
//	PreConditions:	None
//	PostConditions:	returns the coefficient for the input exponent or 0 if the
//					exponent is out of the array bounds
//	Parameters:		Exponent
int Poly::getCoeff(int exp) const {
	if (exp < size && exp >= 0)
		return poly[exp];
	else 
		return 0;
}

//------------------------------  setCoeff  -----------------------------------
//	Sets the specified coefficient.
//	PreConditions:	input exponent is greater than -1
//	PostConditions:	Sets the coefficient of the input exponent to the 
//					input coefficient
//	Parameters:		Coefficient, Exponent
void Poly::setCoeff(int coeff, int exp) {
	if (exp > -1) {	
		if (exp >= size) {
			increaseSize(exp + 1);
		}
		poly[exp] = coeff;
	}
}

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
ostream& operator << (ostream& out, Poly& other) {
	if (other.checkEmpty(0)) {
		out << " 0";
		return out;
	}
	for (int i = other.size - 1; i >= 0; i--) {
		if (other.poly[i] != 0) {
			out << " ";
			if (other.poly[i] > 0)
				out << "+";
			out << other.poly[i];
			if (i != 0 && i != 1)
				out << "x^" << i;
			else if (i != 0)
				out << "x";
		}
	}
	return out;
}

//------------------------------  >>  -----------------------------------------
//	Overloaded input operator for the Poly Class.  Inputs pairs of integers
//	representing coefficients and exponents into the polynomial.
//	PreConditions:	Input must be pairs of integers
//					Where the second of the pair must be 0 or greater
//					And the last pair must be -1 -1 denoting the end
//	PostConditions:	The integer pairs are added to the polynomial
//	Return:			istream& for sequential inputs
istream& operator >> (istream& in, Poly& other) {
	int coeff = -1;
	int exp = -1;
	in >> coeff;
	in >> exp;
	while (coeff != -1 || exp != -1) {
		if (exp > -1) {
			other.setCoeff(coeff + other.poly[exp], exp);
			in >> coeff;
			in >> exp;
		}	
	}
	return in;
}

#endif