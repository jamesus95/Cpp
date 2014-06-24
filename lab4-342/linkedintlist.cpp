/**
 * \file linkedintlist.cpp
 * @details Implementation of a basic linked list of integers.
 */

/**
 * @mainpage Introduction
 * 
 * Project: 	Sorting Algorithms\n
 * Objective: 	Implement and compare performance among different sorting
 * 				algorithms:\n
 * 				- recursivemergesort.cpp
 * 				- iterativemergesort.cpp
 * 				- quicksort.cpp
 * 				- heapsort.cpp
 * 				- mergesortlinkedlist.cpp
 * 				
 * \version		2.12
 * \author		James Murphree
 * \author		Vu Dinh
 * \date 		Feb 23 2014
 * \copyright	WTFPLv2.1
 * 
 */

#ifndef LINKED_INT_LIST_CPP
#define LINKED_INT_LIST_CPP

#include <iostream>

LinkedIntList::LinkedIntList() {
	root = NULL;
	size = 0;
}

LinkedIntList::~LinkedIntList() {
	Node* temp = NULL;
	while(root != NULL) {
		temp = root;
		root = root->getNext();
		delete temp;
	}
	temp = NULL;
	size = 0;
}

void LinkedIntList::insert(int n) {
	Node* newNode = new Node();
	newNode->setData(n);
	newNode->setNext(NULL);
	if (root == NULL) {
		root = newNode;
	} else {
		Node* temp = root;
		while (temp->getNext() != NULL) {
			temp = temp->getNext();
		}
		temp->setNext(newNode);
	}
	size++;
}

Node* LinkedIntList::getRoot() {return root;}
int LinkedIntList::getSize(){return size;}
bool LinkedIntList::isSorted() {
    bool sorted = true;
    for(Node* curr = root; curr->getNext() != NULL; curr = curr->getNext()) {
        if(curr->getData() > curr->getNext()->getData()) {
            sorted = false; break;
        }
    }
    return sorted;
}
void LinkedIntList::setRoot(Node* root) {this->root = root;}

void LinkedIntList::print() {
	Node* temp = root;
	while (temp != NULL) {
		cout << temp->getData() << " ";
		temp = temp->getNext();
	}
	cout << endl;
}

Node::Node() {
	data = 0;
	next = NULL;
}

Node::Node(Node* other) {
	data = other->data;
	next = other->next;
}

Node::~Node() {
	data = -37;
	next = NULL;
}

int Node::getData() {return data;}
Node* Node::getNext() {return next;}
void Node::setData(int data) {this->data = data;}
void Node::setNext(Node* next) {this->next = next;}

#endif