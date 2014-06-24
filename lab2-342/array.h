// file array.h
// Simple class Array (for integers)
// Example from Deitel and Deitel: C++ How To Program

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Array class:  like an int array (retains all functionality) but also
//   includes additional features:
//   -- allows input and output of the whole array
//   -- allows for comparison of 2 arrays, element by element
//   -- allows for assignment of 2 arrays
//   -- size is part of the class (so no longer needs to be passed)
//   -- includes range checking, program terminates for out-of-bound subscripts
//
// Assumptions:
//   -- size defaults to a fixed size of 10 if size is not specified
//   -- array elements are initialized to zero
//   -- user must enter valid integers when using >>
//   -- in <<, integers are displayed 10 per line
//---------------------------------------------------------------------------

class Array {
   friend ostream& operator<<(ostream &, const Array &);
   friend istream& operator>>(istream &, Array &);

public:
   Array(int = 10);                        // default constructor
   Array(const Array &);                   // copy constructor
   ~Array();                               // destructor

   int getSize() const;                    // return size of array
   Array& operator=(const Array &);        // assign arrays
   bool operator==(const Array &) const;   // compare for equal of 2 arrays
   bool operator!=(const Array &) const;   // compare not equal of 2 arrays
   int& operator[](int);                   // subscript operator, mutator
   const int& operator[](int) const;       // subscript operator, accessor
   static int getArrayCount();             // count of arrays instantiated

private:
   int* arrayPtr;                          // pointer to first element of array
   int size;                               // size of the array
   static int arrayCount;                  // # of Arrays instantiated
};

#include "array.cpp"
#endif
