#include "../node.h"

#include <assert.h>

using namespace std;

void testSetters(Node* root);

void testGetters(Node* node1, Node* copy1, Node* root, Node* sroot);

int main() {
     
    cout << "========================== testing Node class " << endl;
    string s = "abc";

    Node* node1 = new Node(s);
    Node* copy1 = new Node(*node1);
    Node* root = new Node("root", 5, node1, copy1, false, false);
    Node* sroot = new Node("sroot", 4, root, NULL, true, false);

    cout << "Constructors work fine." << endl;

    testGetters(node1, copy1, root, sroot);

    cout << *root << "\tShould look like \"root-1\"" << endl;

    testSetters(root);

    delete node1; delete copy1; delete root; delete sroot;

    cout << "Node passed all tests." << endl;
}


void testGetters(Node* node1, Node* copy1, Node* root, Node* sroot) {
    assert(*(node1->getData()) == *(copy1->getData()));
    
    assert(!root->isLeftThreaded());
    assert(!root->isRightThreaded());

    assert(sroot->isLeftThreaded());
    assert(!sroot->isRightThreaded());
    
    //verify that node1 is root's left child
    assert(root->getLeft()->getData() == node1->getData());
    //verify that copy1 is root's right child
    copy1->getData()->increaseCount();
    assert(root->getRight()->getData() == copy1->getData());
}


void testSetters(Node* root) {
    // arbitrary modifications
    root->setLeft(NULL, false);
    root->setRight(NULL, true);

    // test accordingly
    assert(root->getLeft() == NULL);
    assert(root->getRight() == NULL);
    assert(!root->isLeftThreaded());
    assert(root->isRightThreaded());
}
