/**
 * \file heapsort.cpp
 * @details Implementation of a heap sorting algorithm for arrays of integers
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

#ifndef HEAP_SORT_CPP
#define HEAP_SORT_CPP

#include <assert.h>

/**
 * @brief Public heapsort function. Hides internal implementation details. Runs
 * in O(nlogn) time with potentially high overhead.	
 * 
 * @param array array of integers to be sorted
 * @param size size of array
 */
void heapsort(int* array, int size) {
	HeapSort sorter;
	sorter.sort(array, size);
}

/**
 * Public heapsort method. Runs in O(nlogn) time and use O(1) extra storage
 * @param orig array to be heap-sorted
 * @param size size of array
 */
void HeapSort::sort(int* orig, int size) {
	// step 1. heapify the array
	for (int child = 1; child < size; child++) {
		int parent = (child + 1) / 2 - 1;
		if (parent >= 0 && orig[child] > orig[parent]) {
			swapUp(orig, child, parent);
		}
	}
	// step 2.  iteratively removing the max value from the heap
	// 			and inserting it into its position in the array
	for (int i = size - 1; i >= 0; i--) {
		orig[i] = getMax(orig, i);
	}
}

/**
 * Subroutine to help build the heap. Recursively bubbles the parent
 * value up until it gets to its rightful position in the heap.\n
 * Takes O(logn) time.
 * 
 * @param orig   array to be built into heap
 * @param child  child value that is larger than parent value -> swap
 * @param parent value to be bubbled up into sorted position
 */
void HeapSort::swapUp(int* orig, int child, int parent) {
	// 1. swap
	swap(orig, child, parent);
	// 2. recursively bubble `parent` up into its heap position
	int newParent = (parent + 1) / 2 - 1;
	if (newParent >= 0 && orig[parent] > orig[newParent]) {
		swapUp(orig, parent, newParent);
	}
}

/**
 * Extract the max value from the heap while maintaining the heap structure.\n
 * Takes O(logn) time to re-structure the heap.
 * 
 * @param  orig array containing the heap
 * @param  size size of array
 * @return      max value inside the heap
 */
int HeapSort::getMax(int* orig, int size) {
	int temp = orig[0]; // max value, return this
	// replace root with grand-grand child
	orig[0] = orig[size];
	// swap grand-grand child down to maintain heap structure
	swapDown(orig, 0, size + 1);
	return temp;
}

/**
 * Helper subroutine to help re-structure the heap after max value is extracted.
 * \nAlgorithm:\n
 * 		-# Determine whether to swap down the left or right
 * 		-# Recursively swap down accordingly\n
 * Condition for swapping left/right:\n
 * 		-# left/right child must be greater than parent
 * 		-# swap left if left child >= right child
 * 		-# swap right if left child < right child
 * 		
 * @param orig  array holding the heap
 * @param index index of parent value in the array
 * @param size  size of the array, right child cannot exceed
 */
void HeapSort::swapDown(int* orig, int index, int size) {
	int leftChild = (index + 1) * 2 - 1;
	int rightChild = (index + 1) * 2;
	// swap down to the right if:
	// 1. there is still a rightChild
	// 2. rightChild >= leftChild
	if (	rightChild < size 						&&
			orig[rightChild] >= orig[leftChild] 	&&
			orig[rightChild] > orig[index]				) {
		swap(orig, index, rightChild);
		swapDown(orig, rightChild, size);
	} 
	// swap down to the left if:
	// 1. leftChild > parent, and
	// 2. leftChild >= rightChild (or if there's no more rightChild)
	else if (
				(
					(rightChild < size && orig[leftChild] >= orig[rightChild])
					||
					rightChild == size  // leftChild is the last item
				)
				&& orig[leftChild] > orig[index]
			)
	{
		swap(orig, index, leftChild);
		swapDown(orig, leftChild, size);
 	}
}

/**
 * Every sort routine needs a swap subroutine.
 * @param orig       array containing elements to be swapped
 * @param index1 index of one swappee
 * @param index2 index of other swappee
 */
void HeapSort::swap(int* orig, int index1, int index2) {
	int temp = orig[index1];
	orig[index1] = orig[index2];
	orig[index2] = temp;
}

#endif