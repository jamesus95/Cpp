/**
 * @file lab5main.cpp
 * Purpose: lab5main reads text files saving the tokens from them
 * into a TBST.  For each file read in statistics are printed out.
 *
 * @author 		James Murphree <murphs95@uw.edu>
 * @author 		Vu Dinh <vdinh143@uw.edu>
 * @date 		March 13 2014
 * @copyright	WTFPLv2.1
 */

 /**
 * @mainpage Introduction
 * 
 * Project: 	Threaded Binary Search Tree\n
 * Objective: 	Implement a TBST with several functionalities:\n
 * 				- recursive traversal (with functional programming support)
 * 				- iterative inorder traversal (with functional programming
 												support)
 * 				- Iterator traversal (adheres to STL iterator standard use)
 * 				- Self-balancing
 * 				
 * \version		4.07
 * \author		James Murphree
 * \author		Vu Dinh
 * \date 		Mar 13 2014
 * \copyright	WTFPLv2.1
 * 
 */

#ifndef LAB_5_MAIN_CPP
#define LAB_5_MAIN_CPP

#include <string.h>
#include <iostream>
#include <fstream>
#include "tbst.h"
#include <ctime>

using namespace std;

bool debug = false;
char const OUTPUT_FILE[] = "lab5out.txt";
char const DEFAULT_INPUT_FILE[] = "hamlet.txt";
int const MAX_ARGS = 53;
int const MIN_ARGS = 3;
int const MAX_NODE_PRINT = 21;
int const MAX_NODES_PER_LINE = 7;
int const LOWER_CASE_LBOUND = 97;
int const LOWER_CASE_UBOUND = 122;
int const UPPER_CASE_LBOUND = 65;
int const UPPER_CASE_UBOUND = 90;
int const NUMBER_CASE_LBOUND = 48;
int const NUMBER_CASE_UBOUND = 57;
int const APOSTROPHE = 39;

string const TOO_MANY_ARGS = "Program can't handle more than 50 text files";
string const NOT_ENOUGH_ARGS = "2 arguments required\n<FILE> <DEBUG>";
string const FILE_ERROR = "File \"";
string const FAIL = "\" failed to open.";
string const FILE_OUTPUT_SEPARATOR = "======================================";

void giveIntro();
TBST* readFile(const char* name);
string getWord(ifstream& input);
bool addChar(char c);
void printTime(const char* name, double seconds);
bool isWhiteSpace(char c);
NodeData** getMaxes(TBST* orig);
NodeData** getMins(TBST* orig);
void printData(NodeData** data, int size);
void printMinMax(TBST* tree);
void writeNodeToFile(Node* nodeToPrint, ostream& output);
void displayNode(Node* nodeToPrint);

int main(int argc, char* argv[]) {

	// Argument handling
	if (argc < MIN_ARGS) {
		cerr << NOT_ENOUGH_ARGS << endl;
		return 1;
	}
	if (argc > MAX_ARGS) {
		cerr << TOO_MANY_ARGS << endl;
		return 1;
	}
	ostream* output = NULL;
	filebuf fb;
	if (string(argv[argc - 1]) == "DEBUG") {
		debug = true;
	}
	if (string(argv[argc - 2]) == "FILE") {
		fb.open(OUTPUT_FILE, std::ios::out);
        ostream outputFile(&fb);
        output = &(outputFile);
	}

	// WORK PART
	giveIntro();
	if (argc > MIN_ARGS) {
		for (int file = 1; file < argc - 2; file++) {
			char* const fileName = argv[file];
			clock_t begin = clock();
			TBST* stringTree = readFile(fileName);
			if (stringTree != NULL) {
				
				printMinMax(stringTree);
				if (output != NULL) {
					stringTree->iterativeInorder(writeNodeToFile, *output);
				}
				delete stringTree;
				stringTree = NULL;
				clock_t end = clock();
				printTime(fileName, ((double)end - begin) / CLOCKS_PER_SEC);
			}
		}
	} else {
		TBST* stringTree = readFile(DEFAULT_INPUT_FILE);
		clock_t begin = clock();
		printMinMax(stringTree);
		if (output != NULL) {
			stringTree->iterativeInorder(writeNodeToFile, *output);
		}
		clock_t end = clock();
		printTime(DEFAULT_INPUT_FILE, ((double)end - begin) / CLOCKS_PER_SEC);
		delete stringTree;
		stringTree = NULL;
	}
	fb.close();
	return 0;
}

