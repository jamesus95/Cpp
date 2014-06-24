/**
 * @file SortSetList.h
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#ifndef SORTSETLIST_H
#define	SORTSETLIST_H

#include "Node.h"
#include<iostream>
using namespace std;

class SortSetList {

        /** prints the sortSetList
        * @param output: ostream to output to
        * @param rightSide: sortSetList to output
        * @return ostream : the output that the operator output to
        */
        friend ostream& operator<<(ostream& output, const SortSetList& rightSide);

        /** inputs into the sortSetList
        * @param input: istream to input values into the sortSetList from
        * @param rightSide: sortSetList to input to
        * @return istream : the input that the operator input from
        */
        friend istream& operator>>(istream& input, SortSetList& rightSide);

public:

    /** default constructor
    * @post An empty sortSetList.
    */
    SortSetList();

    /** One item constructor
    * @param input1: The first item to insert into the SortSetList
    * @post initializes a SortSetList with the input value in it
    */
    SortSetList(int input1);

    /** Two item constructor
    * @param input1: The first item to insert into the SortSetList
    * @param input2: The second item to insert into the SortSetList
    * @post initializes a SortSetList with the input values in it
    */
    SortSetList(int input1, int input2);

    /** Three item constructor
    * @param input1: The first item to insert into the SortSetList
    * @param input2: The second item to insert into the SortSetList
    * @param input3: The third item to insert into the SortSetList
    * @post initializes a SortSetList with the input values in it
    */
    SortSetList(int input1, int input2, int input3);

    /** Four item constructor
    * @param input1: The first item to insert into the SortSetList
    * @param input2: The second item to insert into the SortSetList
    * @param input3: The third item to insert into the SortSetList
    * @param input4: The fourth item to insert into the SortSetList
    * @post initializes a SortSetList with the input values in it
    */
    SortSetList(int input1, int input2, int input3,
                 int input4);

    /** Five item constructor
    * @param input1: The first item to insert into the SortSetList
    * @param input2: The second item to insert into the SortSetList
    * @param input3: The third item to insert into the SortSetList
    * @param input4: The fourth item to insert into the SortSetList
    * @param input5: The fifth item to insert into the SortSetList
    * @post initializes a SortSetList with the input values in it
    */
    SortSetList(int input1, int input2, int input3,
                 int input4, int input5);

    /** copy constructor
    * @param input: A SortSetList to copy
    * @post initializes a new SortSetList equal to the input SortSetList
    */
    SortSetList(const SortSetList& orig);

    /** destructor releases memory
    */
    ~SortSetList();

    /** Inserts newInt into the sortSetArray
    * @param newInt: Integer to insert
    * @post adds newInt to the sortSetList if it is non-negative
    * and not already included
    * @return bool : True if the insertion was successful, otherwise false
    */
    bool insert(int intToInsert);

    /** Removes an entry from the array
    * @param intRemove: The integer to remove
    * @post removes intRemove if it is in the sortSetList
    * @return bool : True if the remove was successful, otherwise false
    */
    bool remove(int remove);

    /** Checks to see if the array is empty
    * @return bool : true if the array is empty, otherwise false
    */
    bool isEmpty();

    /** Checks to see if intToFind is in the array
    * @param intFind: The integer to find
    * @return bool : True if intFind is in the sortSetList, otherwise false
    */
    bool isInSet(int inSet);

    /** Computes the union between two sets
    * @param rightSide: The sortSetList to union with
    * @return sortSetList : A sortSetList that is the union of
    * the SortSetArrays
    */
    SortSetList& operator+(const SortSetList& rightSide) const;

    /** Computes the difference between two sets
    * @param rightSide: The set to find the difference with
    * @return sortSetList : A sortSetList that is the difference of
    * the first minus the second sortSetList
    */
    SortSetList& operator-(const SortSetList& rightSide) const;

    /** Computes the intersection between two sets
    * @param rightSide: The set to multiply
    * @return sortSetList : A sortSetArray that is the intersection
    * between two SortSetArrays
    */
    SortSetList& operator*(const SortSetList& rightSide) const;

    /** Computes the union between two sets and assigns it to the
    * left sortSetList
    * @param rightSide: The set to union with
    * @return sortSetList : the sortSetList on the left side
    */
    SortSetList& operator+=(SortSetList& rightSide);

    /** Computes the difference between two sets and assigns
    * it to the left sortSetList
    * @param rightSide: The set to find the difference with
    * @return sortSetList : The sortSetList on the left side
    */
    SortSetList& operator-=(SortSetList& rightSide);

    /** Computes the intersection between two sets and assigns
    * it to the left sortSetList
    * @param rightSide: The set to multiply.
    * @return sortSetList : The sortSetList on the left side.
    */
    SortSetList& operator*=(SortSetList& rightSide);

    /** Checks to make sure two sets are equal.
    * @param sortSetList : The set to compare too.
    * @return bool : True if the two sets are equal.  Otherwise false.
    */
    bool operator==(SortSetList& rightSide);

    /** Checks to make sure two sets are equal.
    * @param sortSetList: The set to compare too.
    * @return bool : False if the two sets are equal.  Otherwise True.
    */
    bool operator!=(SortSetList& rightSide);

    /** Assigns the rightSide to the left side
    * @param rightSide: The set to assign to the left side
    * @return sortSetList: the newly assigned left side
    */
    SortSetList& operator=(SortSetList& rightSide);

private:

    /** A pointer called headerNodePointer that points to a node.
     * This will point to the first node in the link.
     */
    Node* mainNodePointer;

    Node* copyNodes(Node& current);
    void initialize(int input[], int count);
    void destruction(Node* current);

};
#endif

