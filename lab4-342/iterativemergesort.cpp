/**
 * \file iterativemergesort.cpp
 * @details Implementation details of iterative merge sort routine.
 */

/**
 * @mainpage Introduction
 * 
 * Project:     Sorting Algorithms\n
 * Objective:   Implement and compare performance among different sorting
 *              algorithms:\n
 *              - recursivemergesort.cpp
 *              - iterativemergesort.cpp
 *              - quicksort.cpp
 *              - heapsort.cpp
 *              
 * \version     2.12
 * \author      James Murphree
 * \author      Vu Dinh
 * \date        Feb 23 2014
 * \copyright   WTFPLv2.1
 * 
 */

#ifndef ITERATIVE_MERGE_SORT_CPP
#define ITERATIVE_MERGE_SORT_CPP

#include <assert.h>

/**
 * Public iterative merge sort function. Hides internal implementation
 * details. Runs in O(nlogn) time and uses one extra temp array.\n
 * Optimization flag and parameter available (default: off), using bubblesort
 * for small datasets. 
 * 
 * @param array array of integers to be sorted
 * @param size size of array
 * @param opt optimization flag. Switches over to using bubble sort once
 *            subarrays get small enough (bubbleSize).
 * @param bubbleSize turnover size for optimization bubble-sort to kick in.
 */
void iterativemergesort(int* array, int size, bool opt, int bubbleSize) {
    IterativeMergeSort sorter;
    sorter.sort(array, size, opt, bubbleSize);
}


/**
 * Iterative implementation of merge sort.\n
 * Requires O(nlogn) running time and O(1) extra storage space
 * 
 * @param orig The array to be sorted
 * @param size size of the array to sort
 * @param opt boolean flag to trigger the optimized version using
 *            bubble sort for small subSets (default: false)
 * @param bubbleSize turnover size to use bubble sort on (default: 6)\n
 *                   The algorithm first "preprocesses" the array
 *                   with bubble sort in groups of size 6, then iteratively
 *                   merge them into larger arrays in sorted order
 */
void IterativeMergeSort::sort(int* orig, const int size, 
                              bool opt, int bubbleSize) {
    // pre-processing the original array with bubble sort if requested
    if(opt == true) {
        bubbleSort(orig, size, bubbleSize);
    }
    // start merge sort
    int* tempStorage = new int[size];
    int runCount = 0;
    // iteratively "sort" (via merging) subarrays of incremental sizes
    // subSize = length of each sub array, min = 1, max = n*2
    for (int subSize = opt ? bubbleSize : 1; subSize < size; subSize *= 2) {
        // even runs write FROM the original TO tempStorage
        if (runCount % 2 == 0) {
            // merge pairs of subarrays of size subSize into bigger sorted arrs
            merge(orig, tempStorage, size, subSize);
        } 
        // odd runs write FROM tempStorage TO the original array
        else {
            merge(tempStorage, orig, size, subSize);
        }
        runCount++;
    }
    // copy back to original if final run wrote to tempStorage
    if (runCount % 2 == 1) {
        for (int i = 0; i < size; i++)
            orig[i] = tempStorage[i];
    }
    delete[] tempStorage; tempStorage = NULL;
}

/**
 * Performs sorted merge on adjacent pairs of subarrays, each of size subSize,
 * using `to` as the overwrite-able storage space.\n This essentially moves
 * all the data from the original array `from` to the temporary storage
 * `to`. Subsequently, this method will be called again with the two arrays
 * in reverse position so that the data can be moved back and further sorted.
 *\n\n
 * E.g. if subSize = 2 and size = 16, there will be a total of 4 pairs of
 * subarrays, each pair having two subarrays of size 2.\n
 * Each of these pair is then merged into one bigger array of double the size
 * (4 now) with data in sorted order.\n\n
 *
 * 
 * @param from      array of length `size` containing data to be sort-merged
 * @param to        array of length `size` to hold the sort-merged data
 * @param size      length of both source and destination arrays
 * @param subSize   size of each subproblem to be merged with its neighbor
 * @post            Subarrays of length size*2 are in sorted order (internally).
 */
void IterativeMergeSort::merge(int* from, int* to, int size, int subSize) {
    /**
     * Special case:
     * If the array size is anything BUT powers of 2, eventually this
     * situation will happen:
     * The final pair will be mismatched in size. The left array will have 
     * subSize numbers, whereas the right one can have anything from 
     * 1 to subSize-1 numbers.
     * 
     * We thus compare the front numbers (as we normally would) while
     * carefully considering the possibility of the right pointer
     * exceeding the big size (even when rightCount has not yet reached
     * subSize).
     */
	// each pair starts at leftFront and ends at leftFront + subSize*2 - 1
    for(int leftFront = 0; leftFront < size; leftFront += subSize * 2) {
        int rightFront = leftFront + subSize;
        int rightEnd   = rightFront + subSize;

        // pointers to keep track of current positions while merging
        int leftPtr  = leftFront;
        int rightPtr = rightFront;
        int mergePtr = leftFront;

        // Normal case: For some right arrays, they will be exhausted before
        //      the rightPtr hits the end of the big array.
        // Special case: For some others (the ones at the end of the big 
        //      array when size != 2^k), the opposite is true.
        // So, check for both.
        while (    leftPtr < rightFront
                && rightPtr < rightEnd         // normal case
                && rightPtr < size)            // special case
        {
            // copy the smaller values over
            if (from[leftPtr] < from[rightPtr]) {
                to[mergePtr++] = from[leftPtr++];
            } else {
                to[mergePtr++] = from[rightPtr++];
            }
        }
        // exited while loop, either left or right has been exhausted
        if (    rightPtr >= rightEnd           // normal case
            ||  rightPtr >= size) {            // special case
            // case 1: exhausted right array, just copy from left
            while (leftPtr < rightFront && leftPtr < size) {
                to[mergePtr++] = from[leftPtr++];
            }
        } else {
            // case 2: exhausted left array, just copy from right
            while(rightPtr < size && rightPtr < size) {
                to[mergePtr++] = from[rightPtr++];
            }
        }
    }
}

/**
 * Preprocessing helper for mergesort to optimize performance on small
 * datasets. Uniquely implemented for such a purpose.\n\n
 * Algorithm: jumps in front of each subsets of size bubbleSize
 *            and performs bubble sort on it.
 * @param orig       array to be sorted
 * @param size       size of whole array
 * @param bubbleSize size of each subset to be bubble-sorted
 */
void IterativeMergeSort::bubbleSort(int* orig, int size, int bubbleSize) {
    // iteratively jump to the front of each subarray
    for(int front = 0; front < size; front += bubbleSize) {
        // then bubble sort each of them by
        // 1. starting at gradually higher indices
        for (int i = front+1; i <= front + bubbleSize && i < size; i++) {
            int count = i;
            // and 2. moving all the way down, swapping as necessary
            while (count > front) {
                if(orig[count] < orig[count - 1])
                    swap(orig, count, count-1);
                count--;
            }
        }
    }
}

/**
 * Every sort routine needs a swap subroutine.
 * @param orig       array containing elements to be swapped
 * @param swapIndex1 index of one swappee
 * @param swapIndex2 index of other swappee
 */
void IterativeMergeSort::swap(int* orig, int swapIndex1, int swapIndex2) {
    int temp = orig[swapIndex1];
    orig[swapIndex1] = orig[swapIndex2];
    orig[swapIndex2] = temp;
}

#endif
