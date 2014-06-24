/**
 * \file heapsort.h
 * @details Contains heapsort function headers
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

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

using namespace std;

void heapsort(int* array, int size);


class HeapSort {

public:
	void sort(int* orig, int size);

private:
    int getMax(int* orig, int size);
	void swapUp(int* orig, int a, int b);
	void swapDown(int* orig, int index, int size);
    void swap(int* orig, int index1, int index2);

};

#include "heapsort.cpp"

#endif