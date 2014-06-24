/** Starter code to test mergesort function.
    It includes some timing code. Test and compare results. 

    This code is not ideal nor guaranteed.
    As with all work you submit, 
    you must make it meet quality/modularity/readability standards.

    Your version must accept/use the command line argument; 
    but, may set a default value if none is provided 
    instead of issuing an error message.
    
    @file lab4driver.cpp 
    @author MF & RCS
    @param size - the number of data elements to be sorted
    @return -1 if there are any problems, 0 otherwise
*/
bool debug = false;  // for global control of output

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>  // for gettimeofday() and timeval
#include <ctime>       // for  clock()and clock_t and CLOCKS_PER_SEC

#include "dummyMergesort.cpp"

using namespace std;

/**  fill array with UNIQUE random numbers 
     This code must be made cleaner and easier to read
*/
void initArray( vector<int> &array, int randMax ) {
  int size = array.size( );

  for ( int i = 0; i < size; ) {
    // if no ceiling value is specified (randMax == -1)
    // then the sky is the limit, otherwise, do not exceed randMax
    int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
    bool hit = false;
    // traverse the generated part
    for ( int j = 0; j < i; j++ ) {
      if ( array[j] == tmp ) {    // looking for tmp
        hit = true;
        break;
      }
    }
    if ( hit )	// found temp, which means temp is a repeat
      continue;	// ignore temp and find a new random value	
    array[i] = tmp; // if temp is unique so far, use it
    i++;
  }
}

/** array printing. use debug to turn off for performance only
     This code must be made cleaner and easier to read
*/

void printArray( vector<int> &array, char arrayName[] ) {
  int size = array.size( );

  for ( int i = 0; i < size; i++ ){
   cout << arrayName << "[" << i << "] = " << array[i] << "\t";
   if ( ((i > 0) && (i % 7 == 0))  || (i+1) >= size ) cout << endl;
  } // for
}

// performance evaluation

void elapsed( timeval &startTime, timeval &endTime ) { // uses <sys/time.h>
   long seconds, microseconds; // milliSecTime,
   seconds  = endTime.tv_sec  - startTime.tv_sec;
   microseconds = endTime.tv_usec - startTime.tv_usec;
   if ( microseconds < 0 ){ 
       microseconds += 1000000 ;  // correct for roll over
   }
   cout << "elapsed time: " << seconds << " sec, " << microseconds << " microsec." << endl;
} // elapsed

void clockElapsed( clock_t clockTimeStart, 
                   clock_t clockTimeEnd ) {  // uses less precise ctime
   clock_t ticks;
   ticks = clockTimeEnd - clockTimeStart;
   cout << "clock time elapsed: " << ticks << " clock ticks ~= " 
        << (float)ticks / (float)CLOCKS_PER_SEC << "seconds\n"; 
} // clockElapsed


int main( int argc, char* argv[] ) {
  // verify arguments                                                          
  if ( argc < 2 ) {
    cerr << "usage: a.out size" << endl;
    return -1;
  }

  // verify an array size                                                      
  int size = atoi( argv[1] );
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }

  // array generation
 
 // use the same srand(seed value) to get exactly the same stream of data                                                          
  srand( size ); // srand( 1 ); 
  vector<int> items( size );
  initArray( items, size );
  cout << "recursiveMergeSort initial: size =" << size << endl;
  if (debug) printArray( items, "items" ); // comment out when evaluating performance only

  // mergesort
  struct timeval startTime, endTime;
  
  clock_t clockTimeStart, clockTimeEnd;
  clockTimeStart = clock();
  
  gettimeofday( &startTime, 0 ); // second parameter was for timezone; but that no longer works

  usleep(4000000); // testing: 1000 microsec = 1 millisec 
  for (int repetition = 1; repetition <= 34; repetition++){
     dummyMergesort( items, 0, size-1 );  // mergesort( items );
     cout << " rep: " << repetition ;
  }
  cout << endl; ;
  gettimeofday( &endTime, 0 );
  
  clockTimeEnd = clock();
  elapsed( startTime, endTime ); 
  // cout << "elapsed time (in ms): " << elapsed( startTime, endTime ) << endl;
  clockElapsed (clockTimeStart, clockTimeEnd);
  // why is elapsed != clockElapsed

  cout << "recursiveMergeSort sorted:" << endl;    
  if (debug) printArray( items, "items" ); // comment out when evaluating performance only

  return 0;
} // main
