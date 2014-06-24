/**
 * The following is the anticipated test code.
 * Specific implementation details can be discussed.
 */

/**
 * @file lab5test.cpp
 * Purpose: implement suggested tests for TBST as well as personal tests.
 * Includes:
 * --- creation of a tree
 * --- copying a tree
 * --- removing from a tree
 * --- iterative inorder traversal of a tree with functional programming
 *
 * --- recursive traversals of the tree
 * --- iterator traversals of the tree
 * --- contains(), isEmpty(), and size()
 * --- getMax/MinByFrequency()
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef LAB_5_TEST_CPP
#define LAB_5_TEST_CPP

#define PREORDER 1
#define INORDER 0
#define POSTORDER -1
#define MAX_CHARACTERS 52
#define DEFAULT_CHARACTER_COUNT 13

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>  // for gettimeofday() and timeval
#include <ctime>       // for  clock()and clock_t and CLOCKS_PER_SEC
#include <assert.h>
#include <string.h>
#include "tbst.h"

const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

using namespace std;

void populateTree(TBST& tree, int size) {
    int count = 0;
    srand(time(NULL));

    bool* usedNums = new bool[size];
    for (int i = 0; i < size; i++)
        usedNums[i] = false;
    
    while(count < size) {
        // Generate a UNIQUE random number from 1 through n    
        int r = rand();
        int n = r % size;  // not unique
        if(!usedNums[n]) {
            // got unique num
            string s(1, alphabet[n]);
            tree.insert(s, n+1);
            usedNums[n] = true;
            count++;
        }
        else {
            // cout << "DEBUG: NOT UNIQUE" << endl;
        }
    }
    delete[] usedNums; usedNums = NULL;
}

void displayNode(Node* nodeToPrint, ostream& output) {
    output << *(nodeToPrint->getData()) << " ";
}

void testIterativeInorder(TBST* tree, ostream& output) {
    tree->iterativeInorder(displayNode, output);
    cout << endl;
}

void testTraverse(TBST* tree, ostream& output = cout) {
    cout << "\nTesting preorder \n\n--------------------------" << endl;
    tree->traverse(displayNode, cout, PREORDER);
    cout << "\nTesting inorder \n\n--------------------------" << endl;
    tree->traverse(displayNode, cout, INORDER);
    cout << "\nTesting postorder \n\n--------------------------" << endl;
    tree->traverse(displayNode, cout, POSTORDER);
}

void testRemoveInterval(TBST* tree, int startIndex, int interval, int size) {
    for(int i = startIndex; i < size; i += interval) {
        string s(1, alphabet[i]);
        tree->remove(s);
    }
}

void testMaxMin(TBST* tree) {
    cout << "max item in myTree = " << *(tree->getMaxByFrequency()) << endl;
    cout << "min item in myTree = " << *(tree->getMinByFrequency()) << endl;
}

int main(int argc, char* argv[]) {

    // 1. make a tree and add 1..n <---> A..z in random order
    int size = (argc > 1) ? (atoi(argv[1])) : (DEFAULT_CHARACTER_COUNT);
    size = (size <= MAX_CHARACTERS) ? (size) : (MAX_CHARACTERS);

    TBST* myTree = new TBST();
    populateTree(*myTree, size);

    // 2. make a copy
    TBST* copy = new TBST(*myTree);

    cout << "before remove, size = " << copy->size() << endl;
    // delete evens
    testRemoveInterval(copy, 1, 2, size);     // remove evens

    cout << "Removed even items from copy, size = " << copy->size() << endl;
    cout << "Testing iterative traversal + print: copy = ";
    testIterativeInorder(copy, cout);
    cout << endl;

    cout << "Testing isEmpty: (expect false) " << copy->isEmpty() << endl;
    cout << "copy contains \"A\": t/f? " << copy->contains("A") << endl;
    cout << endl;

    // delete odds
    testRemoveInterval(copy, 0, 2, size);     // remove odds
    cout << "Removed odd items from copy, size = " << copy->size() << endl;
    cout << "Re-testing iterative traversal + print: copy = (empty)" << endl;
    cout << "Re-testing isEmpty: (expect true) " << copy->isEmpty() << endl;
    cout << "copy contains \"A\": t/f? " << copy->contains("A") << endl;
    cout << endl;

    cout << "test recursive traversal, 3 orders, myTree = " << endl;
    testTraverse(myTree, cout);
    cout << "\n" << endl;
    testMaxMin(myTree);

    delete myTree;
    delete copy;
	return 0;
}

#endif

