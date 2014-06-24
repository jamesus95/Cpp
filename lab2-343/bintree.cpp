/**
 * @file bintree.cpp
 * Purpose: Implementation file for the BinTree class
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        April 14 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the public routine(s)
 * that uses them.
 */

/**
 * @mainpage Binary Search Tree
 * 
 * @section Introduction
 * A dynamic, list-based implementation of the Binary Search Tree data
 * structure. The tree stores and manages the data object from the client 
 * via pointers.
 * 
 * @section Assumptions
 * Data class must have `operator==`, `operator>`, `operator!=`, `operator<<`
 *
 * @section Notes
 * @warning The tree class does not support remove() yet. One workaround is to
 *          move all the data to an array, remove / overwrite the desired
 *          target, then rebuild the tree. This won't preserve the tree's
 *          structure, as the new tree will be balanced.
 *
 * @warning The tree <-> array transfer routines do not support arrays 
 *          holding more than 100 items.
 */

#include "bintree.h"
#include <new>      // catching bad_alloc

#define NODE_INI_ERR_MSG "DEBUG: FAILED to allocate memory for Node"
#define ARRAYSIZE 100


// ************************************ CONSTRUCTORS/DESTRUCTOR

// --------------------------------- default constructor
/**
 * @brief default constructor
 * @details creates an empty BinTree
 */
BinTree::BinTree() {
    root = NULL;
    nodeCount = 0;
}

// --------------------------------- copy constructor
/**
 * @brief Copy constructor
 * @details Creates a copy of the passed in BinTree. Uses a private helper
 *          routine to perform pre-order copy.
 *          Note: The copying procedure makes the node-connection manually
 *          along the way from top down. Utilizing insert() is simpler to code,
 *          but is less efficient.
 *
 * @param other BinTree tree to copy
 */
BinTree::BinTree(const BinTree& other) {
    if (other.root != NULL) {
        root = new Node(*(other.root));
        preorderCopy(root, other.root);
    }
}

// --------------------------------- copy constructor helper
/**
 * @brief   Private helper to build the tree recursively in pre-order.
 * @details Allocates new content and stores it in one pass through the tree.
 *          No back-and-forth traversing involved.
 *
 * @param curr pointer to current Node (root of the subtree to be built)
 * @param origCurr pointer to the Node with the original content to be copied.
 */
void BinTree::preorderCopy(Node* curr, Node* origCurr) {
     if (origCurr->getLeft() != NULL) {
        curr->setLeft(new Node(*(origCurr->getLeft())));
        preorderCopy(curr->getLeft(), origCurr->getLeft());
     }
     if (origCurr->getRight() != NULL) {
        curr->setRight(new Node(*(origCurr->getRight())));
        preorderCopy(curr->getRight(), origCurr->getRight());
     }
}

// --------------------------------- destructor
/**
 * @brief destructor
 * @details releases all BinTree Nodes' memory
 */
BinTree::~BinTree() {
    makeEmpty();
}

// --------------------------------- destructor helper
/**
 * @brief helper for destructor
 * @details recursively delete the nodes in a tree from bottom up post-order
 *
 * @param node The node to delete and recurse on
 */
void BinTree::postorderDelete(Node* node) {
    if (node != NULL) {
        if(node->hasLeftChild())
            postorderDelete(node->getLeft());
        if(node->hasRightChild())
            postorderDelete(node->getRight());
        delete node;
        node = NULL;
    }
}

// --------------------------------- assignment operator=
/**
 * @brief Assignment operator
 * @details makes a deep copy of the rhs with the copy constructor and swap
 *          private, internal resources. The copy goes out of scope by the
 *          end of the routine and destroys the lhs's old resources together
 *          with it, preventing memory leaks.
 *
 * @param rhs reference to the rhs tree to be copied
 * @return reference to the lhs tree
 */
BinTree& BinTree::operator=(const BinTree& rhs) {
    if(this != &rhs) {
        BinTree copy(rhs);

        // swap roots
        Node* temp = root;
        root = copy.root;
        copy.root = temp;
        temp = NULL;

        // copy count over (doesn't really need swapping)
        nodeCount = copy.nodeCount;
    }
    return *this;
}


// ***********************************************************
// ****************************************** PUBLIC METHODS *
// ***********************************************************

