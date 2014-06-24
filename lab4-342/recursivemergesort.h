/**
 * \file recursivemergesort.h
 * @details Contains recursivemergesort function headers
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

#ifndef RECURSIVE_MERGE_SORT_H
#define RECURSIVE_MERGE_SORT_H

#include <iostream>
using namespace std;

void recursivemergesort(int* array, int size,
                        bool opt = false, int bubbleSize = 6);


class RecursiveMergeSort {

public:
	void sort(int* orig, int size, bool opt, int bubbleSize);

private:
    void merge( int* orig, int* left, int* right, int leftSize, int rightSize);
    void bubbleSort(int* orig, int size);
    void swap(int* orig, int swapIndex1, int swapIndex2);
    
};

#include "recursivemergesort.cpp"

#endif