/**
@file data.h
@author James Murphree <murphs95@uw.edu>
@author Darren Hoehna <dhoehns@ue.esu>
@section Assignment Lab3
@section Due Feb. 9th 2013
*/

#ifndef DATA_H
#define DATA_H

#include <cstddef>
#include <iostream>
#define EMPTY_CHARACTER '\0'
#define EMPTY_SPACE -1

class Data {

    friend std::ostream& operator<<(std::ostream& output,
                                    const Data& rightSide);

public:
    Data(char character, int space);
    Data(const Data& orig);
    ~Data();

    char getChar() const;
    int getSpace()const;
    bool insert(char character, int space);
    bool remove();
    bool operator == (const Data& rightSide) const;
    bool operator != (const Data& rightSide) const;
    bool operator < (const Data& rightSide) const;


private:
    char character;
    int space;
    bool isEmpty() const;

};


#endif