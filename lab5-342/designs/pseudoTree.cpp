/**
 * This class defines a Threaded Binary Search Tree.
 * Among supported functionalities are:
 * - inorder Iterator
 * - Recursive traversal inorder, preorder, postorder
 * - self-rebalancing
 * - tree rotation (soon)
 * - functional programming implementation (soon)
 *
 * \version         2.0
 * \author          James Murphree
 * \author          Vu Dinh
 * \date            March 2nd 2014
 * \copyright       WTFPLv2.1
 * 
 */

#define INORDER 0
#define PREORDER 1
#define POSTORDER -1

class TBST {



/**
 * In similar manner to traversing an array:
 * for(int i = begin; i < end; i++)
 * We wish to traverse the tree from its begin() to its end().
 * The end() is a location "just beyond" the final node of the tree.
 * 
 * THE ONLY NODE IN THE THREADED TREE WHOSE RIGHT POINTER IS NULL 
 * IS THE MAX (AND THUS, LAST) NODE.
 * Knowing this, we can control the Iterator's behavior such that
 * it will never point to NULL unless it has passed the last node,
 * thus appropriately pointing at the first location beyond the tree.
 */

    /******************************** Iterator ******************************/

    /**
     * @details Default constructors. Creates an iterator standing
     * at the specified Node. If non is specified, defaults to root.
     * 
     * @param home  the Node at which the iterator will be positioned
     * @return      An Iterator object at the specified location in the tree.
     */
    TBST::Iterator::Iterator(Node* home) {
        currentPtr = home;
    }

    TBST::Iterator::~Iterator() {
        currentPtr = NULL;
    }

    /**
     * overloaded post-fix operator++. Advances the iterator to the next item.
     *
     * @param       dummy dummy int param to overload post-fix
     * @return      `copy = *this` by value to increment *this without
     *                     affecting the value on the RHS of y = x++
     */
    TBST::Iterator TBST::Iterator::operator++(int dummy) {
        make a copy of this iterator (to be returned later)
        // modify this iterator to point to the next in-order item:
        if(not yet at the bottom) {
            take one step down to the right
            go all the way down to the left until hitting NULL
            this is the next item to be processed in-order
        }
        else {
            go right once, this is the next item (the middle)
        }
        return copy; // return the copy from earlier, unmodified
    }

    /**
     * overloaded pre-fix operator++. Advances the iterator to the next item,
     * then returns the new reference.
     *
     * @return      *this by reference to support composite function calls
     */
    TBST::Iterator& TBST::Iterator::operator++() {
        1. modifies the pointer in similar manner to post-fix operator++
        2. return reference to the same object (*this)
    }

    /**
     * retrieve the Node pointer at the current position
     *
     * @return  pointer to current Node
     */
    Node* TBST::Iterator::get() {
        return currentPtr;
    }



    /****************************** TBST ***********************************/

    /**
     * Returns an iterator standing at the beginning of the tree.
     * O(logn) running time.
     * 
     * @return Iterator object pointing at the minimum node (begin of inorder)
     */
    TBST::Iterator TBST::begin() {
        Node* temp = root;
        while(temp->getLeft() != NULL) {
            temp = temp->getLeft();
        }
        Iterator begin(temp);
        return begin;
    }

    /**
     * @brief   Acts as reference point of the end of an inorder iteration
     *          through the tree.
     *  
     * @return  Iterator object pointing to a Node not part of the tree as the
     *          outside world knows of it. This Node serves simply to signify
     *          the end of the tree's inorder traversal.
     */
    TBST::Iterator TBST::end() {
        // there is only one location where an iterator can point to NULL
        return new Iterator(NULL);
    }


    /**
     * @brief default constructor
     * @details creates an empty TBST
     */
    TBST() {
        initialize root to null
    }

    /**
     * @brief copy constructor
     * @details creates a copy of the passed in TBST
     * 
     * @param other TBST tree to copy
     */
    TBST(const TBST& other) {
        design the copy helper function to recursively copy from top-level
        down, similar to the destructor
    }

    /**
     * @brief destructor
     * @details releases all TBST memory
     */
    TBST::~TBST() {
        // recursively destroy the tree from top-level down
        recursiveDelete(left);
        recursiveDelete(right);
        delete root;
    }
    
    /**
     * @brief inserts a value into the TBST
     * @details inserts a value into the TBST, adding a new entry
     * if one does not already exist, and incrementing the entry
     * if it does exist.
     * 
     * @param token entry value to add/increment
     */
    bool insert(string token) {
        if (tree is empty) {
            make new node and point root to it
            return true;
        } else {
            locate where the parent node is, parent is defined as:
                a node with NULL left ptr and token > new token, OR
                a node with a thread      and token < new token.
            if (parent.token >= token) {
                make new node with token data
                add new node to the left of parent
                update thread-status for parent and child:
                    point right ptr of child to parent
                    child is now threaded
                    thread status of parent remains unchanged
                return true;
            } else if (parent.token < token) {
                make new node with token data
                add new node to the right of parent
                update thread-status for parent and child:
                    point right ptr of child to where right ptr of parent
                        used to be (should have kept track)
                    (right ptr of parent now points to child, as expected)
                    parent is no longer threaded
                    child is now threaded
                return true;
            } else {
                return false;
            }
        }
    }

