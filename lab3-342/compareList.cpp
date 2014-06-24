/**
@file compareList.cpp
@author James Murphree <murphs95@uw.edu>
@author Darren Hoehna <dhoehna@uw.edu>
@section Assignment Lab3
@section Due Feb. 9th 2013
@brief A list of pointers that point to nodes.
*/

#include "compareList.h"

/**
 * Default constructor.
 */
CompareList::CompareList() : root(NULL) {}

/**
 *
 * @param orig The CompareList to make a copy of.
 */
CompareList::CompareList(const CompareList& orig) {
    if(orig.root == NULL) {
        this->root = NULL;
    }
    else {
        this->root = this->copyNodes(*orig.root);
    }
}

/**
 * Deconstructor.
 */
CompareList::~CompareList() {removeAll();}

/**
 *
 * @param character The character in the file.
 * @param space The space number in the file.
 * @return True if the insertion was successful, otherwise false.
 * @pre character is a valid ASCII character
 * @post a new Node with character and space is added to the list.
 */
bool CompareList::insert(char character, int space) {
    if (space < 0) {
        return false;
    }
    Node* temp = root;
    if (temp == NULL) {
        root = new Node(new Data(character, space));
        return true;
    } else if (temp->getData()->getSpace() == space) {
        temp = NULL;
        return false;
    }
    while (temp->getNext() != NULL) {
        temp = temp->getNext();
        if (temp->getData()->getSpace() == space) {
            temp = NULL;
            return false;
        }
    }
    temp->setNext(new Node(new Data(character, space)));
    temp = NULL;
    return true;
}

/**
 *
 * @param character The character of the Data of the Node to remove.
 * @param space The space of the data of the Node to remove.
 * @return True if the removal was successful otherwise false.
 * @pre character is a valid ASCII character
 * @post the node with a character of character and a space of space
 *      is removed from the list.
 */
bool CompareList::remove(char character, int space) {
    if (space < 0) {
        return false;
    }
    Node* temp = root;
    if (temp != NULL) {
        Data* tempData = new Data(character, space);
        if (*(temp->getData()) == *tempData) {
            root = root->getNext();
            delete temp;
            temp = NULL;
            delete tempData;
            tempData = NULL;
            return true;
        }
        while (temp->getNext() != NULL) {
            if (*(temp->getNext()->getData()) == *tempData) {
                Node* temp2 = temp->getNext();
                temp->setNext(temp2->getNext());
                delete temp2;
                temp2 = NULL;
                delete tempData;
                tempData = NULL;
                return true;
            }
            temp = temp->getNext();
        }
        delete tempData;
        tempData = NULL;
    }
    return false;
}

/**
 *
 * @param rightSide The compareList to compare to.
 */
void CompareList::compareTo(const CompareList& rightSide,
                            std::ostream* output) const {
    Node* temp = root;
    Node* rightTemp = rightSide.root;
    int total = 0;
    int matches = 0;
    while (temp != NULL && rightTemp != NULL) {
        if (*temp == *rightTemp) {
            matches++;
            *output << "MATCH    ";
        } else {
            *output << "DIFF     ";
        }
        temp = temp->getNext();
        rightTemp = rightTemp->getNext();
        total++;
    }
    *output << std::endl << (static_cast<double>(matches) / total * 100)
              << " percent match" << std::endl << std::endl;
}

/**
* @param n The number of Nodes to print..
* @output The output stream to print to.
*/
void CompareList::print(int n, std::ostream* output) {
    Node* temp = root;
    int count = 0;
    if (temp != NULL && n > 0) {
        *output << *(temp->getData());
        temp = temp->getNext();
        count++;
        while (temp != NULL && count < n) {
            *output << ", " << *(temp->getData());
            temp = temp->getNext();
            count++;
        }
    }
    *output << std::endl;
}

/**
 *
 * @param rightSide The CompareList to test for equality.
 * @return True if the two CompareLists are equal, otherwise false.
 */
bool CompareList::operator == (const CompareList& rightSide) const {
    Node* temp = root;
    Node* rightTemp = rightSide.root;
    while (temp != NULL && rightTemp != NULL) {
        if (*temp != *rightTemp) {
            return false;
        }
        temp = temp->getNext();
        rightTemp = rightTemp->getNext();
    }
    if (temp == NULL && rightTemp == NULL) {
        return true;
    }
    return false;
}

/**
 *
 * @param rightSide The CompareList to test for inequality.
 * @return True if the two CompareLists are not equal, otherwise false.
 */
bool CompareList::operator != (const CompareList& rightSide) const {
    return !(*this == rightSide);
}

/**
 *
 * @param rightSide The CompareList to be assigned.
 * @return A reference to the CompareList to be assigned
 */
CompareList& CompareList::operator = (const CompareList& rightSide) {
    if (this != &rightSide) {
        removeAll();
        Node* temp = rightSide.root;
        while (temp != NULL) {
            this->insert(temp->getData()->getChar(),
                    temp->getData()->getSpace());
        }
    }
    return *this;
}

/**
 *
 * @param output A reference to the output stream.
 * @param rightSide The CompareList to print.
 * @return An output stream.
 */
std::ostream& operator << (std::ostream& output,
                           const CompareList& rightSide) {
    Node* temp = rightSide.root;
    if (temp != NULL) {
        output << *(temp->getData());
        temp = temp->getNext();
        while (temp != NULL) {
            output << ", " << *(temp->getData());
            temp = temp->getNext();
        }
    }
    return output;
}


void CompareList::removeAll() {
    while (root != NULL) {
        Node* temp = root;
        root = root->getNext();
        delete temp;
        temp = NULL;
    }
}

Node* CompareList::copyNodes(const Node& current) {
    if (current.getNext() != NULL) {
        return new Node(new Data(*(current.getData())),
                copyNodes(*(current.getNext())));
    } else {
        return new Node(new Data(*(current.getData())));
    }
}