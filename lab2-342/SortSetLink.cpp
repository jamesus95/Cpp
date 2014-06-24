/*
 * File:   SortSetLink.cpp
 * Author: Test
 *
 * Created on January 21, 2014, 4:55 PM
 */

#include <stddef.h> //for NULL
#include "SortSetList.h"
#include "Node.h"
using namespace std;

SortSetList::SortSetList(): mainNodePointer(NULL) {
}

SortSetList::SortSetList(const SortSetList& orig) {
}

SortSetList::~SortSetList() {
}

void SortSetList::insert(unsigned int intToInsert) {
    Node* newNode = new Node();
    newNode->setItem(intToInsert);
    Node* current = mainNodePointer;
    if(current == NULL || current->getItem() > intToInsert) {
        newNode->setNextNode(mainNodePointer);
        mainNodePointer = newNode;
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
        newNode->setNextNode(current);
        previous->setNextNode(newNode);
    }
}

void SortSetList::remove(unsigned int remove) {
    Node* temp = mainNodePointer;
    if (temp != NULL) {
        if (temp->getItem() == remove) {
            mainNodePointer = mainNodePointer->getNextNode();
        }
        Node* prevTemp = temp;
        temp->getNextNode();
        while (temp != NULL && temp->getItem() < remove) {
            prevTemp = temp;
            temp = temp->getNextNode();
        }
        if (temp != NULL && temp->getItem() == remove) {
            prevTemp->setNextNode(temp->getNextNode());
        }
    }
}

bool SortSetList::isEmpty() {
    return mainNodePointer == NULL;
}

void SortSetList::print() {
    Node* temp = mainNodePointer;
    while(temp != NULL) {
        cout << temp->getItem() << " ";
        temp = temp->getNextNode();
    }
}

bool SortSetList::isInSet(unsigned int inSet) {
    Node* temp = mainNodePointer;
    while (temp != NULL) {
        if (temp->getItem() == inSet) {
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

SortSetList& SortSetList::operator+(SortSetList& rightSide) {
    SortSetArray* newSortedLinkPointer = new SortSetList();
    Node* cur = mainNodePointer;
    while (cur != NULL) {
        newSortedLinkPointer->insert(cur->getItem());
        cur = cur->getNextNode();
    }
    cur = rightSide.mainNodePointer;
    while (cur != NULL) {
        newSortedLinkPointer->insert(cur->getItem());
    }
    return *newSortedLinkPointer;
}

SortSetList& SortSetList::operator-(SortSetList& rightSide) {
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

SortSetList& SortSetList::operator*(SortSetList& rightSide) {
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

SortSetList& SortSetList::operator +=(SortSetList& rightSide) {
    Node* cur = rightSide.mainNodePointer;
    while (cur != NULL) {
        this->insert(cur->getItem());
    }
    return *this;
}

SortSetList& SortSetList::operator -=(SortSetList& rightSide) {
    Node* cur = mainNodePointer;
    Node* curRightSide = rightSide.mainNodePointer;
    while (cur != NULL) {
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide != NULL && curRightSide->getItem() == cur->getItem()) {
            this->remove(cur->getItem());
        }
    }
}

SortSetList& SortSetList::operator *=(SortSetList& rightSide) {
    Node* cur = mainNodePointer;
    Node* curRightSide = rightSide.mainNodePointer;
    while (cur != NULL) {
        while (curRightSide != NULL && curRightSide->getItem() < cur->getItem()) {
            curRightSide = curRightSide->getNextNode();
        }
        if (curRightSide != NULL && curRightSide->getItem() != cur->getItem()) {
            this->remove(cur->getItem());
        }
    }
}

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

bool SortSetList::operator !=(SortSetList& rightSide) {
    return !(*this == rightSide);
}

SortSetList& SortSetList::operator=(SortSetList& rightSide) {
    if (*this != rightSide) {
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