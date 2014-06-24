/**
 * \file linkedintlist.h
 * @details Contains linkedintlist function headers
 */

/**
 * @mainpage Introduction
 * 
 * Project: 	Sorting Algorithms\n
 * Objective: 	Implement and compare performance among different sorting
 * 				algorithms:\n
 * 				- recursivemergesort.cpp
 * 				- iterativemergesort.cpp
 * 				- quicksort.cpp
 * 				- heapsort.cpp
 * 				- mergesortlinkedlist.cpp
 * 				
 * \version		2.12
 * \author		James Murphree
 * \author		Vu Dinh
 * \date 		Feb 23 2014
 * \copyright	WTFPLv2.1
 * 
 */

#ifndef LINKED_INT_LIST_H
#define LINKED_INT_LIST_H

using namespace std;

// Node class used by LinkedIntList class
class Node {

public:
	Node();
	Node(Node* other);
	~Node();
	int getData();
	Node* getNext();
	void setData(int data);
	void setNext(Node* next);

private:
	int data;
	Node* next;
};


// LinkedIntList class
class LinkedIntList {

public:
	LinkedIntList();
	~LinkedIntList();
	void insert(int n);
	Node* getRoot();
	int getSize();
	bool isSorted();
	
	void setRoot(Node* root);
	void print();

private:
	Node* root;
	int size;
};

#include "linkedintlist.cpp"

#endif