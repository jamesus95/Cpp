/**
 * @file lab3main.cpp
 * @author James Murphree <murphs95@uw.edu>
 * @author Darren Hoehna <dhoehna@uw.edu>
 * @section Assignment Lab3
 * @section Due Feb. 9th 2013
 * @brief Compares the time requirements of:
 * 1. comparing two files to 35 files, but searching only the prime
 *      Fibonacci numbers.
 * 2. Comparing two files to 35 files, byte by byte, until the files
 *      do not match.
 * TO PRINT TO A FILE: type the file name as the last parameter
 * when calling the function from the command line.
 */

#include "compareList.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

#define TOTAL_TARGETS 2
#define TOTAL_PROSPECTS 35
#define TOTAL_PRIME_FIB 10
#define FILE_NAME_MAX 100
#define NUM_W_S_CHARS 4

struct FileStats {
    char name[FILE_NAME_MAX];
    int numBytes;
    int size;
    CompareList* primeFibBytes;
};

void intro(std::ostream* output);
void comparePrimeFibs(std::ostream* output);
FileStats readFilePrimeFib(std::ifstream& fileNameReader, FileStats files[],
                           int index);
void makeCompareList(std::ifstream& fileNameReader, FileStats files[],
                     int index);
void compare(FileStats targetFiles[], std::ostream* output);
void deleteFiles(FileStats toDelete[], int totalFiles);
void printFile(FileStats toPrint, bool target, int targetLength,
               std::ostream* output);
void compareByteByByte(std::ostream* output);
void compareBytes(std::ifstream& prospectFiles, char target[],
                  std::ostream* output);
void compareByteStreams(std::ifstream& target, std::ifstream& prospect,
                        int offset, std::ostream* output);
int getOffset(std::ifstream& inFile);
void reportTime(int init, int primeFibT, int byteByByteT);


char const TARGETS[] = "targetFiles.txt";
char const PROSPECTS[] = "prospectFiles.txt";
int const PRIME_FIBS[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229,
                          433494437};
int const WHITE_SPACE[] = {9,10,13,32};

int main(int argc, char *argv[]) {
    std::ostream* output;
    std::filebuf fb;
    if (argc > 1) {
        fb.open(argv[argc - 1], std::ios::out);
        std::ostream outputFile(&fb);
        output = &(outputFile);
    } else {
        output = &(std::cout);
    }
    intro(output);
    clock_t time = clock();
    int init = time;
	comparePrimeFibs(output);
	clock_t primeFibsT = clock();
	compareByteByByte(output);
	clock_t byteByByteT = clock();
    reportTime(init, primeFibsT, byteByByteT);
	fb.close();
	return 0;
}

void intro(std::ostream* output) {
    *output << "Authors: James Murphree and Darren Hoehna" << std::endl;
    *output << "Title: Lab3Main.cpp" << std::endl;
    *output << "Description: 1. comparing two files to 35 files, but searching"
    << "only the prime Fibonacci numbers."
    << "Comparing two files to 35 files, byte by byte, until the files"
    << "do not match." << std::endl;
}

/**
 * Compares each targetlist to each prospect list for each prime Fibonacci
 * character space.
 * @pre TARGETS and PROSPECTS exist
 */
void comparePrimeFibs(std::ostream* output) {
    *output << "Comparing by PrimeFibonacci bytes." << std::endl;
    std::ifstream targetFile(TARGETS);
    FileStats targetToCompare[TOTAL_TARGETS];
    // i is used as the for loop iteration variable to differentiate
    // it from variables from elsewhere in the program
    for(int i = 0; i < TOTAL_TARGETS; i++) {
        makeCompareList(targetFile, targetToCompare, i);
    }
    compare(targetToCompare, output);
    deleteFiles(targetToCompare, TOTAL_TARGETS);

}

/**
 *
 * @param fileNameReader The ifstream that holds the names of all the files.
 * @param files An array of FileStats to holds information about each file.
 * @param index The index to insert the FIleStats structore into.
 * @return A FileStat struct.
 * @pre index is a valid index for the file array.
 * @post There will be a FileStat struct in the index for files.
 */
void makeCompareList(std::ifstream& fileNameReader, FileStats files[],
                     int index) {
    FileStats newFileStats;
    fileNameReader >> newFileStats.name;
    CompareList* newCompareList = new CompareList();
	std::ifstream fileReader(newFileStats.name);
	getOffset(fileReader);
	char next = fileReader.get();
	int counter = 1;
	int nextPrimeFib = 0;
	while (!fileReader.eof() && nextPrimeFib < TOTAL_PRIME_FIB) {
        if (PRIME_FIBS[nextPrimeFib] == counter) {
            newCompareList->insert(next, counter);
            nextPrimeFib++;
        }
        next = fileReader.get();
        counter++;
    }
    newFileStats.numBytes = counter;
    newFileStats.primeFibBytes = newCompareList;
    newFileStats.size = nextPrimeFib;
    files[index] = newFileStats;
}

/**
 *
 * @param targetFiles The Target FileStats array to compare to the prospects
 * @param prospectFiles The prospect FileStats array to compare to
 *      the targets.
 * @param output The output stream to print to.
 * @pre targetFiles has data in it.
 *      ProspectFiles has data in it.
 */
