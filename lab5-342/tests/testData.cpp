#include <iostream>
#include <string>
#include <assert.h>

#include "../nodeData.h"

using namespace std;

NodeData testConstructors();
NodeData testSetters(NodeData& B);

NodeData testConstructors() {
    NodeData A;
    assert(A.getToken() == "");
    assert(A.getCount() == 1);
    NodeData B("hello world");
    assert(B.getToken() == "hello world");
    NodeData C(B);
    assert(C.getToken() == "hello world");
    return B;
}

NodeData testSetters(NodeData& B) {
    NodeData A("a");
    A.decreaseCount();
    assert(A.getCount() == 0);
    
    int bCount = 7;
    while(B.getCount() < bCount) {
        B.increaseCount();
    }
    assert(B.getCount() == bCount);

    assert(A.getToken() < B.getToken());

    A = B;
    assert(A.getToken() == B.getToken());    
    return B;
}

int main() {
    NodeData A("a");
    cout << "A = " << A << "\t\tShould look like \"A = a-1\"" << endl;
    NodeData B = testConstructors();
    B = testSetters(B);
    cout << "Data class has successfully passed unit tests." << endl;
    return true;
}

