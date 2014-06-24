/**
 * @file lab2main.cpp
 * @author James Murphree and Darren Hoehha
 * 1/24/2014
 * CSS 342
 */

#include "SortSetArray.h"
#include "SortSetList.h"
#include <ctime>

/** fills a SortSetArray with Fibonacci numbers
* @param max: maximum Fibonacci number
* @param fSet: the SortSetArray to store the Fibonacci numbers in it
* @return int : the largest Fibonacci number in the set
*/
int fibArray(int max, SortSetArray& fSet);

/** fills a SortSetArray with prime numbers
* @param max: the maximum number to check for primes at
* @return SortSetArray : the SortSetArray containing the primes
*/
SortSetArray* primeArray(int max);

/** fills a SortSetList with Fibonacci numbers
* @param max: maximum Fibonacci number
* @param fSet: the SortSetList to store the Fibonacci numbers in it
* @return int : the largest Fibonacci number in the set
*/
int fibList(int max, SortSetList& fSet);

/** fills a SortSetList with prime numbers
* @param max: the maximum number to check for primes at
* @return SortSetList : the SortSetList containing the primes
*/
SortSetList* primeList(int max);

/** calculates the stats for the Array implementation
* @param prime: the SortSetArray with primes in it
* @param fib: the SortSetArray with Fibonacci numbers in it
* @param init: initial clock ticks
* @param primeT: clock ticks after filling the prime SortSetArray
* @param fibT: clock ticks after filling the Fibonacci SortSetArray
*/
void calcArrayStats(const SortSetArray& prime, const SortSetArray& fib,
                      clock_t init, clock_t primeT, clock_t fibT);

/** calculates the difference between two SortSetArrays
* @param left: the SortSetArray on the left
* @param right: the SortSetArray on the right
*/
void calcArrayDiff(const SortSetArray& left, const SortSetArray& right);

/** calculates the union of two SortSetArrays
* @param left: the SortSetArray on the left
* @param right: the SortSetArray on the right
*/
void calcArrayUnion(const SortSetArray& left, const SortSetArray& right);

/** calculates the intersection of two SortSetArrays
* @param left: the SortSetArray on the left
* @param right: the SortSetArray on the right
*/
void calcArrayIntersection(const SortSetArray& left, const SortSetArray& right);

/** calculates the stats for the List implementation
* @param prime: the SortSetList with primes in it
* @param fib: the SortSetList with Fibonacci numbers in it
* @param init: initial clock ticks
* @param primeT: clock ticks after filling the prime SortSetList
* @param fibT: clock ticks after filling the Fibonacci SortSetList
*/
void calcListStats(const SortSetList& prime, const SortSetList& fib,
                     clock_t init, clock_t primeT, clock_t fibT);

/** calculates the difference between two SortSetLists
* @param left: the SortSetList on the left
* @param right: the SortSetList on the right
*/
void calcListDiff(const SortSetList& left, const SortSetList& right);

/** calculates the union of two SortSetLists
* @param left: the SortSetList on the left
* @param right: the SortSetList on the right
*/
void calcListUnion(const SortSetList& left, const SortSetList& right);

/** calculates the intersection of two SortSetLists
* @param left: the SortSetList on the left
* @param right: the SortSetList on the right
*/
void calcListIntersection(const SortSetList& left, const SortSetList& right);

/** calculates the time it took for each operation
* @param init: initial time
* @param diff1: time after first difference
* @param diff2: time after second difference
* @param unionT: time after union
* @param inter: time after intersection
* @param start: time at start of operations
* @param primeT: time after prime set fills
* @param fibT: time after Fibonacci set fills
*/
void calcTime(clock_t init, clock_t diff1, clock_t diff2, clock_t unionT,
                clock_t inter, clock_t start, clock_t primeT, clock_t fibT);

/** lab2main makes and fills SortSetArrays and SortSetLists
* with prime numbers and Fibonacci numbers and then compares
* the sets
*/
int main() {

    const int FIB_NUMBERS = 46;

    // ARRAY SECTION
    clock_t time = clock();
    int init = time;
    SortSetArray* fSetArray = new SortSetArray();
    int maxFib = fibArray(FIB_NUMBERS, *fSetArray);
    clock_t fibT = clock();
    SortSetArray* pSetArray = primeArray(maxFib);
    clock_t primeT = clock();
    calcArrayStats(*pSetArray, *fSetArray, init, primeT, fibT);
    delete fSetArray;
    delete pSetArray;
    fSetArray = NULL;
    pSetArray = NULL;

    // LIST SECTION
    time = clock();
    init = time;
    SortSetList* fSetList = new SortSetList();
    maxFib = fibList(FIB_NUMBERS, *fSetList);
    fibT = clock();
    SortSetList* pSetList = primeList(maxFib);
    primeT = clock();
    calcListStats(*pSetList, *fSetList, init, primeT, fibT);
    delete fSetList;
    delete pSetList;
    fSetList = NULL;
    pSetList = NULL;


    return 0;
}

