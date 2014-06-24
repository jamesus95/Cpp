/**
 * @file SortSetList.cpp
 * @author James Murphree and Darren
 * 1/24/2014
 * CSS 342
 */

#ifndef SORTSETLIST_CPP
#define SORTSETLIST_CPP

#include "SortSetList.h"

// Constructors

// empty constructor
SortSetList::SortSetList(): mainNodePointer(NULL) {}

// 1 input constructor
SortSetList::SortSetList(int input1):mainNodePointer(NULL) {
    int input[] = {input1};
    initialize(input, 1);
}

// 2 input constructor
SortSetList::SortSetList(int input1, int input2)
        :mainNodePointer(NULL) {
    int input[] = {input1, input2};
    initialize(input, 2);
}

// 3 input constructor
SortSetList::SortSetList(int input1, int input2, int input3)
        :mainNodePointer(NULL) {
    int input[] = {input1, input2, input3};
    initialize(input, 3);
}

// 4 input constructor
SortSetList::SortSetList(int input1, int input2, int input3, int input4
        ):mainNodePointer(NULL) {
    int input[] = {input1, input2, input3, input4};
    initialize(input, 4);
}

// 5 input constructor
SortSetList::SortSetList(int input1, int input2, int input3, int input4,
        int input5):mainNodePointer(NULL) {
    int input[] = {input1, input2, input3, input4, input5};
    initialize(input, 5);
}

// copy constructor
SortSetList::SortSetList(const SortSetList& orig) {
    if (orig.mainNodePointer == NULL) {
        this->mainNodePointer = NULL;
    } else {
        this->mainNodePointer = copyNodes(*orig.mainNodePointer);
    }
}

// destructor
SortSetList::~SortSetList() {
    if (mainNodePointer != NULL) {
        destruction(mainNodePointer);
        delete mainNodePointer;
        mainNodePointer = NULL;
    }
}

// Methods

// insert
bool SortSetList::insert(int intToInsert) {
    if (intToInsert < 0) {
        return false;
    }
    Node* current = mainNodePointer;
    if(current == NULL || current->getItem() > intToInsert) {
        mainNodePointer = new Node(intToInsert, mainNodePointer);
        return true;
    }
    else {
        Node* previous = current;
        current = current->getNextNode();
        /*Go through the while loop.  Once we are at our place, we exit it.*/
        while(current != NULL && current->getItem() < intToInsert) {
            previous = current;
            current = current->getNextNode();
        }
        /*By this time, we are at our correct position in the set.*/
        if (current == NULL || current->getItem() != intToInsert) {
            previous->setNextNode(new Node(intToInsert, current));
            return true;
        }
    }
    return false;
}

// remove
bool SortSetList::remove(int remove) {
    if (remove < 0) {
        return false;
    }
    Node* temp = mainNodePointer;
    if (temp != NULL) {
        if (temp->getItem() == remove) {
            Node* prevTemp = mainNodePointer;
            mainNodePointer = mainNodePointer->getNextNode();
            delete prevTemp;
            prevTemp = NULL;
            return true;
        }
        Node* prevTemp = temp;
        temp->getNextNode();
        while (temp != NULL && temp->getItem() < remove) {
            prevTemp = temp;
            temp = temp->getNextNode();
        }
        if (temp != NULL && temp->getItem() == remove) {
            prevTemp->setNextNode(temp->getNextNode());
            delete temp;
            temp = NULL;
            return true;
        }
    }
    return false;
}

// isEmpty
bool SortSetList::isEmpty() {
    return mainNodePointer == NULL;
}