void compare(FileStats targetFiles[], std::ostream* output) {
    // i is used as the for loop iteration variable to differentiate
    // it from variables from elsewhere in the program
    for (int i = 0; i < TOTAL_TARGETS; i++) {
        // j is used as the for loop iteration variable to differentiate
        // it from variables from elsewhere in the program
        std::ifstream prospectFile(PROSPECTS);
        FileStats prospectFiles[TOTAL_PROSPECTS];
        for(int j = 0; j < TOTAL_PROSPECTS; j++) {
            makeCompareList(prospectFile, prospectFiles, j);
        }
        printFile(targetFiles[i], true, targetFiles[i].size, output);
        *output << std::endl;
        // j is used as the for loop iteration variable to differentiate
        // it from variables from elsewhere in the program
        for (int j = 0; j < TOTAL_PROSPECTS; j++) {
            printFile(prospectFiles[j], false, targetFiles[i].size, output);
            targetFiles[i].primeFibBytes->
                compareTo(*(prospectFiles[j].primeFibBytes), output);
        }
        deleteFiles(prospectFiles, TOTAL_PROSPECTS);
        *output <<std::endl << std::endl;
    }
}

/**
 *
 * @param toPrint The FileStats struct to print.
 * @param target If the FileStat struct is a target or not.
 * @param output The output stream to print to.
 * @pre toPrint has data to print.
 */
void printFile(FileStats toPrint, bool target, int targetLength,
               std::ostream* output) {
    if (target) {
        *output << "Target: ";
    } else {
        *output << "Prospect: ";
    }
    *output << toPrint.name << "  " << toPrint.numBytes << " Bytes"
              << std::endl;
    toPrint.primeFibBytes->print(targetLength, output);
}

/**
 *
 * @param toDelete The FileStats struct to delete
 * @param totalFiles The number of FileStats sturcts in the array.
 * @pre totalFiles is in the bounds of toDelete
 */
void deleteFiles(FileStats toDelete[], int totalFiles) {
    for (int fileIndex = 0; fileIndex < totalFiles; fileIndex++) {
        delete toDelete[fileIndex].primeFibBytes;
    }
}

/**
 * @param output The location to print output.
 */
void compareByteByByte(std::ostream* output) {
    *output << "Compare with byte by byte comparison" << std::endl;
    std::ifstream targetFiles(TARGETS);
    // i is used as the for loop iteration variable to differentiate
    // it from variables from elsewhere in the program
	for(int i = 0; i < TOTAL_TARGETS; i++) {
        std::ifstream prospectFiles(PROSPECTS);
        char targetName[FILE_NAME_MAX];
        targetFiles >> targetName;
        *output << "Target: " << targetName << std::endl << std::endl;
        // j is used as the for loop iteration variable to differentiate
        // it from variables from elsewhere in the program
        compareBytes(prospectFiles, targetName, output);
    }
}

/**
 * @param prospectFiles The file with the name of all the prospect files.
 * @param targetName The name of the target file
 * @param output The output stream to print to.
 */
void compareBytes(std::ifstream& prospectFiles, char targetName[],
                  std::ostream* output) {
    for(int j = 0; j < TOTAL_PROSPECTS; j++) {
        char prospectName[FILE_NAME_MAX];
        prospectFiles >> prospectName;
        *output << "Prospect: " << prospectName << std::endl;
        std::ifstream target(targetName);
        std::ifstream prospect(prospectName);
        getOffset(target);
        int offset = getOffset(prospect);
        compareByteStreams(target, prospect, offset, output);
    }
    *output << std::endl;
}

/**
* @param target The target file to use.
* @param prospect The prospect file to use.
* @param offset The number of white beginning white spaces in the prospect file
* @param output The output stream to print to.
*/
void compareByteStreams(std::ifstream& target, std::ifstream& prospect,
                        int offset, std::ostream* output) {
    int counter = 0;
    char targetChar = target.get();
    char prospectChar = prospect.get();
    while((!target.eof() || !prospect.eof()) &&
            targetChar == prospectChar) {
        targetChar = target.get();
        prospectChar = prospect.get();
        counter++;
    }
    if (target.eof() && prospect.eof()) {
        *output << "Complete Match" << std::endl;
    } else {
        *output << "Mismatch at character " << counter << " plus "
        << offset << " leading white spaces." << std::endl;
    }
    *output << std::endl;
}

/**
 *
 * @param inFile the file to calculate the number of white spaces.
 * @return An integer representation of the number of whitespaces at the
 * beginning of the file.
 */
int getOffset(std::ifstream& inFile) {
    int count = 0;
    bool moreWhiteSpace = true;
    while(moreWhiteSpace) {
        char peek = inFile.peek();
        for (int i = 0; i < NUM_W_S_CHARS; i++) {
            if (peek != WHITE_SPACE[i]) {
                moreWhiteSpace = false;
            } else {
                count++;
                inFile.get();
            }
        }
    }
    return count;
}

/**
* @param init The initial clock time
* @param primeFibT The clock time after the primeFibs comparison.
* @param byteByByteT The clock time after the byte by byte comparison.
* @pre init, primeFibT, and byteByByteT are non-negative numbers.
*/
void reportTime(int init, int primeFibT, int byteByByteT) {
	int primeFibElapsed = primeFibT - init;
	int byteByByteElapsed = byteByByteT - primeFibT;

	std::cout << "Comparing by prime Fibonacci took " <<
		static_cast<double>(primeFibElapsed) / CLOCKS_PER_SEC
		<< " sec" << std::endl;
	std::cout << "Comparing byte by byte tool " <<
		static_cast<double>(byteByByteElapsed) / CLOCKS_PER_SEC
		<< " sec" << std::endl;
}