    /**
     * @brief removes an entry from the TBST
     * @details removes the specified entry from the TBST if
     * it exists, and restructures the tree.\n\n
     * 
     * Concerns involved when removing a node from a threaded BST:\n
     * -# There could be at most ONE thread pointing to the removed node.
     *          fix this thread appropriately.\n
     * -# There could be at most TWO subtrees underneath the removed node.
     *          bring one of them up and put the other into an appropriate
     *          position to maintain tree structure.\n
     *
     * After much consideration, we decided to adopt the following solution.
     * See Illustration of Tree Removal for a more elaborate description.
     * 
     * @param token entry value to remove
     * @return true if the entry is found and removed
     * otherwise false.
     */
    bool remove(string token) {
        locate parent of node with "Remove" token
        if (can find such a parent) {
            keep track of the PARENT with a pointer
            if(the remove node has a left subtree) {
                1. find the GREATGRANDCHILD of the left subtree:
                        from the remove node, go left once then
                        go right until reaching a threaded node.
                   Keep track of this GREATGRANDCHILD
                2. remove the node and move the left subtree up
                3. move the right subtree down to be the right child of
                        the GREATGRANDCHILD
                (4. no need to re-thread the tree.)
            }
            else {
                just remove the node and bring the right subtree (if any)
                up to replace it.
                No threads to fix, no subtrees to reposition.
            }
        }
        else return false;
    }

    /**
     * @brief checks to see if an entry is in the TBST
     * @details checks to see if the specified entry is in 
     * the TBST tree.
     * 
     * @param token entry to look for
     * @return returns true if the entry is found
     * otherwise false.
     */
    bool contains(string token) {
        return contains(token, root);
    }

    // PRIVATE contains helper
    bool contains(string token, Node* node) {
        if (node is leaf) {
            return token == node.token;
        } else if (node''s token is bigger than token) {
            return contains(token, node.left);
        } else {
            return contains(token, node.right);
        }
    }

    /**
     * @brief checks for emptiness
     * @details checks to see if the TBST contains
     * and entries.
     * @return returns true if the TBST is empty
     * otherwise false.
     */
    bool TBST::isEmpty() const {
        if (root is null) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief   Processes the tree in-order iteratively.
     * @details Iteratively steps through the tree and execute the specified
     *          function.
     *
     * @param   func pointer to a function that processes the Nodes
     */
    void TBST::iterativeInorder() const {
        Iterator iter = create iterator at first in-order node;
        Iterator end = create iterator at last in-order node;
        while (iter != end) {
            print iter.currentNode;
            iter++;
        }
    }

    /**
     * Processes the TBST in pre-order, applying the specified function at
     * each Node. Defaults to print(), starting at root.
     *     
     * 
     * @param func  function to apply to each Node pointer along the
     *              traversal path.
     *              Design this function with only a single
     *              Node pointer in mind.
     * @param cur   pointer to Node at which to process and
     *              start recursion on.
     */
    void TBST::preOrder(void (*func)(Node*), Node* cur) {
        func(cur);
        preOrder(func, cur->getLeft());
        preOrder(func, cur->getRight());
    }

    /**
     * Processes the TBST in in-order, applying the specified function at
     * each Node. Defaults to print(), starting at root.
     * 
     * @param func  function to apply to each Node pointer along the
     *              traversal path.
     *              Design this function with only a single
     *              Node pointer in mind.
     * @param cur   pointer to Node at which to process and
     *              start recursion on.
     */
    void TBST::inOrder(void (*func)(Node*), Node* cur) {
        if(cur != NULL) {
            inOrder(func, cur->getLeft());
            func(cur);
            inOrder(func, cur->getRight());
        }
    }

    /**
     * Processes the TBST in post-order, applying the specified function at
     * each Node. Defaults to print(), starting at root.
     * 
     * @param func  function to apply to each Node pointer along the
     *              traversal path.
     *              Design this function with only a single
     *              Node pointer in mind.
     * @param cur   pointer to Node at which to process and
     *              start recursion on.
     */
    void TBST::postOrder(void (*func)(Node*), Node* cur) {
        if(cur != NULL) {
            postOrder(func, cur->getLeft);
            postOrder(func, cur->getRight);
            func(cur);
        }
    }

    /**
     * @brief functional programming implementation of BST recursive traversal
     * @details This method traverses the tree starting at the Node specified,
     *          applying the function `func` specified, in the
     *          order specified.
     * @pre     If no order is specified or if specified order is invalid,
     *          traverses in-order.
     * 
     * @param func  function to apply to each Node pointer along the
     *              traversal path.
     *              Design this function with only a single
     *              Node pointer in mind. Defaults to print().
     * @param traverseRoot   Node to start the traversal from
     * @param order order of recursive traversal 
     *              (in-order = 0, pre-order = 1, post-order = -1)
     */
    void TBST::traverse(void (*func)(Node*), Node* traverseRoot, int order) {
        if(order = POSTORDER)
            postOrder(func, traverseRoot);
        else if(order = PREORDER)
            preOrder(func, traverseRoot);
        else
            inOrder(func, traverseRoot);
    }


    // ===================================================================
    // These are helper functions. The logic-herein is described as part
    // of the main insert() / remove() routines. See above for details.
    // ===================================================================
   

    /**
     * Given appropriate parent-child parings, this method manipulates the
     * pointers to correctly maintain the tree structure while adding 
     * the child. parent =: Node such that
     *                 parent.left == NULL && parent >= child, OR
     *                 parent.isThread && parent < child
     *
     *
     * 
     * @param child  pointer to new Node to be added to the tree
     * @param parent pointer to new Node's parent after addition.
     */
    void insert(Node* child, Node* parent) {
        
    }

    /**
     * Given apporpriate parent-child parings, this method manipulates
     * pointers to correctly maintain the tree structure while removing
     * the specified node from the tree.
     * 
     * @param toRemove   pointer to Node to remove
     * @param removeFrom pointer to parent Node of remove
     */
    void remove(Node* toRemove, Node* removeFrom) {

    }
