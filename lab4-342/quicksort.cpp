/**
 * \file quicksort.cpp
 * @details Implementation of a quick sorting algorithm for arrays of integers
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

#ifndef QUICK_SORT_CPP
#define QUICK_SORT_CPP

#include <stdlib.h> // for rand()

void quicksort(int* array, int size) {
	QuickSort sorter;
	sorter.sort(array, size);
}

/**
 * External public method
 * @param orig array to be quicksorted
 * @param size size of array
 */
void QuickSort::sort(int* orig, int size) {
	sort(orig, 0, size);
}

/**
 * Recursive helper for the public sort routine. This implementation performs
 * in-place swapping, which brings the space use down to O(logn).
 * Chooses a random index as pivot each time. Probabilistic and statistical
 * analysis guarantees an average running time of O(nlogn) with this pivot
 * choice.
 * 
 * @param  orig The array to be sorted
 * @param  from Index of the front of the array
 * @param  to   Index of the end of the array (exclusive)
 */
void QuickSort::sort(int* orig, int from, int to) {
	if (to - from < 2) {	// base case
		// do nothing
	} else {	// recursively sort (pick pivot and partition)
		// choose a pivot index
		int pivotIndex = rand() % (to - from) + from; // random pivot index

		// partition around pivot
		int newPivotIndex = partition(orig, from, to, pivotIndex);
		
		// then recurse
		sort(orig, from, newPivotIndex); // sort from beginning UP TO pivot
		sort(orig, newPivotIndex+1, to); // sort from beyond pivot UP TO end
	}
}


/**
 * In-place partition subroutine to partition the array around the 
 * pivot element. Scan the array and maintain the invariant by swapping the 
 * new-found element iff it is smaller than the pivot element to the end
 * of the "smaller-than" partition. The elements not swapped during the scan
 * comprise the "bigger-than" partition.
 * 
 * @param  array      the array to partition
 * @param  left       the leftmost index of the array
 * @param  right      the rightmost index of the array (exclusive)
 * @param  pivotIndex index of the pivot element
 * @invariant 		  During the linear scan of the array, the processed part
 *                	  is always "partitioned", i.e. the values smaller than the
 *                	  pivot element are all on the left of the values bigger
 *                	  than the pivot element.\n\n
 *                	  The partitions themselves need not be sorted.
 * @pre 			  Assume that array has at least 2 values
 * @return            index of the pivot element (post-partition)
 */
int QuickSort::partition(	int* array, int left, int right,
									int pivotIndex) {
	// pre-processing step: swap pivot to front (or back)
	swap(array, left, pivotIndex);

	// initially, nothing is processed and there is no partition boundary
	int currentPtr 		= left+1;	// end of the processed part
	int boundaryPtr 	= left+1;	// boundary of the two partitions
	
	// traverse the entire array
	while(currentPtr < right) {
		if(array[currentPtr] < array[left]) {	// found new item to swap
			swap(array, currentPtr, boundaryPtr);
			boundaryPtr++;	// extend the boundary only after a swap
		}
		currentPtr++;
	}
	// post-processing step: swap pivot back into place
	// pivot is to be swapped with the rightmost "smaller" element
	swap(array, left, boundaryPtr-1);

	// return the index of the pivot element
	return boundaryPtr-1;
}

/**
 * @brief Swap two values in an array
 * 
 * @param array array holding numbers to swap
 * @param index1 index of 1st number
 * @param index2 index of 2nd number
 */
void QuickSort::swap(int* array, int index1, int index2) {
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}


#endif