// --------------------------------- public insert()
/**
 * @brief inserts a value into the BinTree
 * @details inserts a value into the BinTree, adding a new entry
 * if one does not already exist, and incrementing the entry
 * if it does exist. Running time O(logn).
 *
 * @param data  pointer to the data object to be inserted
 * @return `true` if insertion is successful, `false` otherwise.
 *          Insertion fails when new entry is equal to a parent
 *          with 2 children.
 */
bool BinTree::insert(NodeData* data) {
    if(data != NULL) {
        if (this->root == NULL) {
            // insert to root
            try {
                root = new Node(data);
                nodeCount++;
                return true;
            } catch (std::bad_alloc& ba) {
                cout << NODE_INI_ERR_MSG << endl;
                return false;
            }
        } else {
            return insertHelper(this->root, data);    // recursive helper
        }
    } else {
        return false;
    }
}


// --------------------------------- insert helper
/**
 * @brief helper for the public insert()
 * @details recursively search for the position to insert, then insert it
 * correctly once the base case is reached.
 *
 * @param node The node at which to start the search
 * @param token The token to be inserted into the tree
 * @param frequency the frequency that accompanies the token, also
 *          to be inserted into the tree
 * @return insertion success status
 */
bool BinTree::insertHelper(Node* node, NodeData* data) {
    NodeData* ndata = node->getData();
    if (*ndata > *data) {     // assumes operator> exists
        // ignore right half
        // if empty space on left side, insert, otherwise, recurse
        if (node->hasLeftChild()) {
            return insertHelper(node->getLeft(), data);
        } else {
            // found position for new node
            try {
                node->setLeft(new Node(data));
                nodeCount++;
                return true;
            } catch(std::bad_alloc& ba) {
                cout << NODE_INI_ERR_MSG << endl;
                return false;
            }
        }
    } else if(*ndata < *data) {
        // similar, but on the right
        if (node->hasRightChild()) {
            return insertHelper(node->getRight(), data);
        } else {
            try {
                node->setRight(new Node(data));
                nodeCount++;
                return true;
            } catch(std::bad_alloc& ba) {
                cout << NODE_INI_ERR_MSG << endl;
                return false;
            }
        }
    } else { return false; }
}

// --------------------------------- public remove
/**
 * @brief removes an entry from the BinTree
 * @details removes the specified entry from the BinTree if
 * it exists, and restructures the tree. Running time O(logn).
 *
 * @param token entry value to remove
 * @return true if the entry is found and removed
 * otherwise false.
 */
bool BinTree::remove(NodeData& target) {
    return false;   // not implemented
}

// --------------------------------- remove helper
/**
 * @brief helper method for remove()
 * @details recursively search for the parent of the removal target.\n
 * Once found, remove it accordingly in 1 of 4 scenarios.
 *
 * @param node the node potential to be the removal target's parent
 * @param rmToken the removal target string
 *
 * @return removal success status
 */
bool BinTree::removeHelper(Node* node, NodeData& target) {
    return false;
}

// --------------------------------- makeEmpty()
/**
 * @brief empty the tree completely
 */
void BinTree::makeEmpty() {
    postorderDelete(root);
    root = NULL; nodeCount = 0;
}

// --------------------------------- public retrieve()
/**
 * @brief checks to see if an entry is in the BinTree
 * @details checks to see if the specified entry is in
 * the BinTree tree. Running time O(logn).
 *
 * @param token entry to look for
 * @return returns true if the entry is found
 * otherwise false.
 */
bool BinTree::retrieve(NodeData& target, NodeData*& container) {
    return retrieve(root, target, container);
}

// --------------------------------- retrieve helper
/**
 * @brief private helper for retrieve()
 * @details recursively determine the existence of the search value in the
 * left/right subtrees, then report appropriately.
 *
 * @param node node on which to recursively search for token
 * @param token token to search for in the tree
 *
 * @return `true` if the token is contained in the tree, `false` otherwise
 */
bool BinTree::retrieve(Node* subroot, NodeData& target, NodeData*& container) {
    bool found = false;
    if(subroot != NULL) {
        if(*(subroot->getData()) == target) {
            container = subroot->getData();
            found = true;
        }
        else if(*subroot->getData() < target)
            found = retrieve(subroot->getRight(), target, container);
        else
            found = retrieve(subroot->getLeft(), target, container);
    }
    return found;
}

