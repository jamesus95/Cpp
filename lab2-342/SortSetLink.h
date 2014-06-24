/*
 * File:   SortSetLink.h
 * Author: Test
 *
 * Created on January 21, 2014, 4:55 PM
 */

#ifndef SORTSETLINK_H
#define	SORTSETLINK_H

#include "Node.h"
#include<iostream>
using namespace std;

class SortSetList {
public:
    SortSetList();
    SortSetList(const SortSetList& orig);
    ~SortSetList();

    void insert(unsigned int intToInsert);
    void print();
    void remove(unsigned int remove);
    bool isEmpty();
    bool isInSet(unsigned int inSet);
    SortSetList& operator+(SortSetList& rightSide);
    SortSetList& operator-(SortSetList& rightSide);
    SortSetList& operator*(SortSetList& rightSide);
    SortSetList& operator+=(SortSetList& rightSide);
    SortSetList& operator-=(SortSetList& rightSide);
    SortSetList& operator*=(SortSetList& rightSide);
    SortSetList& operator==(SortSetList& rightSide);
    SortSetList& operator!=(SortSetList& rightSide);
    SortSetList& operator=(SortSetList& rightSide);

private:

    /**
     * @Description: A pointer called headerNodePointer that points to a node.
     * THis will point to the first node in the link.
     */
    Node* mainNodePointer;

};
#endif	/* SORTSETLINK_H */

