/**
@file lab3testmain.cpp
@author James Murphree <murphs95@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
lab3testmain tests the CompareList Data and Node classes
*/

#include "compareList.h"
void testInsert(CompareList* testList);
void insertDuplicates(CompareList* testList);
void insertNegative(CompareList* testList);
void insertAll(CompareList* testList);
void testRemove(CompareList* testList);
void testRemoveBadIndexes(CompareList* testList);
void testRemoveEmpty(CompareList* testList);
void testEquals(CompareList* testList);
void testSetEqual(CompareList* testList);
void testCompareTo();
void testData();
void testDataRemoveInsert(Data& data);
void testDataOpperators(Data& data, Data& data2);
void testNode();
void testNodeGetters(Node& testNode);
void testNodeSetNext(Node& testNode, Node& testNode2);
void testNodeEquals(Node& testNode);

int main() {
    std::cout << "Testing CompareList functions" << std::endl;
    CompareList* testList1 = new CompareList();
    std::cout << "Testing insert" << std::endl;
    testInsert(testList1);
    std::cout << "Testing remove" << std::endl;
    testRemove(testList1);
    std::cout << "Testing ==/!=" << std::endl;
    testEquals(testList1);
    std::cout << "Testing =" << std::endl;
    testSetEqual(testList1);
    testCompareTo();
    delete testList1;
    testList1 = NULL;

    std::cout << std::endl << "Testing Data functions" << std::endl;
    testData();
    std::cout << std::endl << "Testing Node functions" << std::endl;
    testNode();


    return 0;
}

void testInsert(CompareList* testList) {
    testList->insert('D', 9);
    std::cout << "Inserted D and 9" << std::endl;
    testList->insert('C', 99);
    std::cout << "Inserted C and 99" << std::endl;
    testList->insert('H', 999);
    std::cout << "Inserted H and 999" << std::endl;
    testList->insert('J', 9999);
    std::cout << "Inserted J and 9999" << std::endl;
    testList->insert('C', 99999);
    std::cout << "Inserted C and 99999" << std::endl;
    testList->insert('M', 999999);
    std::cout << "Inserted > and 999999" << std::endl;
    std::cout << *testList << std::endl << std::endl;
    insertDuplicates(testList);
    std::cout << *testList << std::endl << std::endl;
    insertNegative(testList);
    std::cout << *testList << std::endl << std::endl;
    insertAll(testList);
    std::cout << *testList << std::endl << std::endl;
}

void insertDuplicates(CompareList* testList) {
    testList->insert('A', 9);
    std::cout << "Inserted A and 9.  Expected to not be inserted"
    << std::endl;
    testList->insert('A', 999);
    std::cout << "Inserted A and 999. Expected to not be inserted"
    << std::endl;
}

void insertNegative(CompareList* testList) {
    testList->insert('A', -1);
    std::cout << "Insert A and -1.  Expected to not be inserted"
    << std::endl;
}

void insertAll(CompareList* testList) {
    std::cout << "Inserting characters 1-255 at indexes 1-255."
    << "Expected to exclude 9 and 99" << std::endl;
    for (int i = 1; i <= 255; i++) {
        testList->insert(i, i);
    }
}

void testRemove(CompareList* testList) {
    std::cout << "Remove characters 1-255 at indexes 1-255" << std::endl;
    std::cout << "Tests remove and removing an index with incorrect character"
    << std::endl;
    for (int i = 1; i <= 255; i++) {
        testList->remove(i, i);
    }
    std::cout << *testList << std::endl;
    testRemoveBadIndexes(testList);
    testRemoveEmpty(testList);
}

void testRemoveBadIndexes(CompareList* testList) {
    std::cout << "Removes at indexes -1, 9999999, and 999 w/wrong char."
    << "Expect to do nothing" << std::endl;
    testList->remove('A', -1);
    testList->remove('A', 9999999);
    testList->remove('C',999);
    std::cout << *testList << std::endl << std::endl;
}

void testRemoveEmpty(CompareList* testList) {
    std::cout << "Removes all nodes in odd order" <<
    "and tests removing when empty." << std::endl;
    testList->remove('D', 9);
    testList->remove('J', 9999);
    testList->remove('C', 99999);
    testList->remove('C', 99);
    testList->remove('H', 999);
    testList->remove('M', 999999);
    testList->remove('A', 44);
    std::cout << "Test: " << *testList << std::endl << std::endl;
}