// --------------------------------- public getDepth()
/**
 * @brief Public accessor to determine node's distance from root
 * @details Definition: A node N is of depth d is there are a total of d nodes
 *                      (inclusive) from the root to N.
 *
 * @param target NodeData object (containing the desired content) to search for
 * @return  integer value indicating the "depth" the requested content in the
 *          tree, as defined above. Unsucessful search returns 0.
 */
int BinTree::getDepth(NodeData& target) {
    return getDepthHelper(target, root, 1);
}

// --------------------------------- getDepth helper
/**
 * @brief private helper routine to support getDepth() recursively
 *
 * @pre   Assumes existence of operator== for the data object
 * @param target reference to the NodeData object containing the content
 *        to search for
 * @param cur current root of subtree recursion
 * @param level current depth of the subtree
 * @return int value indicating the depth of the subtree rooted at `cur`
 */
int BinTree::getDepthHelper(NodeData& target, Node* cur, int level) {
    if (cur == NULL)
        return 0;
    else if (*(cur->getData()) == target)
        return level;
    else
        return getDepthHelper(target, cur->getLeft(), level + 1) +
               getDepthHelper(target, cur->getRight(), level + 1);
}

// --------------------------------- isEmpty()
/**
 * @brief checks for emptiness
 * @details checks to see if the BinTree contains entries.
 *
 * @return returns `true` if the BinTree is empty otherwise `false`.
 */
bool BinTree::isEmpty() const {
    return root == NULL;
}

// --------------------------------- size()
/**
 * @brief public getter for the size of the tree
 * @return count of the tree nodes
 */
int BinTree::size() {
    return nodeCount;
}

// --------------------------------- operator<<
/**
 * @brief overloaded output operator
 * @details dependency: std::stringstream (not strict)
 *
 * @param out ostream reference to be sent to the console
 * @param T reference to the tree to be outputted
 */
ostream& operator<<(ostream& out, const BinTree& T) {
    out << T.toStringInorder();
    return out;
}

// --------------------------------- toString()
/**
 * @brief public toString()
 * @return string representation of the tree's content, in order
 */
string BinTree::toStringInorder() const {
    stringstream ss;
    toStringInorder(ss, root);
    ss << endl;
    return ss.str();
}

// --------------------------------- toString helper
/**
 * @brief private helper for toString(), builds the output string recursively
 * in order.
 * @details dependency: stringstream
 *
 * @param ss stringstream reference, container for all the content strings
 * @param curr pointer to current subtree's root
 */
void BinTree::toStringInorder(stringstream& ss, Node* curr) const {
    if(curr != NULL) {
        toStringInorder(ss, curr->getLeft());
        ss << " " << *curr->getData();
        toStringInorder(ss, curr->getRight());
    }
}

// --------------------------------- operator==
/**
 * Node is an internal structure. We utilize its ... internality
 * to define tree equality in a recursive manner.
 */
bool BinTree::operator==(const BinTree& rhs) const {
    return subtreeEqual(root, rhs.root);
}

// --------------------------------- operator== helper
/**
 * @brief Two subtrees are considered equal if everything is identical
 * @details "Everything" includes: subroot, left subtree, and right subtree.
 *
 * @param subroot Node pointer to the root of the subtree being compared
 * @param otherSubroot Node pointer to the root of the rhs subtree
 *
 * @return `true` if the two subtrees are equal in content and structure
 *         `false` otherwise
 */
bool BinTree::subtreeEqual(Node* subroot, Node* otherSubroot) const {
    bool equal = false;
    // 1. equal if both subroot pointers are NULL
    if(subroot == NULL && otherSubroot == NULL)
        equal = true;
    else if(subroot != NULL && otherSubroot != NULL) {
        // 2. equal if both subroots are not NULL (and equal, of course)
        equal = (*subroot == *otherSubroot  &&
                 subtreeEqual(subroot->getLeft(), otherSubroot->getLeft()) &&
                 subtreeEqual(subroot->getRight(), otherSubroot->getRight()));
    }
    return equal;
}

// --------------------------------- operator!=
/**
 * @brief just a boring re-use of operator==
 * @param rhs reference to rhs tree to compare against
 * @return `true` if the two trees are different in content OR structure,
 *         `false` if they´re identical.
 */
