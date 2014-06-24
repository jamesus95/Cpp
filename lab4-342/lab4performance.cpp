
/**
 * \file lab4performance.cpp
 * @details Test all sorts individually for performance.
 */

/**
 * @mainpage Introduction
 * 
 * Project:   Sorting Algorithms\n
 * Objective:   Implement and compare performance among different sorting
 *        algorithms:\n
 *        - recursivemergesort.cpp
 *        - iterativemergesort.cpp
 *        - recursivequicksort.cpp
 *        - heapsort.cpp
 *        
 * \version   2.12
 * \author    James Murphree
 * \author    Vu Dinh
 * \date    Feb 23 2014
 * \copyright WTFPLv2.1
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>  // for gettimeofday() and timeval
#include <ctime>       // for  clock()and clock_t and CLOCKS_PER_SEC
#include <assert.h>
#include <string.h>

#include "iterativemergesort.h"
#include "recursivemergesort.h"
#include "quicksort.h"
#include "heapsort.h"
#include "linkedintlist.h"
#include "mergesortlinkedlist.h"

using namespace std;

void initArray(int* array, int size, int randMax);
void printArray(int* array, int size, string arrayName);
void clockElapsed(clock_t clockTimeStart, clock_t clockTimeEnd);
void testRecursiveMerge(int size, bool debug);
void testIterativeMerge(int size, bool debug);
void testQuickSort(int size, bool debug);
void testHeapSort(int size, bool debug);
void testAll(int size, bool debug);
void elapsed(timeval &startTime, timeval &endTime);
void giveIntro();

int const DEFAULT_SIZE = 100;
bool const DEFAULT_DEBUG = false;
int const MAX_LINKED_LIST_SIZE = 100000;
int const GRAPH_SIZES[] = {1000, 10000, 100000};
int const GRAPH_POINTS = 3;
int const BUBBLE_SIZE = 20;
int const MICRO_ROLL_OVER = 1000000;

int main(int argc, char* argv[]) {

  giveIntro();
  
  int size = DEFAULT_SIZE;
  bool debug = DEFAULT_DEBUG;

  // verify arguments
  if (argc > 1) {
    size = atoi(argv[1]);
  }
  if (size <= 0) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
  if (argc > 2) {
    debug = strcmp(argv[argc - 1], "DEBUG") == 0 ? true : false;
  } 

  testAll(size, debug);
  // DATA FOR GRAPHS
  for (int i = 0; i < GRAPH_POINTS; i++) {
    testAll(GRAPH_SIZES[i], debug);
  }

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

/**  fill array with random numbers 
     This code must be made cleaner and easier to read
*/
void initArray(int* array, int size) {
  srand(size);
  for (int i = 0; i < size; i++) {
    array[i] = rand( ) % size;
  }
}

/**
 * @brief fill linked int list with random values up to size
 *
 * @param list LinkedIntList pointer
 * @param size size of list
 */
void initLinkedList(LinkedIntList* list, int size) {
  srand(size);
  for (int i = 0; i < size; i++)
  {
    list->insert(rand() % size);
  }
}

/** array printing. use debug to turn off for performance only
     This code must be made cleaner and easier to read
*/
void printArray(int* array, int size, string arrayName) {
    cout << arrayName << " = [" << array[0];
    for ( int i = 1; i < size; i++ ){
        cout << ", " << array[i];
    }
    cout << "]" << endl;
}

void elapsed(timeval &startTime, timeval &endTime) { // uses <sys/time.h>
   long seconds, microseconds; // milliSecTime,
   seconds  = endTime.tv_sec  - startTime.tv_sec;
   microseconds = endTime.tv_usec - startTime.tv_usec;
   if (microseconds < 0){ 
       microseconds += MICRO_ROLL_OVER;  // correct for roll over
   }
   cout << "elapsed time: " << seconds << " sec, " << microseconds << " microsec." << endl;
}

