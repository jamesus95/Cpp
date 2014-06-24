/**
 * @file tbst.cpp
 * Purpose: Implementation file for the TBST class
 * 
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef TBST_CPP
#define TBST_CPP

#include <stdio.h>
#include <assert.h>
#include <new>      // catching bad_alloc

// bool debug = true;

// some constants

/*************************************************************************/
/******************************** Iterator *******************************/
/*************************************************************************/

/**
 * @details Default constructors. Creates an iterator standing at the specified
 *          Node. If non is specified, defaults to root.
 * 
 * @param home  the Node at which the iterator will be positioned
 * @return      An Iterator object at the specified location in the tree.
 */
TBST::Iterator::Iterator(Node* node, TBST* tree) {
    currentPtr = node;
    tree = tree;
}

/**
 * @brief Default destructor for the Iterator
 * @details just NULL-ify the pointers, do not destroy contents
 */
TBST::Iterator::~Iterator() {
    currentPtr = NULL;
    tree = NULL;
}

/**
 * overloaded post-fix operator++. Advances the iterator to the next item.
 *
 * @param       dummy dummy int param to overload post-fix
 * @return      `copy = *this` by value to increment *this without
 *                     affecting the value on the RHS of y = x++
 */
TBST::Iterator TBST::Iterator::operator++(int dummy) {
    Iterator copy(*this);
    // modify *this
    assert(currentPtr != NULL);
    if(currentPtr->hasRightChild()) {
        currentPtr = currentPtr->getRight();
        while( currentPtr != NULL && currentPtr->hasLeftChild() )
            currentPtr = currentPtr->getLeft();
    } else {
        currentPtr = currentPtr->getRight();
    }
    return copy;
}

/**
 * overloaded pre-fix operator++. Advances the iterator to the next item.
 *
 * @return      *this by reference to support composite function calls
 */
TBST::Iterator& TBST::Iterator::operator++() {
    assert(currentPtr != NULL);
    if(currentPtr->hasRightChild()) {
        currentPtr = currentPtr->getRight();
        while( currentPtr != NULL && currentPtr->hasLeftChild() )
            currentPtr = currentPtr->getLeft();
        assert(currentPtr != NULL);
    } else {
        currentPtr = currentPtr->getRight();
    }
    return *this;
}

/**
 * @brief Checks if two iterators are at the same spot
 * 
 * @param other A separate iterator that potentially points to the same Node.
 * @return `true` if both iterators point to the same Node, `false` otherwise.
 */
bool TBST::Iterator::operator!=(TBST::Iterator other) {
    return (currentPtr != other.currentPtr);
}

/**
 * retrieve the Node pointer at the current position
 *
 * @return  pointer to current Node
 */
Node* TBST::Iterator::getCurrentNode() {
    return currentPtr;
}

/**
 * @brief manages iterator positioning when a node is removed
 * @details Adopts the standard behavior of ITERATORS. i.e. iter.remove()
 * @return success status of the removal process
 */
bool TBST::Iterator::removeCurrentNode() {
    Node* temp = currentPtr;
    ++(*this);
    return tree->remove(temp->getData()->getToken());
}

/***********************************************************************/
/***********************************************************************/
/********************* Threaded Binary Search Tree *********************/
/********************* Threaded Binary Search Tree *********************/
/********************* Threaded Binary Search Tree *********************/
/***********************************************************************/
/***********************************************************************/

// **************** ITERATOR HELPERS
/**
 * returns an iterator standing at the beginning of the tree
 * O(logn) running time.
 * 
 * @return Iterator object pointing at the minimum node (begin of inorder)
 */
TBST::Iterator TBST::begin() {
    Node* temp = root;
    while(temp->hasLeftChild()) {
        temp = temp->getLeft();
    }
    Iterator begin(temp, this);
    return begin;
}