void testEquals(CompareList* testList1) {
    CompareList* testList2 = new CompareList();
    CompareList* testList3 = new CompareList();
    testList2->insert('A', 1);
    testList3->insert('A', 1);
    testList2->insert('B', 2);
    testList3->insert('B', 2);
    std::cout << "Inserted A 1 and B 2 into testList 2 and 3" << std::endl;
    std::cout << "also tests node and data == and !=" << std::endl;
    std::cout << "testList 2 == 3 " << (*testList2 == *testList3)
    << " : should be 1" << std::endl;
    std::cout << "testList 2 != 3 " << (*testList2 != *testList3)
    << " : should be 0" << std::endl;
    CompareList* testList4 = new CompareList(*testList1);
    std::cout << "Test copy constructor for compareList and Data" << std::endl;
    std::cout << "testList1 == copy of testList1 (testList4)" << std::endl;
    std::cout << (*testList4 == *testList1) << " : should be 1" << std::endl;
    std::cout << "Test when not equal" << std::endl;
    testList2->remove('B', 2);
    std::cout << "remove B 2 from 3" << std::endl;
    std::cout << "testList 2 == 3 " << (*testList2 == *testList3)
    << " : should be 0" << std::endl;
    std::cout << "testList 2 != 3 " << (*testList2 != *testList3)
    << " : should be 1" << std::endl;
    delete testList2;
    delete testList3;
    delete testList4;
    testList2 = NULL;
    testList3 = NULL;
    testList4 = NULL;
    std::cout << std::endl;
}

void testSetEqual(CompareList* testList) {
    CompareList testList2 = *testList;
    std::cout << "testList2 = testList  check to see if equal" << std::endl;
    std::cout << (testList2 == *testList) << " : should be 1" << std::endl;
}

void testCompareTo() {
    CompareList* l1 = new CompareList();
    CompareList* l2 = new CompareList();
    l1->insert('a', 1);
    l2->insert('a', 1);
    l1->insert('b', 2);
    l2->insert('b', 2);
    std::cout << std::endl;
    l1->print(2, &std::cout);
    l2->print(2, &std::cout);
    l1->compareTo(*l2, &std::cout);
    delete l1;
    delete l2;
    l1 = NULL;
    l2 = NULL;
}

void testData() {
    Data* testData = new Data('A', 10);
    std::cout << "testing Data basic constructor"
    << "with A 10 and Data << operator"
    << std::endl;
    std::cout << "should be (A, 10) : " << *testData << std::endl;
    testDataRemoveInsert(*testData);
    Data* testData2 = new Data(*testData);
    std::cout << "testing Data copy constructor with first Data" << std::endl;
    std::cout << "should be (B, 20) : " << *testData2 << std::endl;
    testData->remove();
    testData->insert('A', 10);
    testDataOpperators(*testData, *testData2);
    delete testData;
    delete testData2;
    testData = NULL;
    testData2 = NULL;
}

void testDataRemoveInsert(Data& data) {
    data.remove();
    std::cout << "Test Data Remove : " << data << std::endl;
    data.insert('B', 20);
    std::cout << "TestData Insert B 20 : " << data << std::endl;
}

void testDataOpperators(Data& data, Data& data2) {
    std::cout << "Test equals and not equals" << std::endl;
    std::cout << "Data=" << data << " Data2=" << data2 << std::endl;
    std::cout << "Data == Data2 is " << (data == data2) << std::endl;
    std::cout << "Data != Data2 is " << (data != data2) << std::endl;
    std::cout << "false = " << false << "  true = " << true << std::endl;
    std::cout << "Test less than" << std::endl;
    std::cout << "Data > Data2  : " << (data < data2) << std::endl;
}

void testNode() {
    std::cout << "Testing Node Constructors" << std::endl;
    Node* testNode = new Node(new Data('A', 1));
    std::cout << "Node data: " << *(testNode->getData()) << " Node next: "
    << testNode->getNext() << std::endl;
    Node* testNode2 = new Node(new Data('B', 2), testNode);
    std::cout << "Node data: " << *(testNode2->getData()) << " Node next: "
    << testNode2->getNext() << std::endl;
    std::cout << "Testing Copy Constructor" << std::endl;
    Node* testNode3 = new Node(*testNode2);
    std::cout << "Node data: " << *(testNode3->getData()) << " Node next: "
    << testNode3->getNext() << std::endl;
    testNodeGetters(*testNode2);
    testNodeSetNext(*testNode, *testNode3);
    testNodeEquals(*testNode);
    delete testNode;
    delete testNode2;
    delete testNode3;
    testNode = NULL;
    testNode2 = NULL;
    testNode3 = NULL;
}

void testNodeGetters(Node& testNode) {
    std::cout << "Test getData : " << *(testNode.getData()) << std::endl;
    std::cout << "Test getNext : " << testNode.getNext() << std::endl;
}

void testNodeSetNext(Node& testNode, Node& testNode2) {
    testNode.setNext(&testNode2);
    std::cout << "Testing setNext" << std::endl;
    std::cout << testNode.getNext() << " should equal " << &testNode2
    << std::endl;
}

void testNodeEquals(Node& testNode) {
    Node* test2 = new Node(testNode);
    std::cout << "== should be 1 : " << (testNode == *test2) << std::endl;
    std::cout << "!= should be 0 : " << (testNode != *test2) << std::endl;
    delete test2;
    test2 = NULL;
}
