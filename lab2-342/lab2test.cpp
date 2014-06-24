/**
 * @file lab2test.cpp
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#include "SortSetArray.h"
#include "SortSetList.h"
#include <fstream>
#include <iomanip>
#include <string.h>

const char INPUTFILE[] = "inputText.txt" ;

int main() {

    ifstream input(INPUTFILE);
    //unit test add
    SortSetArray* test = new SortSetArray();
    test->insert(5);
    test->insert(10);
    test->insert(1);
    test->insert(5);
    test->insert(-10);
    cout << "Add Test" << endl;
    cout << "Added 5, 10, 1, 5, -10 to test" << endl;
    cout << "Test: " << *test << endl;

    input >> *test; //5, 2, 7
    cout << "inputted 5 from file" << endl;
    cout << *test << endl;
    input >> *test;
    cout << "inputted 2 from file" << endl;
    cout << *test << endl;
    input >> *test;
    cout << "inputtes 7 from file" << endl;
    cout << *test << endl;




     //unit test remove
    cout << "Remove Test" << endl;
    cout << "Remove 1 from test" << endl;
    test->remove(1);
    cout << "Test: " << *test << endl;
    cout << "Removing 10 from test" << endl;
    test->remove(10);
    cout << "Test: " << *test << endl << endl;

     //unit test isEmpty
    cout << "IsEmpty test" << endl;
    cout << test->isEmpty() << " : should be false (0)" << endl;
    cout << "Remove 5 and 4 from test (last ints in test)" << endl;
    test->remove(5);
    test->remove(2);
    test->remove(7);
    cout << test->isEmpty() << " : should be true (1)" << endl;
    cout << "(Printing) Test: " << *test << endl << endl;

    // unit test isInSet
    cout << "inInSet test" << endl;
    cout << "Add 100 to test" << endl;
    test->insert(100);
    cout << "is 100 in test?" << endl;
    cout << test->isInSet(100) << " : should be true (1)" << endl;
    cout << "is 10 in test?" << endl;
    cout << test->isInSet(10) << " : should be false (0)" << endl;
    cout << endl;

     //unit test increaseSize/+/=
    cout << "+/=/ test" << endl;
    SortSetArray* test2 = new SortSetArray();
    test2->insert(5);
    test2->insert(1);
    test->insert(11);
    cout << "Test: " << *test << endl;
    cout << "Test2: " << *test2 << endl;
    cout << "add test and test2 to test3" << endl;
    SortSetArray* test3 = NULL;
    test3 = &(*test + *test2);
    cout << "Test3: " << *test3 << endl << endl;

    //unit test -
    cout << "- test" << endl;
    test->insert(10);
    test->insert(15);
    test2->insert(10);
    test2->insert(15);
    cout << "Test: " << *test << endl;
    cout << "Test 2: " << *test2;
    cout << "Test3 = test - test2" << endl;
    delete test3;
    test3 = &(*test - *test2);
    cout << "Test 3: " << *test3 << endl;
    cout << "Test3 = test2 - test" << endl;
    delete test3;
    test3 = &(*test2 - *test);
    cout << "Test3: " << *test3 << endl << endl;

    // unit test *
    cout << endl << "* test" << endl;
    cout << "test3 = test * test2" << endl;
    delete test3;
    test3 = &(*test * *test2);
    cout << "Test3: " << *test3 << endl << endl;

    //unit test +=
    cout << "+= test" << endl;
    cout << "Test 2: " << *test2 << endl;
    cout << "Test 3: " << *test3 << endl;
    cout << "test3 += test2" << endl;
    *test3 = *test2;
    cout << "Test3: " << *test3 << endl << endl;

     //unit test -=
    cout << "-= test" << endl;
    cout << "Test 2: " << *test2 << endl;
    cout << "Test 3: " << *test3 << endl;
    cout << "test3 -= test2" << endl;
    *test3 -= *test2;
    cout << "Test3: " << *test3 << endl << endl;

     //unit test *=
    *test3 += *test;
    *test2 += *test;
    test3->remove(5);
    test3->remove(6);
    test2->remove(100);
    cout << "*= test" << endl;
    cout << "Test 2: " << *test2 << endl;
    cout << "Test 3: " << *test3 << endl;
    cout << "test3 *= test2" << endl;
    *test3 *= *test2;
    cout << "Test3: " << *test3 << endl << endl;

     //unit test ==/!=
    cout << "test ==/!=" << endl;
    cout << "Test: " << *test << endl;
    cout << "Test3: " << *test3 << endl;
    cout << "testBool = test3 == test" << endl;
    bool testBool = *test3 == *test;
    cout << testBool << " should be 0 (false)" << endl;
    testBool = *test3 != *test;
    cout << "testBool = test3 != test" << endl;
    cout << testBool << " should be 1 (true)" << endl << endl;

     //unit test constructors 1-5 input
    SortSetArray* one = new SortSetArray(1);
    SortSetArray* two = new SortSetArray(1,2);
    SortSetArray* three = new SortSetArray(1,2,3);
    SortSetArray* four = new SortSetArray(1,3,2,4);
    SortSetArray* five = new SortSetArray(5,4,3,2,1);

     //Constructor Test
    cout << "Constructor Tests" << endl;
    cout << "constructed (1)" << endl;
    cout << *one << endl;
    cout << "constructed (1,2)" << endl;
    cout << *two << endl;
    cout << "constructed (1,2,3)" << endl;
    cout << *three << endl;
    cout << "constructed (1,3,2,4)" << endl;
    cout << *four << endl;
    cout << "constructed (5,4,3,2,1)" << endl;
    cout << *five << endl;

    SortSetArray* copyOf = new SortSetArray(*five);
    cout << "copy of five inputs :" << *copyOf << endl << endl;

    delete test;
    delete test2;
    delete test3;
    delete one;
    delete two;
    delete three;
    delete four;
    delete five;
    delete copyOf;
    test = NULL;
    test2 = NULL;
    test3 = NULL;
    one = NULL;
    two = NULL;
    three = NULL;
    four = NULL;
    five = NULL;
    copyOf = NULL;


     //Testing SortSetList

     ifstream input2(INPUTFILE);
    SortSetList* listTest1 = new SortSetList();

     //unit testing insert
    cout << "Testing insert" << endl;
    listTest1->insert(1);
    listTest1->insert(10);
    listTest1->insert(-10);
    listTest1->insert(5);
    listTest1->insert(5);
    cout << "inserted 1, 10, -10, 5, 5" << endl;
    cout << "listTest1: " << *listTest1 << endl;
    cout << "input 2, 5, 7 from file" << endl;
    input2 >> *listTest1 >> *listTest1 >> *listTest1;
    cout << "listTest1: " << *listTest1 << endl << endl;



     //unit test remove
    cout << "Remove Test" << endl;
    cout << "Remove 1 from listTest1" << endl;
    listTest1->remove(1);
    cout << "listTest1: " << *listTest1 << endl;
    cout << "Removing 10 from listTest1" << endl;
    listTest1->remove(10);
    cout << "listTest1: " << *listTest1 << endl << endl;



     //unit test isEmpty
    cout << "IsEmpty test" << endl;
    cout << listTest1->isEmpty() << " : should be false (0)" << endl;
    cout << "Remove 5 and 4 from listTest1 (last ints in listTest1)" << endl;
    listTest1->remove(5);
    listTest1->remove(2);
    listTest1->remove(7);
    cout << listTest1->isEmpty() << " : should be true (1)" << endl;
    cout << "(Printing) listTest1: " << *listTest1 << endl << endl;

     //unit test isInSet
    cout << "inInSet test" << endl;
    cout << "Add 100 to listTest1" << endl;
    listTest1->insert(100);
    cout << "is 100 in listTest1?" << endl;
    cout << listTest1->isInSet(100) << " : should be true (1)" << endl;
    cout << "is 10 in listTest1?" << endl;
    cout << listTest1->isInSet(10) << " : should be false (0)" << endl;
    cout << endl;

     //unit test increaseSize/+/=
    cout << "+/=/ test" << endl;
    SortSetList* listTest2 = new SortSetList();
    listTest2->insert(5);
    listTest2->insert(1);
    listTest2->insert(11);
    cout << "listTest1: " << *listTest1 << endl;
    cout << "listTest2: " << *listTest2 << endl;
    cout << "add listTest1 and listTest2 to listTest3" << endl;
    SortSetList* listTest3 = NULL;
    listTest3 = &(*listTest1 + *listTest2);
    cout << "listTest3: " << *listTest3 << endl << endl;

    //unit test -
    cout << "- test" << endl;
    listTest1->insert(10);
    listTest1->insert(15);
    listTest2->insert(10);
    listTest2->insert(15);
    cout << "listTest1: " << *listTest1 << endl;
    cout << "listTest2: " << *listTest2;
    cout << "listTest3 = listTest1 - listTest2" << endl;
    delete listTest3;
    listTest3 = &(*listTest1 - *listTest2);
    cout << "listTest3: " << *listTest3 << endl;
    cout << "listTest3 = listTest2 - listTest1" << endl;
    delete listTest3;
    cout << "before -2" << endl;
    listTest3 = &(*listTest2 - *listTest1);
    cout << "listTest3: " << *listTest3 << endl << endl;

     //unit test *
    cout << endl << "* test" << endl;
    cout << "listTest3 = listTest1 * listTest2" << endl;
    delete listTest3;
    listTest3 = &(*listTest1 * *listTest2);
    cout << "listTest3: " << *listTest3 << endl << endl;

    //unit test +=
    cout << "+= test" << endl;
    cout << "listTest2: " << *listTest2 << endl;
    cout << "listTest3: " << *listTest3 << endl;
    cout << "listTest3 += listTest2" << endl;
    *listTest3 = *listTest2;
    cout << "listTest3: " << *listTest3 << endl << endl;

     //unit test -=
    cout << "-= test" << endl;
    cout << "listTest2: " << *listTest2 << endl;
    cout << "listTest3: " << *listTest3 << endl;
    cout << "test3 -= listTest2" << endl;
    *listTest3 -= *listTest2;
    cout << "Test3: " << *listTest3 << endl << endl;

     //unit test *=
    *listTest3 += *listTest1;
    *listTest2 += *listTest1;
    listTest3->remove(5);
    listTest3->remove(6);
    listTest2->remove(100);
    cout << "*= test" << endl;
    cout << "listTest2: " << *listTest2 << endl;
    cout << "listTest3: " << *listTest3 << endl;
    cout << "listTest3 *= listTest2" << endl;
    *listTest3 *= *listTest2;
    cout << "listTest3: " << *listTest3 << endl << endl;

     //unit test ==/!=
    cout << "test ==/!=" << endl;
    cout << "listTest1: " << *listTest1 << endl;
    cout << "listTest3: " << *listTest3 << endl;
    cout << "testBool = listTest3 == listTest1" << endl;
    testBool = *listTest3 == *listTest1;
    cout << testBool << " should be 0 (false)" << endl;
    testBool = *listTest3 != *listTest1;
    cout << "testBool = listTest3 != listTest1" << endl;
    cout << testBool << " should be 1 (true)" << endl << endl;

    SortSetList* oneList = new SortSetList(1);
    SortSetList* twoList = new SortSetList(1,2);
    SortSetList* threeList = new SortSetList(1,2,3);
    SortSetList* fourList = new SortSetList(1,3,2,4);
    SortSetList* fiveList = new SortSetList(5,4,3,2,1);

     //Constructor Test
    cout << "Constructor Tests" << endl;
    cout << "constructed (1)" << endl;
    cout << *oneList << endl;
    cout << "constructed (1,2)" << endl;
    cout << *twoList << endl;
    cout << "constructed (1,2,3)" << endl;
    cout << *threeList << endl;
    cout << "constructed (1,3,2,4)" << endl;
    cout << *fourList << endl;
    cout << "constructed (5,4,3,2,1)" << endl;
    cout << *fiveList << endl;

    SortSetList* copyOfList = new SortSetList(*fiveList);
    cout << "copy of five inputs :" << *copyOfList << endl;

    delete listTest1;
    delete listTest2;
    delete listTest3;
    delete oneList;
    delete twoList;
    delete threeList;
    delete fourList;
    delete fiveList;
    delete copyOfList;
    listTest1 = NULL;
    listTest2 = NULL;
    listTest3 = NULL;
    oneList = NULL;
    twoList = NULL;
    threeList = NULL;
    fourList = NULL;
    fiveList = NULL;
    copyOfList = NULL;


}