/**
 * @brief   Acts as reference point of the end of an inorder iteration
 * through the tree.
 *  
 * @return  Iterator object pointing to a Node not part of the tree as the
 *          outside world knows of it. This Node serves simply to signify
 *          the end of the tree's inorder traversal.
 */
TBST::Iterator TBST::end() {
    Iterator end(NULL, this);
    return end;
}

// **************** CONSTRUCTORS/DESTRUCTOR
/**
 * @brief default constructor
 * @details creates an empty TBST
 */
TBST::TBST() {
    root = NULL;
    nodeCount = 0;
}

/** 
 * @brief copy constructor
 * @details creates a copy of the passed in TBST
 * 
 * @param other TBST tree to copy
 */
TBST::TBST(const TBST& other) {
    root = NULL;
    nodeCount = 0;
    if(other.root != NULL) {
        // handle root separately
        assert(root == NULL); // make sure that tree is empty
        // then add the root
        NodeData* rootData = other.root->getData();
        insert(rootData->getToken(), rootData->getCount());

        // recursively copy the left and right subtrees
        recursiveCopy(other.root->getLeft());
        recursiveCopy(other.root->getRight());
    }
    else {
        root = NULL;
    }
}


/**
 * @brief helper for copy-constructor
 * @details recursively copy nodes from a tree pre-order
 * 
 * @param origNode Node on the original tree to be copied over
 */
void TBST::recursiveCopy(Node* origNode) {
    if(origNode != NULL) { 
        if(origNode->isLeaf()) {
            NodeData* d = origNode->getData();
            insert(d->getToken(), d->getCount());
            d = NULL;
        } else if(!origNode->hasLeftChild()) {
            // 1: have right child, no left child
            // copy the node
            NodeData* d = origNode->getData();
            insert(d->getToken(), d->getCount());
            d = NULL;
            // then recurse down and copy the right child
            recursiveCopy(origNode->getRight());
        } else if(!origNode->hasRightChild()) {
            // 2: have left child, no right child
            NodeData* d = origNode->getData();
            insert(d->getToken(), d->getCount());
            d = NULL;
            // then recurse down and copy the left child
            recursiveCopy(origNode->getLeft());
        } else {
            // 3: have children on both sides
            NodeData* d = origNode->getData();
            insert(d->getToken(), d->getCount());
            d = NULL;
            // then recurse down and copy both children
            recursiveCopy(origNode->getLeft());
            recursiveCopy(origNode->getRight());
        }
    }
}

/**
 * @brief destructor
 * @details releases all TBST Nodes' memory
 */
TBST::~TBST() {
    recursiveDelete(root);
    root = NULL;
}


/**
 * @brief helper for destructor
 * @details recursively delete the nodes in a tree from top down pre-order
 * 
 * @param node The node to delete and recurse on
 */
void TBST::recursiveDelete(Node* node) {
    if (node != NULL) {
        assert(node != NULL);
        if(node->hasLeftChild())
            recursiveDelete(node->getLeft());
        if(node->hasRightChild())
            recursiveDelete(node->getRight());
        delete node;
    }
    node = NULL;
}



// **************** PUBLIC METHODS
/**
 * @brief inserts a value into the TBST
 * @details inserts a value into the TBST, adding a new entry
 * if one does not already exist, and incrementing the entry
 * if it does exist. Running time O(logn).
 * 
 * @param token entry value to add/increment
 * @return `true` if insertion is successful, `false` otherwise.
 *                Insertion fails when new entry is equal to a parent
 *                with 2 children.
 */
