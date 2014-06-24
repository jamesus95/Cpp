/**
@file compareList.h
@author James Murphree <murphs95@uw.edu>
@author Darren Hoehna <dhoehna@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
*/

#ifndef COMPARE_LIST_H
#define COMPARE_LIST_H

#include "node.h"
#include <iostream>
#include <fstream>

// use an array of primefibs as a #constant

class CompareList {

    friend std::ostream& operator << (std::ostream& output,
                                      const CompareList& rightSide);

public:
    CompareList();
    CompareList(const CompareList& other);
    ~CompareList();

    bool insert(char character, int space);
    bool remove(char character, int space);
    void compareTo(const CompareList& rightSide, std::ostream* output) const;
    void print(int n, std::ostream* output);
    bool operator == (const CompareList& rightSide) const;
    bool operator != (const CompareList& rightSide) const;
    CompareList& operator = (const CompareList& rightSide);
private:
    Node* root;
    void removeAll();
    Node* copyNodes(const Node& current);

};


#endif