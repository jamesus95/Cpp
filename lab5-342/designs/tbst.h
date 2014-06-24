/**
 * This class defines a Threaded Binary Search Tree.
 * Among supported functionalities are:
 * - inorder Iterator
 * - Recursive traversal inorder, preorder, postorder
 * - self-rebalancing
 * - tree rotation (soon)
 * - functional programming implementation (soon)
 *
 * \version         2.0
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#ifndef TBST_H
#define TBST_H

#include "node.h"

using namespace std;

class TBST {

public:
	
	TBST();
	TBST(const TBST& other);
    TBST(const Node* otherRoot);
    TBST operator=(TBST& other);
	~TBST();

    // mutators
	bool insert(string token);
	bool remove(string token);
    void selfBalance();

    // accessors
	bool contains(string token) const;
	bool isEmpty() const;
    int  distanceTo(string targetToken);
    int  size();
    int  getHeight();

    // traversors
	void iterativeInorder(void (*func)(Node*));            // iterative
	void traverse(void (*func)(Node*), int order = 0);     // recursive
    void traverse(void (*func)(Node*), Node* cur, int order); // helper
    class Iterator {                                       // with iterator
    public:
        Iterator& operator++();     // post-fix
        Iterator  operator++(int);  // pre-fix
        Node* get();
        Iterator(Node* home = root); // default to start iterator at root
        ~Iterator();
    private:
        Node* currentPtr;
    };
    // iterator helpers
    Iterator begin();
    Iterator end();
	

private:
	Node* root;
    Node* Iterator_End_Node; // node AFTER the final Node in the tree
    int nodeCount;

	Node* popUp(node* node);
	// Node* find(Node* (*f)(Node*,string), Node* cur, bool findSpot, string s);
    Node* findParentFor(string s); 
	Node* contains(Node* node, string s);

	void preOrder(void (*f)(), Node* cur = root);
	void inOrder(void (*f)(), Node* cur = root);
	void postOrder(void (*f)(), Node* cur = root);

    // helpers
    void insert(Node* toInsert, Node* insertTo);
    void remove(Node* toRemove, Node* removeFrom);
    void recursiveDelete(Node* subroot);
};

#include "tbst.cpp"

#endif