bool TBST::insert(string token, int frequency) {
    if (this->root == NULL) {
        try {
            root = new Node(token, frequency);
            nodeCount++;
            return true;
        } catch (std::bad_alloc& ba) {
            cout << "DEBUG: FAILED to allocate memory for Node" << endl;
            return false;
        }
    } else {
        return insert(this->root, token, frequency);
    }
}

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
bool TBST::insert(Node* node, string token, int frequency) {
    string nodeToken = node->getData()->getToken();
    if (token == nodeToken) {
        // base case: found an existing node with the same token
        // just increment the frequency
        node->getData()->increaseCount();
        return true;
    } else if (token < nodeToken) {
        // look on the left
        if (node->hasLeftChild()) {
            // keep looking
            return insert(node->getLeft(), token, frequency);
        } else {
            // found position for new node
            try {
                Node* temp = new Node(  token, frequency,
                                        node->getLeft(), node, true, true);
                node->setLeft(temp, false);
                nodeCount++;
                return true;
            } catch(std::bad_alloc& ba) {
                cout << "DEBUG: FAILED to allocate memory for Node" << endl;
                return false;
            }
        }
    } else {
        // similar, but on the right
        if (node->hasRightChild()) {
            return insert(node->getRight(), token, frequency);
        } else {
            try {
                Node* temp = new Node(  token, frequency,
                                        node, node->getRight(), true, true);
                node->setRight(temp, false);
                nodeCount++;
                return true;
            } catch(std::bad_alloc& ba) {
                cout << "DEBUG: FAILED to allocate memory for Node" << endl;
                return false;
            }
        }
    }
}

/**
 * @brief removes an entry from the TBST
 * @details removes the specified entry from the TBST if
 * it exists, and restructures the tree. Running time O(logn).
 * 
 * @param token entry value to remove
 * @return true if the entry is found and removed
 * otherwise false.
 */
bool TBST::remove(string token) {
    if (root != NULL && root->getData()->getToken() == token) {
        if(removeRoot()) {
            nodeCount--;
            return true;
        } else return false;
    } else if (root != NULL) {
        if(remove(root, token)) {
            nodeCount--;
            return true;
        } else return false;
    } else {
        return false;
    }
}

/**
 * @brief helper method for remove(). Focuses on removing the root Node in
 * various circumstances.
 * @details There are 4 situations in which a root Node is to be removed:\n
 * -# Root is the only node in the tree
 * -# Root has a left branch
 * -# Root has a right branch
 * -# Root has both children branches
 * 
 * \nThis is too long, but if we run out of time to refactor it, we'll accept
 * point loss.
 * 
 * @return removal success status.
 */
bool TBST::removeRoot() {
    // Root is leaf
    if (root->isLeaf()) {
        delete root;
        root = NULL;
    // Root has left
    } else if (root->getLeft() != NULL && root->getRight() == NULL) {
        Node* temp = root->getLeft();
        delete root;
        root = temp;
        while (temp->hasRightChild()) {
            temp = temp->getRight();
        }
        temp->setRight(NULL, true);
    // Root has right
    } else if (root->getLeft() == NULL && root->getRight() != NULL) {
        Node* temp = root->getRight();
        delete root;
        root = temp;
        while (temp->hasLeftChild()) {
            temp = temp->getLeft();
        }
        temp->setLeft(NULL, true);
    // Root has both
    } else {
        Node* temp = root;
        Node* temp2 = temp->getRight();
        while (temp2->hasLeftChild()) {
            temp2 = temp2->getLeft();
        }
        // If we moved temp2
        if (*(temp->getRight()) != *temp2) {
            // If temp2 doesn't have right children
            if (!temp2->hasRightChild()) {
                temp2->getRight()->setLeft(temp2, true);
            // Go to temp2's parent and set to temp2's child
            } else {
                Node* temp3 = temp2->getRight();
                while (temp3->hasRightChild()) {
                    temp3 = temp3->getRight();
                }
                temp3 = temp3->getRight();
                temp3->setLeft(temp2->getRight(), false);
            }
            // replace temp with temp2 (right side)
            temp2->setRight(temp->getRight(), false);
        }
        // replace temp with temp2 (left side)
        temp2->setLeft(temp->getLeft(), false);
        root = temp2;
        Node* temp3 = temp2->getLeft();
        while (temp3->hasRightChild()) {
            temp3 = temp3->getRight();
        }
        temp3->setRight(temp2, true);
        delete temp;
        temp = NULL;
        return true;
    }
    return true;
}