// isInSet
bool SortSetList::isInSet(int inSet) {
    Node* temp = mainNodePointer;
    while (temp != NULL) {
        if (temp->getItem() == inSet) {
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

// +
SortSetList& SortSetList::operator+(const SortSetList& rightSide) const  {
    SortSetList* newSortedLinkPointer = new SortSetList();
    Node* cur = mainNodePointer;
    while (cur != NULL) {
        newSortedLinkPointer->insert(cur->getItem());
        cur = cur->getNextNode();
    }
    cur = rightSide.mainNodePointer;
    while (cur != NULL) {
        newSortedLinkPointer->insert(cur->getItem());
        cur = cur->getNextNode();
    }
    return *newSortedLinkPointer;
}

// -
SortSetList& SortSetList::operator-(const SortSetList& rightSide) const {
    SortSetList* newSortedLinkPointer = new SortSetList();
    Node* cur = mainNodePointer;
    while (cur != NULL) {
        Node* curRightSide = rightSide.mainNodePointer;
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide != NULL && curRightSide->getItem() > cur->getItem()) {
            newSortedLinkPointer->insert(cur->getItem());
        }
        cur = cur->getNextNode();
    }
    return *newSortedLinkPointer;
}

// *
SortSetList& SortSetList::operator*(const SortSetList& rightSide) const {
    SortSetList* newSortedLinkPointer = new SortSetList();
    Node* cur = mainNodePointer;
    while (cur != NULL) {
        Node* curRightSide = rightSide.mainNodePointer;
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide != NULL && curRightSide->getItem() == cur->getItem()) {
            newSortedLinkPointer->insert(cur->getItem());
        }
        cur = cur->getNextNode();
    }
    return *newSortedLinkPointer;
}

// +=
SortSetList& SortSetList::operator +=(SortSetList& rightSide) {
    Node* cur = rightSide.mainNodePointer;
    while (cur != NULL) {
        this->insert(cur->getItem());
        cur = cur->getNextNode();
    }
    return *this;
}

// -=
SortSetList& SortSetList::operator -=(SortSetList& rightSide) {
    Node* cur = mainNodePointer;
    Node* curRightSide = rightSide.mainNodePointer;
    while (cur != NULL) {
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide != NULL && curRightSide->getItem() == cur->getItem()) {
            cur = cur->getNextNode();
            this->remove(curRightSide->getItem());
        } else {
            cur = cur->getNextNode();
        }
    }
    return *this;
}

// *=
SortSetList& SortSetList::operator *=(SortSetList& rightSide) {
    Node* cur = mainNodePointer;
    Node* curRightSide = rightSide.mainNodePointer;
    while (cur != NULL) {
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide == NULL || curRightSide->getItem() != cur->getItem()) {
            int removeInt = cur->getItem();
            cur = cur->getNextNode();
            this->remove(removeInt);
        } else {
            cur = cur->getNextNode();
        }
    }
    return *this;
}

// ==
bool SortSetList::operator ==(SortSetList& rightSide) {
    Node* cur = mainNodePointer;
    Node* curRightSide = rightSide.mainNodePointer;
    while (cur != NULL && curRightSide != NULL) {
        if (cur->getItem() != curRightSide->getItem()) {
            return false;
        }
        cur = cur->getNextNode();
        curRightSide->getNextNode();
    }
    if (cur == NULL && curRightSide == NULL) {
        return true;
    }
    return false;
}

// !=
bool SortSetList::operator !=(SortSetList& rightSide) {
    return !(*this == rightSide);
}

// =
SortSetList& SortSetList::operator=(SortSetList& rightSide) {
    if (this != &rightSide) {
        while (mainNodePointer != NULL) {
            this->remove(mainNodePointer->getItem());
        }
        Node* cur = rightSide.mainNodePointer;
        while (cur != NULL) {
            this->insert(cur->getItem());
            cur = cur->getNextNode();
        }
    }
    return *this;
}

// <<
std::ostream& operator<<(ostream& output, const SortSetList& rightSide) {
    bool isFirst = true;
    Node* listNodePointer = rightSide.mainNodePointer;
    while(listNodePointer != NULL) {
        if(isFirst) {
            output << listNodePointer->getItem();
            isFirst = false;
        }
        else {
            output << ", " << listNodePointer->getItem();
        }
        listNodePointer = listNodePointer->getNextNode();
    }
    return output;
}

// >>
std::istream& operator>>(istream& input, SortSetList& rightSide) {
    int getInt = -1;
    input >> getInt;
    rightSide.insert(getInt);
    return input;
}

// Private Methods

// destructor helper
void SortSetList::destruction(Node* current) {
    if (current->getNextNode() != NULL) {
        destruction(current->getNextNode());
        delete current->getNextNode();
        current->setNextNode(NULL);
    }
}

// initializer
void SortSetList::initialize(int input[], int count) {
    for(int index = 0; index< count; index++) {
        this->insert(input[index]);
    }
}

// copy constructor helper
Node* SortSetList::copyNodes(Node& current) {
    if (current.getNextNode() != NULL) {
        return new Node(current.getItem(), copyNodes(*current.getNextNode()));
    } else {
        return new Node(current.getItem());
    }
}

#endif