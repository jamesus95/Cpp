/**
 * This class defines the Node class to be used in a Threaded 
 * Binary Search Tree.
 *
 * \version         1.1
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

class Node {

    Node::Node(string token) {
        create a new node with count 1 and passed in token
    }

    Node::Node(string token, Node* left, Node* right) {
        create a new node with count 1 and passed in token
        set left and right children to passed in values
    }

    Node::Node(string token, Node* left, Node* right, bool threadStatus) {
        create a new node with count 1 and passed in token
        set left and right children to passed in values
        set thread flag to the argument
    }

    Node::Node(const Node& other) {
        create new copy of passed in node
    }

    Node::~Node() {
        delete the NodeData inside, NULL the pointers
        randomize the other attribute
    }

    /**
     * Set the left pointer to the argument Node
     * 
     * @param left       pointer to the Node to become this Node's left child
     */
    void Node::setLeft(Node* left) {this->left = left;}
    void Node::setRight(Node* right, bool threadStatus) {
        this->right = right;
        this->isThread = threadStatus;
    }

    Node* Node::getLeft() const {return left;}
    Node* Node::getRight() const {return right;}
    NodeData* Node::getData() const {return data;}

    bool Node::isThreaded() const {return isThread;}

    ostream& Node::operator<<(ostream& out, const Node& node) {
        append NodeData content to ostream
        return out;
    } 

};