//======================= testers ===================================
// recursive merge sort
void testRecursiveMerge(int size, bool debug, bool opt, int bubbleSize) {
  int* items = new int[size];
  initArray(items, size);
  struct timeval startTime, endTime;
  gettimeofday(&startTime, 0); // second parameter was for timezone; but that no longer works
  if (debug) {
    printArray(items, size, "pre recursive mergesort");
  }
  recursivemergesort(items, size, opt, bubbleSize);
  if (debug) {
    printArray(items, size, "post recursive mergesort");
  }
  cout << endl;
  gettimeofday(&endTime, 0); 
  elapsed(startTime, endTime);
  delete[] items;
}

// iterative mergesort
void testIterativeMerge(int size, bool debug, bool opt, int bubbleSize) {
  int* items = new int[size];
  initArray(items, size);
  struct timeval startTime, endTime;
  gettimeofday(&startTime, 0); // second parameter was for timezone; but that no longer works
  if (debug) {
    printArray(items, size, "pre iterative mergesort");
  }
  iterativemergesort(items, size, opt, bubbleSize);
  if (debug) {
    printArray(items, size, "post iterative mergesort");
  }
  cout << endl;
  gettimeofday(&endTime, 0); 
  elapsed(startTime, endTime);
  delete[] items;
}

// quick sort
void testQuickSort(int size, bool debug) { 
  int* items = new int[size];
  initArray(items, size);
  struct timeval startTime, endTime;
  gettimeofday(&startTime, 0); // second parameter was for timezone; but that no longer works
  if (debug) {
    printArray(items, size, "pre quicksort");
  }
  quicksort(items, size);
  if (debug) {
    printArray(items, size, "post quicksort");
  }
  cout << endl;
  gettimeofday(&endTime, 0); 
  elapsed(startTime, endTime);
  delete[] items;
}

// heap sort
void testHeapSort(int size, bool debug) {
  int* items = new int[size];
  initArray(items, size);
  struct timeval startTime, endTime;
  gettimeofday(&startTime, 0); // second parameter was for timezone; but that no longer works
  if (debug) {
    printArray(items, size, "pre heapsort");
  }
  heapsort(items, size);
  if (debug) {
    printArray(items, size, "post heapsort");
  }
  cout << endl;
  gettimeofday(&endTime, 0); 
  elapsed(startTime, endTime);
  delete[] items;
}

void testLinkedListMerge(int size, bool debug) {
  if(size >= MAX_LINKED_LIST_SIZE) {
    cout << "Linkedlist merge cannot handle input sizes >= 100,000" << endl;
  }
  else {
    LinkedIntList* items = new LinkedIntList();
    initLinkedList(items, size);
  struct timeval startTime, endTime;
  gettimeofday(&startTime, 0); // second parameter was for timezone; but that no longer works
    if (debug) {
      cout << "presort" << endl; items->print();
    }
    linkedlistmergesort(items);
    if (debug) {
      cout << "postsort" << endl; items->print();
    }
    cout << endl;
    gettimeofday(&endTime, 0); 
    elapsed(startTime, endTime);
    delete items; 
  }
}

void testAll(int size, bool debug) {
  cout << "Size = " << size << endl;
  
  cout << "\nRecursive Merge Sort:" << endl;
  testRecursiveMerge(size, debug, false, BUBBLE_SIZE);
  cout << "\n-------------------------------------------" << endl;
  cout << "\nRecursive Merge Sort with optimization:" << endl;
  testRecursiveMerge(size, debug, true, BUBBLE_SIZE);
  cout << "\n-------------------------------------------" << endl;

  cout << "Iterative Merge Sort:" << endl;    
  testIterativeMerge(size, debug, false, BUBBLE_SIZE);
  cout << "\n-------------------------------------------" << endl;
  cout << "Iterative Merge Sort with optimization:" << endl;    
  testIterativeMerge(size, debug, true, BUBBLE_SIZE);
  cout << "\n-------------------------------------------" << endl;
  
  cout << "Quick Sort:" << endl;
  testQuickSort(size, debug);
  cout << "\n-------------------------------------------" << endl;

  cout << "Heap Sort:" << endl;
  testHeapSort(size, debug);
  cout << "\n-------------------------------------------" << endl;
  
  cout << "Linked List Merge Sort:" << endl;
  testLinkedListMerge(size, debug);
  cout << "\n-------------------------------------------" << endl;

  cout << "\n===========================================" << endl;
  cout << "===========================================" << endl;
 
}