The design documentation is written in .cpp format to provide color-coding.
Use your editor of choice to read.

Please view the pseudo code together with the respective .h files for
added comprehensiveness.

The directory "lab5 drawings" contain graphical presentation of the processes:
---traversing a tree in-order iteratively using thread links
---how to remove a node and maintain threads/links/tree structure

The files test*.cpp contain unit tests for each respective class.

The file lab5test.cpp contains the test for the whole program as 
specified in the requirements doc.


[Optional reading from this point on.]


=================================================================================
============ Answers to preliminary questions (also available in Doc) ===========
=================================================================================

1. How can we distinguish threads from real child pointers?
	Have boolean flags to determine whether a pointer is a normal pointer or
	a thread.

2. What are the potential advantages of using threaded trees?
	Iterative traversal of tree is possible and more memory-efficient on the stacks

3. Does your implementation use any more memory than the "plain" BST implementation?
	Yes, see (1).
	If yes, can you think of any (obscure?) way to eliminate this extra memory requirement?
	Yes, only one thread is needed for in-order traversal => use 1 boolean instead of 2.

4. What is your implementation/test plan.
	Write from Data --> Node --> Tree // test all 3 classes' unit functions
	Implement Threaded build           // test in-order traversal
	Implement in-order iterator          // test iterator with various tree shapes
	Implement tree re-balancing        // test balancing on various tree shapes
	If time permits, implement functional programming into the iterator

5. What steps must you go through to change the vanilla BST implementation to a TBST?
	While adding child nodes, append threads appropriately with regards to the parent's threads. In detail:
	- If child < parent: thread to parent
	- If child > parent: no thread, right pointer points to NULL

6. Which BST methods need to be modified/overriden and which will work as is?
	Working as is:
	- begin()
	- end()                    // these 2 are for the iterator
	- constructors
	- balance()
	- contains() may remain intact if we wish to search recursively
	- isEmpty()
	- findParentOf()
	Modified:
	- Node::isLeaf() now needs to check for threaded-ness in addition to NULL-ness
	- print() now can use the iterator to abstract traversal details away
	- add() or insert() needs to create threads and modify threaded-ness
	- remove() needs to modify threaded-ness
	- contains() may be modified if we wish to search iteratively

7. What are the advantages and disadvantages of modifying the Carrano BST versus sub-classing from it?
	Modifying:
	---Advantage:
	------Able to fix bugs in his code
	------
	---Disadvantages:
	------Time consuming
	Subclassing: other way around