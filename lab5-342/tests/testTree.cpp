#include "../tbst.h"
#include <assert.h>
#include <string>

#define INORDER 0
#define PREORDER 1
#define POSTORDER -1

void increaseCount();
void printNode();
void testAccessors();
void testTraversors();

int main() {
    // ================= test constructors and mutators
    TBST tree1;
    for(int i=0; i < 7; i++) {
        tree1.insert(str(i));
    }
    assert(tree1.remove("0"));
    TBST tree2(tree1);
    TBST tree3 = tree2;

    int oldHeight = tree1.getHeight();
    tree1.selfBalance();
    assert(oldHeight < tree1.getHeight());

    // ================= test accessors
    testAccessors(tree1, tree2);

    // ================= test traversors
    testTraversors(tree1, tree2, tree3);
}

void increaseCount(Node* node) {
    if(node != NULL)
        node->getData()->increaseCount();
}

void printNode(Node* node) {
    if(node != NULL)
        cout << node << " ";
}

void testAccessors(TBST& tree1, TBST& tree2) {
    assert(tree1.contains("4"));
    TBST emptyTree;
    assert(emptyTree.isEmpty());
    assert(tree2.distanceTo("5") == 4);
}

void testTraversors(TBST& tree1, TBST& tree2, TBST& tree3) {
    // ------- with iterator
    TBST::Iterator iter = tree1.begin();
    while(iter != tree1.end()) {
        cout << *(iter.get()) << " ";
        iter++;
    }
    cout << "\nexpects: 1-1 2-1 3-1 4-1 5-1 6-1" << endl;

    // O(nlogn) remove algorithm (use iterator for O(n) instead)
    for(int i=0; i < 7; i+=2) {
        assert(tree2.contains(str(i)));
        assert(tree2.remove(str(i)));
    }

    // ------- with threads and function pointers
    tree2.iterativeInorder(increaseCount);  // function pointer
    tree2.iterativeInorder(printNode);      // function pointer
    cout << "\nexpects: 1-2 3-2 5-2" << endl;

    // ------- with recursion
    tree3.traverse(printNode, INORDER);
    cout << "\nIn order, expects: 1-1 2-1 3-1 4-1 5-1 6-1" << endl;
    tree3.traverse(printNode, POSTORDER);
    cout << "\nPost order, expects: 6-1 5-1 4-1 3-1 2-1 1-1" << endl;
    tree3.traverse(increaseCount, PREORDER);
    tree3.traverse(printNode, PREORDER);
    cout << "\nPre order, expects: 1-2 2-2 3-2 4-2 5-2 6-2" << endl;
}