int fibArray(int max, SortSetArray& fSet) {
    int fib1 = 1;
    int fib2 = 1;
    fSet.insert(1);
    for (int i = 1; i < max; i++) {
        int temp = fib1;
        fib1 = fib2;
        fib2 += temp;
        fSet.insert(fib2);
    }
    return fib2;
}

int fibList(int max, SortSetList& fSet) {
    int fib1 = 1;
    int fib2 = 1;
    fSet.insert(1);
    for (int i = 1; i < max; i++) {
        int temp = fib1;
        fib1 = fib2;
        fib2 += temp;
        fSet.insert(fib2);
    }
    return fib2;
}

SortSetArray* primeArray(int max) {
    SortSetArray* pSet = new SortSetArray();
    for (int i = 2; i < max; i++) {
        pSet->insert(i);
    }
    for (int i = 2; i < max; i++) {
        for (int j = i; j < max; j++) {
            if (j % i == 0 && j != i) {
                pSet->remove(j);
            }
        }
    }
    return pSet;
}

SortSetList* primeList(int max) {
    SortSetList* pSet = new SortSetList();
    for (int i = max; i > 1; i--) {
        pSet->insert(i);
    }
    for (int i = 2; i < max; i++) {
        for (int j = i; j < max; j++) {
            if (j % i == 0 && j != i) {
                pSet->remove(j);
            }
        }
    }
    return pSet;
}

void calcArrayStats(const SortSetArray& prime, const SortSetArray& fib,
                      clock_t start, clock_t primeT, clock_t fibT) {
    cout << "SortSetArray Stats" << endl;
    clock_t init = clock();
    calcArrayDiff(prime, fib);
    clock_t diff1 = clock();
    calcArrayDiff(fib, prime);
    clock_t diff2 = clock();
    calcArrayUnion(prime, fib);
    clock_t unionT = clock();
    calcArrayIntersection(prime, fib);
    clock_t inter = clock();
    calcTime(init, diff1, diff2, unionT, inter, start, primeT, fibT);
}



void calcArrayDiff(const SortSetArray& left, const SortSetArray& right) {
    SortSetArray* temp = &(left - right);
    delete temp;
    temp = NULL;
}

void calcArrayUnion(const SortSetArray& left, const SortSetArray& right) {
    SortSetArray* temp = &(left + right);
    delete temp;
    temp = NULL;
}

void calcArrayIntersection(const SortSetArray& left,
                           const SortSetArray& right) {
    SortSetArray* temp = &(left * right);
    delete temp;
    temp = NULL;
}

void calcListStats(const SortSetList& prime, const SortSetList& fib,
                     clock_t start, clock_t primeT, clock_t fibT) {
    cout << "SortSetList stats" << endl;
    clock_t init = clock();
    calcListDiff(prime, fib);
    clock_t diff1 = clock();
    calcListDiff(fib, prime);
    clock_t diff2 = clock();
    calcListUnion(prime, fib);
    clock_t unionT = clock();
    calcListIntersection(prime, fib);
    clock_t inter = clock();
    calcTime(init, diff1, diff2, unionT, inter, start, primeT, fibT);
}


void calcListDiff(const SortSetList& left, const SortSetList& right) {
    SortSetList* temp = &(left - right);
    delete temp;
    temp = NULL;
}

void calcListUnion(const SortSetList& left, const SortSetList& right) {
    SortSetList* temp = &(left + right);
    delete temp;
    temp = NULL;
}

void calcListIntersection(const SortSetList& left, const SortSetList& right) {
    SortSetList* temp = &(left * right);
    delete temp;
    temp = NULL;
}

void calcTime(clock_t start, clock_t diff1, clock_t diff2, clock_t unionT,
                clock_t inter, clock_t init, clock_t primeT, clock_t fibT) {
    int f = fibT - init;
    int p = primeT - fibT;
    int d1 = diff1 - start;
    int d2 = diff2 - diff1;
    int u = unionT - diff2;
    int i = inter - unionT;
    cout << "Calculating Fibonaccis took " <<
        static_cast<double>(f) / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Calculating Primes took " <<
        static_cast<double>(p) / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Difference one took " <<
        static_cast<double>(d1) / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Difference two took " <<
        static_cast<double>(d2) / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Union took " << static_cast<double>(u) / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Intersection took " <<
        static_cast<double>(i) / CLOCKS_PER_SEC << " sec" << endl << endl;
}
