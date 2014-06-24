/**
 * @file node.cpp
 * Purpose: implementation file for the Node class.
 * 
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef NODE_CPP
#define NODE_CPP

/**
 * @brief Default constructor
 * @details Defaults frequency value to 1 for convenience
 * 
 * @param token string object to store as token
 * @param   frequency integer value indicating frequency of occurrence 
 *          for token
 */
Node::Node(string token, int frequency) :  left(NULL), right(NULL),
                            leftThread(true), rightThread(true) {
    data = new NodeData(token, frequency);
}

/**
 * @brief Detailed constructor
 * @details Sets every field to a specified value
 * 
 * @param token string object to store as token
 * @param   frequency integer value indicating frequency of occurrence 
 *          for token * @param left [description]
 * @param left pointer to the left child Node         
 * @param right pointer to the right child Node
 * @param leftThreadStatus bool value indicating whether
 *          the left-child pointer is a thread
 * @param rightThreadStatus bool value indicating whether
 *          the right-child pointer is a thread
 */
Node::Node( string token, int frequency,
            Node* left, Node* right,
            bool leftThreadStatus, bool rightThreadStatus) :
                left(left), right(right),
                leftThread(leftThreadStatus), rightThread(rightThreadStatus) {
    data = new NodeData(token, frequency);
}

/**
 * @brief copy constructor
 * @details make a new NodeData object with the same content, copy every other
 * attributes as well
 * 
 * @param other other Node to copy from, passed in by reference
 */
Node::Node(const Node& other) {
    data = new NodeData(*other.data);
    left  = other.left;
    right = other.right;
    leftThread = other.leftThread;
    rightThread = other.rightThread;
}

/**
 * @brief default destructor
 * @details delete the NodeData object and clear all pointers
 */
Node::~Node() {
    delete data;
    data = NULL;
    left = NULL;
    right = NULL;
    leftThread = false;
    rightThread = false;
}

void Node::setLeft(Node* left, bool leftThreadStatus) {
    this->left = left;
    this->leftThread = leftThreadStatus;
}

/**
 * @brief Modifies the right pointer of the Node
 * @details Modifies the right pointer as well as its thread status as
 *          specified.
 * 
 * @param right pointer to a Node to become this Node's right child
 * @param threadStatus flag whether the right pointer will now be a thread.
 */
void Node::setRight(Node* right, bool rightThreadStatus) {
    this->right = right;
    this->rightThread = rightThreadStatus;
}

/**
 * @brief public getter for left child
 * @return pointer to the left child
 */
Node* Node::getLeft() const {return left;}

/**
 * @brief public getter for right child
 * @return pointer to the right child
 */
Node* Node::getRight() const {return right;}

/**
 * @brief public getter for content NodeData
 * @return pointer to the NodeData object
 */
NodeData* Node::getData() const {return data;}

/**
 * @brief public getter to distinguish a normal left pointer and a threaded one
 * @details needed for proper traversal through the tree.\n
 * NULL pointers are considered threaded.
 * @return `true` if the left pointer does not point to a child, but is a
 * thread instead.
 */
bool Node::isLeftThreaded() const {return leftThread;}

/**
 * @brief public getter to distinguish a normal left pointer and a threaded one
 * @details needed for proper traversal through the tree.\n
 * NULL pointers are considered threaded.
 * @return `true` if the left pointer does not point to a child, but is a
 * thread instead.
 */
bool Node::isRightThreaded() const {return rightThread;}

/**
 * @brief logic check to determine the existence of a left child
 * @details helper method for traversal through the tree.
 * @return `true` if the Node has a left child (determined with status
 * of the left pointer)
 */
bool Node::hasLeftChild() const {
    return (left != NULL) && (!isLeftThreaded());
}

/**
 * @brief logic check to determine the existence of a right child
 * @details helper method for traversal through the tree.
 * @return `true` if the Node has a right child (determined with status
 * of the right pointer)
 */
bool Node::hasRightChild() const {
    return (right != NULL) && (!isRightThreaded());
}

/**
 * @brief logic check to determine whether the current node is a leaf
 * @details helper to make code on the outside world more readable
 * @return `true` if the Node has no children, `false` otherwise
 */
bool Node::isLeaf() const {
    return  !hasLeftChild() && !hasRightChild();
}

/**
 * @brief overloaded output operator
 * @details append the content of the NodeData to the outstream
 * 
 * @param out ostream object to append content to
 * @param node node containing content to be appended
 */
ostream& operator<< (ostream& out, const Node& node) {
    out << *(node.getData());
    return out;
} 

/**
 * @brief equality comparison operator
 * @details compare for equality between two NodeDatas
 * 
 * @param other reference to the other NodeData object to compare against
 * @return `true` if the two Nodes have the exact same content, `false`
 *          otherwise
 */
bool Node::operator == (const Node& other) const {
    return &data == &other.data;
}

/**
 * @brief inequality comparison operator
 * @details compare for inequality between two NodeDatas. Just the opposite of
 * operator==
 * 
 * @param other reference to the other NodeData object to compare against
 * @return `true` if the two Nodes do not have the exact same content, `false`
 *          otherwise
 */
bool Node::operator != (const Node& other) const {
    return !(*this == other);
}

#endif