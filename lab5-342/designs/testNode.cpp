/**
 * This file implements unit testing for the Node class.
 *
 * \version         1.2
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#include "../node.h"

#include <assert.h>

using namespace std;

void testSetters(Node* root);

void testGetters(Node* node1, Node* node2, Node* root, Node* sroot);

int main() {
     
    cout << "========================== testing Node class " << endl;
    string s = "abc";

    Node* node1 = new Node(s);
    Node* node2 = new Node(*node1);
    Node* root = new Node("root", node1, node2);
    Node* sroot = new Node("sroot", root, NULL, true);

    cout << "Constructors work fine." << endl;

    testGetters(node1, node2, root, sroot);

    cout << *root << "\tShould look like \"root-1\"" << endl;

    testSetters(root);

    delete node1; delete node2; delete root; delete sroot;

    cout << "Node passed all tests." << endl;
}


void testSetters(Node* root) {
    root->setLeft(NULL);
    root->setRight(NULL, true);
    assert(root->getLeft() == NULL);
    assert(root->getRight() == NULL);
    assert(root->isThreaded());
}

void testGetters(Node* node1, Node* node2, Node* root, Node* sroot) {
    assert(*(node1->getData()) == *(node2->getData()));
    assert(!root->isThreaded());
    assert(sroot->isThreaded());
    assert(root->getLeft()->getData() == node1->getData());
    node2->getData()->increaseCount();
    assert(root->getRight()->getData() == node2->getData());
}