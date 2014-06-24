/** Simple int array class:
    @file array.cpp
// Member function definitions for class Array
// Example from Deitel and Deitel: C++ How To Program
   added initializer for copy constructor so we could use operator= rcs13Jan14
*/

#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <assert.h>
#include "array.h"

// Note that the side comments in this file are for teaching
// purposes only.  In production code, they would all be
// unnecessary as they repeat what the actual code does. 

// If you want to follow order of calling constructors and
// destructors, uncomment cout code.

// Initialize static data member at file scope
int Array::arrayCount = 0;              // no objects yet

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for class Array
Array::Array(int arraySize) {
//   cout << "IN DEFAULT CONSTRUCTOR!!!" << *this << endl;
   ++arrayCount;                               // count one more object
   size = (arraySize > 0 ? arraySize : 10);    // default size is 10
   arrayPtr = new int[size];                   // create space for array

   for (int i = 0; i < size; i++)
      arrayPtr[i] = 0;                         // initialize array elements
}

// ---------------------------------------------------------------------------
// Copy 
// Copy constructor for class Array
// causes access violation see array2 for working version
Array::Array(const Array &init) {
    cout << "IN COPY CONSTRUCTOR!!!" << *this << endl;
   ++arrayCount;                             // count one more object   
   size = init.size;                         // size this object
   arrayPtr = new int[size];                 // create space for array

   for (int i = 0; i < size; i++)
      arrayPtr[i] = init.arrayPtr[i];        // copy init into object
}

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for class Array
Array::~Array() {
//   cout << "IN DESTRUCTOR!!!" << *this << endl;
   --arrayCount;                             // one fewer objects
   delete [] arrayPtr;                       // reclaim space for array
   arrayPtr = NULL;
}

// ---------------------------------------------------------------------------
// operator= 
// Overloaded assignment operator
Array& Array::operator=(const Array& right) {
   if (&right != this) {                    // check for self-assignment
      delete [] arrayPtr;                   // reclaim space
      size = right.size;                    // resize this object
      arrayPtr = new int[size];             // create space for array copy

      for (int i = 0; i < size; i++)
         arrayPtr[i] = right.arrayPtr[i];   // copy array into object
   }

   return *this;                            // enables x = y = z;
}

// --------------------------------------------------------------------------
// getSize 
// Get the size of the array
int Array::getSize() const { return size; }

// --------------------------------------------------------------------------
// operator== 
// Determine if two arrays are equal.
bool Array::operator==(const Array& right) const {
   if (size != right.size)
      return false;                    // arrays of different sizes

   for (int i = 0; i < size; i++)
      if (arrayPtr[i] != right.arrayPtr[i])
         return false;                 // arrays are not equal
   return true;                        // arrays are equal
}

// --------------------------------------------------------------------------
// operator!= 
// Determine if two arrays are not equal.
bool Array::operator!=(const Array& right) const {
   return !(*this == right);
}

// --------------------------------------------------------------------------
// [] mutator 
// Overloaded subscript operator, mutator
// terminates if subscript out of range error
int& Array::operator[](int subscript) {
   assert(0 <= subscript && subscript < size);
   return arrayPtr[subscript];               // reference return creates lvalue
}

// --------------------------------------------------------------------------
// [] accessor 
// Overloaded subscript operator, accessor
// terminates if subscript out of range error
const int& Array::operator[](int subscript) const {
   assert(0 <= subscript && subscript < size);
   return arrayPtr[subscript];               
}

// --------------------------------------------------------------------------
// getArrayCount 
// Return the number of Array objects instantiated
int Array::getArrayCount() { return arrayCount; }

// --------------------------------------------------------------------------
// operator>> 
// Overloaded input operator for class Array;
// inputs values for entire array.
istream& operator>>(istream &input, Array &a) {
   for (int i = 0; i < a.size; i++)
      input >> a.arrayPtr[i];
   return input;                        // e.g., enables cin >> x >> y;
}

// --------------------------------------------------------------------------
// operator<< 
// Overloaded output operator for class Array
ostream& operator<<(ostream &output, const Array &a) {
   int i;
   for (i = 0; i < a.size; i++) {
      output << a.arrayPtr[i] << ' ';
      if ((i + 1) % 10 == 0)           // display 10 per line
         output << endl;
   }

   if (i % 10 != 0)
      output << endl;
   return output;                      // e.g., enables cout << x << y;
}
#endif