/**
 * @brief helper methodfor remove()
 * @details recursively search for the parent of the removal target.\n
 * Once found, remove it accordingly in 1 of 4 scenarios.
 * 
 * @param node the node potential to be the removal target's parent
 * @param rmToken the removal target string
 * 
 * @return removal success status
 */
bool TBST::remove(Node* node, string rmToken) {
    string nodeToken = node->getData()->getToken();
    bool targetIsOnLeft = (rmToken < nodeToken);
    
    Node* rmTarget;
    // looking for the removal node
    if (targetIsOnLeft) {
        if (node->hasLeftChild()) {
            rmTarget = node->getLeft();
        } else {
            return false;
        }
    } else {
        if (node->hasRightChild()) {
            rmTarget = node->getRight();
        } else {
            return false;
        }
    }
    // if found, then remove with 1 of 4 cases
    if (rmToken == rmTarget->getData()->getToken()) {
        if (rmTarget->isLeaf()) {
            return rmLeaf(node, targetIsOnLeft);
        } else if (rmTarget->hasLeftChild() && !rmTarget->hasRightChild()) {
            return rmNodeWithLeft(node, targetIsOnLeft);
        } else if (rmTarget->hasRightChild() && !rmTarget->hasLeftChild()) {
            return rmNodeWithRight(node, targetIsOnLeft);
        } else {
            return rmNodeWithBoth(node, targetIsOnLeft);
        }
    // otherwise, recurse
    } else {
        return remove(rmTarget, rmToken);
    }
}

/**
 * @brief helper method for removing a non-root node inside a tree with
 * only left branch.
 * @details manages pointers coming TO and FROM the removal target
 * to proper maintain the threaded tree structure.
 * 
 * @param parent pointer to the parent of the removal target node. 
 * @param targetIsOnLeft bool flag to indicate whether the removal target is
 * the left or right child of the parent node.
 * 
 * @return removal success status.
 */
bool TBST::rmLeaf(Node* parent, bool targetIsOnLeft) {
    Node* rmTarget;
    if (targetIsOnLeft) {
        rmTarget = parent->getLeft();
        parent->setLeft(rmTarget->getLeft(), true);
    } else {
        rmTarget = parent->getRight();
        parent->setRight(rmTarget->getRight(), true);
    }
    // Delete
    delete rmTarget;
    rmTarget = NULL;
    return true;
}

/**
 * @brief helper method for removing a non-root node inside a tree
 * @details manages pointers coming TO and FROM the removal target
 * to proper maintain the threaded tree structure.\n
 * Remove the removal target node and replaces it with its left child.\n
 * 
 * Perfectly mirrored with rmNodeWithRight()
 * 
 * @param parent pointer to the parent of the removal target node. 
 * @param targetIsOnLeft bool flag to indicate whether the removal target is
 * the left or right child of the parent node.
 * 
 * @return removal success status.
 */
bool TBST::rmNodeWithLeft(Node* parent, bool targetIsOnLeft) {
    Node* rmTarget;
    if (targetIsOnLeft) {
        rmTarget = parent->getLeft();
        parent->setLeft(rmTarget->getLeft(), false);
    } else {
        rmTarget = parent->getRight();
        parent->setRight(rmTarget->getLeft(), false);
    }
    // Thread
    Node* inPredecessor = rmTarget->getLeft();
    while (inPredecessor->hasRightChild()) {
        inPredecessor = inPredecessor->getRight();
    }
    inPredecessor->setRight(rmTarget->getRight(), rmTarget->isRightThreaded());
    // Delete
    delete rmTarget;
    rmTarget = NULL;
    return true;
}