bool BinTree::operator!=(const BinTree& rhs) const {
    return !(*this == rhs);
}

// --------------------------------- public displaySideways()
/**
 * @details Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 */
void BinTree::displaySideways() const {
   sideways(root, 0);
}

// --------------------------------- sideways() helper
/**
 * @brief private recursive helper to output the tree´s content
 * @warning   hard-coded to only support standard output to the console
 *
 * @param current pointer to root of current subtree
 * @param level level of current subtree
 */
void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->getRight(), level);

      // indent for readability, 4 spaces per depth level
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->getData() << endl;    // display information of object
      sideways(current->getLeft(), level);
   }
}

// --------------------------------- bstreeToArray()
/**
 * @brief   conversion routine to output the data in the tree into an array
 * @details The data is outputted in sorted order.
 * @pre     Assumes that the array has sufficient space. Query for this info
 *          with the tree´s public `size()` method.
 * @post    The tree is made empty after the content is extracted.
 *
 * @param nodeArray array of pointers (which are declared to point to the
 *                  data type held in the tree data structure).
 */
void BinTree::bstreeToArray(NodeData* nodeArray[]) {
    int* index = new int(0);
    root = bstreeToArrayHelper(root, index, nodeArray);
    nodeCount = 0;  // crude but functional for now
    delete index; index = NULL;
}

// --------------------------------- bstreeToArrayHelper()
/**
 * @brief recursive helper to output subtrees into array
 *
 * @param current pointer to the root of the current subtree
 * @param index reference to a counter variable global to the whole process
 * @param nodeArray target storage location. The pointers contained in this
 *                  array will be directed to the appropriate data objects.
 * @return pointer to the current node after cleanup. Just an implementation
 *         detail.
 */
BinTree::Node* BinTree::bstreeToArrayHelper( Node* current, int* index,
                                    NodeData* nodeArray[]) {
    if(current != NULL && *index < 100) {
        // recursion on the left
        current->setLeft(bstreeToArrayHelper(
            current->getLeft(), index, nodeArray));
        // processing #1
        nodeArray[*index] = current->getData();
        current->setDataToNULL();
        (*index)++;
        // recursion on the right
        current->setRight(bstreeToArrayHelper(
            current->getRight(), index, nodeArray));
        // processing #2
        delete current;
        // clean up
        current = NULL;
    }
    return current;
}


// --------------------------------- arrayToBSTree()
/**
 * @brief conversion routine to input the data from an array into the tree
 * @details The data is inserted in a manner that creates a most balanced tree.
 *          Used together with bstreeToArray to achieve manual tree balancing.
 * 
 * @param nodeArray source storage of data. The array contains pointers to
 * the data objects to be inserted.
 */
void BinTree::arrayToBSTree(NodeData* nodeArray[]) {
    arrayToBSTreeHelper(nodeArray, 0, getArraySize(nodeArray) - 1);
}

// --------------------------------- arrayToBSTreeHelper()
/**
 * @brief recursive helper to extract the middle element in each subarray.
 * @details Preorder insertion of medium data values creates a balanced tree.
 * 
 * @param nodeArray source storage of data.
 * @param lo first index of the subarray (inclusive)
 * @param hi last index of the subarray (inclusive)
 */
void BinTree::arrayToBSTreeHelper(NodeData* nodeArray[], int lo, int hi) {
    if(!(lo > hi)) {
        int middle = (lo + hi) / 2;
        // process
        if(nodeArray[middle] != NULL) {
            insert(nodeArray[middle]);
            nodeArray[middle] = NULL;
        }
        // recurse
        arrayToBSTreeHelper(nodeArray, lo, middle - 1);
        arrayToBSTreeHelper(nodeArray, middle + 1, hi);
    }
}


// --------------------------------- getArraySize()
/**
 * @brief helper method to determine the size of an array of pointers
 * @pre   Assumes that the sensible data is stored at the front of the array.
 *        Search stops when NULL is met.
 * @pre   Max supported array size: 100 (modifiable in tree´s header file)
 * 
 * @param nodeArray the array of object pointers to be sized
 * @return size of the input pointer array
 */
int BinTree::getArraySize(NodeData* nodeArray[]) {
    int size = 0;
    while (nodeArray[size] != NULL && size < ARRAYSIZE) {
        size++;
    }
    return size;
}

// ========================= Node class ===================================

