

#include "bintree.h"
#include <iostream>

using namespace std;

int main() {

	// Valid constructors
	BinTree t1 = BinTree();
	//Node* n1 = new Node();
	NodeData* d1 = new NodeData();
	NodeData* d2 = new NodeData("D2");
	NodeData* d3 = new NodeData("D3");
	NodeData* d4 = new NodeData("D4");
	NodeData* d5 = new NodeData("D5");
	NodeData* d6 = new NodeData("D6");
	//Node* n5 = new Node(d5);
	//Node* n2 = new Node(d2);
	//Node* n3 = new Node(d3, n2);
	//Node* n4 = new Node(d4, n3, n5);
	t1.insert(d3);
	t1.insert(d2);
	t1.insert(d4);
	BinTree t2 = BinTree(t1);
	NodeData* dC = new NodeData(*d5);
	//Node* nC = new Node(*n4);

	cout << t1 << endl;
	cout << t2 << endl;
	cout << endl;

	cout << *d5 << endl;
	cout << *dC << endl;
	cout << endl;

	//cout << *n4 << endl;
	//cout << *nC << endl;
	cout << endl;

	// insert duplicate
	t1.insert(d3);

	cout << t1 << endl;

	//t1.makeEmpty();
	//t1.makeEmpty();

	NodeData* temp;
	t1.retrieve(*d3, temp);
	cout << *temp << endl;

	t1.retrieve(*d2, temp);
	cout << *temp << endl;

	cout << t1.isEmpty() << "  " << t1.size() << endl;
	// t1.makeEmpty();
	cout << t1.isEmpty() << "  " << t1.size() << endl;

	cout << t1.getDepth(*d2) << endl;
	cout << t1.getDepth(*d3) << endl;
	cout << t1.getDepth(*d5) << endl;

	delete d1;
	delete d5;
	delete d6;
	delete dC;

}
