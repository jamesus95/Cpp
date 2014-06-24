/**
 * \file mergesortlinkedlist.h
 * @details Contains mergesortlinkedlist function headers
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

#ifndef MERGE_SORT_LINKED_LIST_H
#define MERGE_SORT_LINKED_LIST_H

#include <iostream>
#include "linkedintlist.h"

using namespace std;

void linkedlistmergesort(LinkedIntList* orig);


class MergeSortLinkedList {

public:
	void sort(LinkedIntList* orig);

private:
	Node* sortHelper(Node* front, const int size);
	Node* merge(Node* leftFront, Node* rightFront, int leftSize, int rightSize);

};

#include "mergesortlinkedlist.cpp"

#endif