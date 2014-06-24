class TBST {


	/**
	 * @brief default constructor
	 * @details creates an empty TBST
	 */
	TBST() {
		set root to null
	}

	/**
	 * @brief copy constructor
	 * @details creates a copy of the passed in TBST
	 * 
	 * @param other TBST tree to copy
	 */
	TBST(const TBST& other) {
		copy in all nodes from other
	}

	/**
	 * @brief destructor
	 * @details releases all TBST memory
	 */
	TBST::~TBST() {

	}
    
    /**
	 * @brief insers a value into the TBST
	 * @details inserts a value into the TBST, adding a new entry
	 * if one does not already exist, and incrementing the entry
	 * if it does exist.
	 * 
	 * @param token entry value to add/increment
	 */
	bool insert(string token) {
		bool success = false;
		find(insert(), root, false, token, &success);
		return success;
	}

	/**
	 * @brief removes an entry from the TBST
	 * @details removes the specified entry from the TBST if
	 * it exists, and restructures the tree.
	 * 
	 * @param token entry value to remove
	 * @return true if the entry is found and removed
	 * otherwise false.
	 */
	bool remove(string token) {
		bool success = false;
		find(remove(), root, false, token, &success);
		return success;
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
		bool success = false;
		find(contains(), root, false, token, &success);
		return success;
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
	 * @brief prints the TBST in-order
	 * @details iterates over the TBST in-order 
	 * and prints values.
	 */
	void TBST::iterativeIn() const {
		Iterator iter = create iterator at first in-order node;
		Iterator end = create iterator at last in-order node;
		while (iter != end) {
			print iter.currentNode;
			iter++;
		}
	}

	/**
	 * @brief prints the TBST pre-order
	 * @details recurses over the TBST in pre-order 
	 * and prints values.
	 */
	void TBST::preOrder() const {
		traverse(root, -1);
	}

	/**
	 * @brief prints the TBST in-order
	 * @details recurses over the TBST in-order
	 * and prints values.
	 */
	void TBST::inOrder() const {
		traverse(root, 0);
	}

	/**
	 * @brief prints the TBST post-order
	 * @details recurses over the TBST in post-order
	 * and prints the values.
	 */
	void TBST::postOrder() const {
		traverse(root, 1);
	}

	/**
	 * @brief traverses the TBST recursively
	 * @details traverses the TBST recursively and prints
	 * the nodes depending on the desired order.
	 * 
	 * @param cur current node being looked at
	 * @param order -1, 0, or 1 for pre, in, and post order
	 * traversals
	 */
	void traverse(Node* cur, int order) {
		if (order == -1) {
			cur.print();
			travers(left sub tree);
			traverse(right sub tree);
		} else if (order == 0) {
			travers(left sub tree);
			cur.print();
			traverse(right sub tree);
		} else if (order == 1) {
			travers(left sub tree);
			traverse(right sub tree);
			cur.print();
		}
	} 

	/**
	 * @brief traverses the TBST and executes a function
	 * @details traverses the TBST and executes the passed
	 * in function
	 * 
	 * @param f the passed in function (insert/remove/contains)
	 * @param cur the current node
	 * @param findSpot determins whether to find a spot for a node (insert)
	 * or to find a specific node (remove/contains/insert)
	 * @param token the token of the node being looked for
	 * @param  success false bool pointer changed to true
	 * if the operation is successful
	 * 
	 * @return a pointer to the node that was opperated on
	 */
	Node* find(Node* (*f)(Node*,string,bool*), Node* cur, bool findSpot, string token, bool& success) {
		if (cur is not NULL) {
			if (the token being searched for is less than cur''s token) {
				set cur''s left child = find(f, cur.left, findSpot, token, &success);
				return cur;
			} else if (the token being searched for is greater than cur''s token) {
				set cur''s right child = find(f, cur.right, findSpot, token, &success);
				return cur;
			} else we found the spot {
				return a call to the function passed in f(cur, token, &success);
			}
		} else if (findSpot) { // if the function is looking for a spot vs a node
			return a call to the function passed in f(cur, token, &success);
		}
	}

	/**
	 * @brief inserts a node
	 * @details inserts a node at the location given
	 * or increments the nodes count if it already exists
	 * 
	 * @param node node to augment
	 * @param token token for making a new node
	 * @param  success false bool pointer changed to true
	 * if the operation is successful
	 * 
	 * @return node created or augmented
	 */
	Node* insert(Node* node, string token, bool& success) {
		success = true;
		if (node != NULL) {
			increment the node''s counter
			return node;
		} else {
			return a new node with the passed in token
		}
	}

	/**
	 * @brief removes a node if found
	 * @details removes the specified node if it exists
	 * 
	 * @param node node to remove
	 * @param s dummy variable for pointer function call
	 * @param  success false bool pointer changed to true
	 * if the operation is successful
	 * 
	 * @return the new node in place of the deleted one
	 * or NULL if the node didn't exist
	 */
	Node* remove(Node* node, string s, bool& success) {
		if (node != NULL) {
			Node* temp = node;
			Node* temp2 = pull up nodes recursively to fill in deleted space;
			temp2.left = temp.left;
			delete temp;
			temp = NULL;
			success = true;
			return temp2;
		} else {
			return NULL;
		}
	}

	/**
	 * @brief checks for a nodes existance
	 * @details checks to see if a node is in the TBST
	 * 
	 * @param node node to check
	 * @param s dummy variable for pointer function call
	 * @param  success false bool pointer changed to true
	 * if the operation is successful
	 * 
	 * @return the node if found or NULL if not found
	 */
	Node* contains(Node* node, string s, bool& success) {
		if (node != NULL) {
			success = true;
			return node;
		} else {
			return NULL;
		}
	}

	/**
	 * @brief pulls up nodes after a remove
	 * @details recursively goes down the right side of the tree as
	 * far as possible and shifts each node up adjusting left children
	 * as it returns
	 * 
	 * @param node node to shift up
	 * @return the node shifted up
	 */
	Node* popUp(Node* node) {
		if (node has right child) {
			Node* temp = popUp(rightChild);
			temp.left = node.left;
			node.left = NULL;
			return node;
		} else if (node has left child but no right) {
			node.right = node.left;
			node.left = NULL;
			return node;
		} else if (node is a leaf) {
			return node;
		}
	}

};


class Iterator {
	/**
	 * @details Default constructors. Creates an iterator standing at the specified
	 *          Node. If non is specified, defaults to root.
	 * 
	 * @param home  the Node at which the iterator will be positioned
	 * @return      An Iterator object at the specified location in the tree.
	 */
	Iterator(Node* home) {
	    currentPtr = home;
	}

	/**
	 * overloaded post-fix++ operator. Advances the iterator to the next item.
	 *
	 * @return      *this to support composite function calls
	 */
	Iterator& operator++() {
	    currentPtr = get the next right node;
	    if(the node is not threaded) {
	        while(there are more nodes to the left)
	            currentPtr = get the next left node;
	    }
	    return *this;
	}

	void print() {
		print out the current node''s data;
	}

};