/**
 * Purpose: implementation file for the Node class.
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        April 13 2014
 * @copyright   WTFPLv2.1
 */

/**------------------------------------ Constructor *//**
 * @brief Constructors supporting default values for conciseness
 * 
 * @param data pointer to external Data class (default = NULL)
 * @param left pointer to left child node (default = NULL)
 * @param right pointer to left child node (default = NULL)
 */
BinTree::Node::Node(NodeData* data, BinTree::Node* left, BinTree::Node* right) :
                data(data), left(left), right(right) {}

/**------------------------------------ Copy Constructor *//**
 * @brief copy constructor
 * @details make a new NodeData object with the same content, copy every other
 * attributes as well
 *
 * @param other other Node to copy from, passed in by reference
 * @warning left/right pointers are also copied, resulting in
 *          shared references (multiple objects pointing to the same obj)
 */
BinTree::Node::Node(const BinTree::Node& other) {
    data  = new NodeData(*other.data);
    left  = other.left;     // shared reference
    right = other.right;
}

/**------------------------------------ destructor *//**
 * @brief default destructor
 * @details delete the NodeData object and clear all pointers
 */
BinTree::Node::~Node() {
    if(data != NULL)
        delete data;
    data = NULL; left = NULL; right = NULL;
}

/**------------------------------------ setLeft() *//**
 * @brief Modifies the left child pointer
 * 
 * @param left left child pointer
 */
void BinTree::Node::setLeft(Node* left) {
    this->left = left;
}
/**------------------------------------ setRight() *//**
 * @brief Modifies the right pointer of the Node
 *
 * @param right pointer to a Node to become this Node's right child
 */
void BinTree::Node::setRight(Node* right) {
    this->right = right;
}

/**------------------------------------ set NULL *//**
 * @brief nullify the data inside the Node
 */
void BinTree::Node::setDataToNULL() {
    data = NULL;
}

/**------------------------------------ getLeft() *//**
 * @brief public getter for left child
 * @return pointer to the left child
 */
BinTree::Node* BinTree::Node::getLeft() const { return left; }

/**------------------------------------ getRight() *//**
 * @brief public getter for right child
 * @return pointer to the right child
 */
BinTree::Node* BinTree::Node::getRight() const { return right; }

/**------------------------------------ hasLeftChild() *//**
 * @brief   logic check to determine the existence of a left child
 * @details The logic behind having a child may differ between different
 *          types of trees (at least Threaded BST comes to mind).
 * @return `true` if the Node has a left child
 */
bool BinTree::Node::hasLeftChild() const {
    return (left != NULL);
}

/**------------------------------------ hasRightChild() *//**
 * @brief logic check to determine the existence of a right child
 * @details helper method for traversal through the tree.
 * @return `true` if the Node has a right child (determined with status
 * of the right pointer)
 */
bool BinTree::Node::hasRightChild() const {
    return (right != NULL);
}

/**------------------------------------ isLeaf() *//**
 * @brief logic check to determine whether the current node is a leaf
 * @details helper to make code on the outside world more readable
 * @return `true` if the Node has no children, `false` otherwise
 */
bool BinTree::Node::isLeaf() const {
    return  !hasLeftChild() && !hasRightChild();
}

/**------------------------------------ getData() *//**
 * @brief public getter for content NodeData
 * @return pointer to the NodeData object
 */
NodeData* BinTree::Node::getData() const { return data; }

/**------------------------------------ operator== *//**
 * @brief equality comparison operator
 * @details compare for equality between two NodeDatas
 *
 * @param other reference to the other NodeData object to compare against
 * @return `true` if the two Nodes have the exact same content, `false`
 *          otherwise
 */
bool BinTree::Node::operator==(const Node& other) const {
    bool equal = false;
    if((data == NULL) && (other.data == NULL))
        equal = true;
    else if(data != NULL && other.data != NULL)
        equal = (*data == *other.data);
    return equal;
}

/**------------------------------------ operator!= *//**
 * @brief inequality comparison operator
 * @details compare for inequality between two NodeDatas. Just the opposite of
 * operator==
 *
 * @param other reference to the other NodeData object to compare against
 * @return `true` if the two Nodes do not have the exact same content, `false`
 *          otherwise
 */
bool BinTree::Node::operator!=(const Node& other) const {
    return !(*this == other);
}
