/**
 * \file lab4test.cpp
 * @details Test all sorts individually for functionality, not performance.
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

#include "iterativemergesort.h"
#include "recursivemergesort.h"
#include "quicksort.h"
#include "heapsort.h"
#include "linkedintlist.h"
#include "mergesortlinkedlist.h"
#include <iostream>
#include <assert.h>
#include <ctime>
#include "stdlib.h"

using namespace std;

int* randomArray(int size);
int* reverseArray(int size);
void printArray(int* array, int size);
bool isArraySorted(int* array, int size);

void testQuickSort(int size, bool random);
void testIterMergeSort(int size, bool random);
void testRecurMergeSort(int size, bool random);
void testHeapSort(int size, bool random);
void testListMergeSort(int size, bool random);
void testBubbleOpt(int size, bool random);
void testSorts(int size, bool random);
void giveIntro();

// Debug mode prints pre-sort and post-sort arrays
bool const DEBUG = true;
int const DEFAULT_SIZE = 10;
int const FIBS[] = {0,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,
				   10946,17711,28657,46368,75025,121393,196418,317811,514299,832040,
				   1346269,2178309,3524578,5702887,9227465};
int const FIB_LENGTH = 34;
int const BUBBLE[] = {5,7,10,15,20,25,30};
int const BUBBLE_LENGTH = 7;
int const BUBBLE_SIZE = 100000;

int main(int argc, char* argv[]) {

	giveIntro();

	int size = DEFAULT_SIZE;

	// Program call takes an input to determin size of arrays to sort
	if (argc > 1) {
		size = atoi(argv[1]);
	}

	// sorting and printing
	testSorts(size, true);
	testSorts(size, false);
	testBubbleOpt(BUBBLE_SIZE, true);

	return 0;
}

void giveIntro() {
    cout << "Program:       Lab 4 assignment" << endl;
    cout << "Description:   Compares various sorting algorithms" << endl;
    cout << "Authors:       Vu Dinh, James Murphree" << endl;
    cout << "Setting:       CSS342 programming assignment" << endl;
    cout << "Date:          Feb 23 2014" << endl;
    cout << "Notes:         Refer to the description files for details.\n";
    cout << "\n==========================================================\n\n";
    cout << "Timings for various operations: " << endl;
}

void testSorts(int size, bool random) {
	testQuickSort(size, random);         // thoroughly checked ~10m
	testIterMergeSort(size, random);     // thoroughly checked ~10m
	testRecurMergeSort(size, random);    // thoroughly checked ~10m
	testHeapSort(size, random);          // thoroughly checked ~10m
	testListMergeSort(size, random);     // max size = ~100k
}

int* randomArray(int size) {
	int* randomArray = new int[size];
	for (int i = 0; i < size; i++) {
		randomArray[i] = rand() % size + 1;
	}
	return randomArray;
}

int* reverseArray(int size) {
	int* reverseArray = new int[size];
	for(int i = 0; i < size; i++) {
		reverseArray[i] = size - i;
	}
	return reverseArray;
}

void printArray(int* array, int size) {
	if (size > 18) {
		for (int i = 0; i < 9; i++) {
			cout << array[i] << " ";
		}
		cout << "... ";
		for (int i = size - 10; i < size; i++) {
			cout << array[i] << " ";
		}
	} else {
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
	}
	cout << endl;
}

bool isArraySorted(int* array, int size) {
	bool sorted = true;
	for(int i = 1; i < size; i++) {
		if(array[i] < array[i-1])
			sorted = false;
	}
	return sorted;
}

void testQuickSort(int size, bool random) {
    QuickSort quickSorter;
    int* arrayA;
    if (random) {
    	arrayA = randomArray(size);
    } else {
    	arrayA = reverseArray(size);
	}
	if(DEBUG) {
		cout << "pre-sort A = "; printArray(arrayA, size);	
	}
	quickSorter.sort(arrayA, size);			// quicksort
	if(DEBUG) {
		cout << "A = "; printArray(arrayA, size);	
	}
	assert(isArraySorted(arrayA, size));
	delete[] arrayA;
}

void testIterMergeSort(int size, bool random) {
    IterativeMergeSort iterMergeSorter;
    int* arrayB;
    if (random) {
    	arrayB = randomArray(size);
    } else {
    	arrayB = reverseArray(size);
	}
	if(DEBUG) {
		cout << "pre-sort B = "; printArray(arrayB, size);
	}
	iterMergeSorter.sort(arrayB, size, true, 6);		// iterative mergesort
	if(DEBUG) {
		cout << "B = "; printArray(arrayB, size);
	}
	assert(isArraySorted(arrayB, size));
	delete[] arrayB;
}

void testRecurMergeSort(int size, bool random) {
    RecursiveMergeSort recurMergeSorter;
    int* arrayC;
    if (random) {
    	arrayC = randomArray(size);
    } else {
    	arrayC = reverseArray(size);
	}
	if(DEBUG) {
		cout << "pre-sort C = "; printArray(arrayC, size);
	}
	recurMergeSorter.sort(arrayC, size, true, 6);		// recursive mergesort
	if(DEBUG) {
		cout << "C = "; printArray(arrayC, size);
	}
	assert(isArraySorted(arrayC, size));
	delete[] arrayC;
}

void testHeapSort(int size, bool random) {
    HeapSort heapSorter;
    int* arrayD;
    if (random) {
    	arrayD = randomArray(size);
    } else {
    	arrayD = reverseArray(size);
	}
	if(DEBUG) { 
		cout << "pre-sort D = "; printArray(arrayD, size);
	}
	heapSorter.sort(arrayD, size);			// heapsort
	if(DEBUG) { 
		cout << "D = "; printArray(arrayD, size);
	}
	assert(isArraySorted(arrayD, size));
	delete[] arrayD;
}

void testBubbleOpt(int size, bool random) {
	for (int i = 0; i < BUBBLE_LENGTH; i++) {
		clock_t start = clock();
		for (int j = 0; j < FIB_LENGTH; j++) {
			srand(FIBS[j]);
			int* array = randomArray(size);
			recursivemergesort(array, size, true, BUBBLE[i]);
		}
		clock_t end = clock();
		clock_t time = end - start;
		cout << "Bubble time for " << BUBBLE[i] << ": " 
		     << (float)time/(float)CLOCKS_PER_SEC << endl;
	}
}

void testListMergeSort(int size, bool random) {
    MergeSortLinkedList listMergeSorter;
    LinkedIntList* linkedList = new LinkedIntList();
	for (int i = 0; i < size; i++) {
		if (random) {
			linkedList->insert(rand() % size + 1);
		} else {
			linkedList->insert(size - i);
		}
	}
	listMergeSorter.sort(linkedList);			// linkedlist mergesort
	assert(linkedList->isSorted());
	delete linkedList;
}