/**
 * \file iterativemergesort.h
 * @details Contains iterativemergesort function headers
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

#ifndef ITERATIVE_MERGE_SORT_H
#define ITERATIVE_MERGE_SORT_H

#include <iostream>

using namespace std;

void iterativemergesort(int* array, int size, 
						bool opt = false, int bubbleSize = 6);


class IterativeMergeSort {

public:
	void sort(int* orig, const int size, bool opt, int bubbleSize);

private:
    void merge(int* from, int* to, int size, int subSize);
    void bubbleSort(int* orig, int size, int bubbleSize);
    void swap(int* orig, int swapIndex1, int swapIndex2);

};

#include "iterativemergesort.cpp"

#endif