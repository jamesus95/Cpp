/**
 * \file mergesortlinkedlist.cpp
 * @details Implementation of a merge sort algorithm for linked lists of integers
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
 *              - mergesortlinkedlist.cpp
 *              
 * \version     2.12
 * \author      James Murphree
 * \author      Vu Dinh
 * \date        Feb 23 2014
 * \copyright   WTFPLv2.1
 * 
 */

#ifndef MERGE_SORT_LINKED_LIST_CPP
#define MERGE_SORT_LINKED_LIST_CPP


/**
 * @brief public function
 * 
 * @param orig pointer to root of linked list to sort
 */
void linkedlistmergesort(LinkedIntList* orig) {
    MergeSortLinkedList sorter;
    sorter.sort(orig);
}

/**
 * Public external method
 * @param list pointer to a linked list of integers to be sorted
 */
void MergeSortLinkedList::sort(LinkedIntList* list) {
    list->setRoot(sortHelper(list->getRoot(), list->getSize()));
}

/**
 * Recursive routine to perform mergesort on a Linked List starting
 * at `subRoot` and spanning up to size == `size`.\n\n
 *
 * This routine manipulates pointers for sorting. It creates O(1) extra storage
 * space for each split & merge.\n
 * Therefore the total extra space created is O(logn).\n
 * Otherwise, it operates on the same logic as recursive merge sort on arrays.
 * 
 * @param  subRoot pointer to the front of the linked list
 * @param  size    size of the linked list
 * @return         pointer to the front of the sorted linked list
 */
Node* MergeSortLinkedList::sortHelper(Node* subRoot, int size) {
    if (size == 1) {
        return subRoot;
    } else {
        Node* rightFront = subRoot;
        int steps = 0;
        int leftSize = size / 2; int rightSize = size - (size / 2);
        while(steps < leftSize) {
            rightFront = rightFront->getNext();
            steps++;
        }
        // now have 2 halves of roughly equal sizes, recursively sort them
        subRoot = sortHelper(subRoot, leftSize);
        rightFront = sortHelper(rightFront, rightSize);
        return merge(subRoot, rightFront, leftSize, rightSize);
    }
}

/**
 * Performs sorted-merge on two linked lists via manipulating pointers.
 * Creates only O(1) extra storage Nodes.\n\n
 * Operates on the same logic as merge sort: add the smaller of the two
 * current values to the merger, then advance and repeat. Once either
 * source is exhausted, append the rest of the other to merger.
 * 
 * @param  leftFront  pointer to Node at the front of one sorted linkedlist
 * @param  rightFront pointer to Node at the front of other sorted linkedlist
 * @param  leftSize   size of the first linkedlist, necessary since with
 *                    pointer manipulation, the end of a linked list is not
 *                    necessarily NULL.
 * @param  rightSize  size of the other linkedlist, same rationale as leftSize.
 * @return            pointer to Node at the front of the merged linkedlist
 */
Node* MergeSortLinkedList::merge(   Node* leftFront, Node* rightFront,
                                    int leftSize, int rightSize     ) {
    // declare root of merged linkedlist, holding the smallest value
    // in both linked lists
    Node* newRoot = NULL;
    if (leftFront->getData() < rightFront->getData()) {
        newRoot = leftFront;
        leftFront = leftFront->getNext();
        leftSize--;
    }
    else {
        newRoot = rightFront;
        rightFront = rightFront->getNext();
        rightSize--;
    }

    Node* cur = newRoot; // `current position` pointer in the merged linkedlist

    while (leftSize > 0 && rightSize > 0) {
        if (leftFront->getData() > rightFront->getData()) {
            // append node on the right to merger
            cur->setNext(rightFront);
            cur = cur->getNext();
            // remove added node from source and advance to next node
            rightFront = rightFront->getNext();
            rightSize--;
        } else {
            // append node on the left to merger
            cur->setNext(leftFront);
            cur = cur->getNext();
            // remove added node from source and advance to next node
            leftFront = leftFront->getNext();
            leftSize--; 
        }
    }
    // exhausted either source, append the other now
    while (leftSize > 0) {
        cur->setNext(leftFront);
        leftFront = leftFront->getNext();
        cur = cur->getNext();
        leftSize--;
    }
    while (rightSize > 0) {
        cur->setNext(rightFront);
        rightFront = rightFront->getNext();
        cur = cur->getNext();
        rightSize--;
    }
    cur->setNext(NULL); // terminate pointers to avoid loops
    return newRoot;
}

#endif
