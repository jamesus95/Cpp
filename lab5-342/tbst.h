/**
 * @file tbst.h
 * Purpose: header files and includes for the tbst.cpp file
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef TBST_H
#define TBST_H

#include "node.h"
#include <iostream>
#include <string>

#define PREORDER 1
#define INORDER 0
#define POSTORDER -1
#define NODES_PER_LINE 7


using namespace std;

class TBST {

public:

    // constructors/destructor ------------------
    TBST();
    TBST(const TBST& other);
    ~TBST();
    
    // setters ----------------------------------
    bool insert(string token, int frequency = 1);
    bool remove(string token);
    TBST& operator = (TBST& other);
    
    // getters ----------------------------------
    bool contains(string token);
    bool isEmpty() const;
    NodeData* getMaxByFrequency();
    NodeData* getMinByFrequency();
    int size();
    int getHeight();
    int distanceTo(string token);

    // traversals -------------------------------
    void traverse(void (*func)(Node*, ostream&), ostream& output, int order);
    void iterativeInorder(void (*func)(Node*, ostream&), ostream& output);


    // ****************************************** Iterator
    class Iterator {                                       // with iterator
    
    public:
        Iterator();
        Iterator(Node* node, TBST* tree);
        ~Iterator();

        Iterator&   operator++();     // post-fix
        Iterator    operator++(int);  // pre-fix
        bool        operator!=(Iterator other);
        Node* getCurrentNode();
        bool removeCurrentNode();
        
    private:
        Node* currentPtr;
        TBST* tree;
    
    };
    // ****************************************************	

    // iterator helpers
    Iterator begin();
    Iterator end();

private:

    // fields -----------------------------------
    Node* root;
    int nodeCount;

    // constructor/destructo helpers ------------
    void recursiveDelete(Node* node);
    void recursiveCopy(Node* node);
    
    // setter helpers ---------------------------
    bool insert(Node* node, string token, int frequency);
    bool remove(Node* node, string token);
    bool removeRoot();
    bool rmLeaf(Node* node, bool left);
    bool rmNodeWithLeft(Node* node, bool left);
    bool rmNodeWithRight(Node* node, bool left);
    bool rmNodeWithBoth(Node* node, bool left);

    // traversal helpers ------------------------
    void preOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur);
    void inOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur);
    void postOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur);
    void recursivePrintTree(Node* node, int level);
    
    // getter helpers ---------------------------
    NodeData* getMaxByFrequency(Node* subroot);
    NodeData* getMinByFrequency(Node* subroot);
    bool contains(Node* node, string token);

};

#include "tbst.cpp"

#endif