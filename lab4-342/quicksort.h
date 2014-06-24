/**
 * \file quicksort.h
 * @details Contains quicksort function headers
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

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

using namespace std;

void quicksort(int* array, int size);


class QuickSort {

public:
	void sort(int* orig, int size);

private:
    void sort(int* orig, int from, int to);
    int partition(int* array, int from, int to, int pivotIndex);
    void swap(int* array, int index1, int index2);

};

#include "quicksort.cpp"

#endif