/**
 * @brief helper method for removing a non-root node inside a tree with
 * only right branch
 * @details manages pointers coming TO and FROM the removal target
 * to proper maintain the threaded tree structure.\n
 * Remove the removal target node and replaces it with its right child.\n
 * 
 * Perfectly mirrored with rmNodeWithLeft()
 * 
 * @param parent pointer to the parent of the removal target node. 
 * @param targetIsOnLeft bool flag to indicate whether the removal target is
 * the left or right child of the parent node. Note: NOT to be 
 * confused with whether the child of the removal target is on
 * its left or right.
 * 
 * @return removal success status.
 */
bool TBST::rmNodeWithRight(Node* parent, bool targetIsOnLeft) {
    Node* rmTarget;
    if (targetIsOnLeft) {
        rmTarget = parent->getLeft();
        parent->setLeft(rmTarget->getRight(), false);
    } else {
        rmTarget = parent->getRight();
        parent->setRight(rmTarget->getRight(), false);
    }
    // Thread
    Node* temp2 = rmTarget->getRight();
    while (temp2->hasLeftChild()) {
        temp2 = temp2->getLeft();
    }
    temp2->setLeft(rmTarget->getLeft(), rmTarget->isLeftThreaded());
    // Delete
    delete rmTarget;
    rmTarget = NULL;
    return true;
}

/**
 * @brief helper method for removing a non-root node inside a tree with 2 
 * children.
 * @details manages pointers coming TO and FROM the removal target
 * to proper maintain the threaded tree structure.\n
 * Remove the removal target node and replaces it with its
 * smallest successor.\n
 * 
 * @param parent pointer to the parent of the removal target node. 
 * @param targetIsOnLeft bool flag to indicate whether the removal target is
 * the left or right child of the parent node.
 * 
 * @return removal success status.
 */
bool TBST::rmNodeWithBoth(Node* parent, bool targetIsOnLeft) {
    Node* rmTarget = (targetIsOnLeft) ? (parent->getLeft()) : 
                                        (parent->getRight());

    // inSuccessor is the inorder successor of the rmTarget node
    // i.e. it is the smallest node greater than the rmTarget
    Node* inSuccessor = rmTarget->getRight();

    while (inSuccessor->hasLeftChild()) {
        inSuccessor = inSuccessor->getLeft();
    }
    // If we moved inSuccessor
    if (*(rmTarget->getRight()) != *inSuccessor) {
        Node* successorParent;
        // If inSuccessor doesn't have right children
        if (!inSuccessor->hasRightChild()) {
            successorParent = inSuccessor->getRight();
            successorParent->setLeft(inSuccessor, true);
        // Go to inSuccessor's parent and set to inSuccessor's child
        } else {
            Node* temp = inSuccessor->getRight();
            while (temp->hasRightChild()) {
                temp = temp->getRight();
            }
            successorParent = temp->getRight();
            successorParent->setLeft(inSuccessor->getRight(), false);
        }
        // replace rmTarget with inSuccessor (right side)
        inSuccessor->setRight(rmTarget->getRight(), false);
    }
    // replace rmTarget with inSuccessor (left side)
    inSuccessor->setLeft(rmTarget->getLeft(), false);
    // swap inSuccessor in to become child of parent
    if(targetIsOnLeft)
        parent->setLeft(inSuccessor, false);
    else
        parent->setRight(inSuccessor, false);
    
    // thread the inorder predecessor of the previously-successor
    Node* inPredecessor = inSuccessor->getLeft();
    while (inPredecessor->hasRightChild()) {
        inPredecessor = inPredecessor->getRight();
    }
    inPredecessor->setRight(inSuccessor, true);
    delete rmTarget; rmTarget = NULL;   // clean up
    return true;
}


/**
 * @brief checks to see if an entry is in the TBST
 * @details checks to see if the specified entry is in 
 * the TBST tree. Running time O(logn).
 * 
 * @param token entry to look for
 * @return returns true if the entry is found
 * otherwise false.
 */
bool TBST::contains(string token) {
    return contains(root, token);
}