void giveIntro() {
    cout << "Program:       Lab 5 assignment" << endl;
    cout << "Description:   Counts words in files" << endl;
    cout << "Authors:       Vu Dinh, James Murphree" << endl;
    cout << "Setting:       CSS342 programming assignment" << endl;
    cout << "Date:          Mar 13 2014" << endl;
    cout << "Notes:         Refer to the description files for details.\n";
    cout << "==========================================================\n\n";
}

void printMinMax(TBST* tree) {
	NodeData** maxes = getMaxes(tree);
	NodeData** mins = getMins(tree);
	int size = tree->size() < MAX_NODE_PRINT ? tree->size() : MAX_NODE_PRINT;
	printData(maxes, size);
	cout << endl;
	printData(mins, size);
	cout << endl;
	for (int i = 0; i < size; i++) {
		delete maxes[i];
		delete mins[i];
	}
	delete[] maxes;
	delete[] mins;
}

void displayNode(Node* nodeToPrint) {
    cout << *(nodeToPrint->getData()) << " ";
}

void writeNodeToFile(Node* nodeToPrint, ostream& output) {
    output << *(nodeToPrint->getData()) << " ";
}

TBST* readFile(const char* name) {
	ifstream input(name);
	if (!input) {
		cerr << FILE_ERROR << name << FAIL << endl;
		return NULL;
	} else {
		TBST* tree = new TBST();
		input.peek();
		while (!input.eof()) {
			string s = getWord(input);
			tree->insert(s);
		}
		return tree;
	}
}

string getWord(ifstream& input) {
	string s = "";
	char c = input.peek();

	while(isWhiteSpace(c) && !input.eof()) {
		input.get(); // ignore output
		c = input.peek();
	}

	if(!addChar(c)) {
		// c is punctuation, just return it as a token
		if(!isWhiteSpace(c))
			s += input.get();
		else {
			input.get();
		}
	}
	else {
		while (addChar(c) && !input.eof()) {
			s += input.get();
			c = input.peek();
		}
	}
	return s;
}

bool isWhiteSpace(char c) {
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool addChar(char c) {
	int x = int(c);
	return (x <= LOWER_CASE_UBOUND && x >= LOWER_CASE_LBOUND) 	||
		   (x <= UPPER_CASE_UBOUND && x >= UPPER_CASE_LBOUND) 	||
		   (x <= NUMBER_CASE_UBOUND && x >= NUMBER_CASE_LBOUND) ||
		   (x == APOSTROPHE);
}

void printTime(const char* name, double seconds) {
	cout << name << ": " << seconds << " sec" << endl;
	cout << FILE_OUTPUT_SEPARATOR << "\n" << endl;
}

NodeData** getMaxes(TBST* orig) {
	TBST* tree = new TBST(*orig);
	int size = tree->size() < MAX_NODE_PRINT ? tree->size() : MAX_NODE_PRINT;
	NodeData** maxes = new NodeData*[size];
	for (int i = size - 1; i >= 0; i--) {
		maxes[i] = new NodeData(*(tree->getMaxByFrequency()));
		tree->remove(maxes[i]->getToken());
	}
	delete tree;
	tree = NULL;
	return maxes;
}

NodeData** getMins(TBST* orig) {
	TBST* tree = new TBST(*orig);
	int size = tree->size() < MAX_NODE_PRINT ? tree->size() : MAX_NODE_PRINT;
	NodeData** mins = new NodeData*[size];
	for (int i = 0; i < size; i++) {
		mins[i] = new NodeData(*(tree->getMinByFrequency()));
		tree->remove(mins[i]->getToken());
	}
	delete tree;
	tree = NULL;
	return mins;
}

void printData(NodeData** data, int size) {
	for (int i = 0; i < size; i++) {
		cout << *data[i] << " ";
		if ((i + 1) % MAX_NODES_PER_LINE == 0)
			cout << endl;
	}
}


#endif