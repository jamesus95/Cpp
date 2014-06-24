/**
 * \file recursivemergesort.cpp
 * @details Implementation details of iterative merge sort routine for arrays of integers.
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
 * 				
 * \version		2.12
 * \author		James Murphree
 * \author		Vu Dinh
 * \date 		Feb 23 2014
 * \copyright	WTFPLv2.1
 * 
 */

#ifndef RECURSIVE_MERGE_SORT_CPP
#define RECURSIVE_MERGE_SORT_CPP

/**
 * Public recursive merge sort function. Hides internal implementation
 * details. Runs in O(nlogn) time and uses O(nlogn) space.\n
 * Optimization flag and parameter available (default: off), using bubblesort
 * for small datasets. 
 * 
 * @param array array of integers to be sorted
 * @param size size of array
 * @param opt optimization flag. Switches over to using bubble sort once
 *            subarrays get small enough (bubbleSize).
 * @param bubbleSize turnover size for optimization bubble-sort to kick in.
 */
void recursivemergesort(int* array, int size, bool opt, int bubbleSize) {
	RecursiveMergeSort sorter;
	sorter.sort(array, size, opt, bubbleSize);
}

/**
 * Recursive implementation of merge sort.\n
 * Requires O(nlogn) running time and O(nlogn) extra storage space
 * 
 * @param orig The array to be sorted
 * @param size size of the array to sort
 * @param opt  bool flag to trigger optimization with bubblesort on small
 *             datasets.
 * @param bubbleSize	turnover size to start bubbling instead of merging
 */
void RecursiveMergeSort::sort(int* orig, int size, bool opt, int bubbleSize) {
	if(size < 2) {
		// base case, do nothing
	} else if(opt == true && size <= bubbleSize) {
		bubbleSort(orig, size);
	} else {
		// split big array into two subarrays of roughly equal size
		int leftSize = (size / 2);
		int rightSize = size - leftSize;
		int* left = new int[leftSize];
		for (int i = 0; i < leftSize; i++)
			left[i] = orig[i];
		int* right = new int[rightSize];
		for (int i = 0; i < rightSize; i++) {
			right[i] = orig[i + leftSize];
		}
		// recursively sort each array
		sort(left, leftSize, opt, bubbleSize);
		sort(right, rightSize, opt, bubbleSize);
		// then merge the two sorted subarrays into one big sorted array
		merge(orig, left, right, leftSize, rightSize);
		// clean up
		delete left; delete right;
		left = NULL; right = NULL;
	}
}

/**
 * Merges sorted data from each subarray (left and right) to a bigger array
 * in sorted order.
 * 
 * @param orig      Large array to merge into
 * @param left      subarray #1
 * @param right     subarray #2
 * @param leftSize  size of subarray #1
 * @param rightSize size of subarray #2
 */
void RecursiveMergeSort::merge(	int* orig, int* left, int* right,
							    int leftSize, int rightSize			) {
	int countL = 0;
	int countR = 0;
	int index = 0;
	while (countL < leftSize && countR < rightSize) {
		if (left[countL] < right[countR])
			orig[index++] = left[countL++];		// copy, then increment
		else
			orig[index++] = right[countR++];
	}
	// exited while loop, either countL == leftSize or countR == rightSize
	// just append stuff from whichever set that still has data
	while (countR < rightSize) {
		orig[index++] = right[countR++]; 		// copy, then increment
	}
	while (countL < leftSize) {
		orig[index++] = left[countL++];
	}
}

/**
 * Plain old bubble sort. Nothing special.
 * 
 * @param orig       array to be sorted
 * @param size       size of whole array
 * @param bubbleSize size of each subset to be bubble-sorted
 */
void RecursiveMergeSort::bubbleSort(int* orig, int size) {
	if(size > 1) {
		// 1. Start at gradually higher indices
		for (int i = 1; i < size; i++) {
            int curr = i;
            // 2. Move all the way down, swapping as necessary
            while (curr > 0) {
                if(orig[curr] < orig[curr - 1])
                    swap(orig, curr, curr-1);
                curr--;
            }
        }
	}
}

/**
 * Every sort routine needs a swap subroutine.
 * 
 * @param orig       array containing elements to be swapped
 * @param swapIndex1 index of one swappee
 * @param swapIndex2 index of other swappee
 */
void RecursiveMergeSort::swap(int* orig, int swapIndex1, int swapIndex2) {
    int temp = orig[swapIndex1];
    orig[swapIndex1] = orig[swapIndex2];
    orig[swapIndex2] = temp;
}

#endif
