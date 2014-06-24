/**
 * @file BinTree.h
 * Purpose: header files and includes for the BinTree.cpp file
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        April 12 2014
 * @copyright   WTFPLv2.1
 */

#ifndef BinTree_H
#define BinTree_H

#include "generic.h"
#include <iostream>
#include <string>
#include <sstream>

#define PREORDER 1
#define INORDER 0
#define POSTORDER -1


using namespace std;

/**
 * @class BinTree bintree.h
 * Dynamic, list-based Binary Search Tree. The tree handles external data types
 * via pointers. Proper functionality of the data structure assumes that the
 * data class supports:
 * --- operator > < == !=
 * --- operator<<
 *
 * Data objects need to be instantiated external to the tree, in the client.
 * The tree then handles storage, management, and destruction of the data.
 */

class BinTree {
    
friend ostream& operator<<(ostream&, const BinTree&);


// private BST members =====================================================
// =========================================================================
private:

    class Node {

    public:
        // constructors / destructors
        Node(Generic* data = NULL, Node* left = NULL, Node* right = NULL);
        //Node(const Node& other);
        ~Node();

        // setters ----------------------------------
        void setLeft(Node* left);
        void setRight(Node* right);
        void setDataToNULL();           // "nullify" the data without deletion

        // getters ----------------------------------
        Node* getLeft() const;
        Node* getRight() const;
        Generic* getData() const;
        bool isLeaf() const;
        bool hasLeftChild() const;
        bool hasRightChild() const;

        // comparision operators --------------------
        bool operator==(const Node& other) const;
        bool operator!=(const Node& other) const;

    private:

        // fields -----------------------------------
        Generic* data;
        Node* left;
        Node* right;

    };

    // fields -----------------------------------
    Node* root;
    int  nodeCount;

    // constructor/destructor helpers ------------
    void preorderCopy(Node*, Node*);  // copy another tree from top down
    void postorderDelete(Node* node); // delete the tree content from bottom up
    
    // mutator helpers ---------------------------
    bool insertHelper(Node*, Generic*);    // recursive insertion, no dups
    bool removeHelper(Node*, Generic&);
    void arrayToBSTreeHelper(Generic*[], int, int);
    
    // accessor helpers ---------------------------
    bool retrieve(Node*, Generic&, Generic*&);
    int  getDepthHelper(Generic& target, Node* cur, int level);
    int  getArraySize(Generic* nodeArray[]);
    bool subtreeEqual(Node*, Node*) const;      // operator== helper

    // mass retrieves
    void toStringInorder(stringstream&, Node*) const;
    void sideways(Node*, int) const;       // displaySideways() helper
    Node* bstreeToArrayHelper(Node*, int*, Generic*[]);



// public BST members ======================================================
// =========================================================================
public:

    // constructors/destructor ------------------
    BinTree();
    //BinTree(const BinTree& other);
    ~BinTree();
    
    // setters ----------------------------------
    bool insert(Generic* newData);     // deals only with premade data objects
    bool remove(Generic& oldData);
    void displaySideways() const;       // public interface
    void makeEmpty();                   // clean up the tree
    BinTree& operator=(const BinTree& other);
    void arrayToBSTree(Generic*[]);
    void bstreeToArray(Generic*[]);

    // getters ----------------------------------
    bool isEmpty() const;
    bool retrieve(Generic&, Generic*&);
    int  size();
    int  getDepth(Generic&);

    string toStringInorder() const;     // public toString()
    bool operator==(const BinTree& rhs) const;
    bool operator!=(const BinTree& rhs) const;

    // traversals -------------------------------
    // TODO: Look into functors and implement this in spare time

    Node* getRoot() const;

};


#endif