

#include "tbst.h"

void makeTree(TBST* tree) {
	tree->insert("o");
	tree->insert("g");
	tree->insert("c");
//	tree->insert("a");
//	tree->insert("e");
	tree->insert("k");
//	tree->insert("i");
//	tree->insert("m");
	tree->insert("x");
	tree->insert("s");
//	tree->insert("q");
//	tree->insert("u");
	tree->insert("y");
//	tree->insert("x");
//	tree->insert("z");
	tree->insert("h");
	tree->insert("j");
	tree->insert("i");
	// tree->insert("l");
	// tree->insert("t");
	// tree->insert("w");
	// tree->insert("u");
}

void remove(TBST* tree, string s) {
	tree->remove(s);
	tree->recursivePrintTree();
	cout << "\n" << endl;
}

int main() {

	TBST* test = new TBST();
	makeTree(test);
	test->recursivePrintTree();
	cout << "\n" << endl;
	// remove(test, "q");
	// remove(test, "g");
	// remove(test, "z");
	// remove(test, "o");
	//remove(test, "i");

	// 2 child delete
	// remove(test, "g");
	// remove(test, "w");

	// ROOT DELETION
	// remove(test, "o");
	// remove(test, "k");
	// remove(test, "g");
	// remove(test, "c");
	// remove(test, "w");
	// remove(test, "s");
	// remove(test, "y");
	// test->insert("a");
	// remove(test, "b");

	// Replace node has a child
	// remove(test, "s");
	remove(test, "k");

}