/**
 * @brief private helper for contains()
 * @details recursively determine the existence of the search value in the 
 * left/right subtrees, then report appropriately.
 * 
 * @param node node on which to recursively search for token
 * @param token token to search for in the tree
 * 
 * @return `true` if the token is contained in the tree, `false` otherwise
 */
bool TBST::contains(Node* node, string token) {
    if (node != NULL && node->getData()->getToken() != token) {
        if (node->getData()->getToken() < token) {
            return contains(node->getRight(), token);
        } else {
            return contains(node->getLeft(), token);
        }
    } else if (node != NULL && node->getData()->getToken() == token) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief checks for emptiness
 * @details checks to see if the TBST contains entries.
 * 
 * @return returns `true` if the TBST is empty
 * otherwise `false`.
 */
bool TBST::isEmpty() const {
    return root == NULL;
}


/**
 * @brief functional programming implementation of BST recursive traversal
 * @details This method traverses the tree starting at the Node specified,
 *          applying the function `func` specified, in the order specified.
 * @pre     If no order is specified or if specified order is invalid,
 *          traverses in-order.
 * 
 * @param func  function to apply to each Node pointer along the traversal path
 *              \nDoes not check input. YOLO.
 *              Design this function with only a single Node pointer in mind.
 * @param output    ostream object to append the output content to
 * @param order order of recursive traversal 
 *              (in-order = 0, pre-order = 1, post-order = -1)
 */
void TBST::traverse(void (*func)(Node*, ostream&), ostream& output, int order) {
    if(order == POSTORDER)
        postOrder(func, output, root);
    else if(order == PREORDER)
        preOrder(func, output, root);
    else
        inOrder(func, output, root);
}


/**
 * Processes the TBST in pre-order, applying the specified function at
 * each Node. Defaults to print(), starting at root.
 *     
 * 
 * @param func  function to apply to each Node pointer along the
 *              traversal path.
 * @param output    ostream object to append the output content to
 *              Design this function with only a single Node pointer in mind.
 * @param cur   pointer to Node at which to process and start recursion on.
 */
void TBST::preOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur) {
    if(cur != NULL) {
        func(cur, output);
        if(cur->hasLeftChild())
            preOrder(func, output, cur->getLeft());
        if(cur->hasRightChild())
            preOrder(func, output, cur->getRight());
    }
}

/**
 * Processes the TBST in in-order, applying the specified function at
 * each Node. Defaults to print(), starting at root.
 * 
 * @param func  function to apply to each Node pointer along the path.
 *              Design this function with only a single Node pointer in mind.
 * @param output    ostream object to append the output content to
 * @param cur   pointer to Node at which to process and start recursion on.
 */
void TBST::inOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur) {
    if(cur != NULL) {
        if(cur->hasLeftChild())
            inOrder(func, output, cur->getLeft());
        func(cur, output);
        if(cur->hasRightChild())
            inOrder(func, output, cur->getRight());
    }
}

/**
 * Processes the TBST in post-order, applying the specified function at
 * each Node. Defaults to print(), starting at root.
 * 
 * @param func  function to apply to each Node pointer along the path.
 *              Design this function with only a single Node pointer in mind.
 * @param output    ostream object to append the output content to
 * @param cur   pointer to Node at which to process and start recursion on.
 */
void TBST::postOrder(void (*func)(Node*, ostream&), ostream& output, Node* cur) {
    if(cur != NULL) {
        if(cur->hasLeftChild())
            postOrder(func, output, cur->getLeft());
        if(cur->hasRightChild())
            postOrder(func, output, cur->getRight());
        func(cur, output);
    }
}


/**
 * @brief   Processes the tree in-order iteratively.
 * @details Iteratively steps through the tree and execute the specified
 *          function. Appends the output to the ostream object if the function
 *          has anything to do with printing. This is silly because the
 *          function now requires the public world to supply an ostream object
 *          just to work, but it is needed to achieve the 7-nodes-per-line
 *          printing behavior.
 *
 * @param   func pointer to a function that processes the Nodes
 */
