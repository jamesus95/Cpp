/**
 * This file implements integration testing for the three classes, from
 * and outside perspective. The specific tests are specified in the
 * requirement document.
 *
 * \version         2.0
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#ifndef LAB_5_TEST_CPP
#define LAB_5_TEST_CPP

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int main() {

	char first[] = "james";
	char second[] = "vu";
	cout << strcmp(first, second) << endl;

    // ========================= version alpha test code =====================
    // 1. make a tree and add 1..n <---> A..z in random order
    int size = argv[1];
    TBST myTree(size);
    // 'A' = 65 <----> 1
    int count = 0;
    int n; 
    char c;
    string s;
    while(count < size) {
        // Generate a UNIQUE random number from 1 through n
        int n = rand() % size + 1;  // not unique
        char c = n + 64; // don't be a dick and give me a large size
        s = string(c);
        myTree.add(n, s);
    }

    // 2. make a copy, delete evens
    TBST copy(myTree);
    TBST::iterator iter; 
    Data* currData;
    for(iter = copy.begin(); iter != copy.end(); iter++) { // C++ idiom
        currData = iter.getCurrent();
        if( currData->getNum() % 2 == 0 ) {
            iter.remove(); // can't let the tree do it instead, 'cause there might be duplicates for that value
        }
    }

    // 3. in-order traversal of both trees
    //    pass each tree into a function containing the following code
    int rep = 1;
    Data* curr;
    for(TBST::iterator iter = tree.begin(); iter != tree.end(); iter++) {
        curr = iter.getCurrent();
        if(rep % 7 == 0)
            cout << endl;
        cout << curr->getNum() << "-" << curr->getString();
    }

    // =====================================================================

	return 0;
}

#endif

