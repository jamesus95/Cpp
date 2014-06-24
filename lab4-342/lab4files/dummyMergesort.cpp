/** dummy mergesort to waste time
    @file dummyMergesort.cpp
*/
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int MAXDELAY = 205 * 1000000;  // ~ .5 sec on 2.53 Ghz pc

void dummyMergesort( vector<int> items, int start = 0, int top = 0 ){
   if (debug) cout << "dummyMergesort delay loop repetitions = " << MAXDELAY << endl;
   
   int repetitions = top > 0 ? top : MAXDELAY; // spend at least .5 sec.
   for(int i =0; i < repetitions; i++){ 
      int timeWaster;
      timeWaster = 1235; 
   }
} // mergsort

