/**
 * @file SortSetArray.cpp
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#ifndef SORTSETARRAY_CPP
#define SORTSETARRAY_CPP

#include "SortSetArray.h"

int SortSetArray::DEFAULTMAXITEMS = 1000000;

/* Constructors */

// default constructor
SortSetArray::SortSetArray():itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[maxItems];
    initialize(NULL, 0);
}

// 1 input constructor
SortSetArray::SortSetArray(int input1):itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[DEFAULTMAXITEMS];
    int input[] = {input1};
    initialize(input, 1);
}

// 2 input constructor
SortSetArray::SortSetArray(int input1, int input2)
        :itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[DEFAULTMAXITEMS];
    int input[] = {input1, input2};
    initialize(input, 2);
}

// 3 input constructor
SortSetArray::SortSetArray(int input1, int input2, int input3)
        :itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[DEFAULTMAXITEMS];
    int input[] = {input1, input2, input3};
    initialize(input, 3);
}

// 4 input constructor
SortSetArray::SortSetArray(int input1, int input2, int input3, int input4
        ):itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[DEFAULTMAXITEMS];
    int input[] = {input1, input2, input3, input4};
    initialize(input, 4);
}

// 5 input constructor
SortSetArray::SortSetArray(int input1, int input2, int input3, int input4,
        int input5):itemCount(0), maxItems(DEFAULTMAXITEMS) {
    sortedArrayPointer = new bool[DEFAULTMAXITEMS];
    int input[] = {input1, input2, input3, input4, input5};
    initialize(input, 5);
}

// copy constructor
SortSetArray::SortSetArray(const SortSetArray& input):itemCount(input.itemCount), maxItems(input.maxItems) {
    sortedArrayPointer = new bool[maxItems];
    for (int i = 0; i < maxItems; i++) {
        sortedArrayPointer[i] = input.sortedArrayPointer[i];
    }
}

// deconstructor
SortSetArray::~SortSetArray() {
    delete[] sortedArrayPointer;
    sortedArrayPointer = NULL;
}

// Methods

// insert
bool SortSetArray::insert(int newInt) {
    if (newInt < 0) {
        return false;
    }
    while (maxItems - 1 < newInt) {
        increaseSize();
    }
    if (!this->isInSet(newInt)) {
        sortedArrayPointer[newInt] = true;
        itemCount++;
        return true;
    }
    return false;
}

// remove
bool SortSetArray::remove(int intRemove) {
    if (intRemove < 0 || intRemove >= maxItems) {
        return false;
    }
    if (this->isInSet(intRemove)) {
        sortedArrayPointer[intRemove] = false;
        itemCount--;
        return true;
    }
    return false;
}

// isEmpty
bool SortSetArray::isEmpty() const {
    return itemCount == 0;
}

bool SortSetArray::isInSet(int intFind) const {
    if (intFind < 0 || intFind >= maxItems) {
        return false;
    }
    return sortedArrayPointer[intFind] == true;
}

// +
SortSetArray& SortSetArray::operator+(const SortSetArray& rightSide) const {
    SortSetArray *newSortedArrayPointer = new SortSetArray();
    for (int i = 0; i < maxItems; i++) {
        if (this->isInSet(i)) {
            newSortedArrayPointer->insert(i);
        }
    }
    for (int i = 0; i < rightSide.maxItems; i++) {
        if (rightSide.isInSet(i)) {
            newSortedArrayPointer->insert(i);
        }
    }
    return *newSortedArrayPointer;
}

// -
SortSetArray& SortSetArray::operator-(const SortSetArray& rightSide) const {
    SortSetArray* newSortedArrayPointer = new SortSetArray();
    for (int i = 0; i < maxItems; i++) {
        if (sortedArrayPointer[i] && (rightSide.maxItems > i &&
                    !rightSide.sortedArrayPointer[i])) {
            newSortedArrayPointer->insert(i);
        }
    }
    return *newSortedArrayPointer;
}

// *
SortSetArray& SortSetArray::operator*(const SortSetArray& rightSide) const {
    SortSetArray* newSortedArrayPointer = new SortSetArray();
    for (int i = 0; i < maxItems; i++) {
        if (this->isInSet(i) && rightSide.isInSet(i)) {
            newSortedArrayPointer->insert(i);
        }
    }
    return *newSortedArrayPointer;
}

// +=
SortSetArray& SortSetArray::operator+=(const SortSetArray& rightSide) {
    for (int i = 0; i < rightSide.maxItems; i++) {
        if (rightSide.isInSet(i)) {
            this->insert(i);
        }
    }
    return *this;
}

// -=
SortSetArray& SortSetArray::operator-=(const SortSetArray& rightSide) {
    for (int i = 0; i < maxItems; i++) {
        if (this->isInSet(i) && rightSide.isInSet(i)) {
            this->remove(i);
        }
    }
    return *this;
}

// *=
SortSetArray& SortSetArray::operator*=(const SortSetArray& rightSide) {
    for (int i = 0; i < maxItems; i++) {
        if (this->isInSet(i) && !rightSide.isInSet(i)) {
            this->remove(i);
        }
    }
    return *this;
}

// =
SortSetArray& SortSetArray::operator=(const SortSetArray& rightSide) {
    if (this != &rightSide) {
        delete[] sortedArrayPointer;
        maxItems = rightSide.maxItems;
        itemCount = rightSide.itemCount;
        sortedArrayPointer = new bool[maxItems];
        for (int i = 0; i < maxItems; i++) {
            sortedArrayPointer[i] = rightSide.sortedArrayPointer[i];
        }
    }
    return *this;
}

// ==
bool SortSetArray::operator==(const SortSetArray& rightSide) const {
    if (itemCount != rightSide.itemCount) {
        return false;
    }
    for (int i = 0; i < itemCount; i++) {
        if (sortedArrayPointer[i] != rightSide.sortedArrayPointer[i]) {
            return false;
        }
    }
    return true;
}

// !=
bool SortSetArray::operator!=(const SortSetArray& rightSide) const {
    return !(*this == rightSide);
}

// <<
std::ostream& operator<<(ostream& output, const SortSetArray& rightSide) {
    bool isFirst = true;
    for(int index = 0; index < rightSide.maxItems; index++) {
        if(isFirst && rightSide.sortedArrayPointer[index]) {
            output << index;
            isFirst = false;
        }
        else if (!isFirst && rightSide.sortedArrayPointer[index]) {
            output << ", " << index;
        }
    }
    return output;
}

// >>
std::istream& operator>>(istream& input, SortSetArray& rightSide) {
    int getInt = -1;
    input >> getInt;
    rightSide.insert(getInt);
    return input;
}

// Private Methods

// increaseSize
void SortSetArray::increaseSize() {
    bool* temp = sortedArrayPointer;
    sortedArrayPointer = new bool[maxItems * 2];
    for (int i = 0; i < maxItems; i++) {
        sortedArrayPointer[i] = temp[i];
    }
    for (int i = maxItems; i < maxItems * 2; i++) {
        sortedArrayPointer[i] = false;
    }
    delete[] temp;
    temp = NULL;
    maxItems *= 2;
}

// initialize
void SortSetArray::initialize(int input[], int count) {
    for (int i = 0; i < maxItems; i++) {
        sortedArrayPointer[i] = false;
    }
    for (int i = 0; i < count; i++) {
        this->insert(input[i]);
    }
}

#endif