void TBST::iterativeInorder(void (*func)(Node*, ostream&), ostream& output) {
    if(root != NULL) {    
        Node* curr = root;
        while(curr->getLeft() != NULL)
            curr = curr->getLeft();

        int iter = 0;
        // traverse until the end
        do {
            // this is stupid--it has no relationship with `func` except when
            // `func` is displayNode
            // but it's required to print 7 nodes per line.
            if(iter % 7 == 0)
                output << endl;
            func(curr, output); iter++;

            // if threaded, go right once
            if(curr->isRightThreaded()) {
                curr = curr->getRight();
            } else {
            // if not threaded, go down right once, go left ALLL THE WAYYYYY
                curr = curr->getRight();
                while(curr->hasLeftChild())
                    curr = curr->getLeft();
            }
        } while(curr != NULL);
    }
}

/**
 * @brief public getter for the size of the tree
 * @details just simply reports the count of the tree nodes
 * @return count of the tree nodes
 */
int TBST::size() {
    return nodeCount;
}

/**
 * @brief public method to retrieve NodeData with maximum secondary value.
 * @return pointer to NodeData with maximum frequency in the tree. NULL if not
 *         found.
 */ 
NodeData* TBST::getMaxByFrequency() {
    return getMaxByFrequency(root);
}

/**
 * @brief Recursively query for max NodeDatas from left/right subtrees
 * and compare.
 * @details private recursive method. Compares maximum candidates from the root
 * node, the left subtree, and the right subtree. O(n) running time.
 * 
 * @param subroot Node pointer to the root of the subtree currently recursed on
 * @return NodeData with maximum secondary value among the 3 candidates
 */
NodeData* TBST::getMaxByFrequency(Node* subroot) {
    if(subroot != NULL) {
        NodeData* maxData = subroot->getData(); // default max
        NodeData* leftMax = NULL; NodeData* rightMax = NULL;

        if(subroot->hasLeftChild())
            leftMax = getMaxByFrequency(subroot->getLeft());
        if(subroot->hasRightChild())
            rightMax = getMaxByFrequency(subroot->getRight());
        
        if(leftMax != NULL && maxData->getCount() < leftMax->getCount())
            maxData = leftMax;
        // break ties in favor of the right branch since we desire an
        // increasing sort order
        if(rightMax != NULL && maxData->getCount() <= rightMax->getCount())
            maxData = rightMax;
        
        return maxData;
    }
    else return NULL;
}

/**
 * @brief public method to retrieve NodeData with minimum secondary value.
 * @return pointer to NodeData with minimum frequency in the tree. NULL if not
 *         found.
 */ 
NodeData* TBST::getMinByFrequency() {
    return getMinByFrequency(root);
}

/**
 * @brief Recursively query for max NodeDatas from left/right subtrees
 * and compare.
 * @details private recursive method. Compares minimum candidates from the root
 * node, the left subtree, and the right subtree. Runs in O(n) time.
 * 
 * @param subroot Node pointer to the root of the subtree currently recursed on
 * @return NodeData with minimum secondary value among the 3 candidates
 */
NodeData* TBST::getMinByFrequency(Node* subroot) {
    if(subroot != NULL) {
        NodeData* minData = subroot->getData(); // default min
        NodeData* leftMin = NULL; NodeData* rightMin = NULL;

        if(subroot->hasLeftChild())
            leftMin = getMinByFrequency(subroot->getLeft());
        if(subroot->hasRightChild())
            rightMin = getMinByFrequency(subroot->getRight());
        
        // break ties in favor of the node on the left since we want increasing
        // sort order
        if(leftMin != NULL && minData->getCount() >= leftMin->getCount()) {
            minData = leftMin;
        }
        if(rightMin != NULL && minData->getCount() > rightMin->getCount()) {
            minData = rightMin;
        }
        return minData;
    }
    else return NULL;
}

#endif
