/**
 * @file SortSetArray.h
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#ifndef SORTSETARRAY_H
#define SORTSETARRAY_H

#include <iostream>
using namespace std;

class SortSetArray {

        /** prints the SortSetArray
        * @param output: ostream to output to
        * @param rightSide: SortSetArray to output
        * @return ostream : the output that the operator output to
        */
        friend ostream& operator<<(ostream& output, const SortSetArray& rightSide);

        /** inputs into the SortSetArray
        * @param input: istream to input values into the SortSetArray from
        * @param rightSide: SortSetArray to input to
        * @return istream : the input that the operator input from
        */
        friend istream& operator>>(istream& input, SortSetArray& rightSide);

public:

    /** default constructor
    * @post An empty sortSetArray.
    */
    SortSetArray();

    /** One item constructor
    * @param input1: A number to insert into the sortedSetArray
    * @post initializes a sortSetArray that has the input item in it.
    */
    SortSetArray(int input1);

    /** Two item constructor
    * @param input1: The first item to insert into the sortSetArray.
    * @param input2: The second item to insert into the sortSetArray.
    * @post initializes a sortSetArray that has the input items in it.
    */
    SortSetArray(int input1, int input2);

    /**Three item constructor
    * @param input1: The first item to insert into the sortSetArray.
    * @param input2: The second item to insert into the sortSetArray.
    * @param input3: The third item to insert into the sortSetArray.
    * @post initializes a sortSetArray that has the input items in it.
    */
    SortSetArray(int input1, int input2, int input3);

    /** Four item constructor
    * @param input1: The first item to insert into the sortSetArray.
    * @param input2: The second item to insert into the sortSetArray.
    * @param input3: The third item to insert into the sortSetArray.
    * @param input4: The fourth item to insert into the sortSetArray.
    * @post initializes a sortSetArray that has the input items in it.
    */
    SortSetArray(int input1, int input2, int input3,
                 int input4);

    /** Five item constructor
    * @param input1: The first item to insert into the sortSetArray.
    * @param input2: The second item to insert into the sortSetArray.
    * @param input3: The third item to insert into the sortSetArray.
    * @param input4: The fourth item to insert into the sortSetArray.
    * @param input5: The fifth item to insert into the sortSetArray.
    * @post initializes a sortSetArray that has the input items in it.
    */
    SortSetArray(int input1, int input2, int input3,
                 int input4, int input5);

    /** copy constructor
    * @param input: A SortSetArray to copy
    * @post initializes a new SortSetArray equal to the input SortSetArray
    */
    SortSetArray(const SortSetArray& input);

    /** destructor releases memory
    */
    ~SortSetArray();

    /** Inserts newInt into the sortSetArray
    * @param newInt: Integer to insert
    * @post adds newInt to the SortSetArray if it is non-negative
    * and not already included
    * @return bool : True if the insertion was successful, otherwise false
    */
    bool insert(int newInt);

    /** Removes an entry from the array
    * @param intRemove: The integer to remove
    * @post removes intRemove if it is in the SortSetArray
    * @return bool : True if the remove was successful, otherwise false
    */
    bool remove(int intRemove);

    /** Checks to see if the array is empty
    * @return bool : true if the array is empty, otherwise false
    */
    bool isEmpty() const;

    /** Checks to see if intToFind is in the array
    * @param intFind: The integer to find
    * @return bool : True if intFind is in the SortSetArray, otherwise false
    */
    bool isInSet(int intFind) const;

    /** Computes the union between two sets
    * @param rightSide: The SortSetArray to union with
    * @return SortSetArray : A SortSetArray that is the union of
    * the SortSetArrays
    */
    SortSetArray& operator+(const SortSetArray& rightSide) const;

    /** Computes the difference between two sets
    * @param rightSide: The set to find the difference with
    * @return SortSetArray : A SortSetArray that is the difference of
    * the first minus the second SortSetArray
    */
    SortSetArray& operator-(const SortSetArray& rightSide) const;

    /** Computes the intersection between two sets
    * @param rightSide: The set to multiply
    * @return SortSetArray : A sortSetArray that is the intersection
    * between two SortSetArrays
    */
    SortSetArray& operator*(const SortSetArray& rightSide) const;

    /** Computes the union between two sets and assigns it to the
    * left SortSetArray
    * @param rightSide: The set to union with
    * @return SortSetArray : the SortSetArray on the left side
    */
    SortSetArray& operator+=(const SortSetArray& rightSide);

    /** Computes the difference between two sets and assigns
    * it to the left SortSetArray
    * @param rightSide: The set to find the difference with
    * @return SortSetArray : The SortSetArray on the left side
    */
    SortSetArray& operator-=(const SortSetArray& rightSide);

    /** Computes the intersection between two sets and assigns
    * it to the left SortSetArray
    * @param rightSide: The set to multiply.
    * @return SortSetArray : The SortSetArray on the left side.
    */
    SortSetArray& operator*=(const SortSetArray& rightSide);

    /** Assigns the rightSide to the left side
    * @param rightSide: The set to assign to the left side
    * @return SortSetArray: the newly assigned left side
    */
    SortSetArray& operator=(const SortSetArray& rightSide);

    /** Checks to make sure two sets are equal.
    * @param SortSetArray : The set to compare too.
    * @return bool : True if the two sets are equal.  Otherwise false.
    */
    bool operator==(const SortSetArray& rightSide) const;

    /** Checks to make sure two sets are equal.
    * @param SortSetArray: The set to compare too.
    * @return bool : False if the two sets are equal.  Otherwise True.
    */
    bool operator!=(const SortSetArray& rightSide) const;

private:
    int itemCount, maxItems;
    bool* sortedArrayPointer;
    static int DEFAULTMAXITEMS;

    void shiftUp(int insertIndex);
    void shiftDown(int removeIndex);
    void increaseSize();
    void initialize(int input[], int count);

};

#endif