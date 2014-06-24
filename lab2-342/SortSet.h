#ifndef SORTSET_H
#define SORTSET_H

#include <iostream>
using namespace std;

class SortSet {

        friend ostream& operator<<(ostream& output, const SortSet& rightSide);
        friend istream& operator>>(istream& input, SortSet& rightSide);

public:
    SortSet();
    SortSet(int inputs[], int count);
    SortSet(const SortSet& input);
    ~SortSet();

    bool insert(int newInt);
    bool remove(int intRemove);
    bool isEmpty();
    bool isInSet(int intFind);

    SortSet operator+(SortSet rightSide);
    SortSet operator-(SortSet rightSide);
    SortSet operator*(SortSet rightSide);
    SortSet operator+=(SortSet rightSide);
    SortSet operator-=(SortSet rightSide);
    SortSet operator*=(SortSet rightSide);
    SortSet operator=(SortSet rightSide);
    bool operator==(SortSet rightSide);
    bool operator!=(SortSet rightSide);

private:
    int itemCount, maxItems;
    static int DEFAULTMAXITEMS;
};

//#include "SortSetArray.cpp"
//#include "SortSetList.cpp"
#endif