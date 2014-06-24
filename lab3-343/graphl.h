#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include <string>
#include <iomanip>

#define DEFAULT_SIZE 101    // 1-indexing, 100 nodes at max
#define H_LINE "---------------------------------------------------------------"

using namespace std;

/**
 * @class GraphL graphl.h
 * 
 * Adjacency list implementation of the graph data structure. 
 * 
 * Limits and Assumptions:
 * 
 * - There are at most 100 nodes per graph
 * - Each node has a description not exceeding 50 characters in length
 * - Expect Garbage-In-Garbage-Out (GIGO) behavior. Inputs need to be sensible;
 *   out-of-bound output requests will typically get ignored and unreliable
 *   results caused by bad input are not checked (e.g. negative edge weight).
 * - Does not support edge weight. This implementation is done only to perform
 *   depth-first processing.
 * - Expect well-formed data files. Ignores bad data entries from data file.  
 */

class GraphL {

private:

    /**<!---------------------------------- EdgeNode struct -->
     * @brief   A neighboring Node of a GraphNode. These are NOT "physically
     *          on the graph". They are just a record of the edges.
     * @details Each EdgeNode is a "private property" of a unique GraphNode; it
     *          represents an edge from this "master" GraphNode to another
     *          GraphNode on the graph.
     *          An EdgeNode E accessible via GraphNode N's `head` pointer
     *          represents a connection (an edge) from the actual GraphNode N to
     *          the actual GraphNode E. If such an EdgeNode E doesn't exist,
     *          GraphNode E is not a neighbor from GraphNode N. \n\n
     *          
     *          If the "master" GraphNode N has multiple neighbors, the first
     *          EdgeNode of N will point to the next EdgeNode of N, creating a
     *          linked list of neighbors of N. This list's ordering reflects
     *          the order of reading from the data file.
     */
    struct EdgeNode {
        int toIndex;    // index (in the GraphNode array) of the neighboring
                        // GraphNode that this EdgeNode represents
        EdgeNode* next; // pointer to the "next" EdgeNode
    };

    /**<!---------------------------------- GraphNode struct -->
     * @brief This struct is treated as the actual nodes on the graph
     * @details These are considered the source nodes of various paths.
     *          A path from node S to node T would start from GraphNode S
     *          to EdgeNode R to EdgeNode T.
     *          A path from node T to node S would start from GraphNode T
     *          to EdgeNode R to EdgeNode S.
     */
    struct GraphNode {
        EdgeNode* head;     // the first EdgeNode (neighbor) of this node
        bool visited;       // processing status of this Node in a traversal
        string s;           // content contained in this Node
    };

    GraphNode** nodes;      // array of actual nodes visible on the graph
    int size;               // size of the graph (number of nodes)

    // <!---------------------------------- Private helpers -->

    void makeAllUnvisited();            // initializer helper before a traversal
    void exploreNodeEdge(int, int&);    // depth-first processing of an edgenode
    void deleteNodes(EdgeNode*);        // destructor helper / delete the edges



public:

    // <!---------------------------------- Class basics -->
    GraphL();
    ~GraphL();

    // <!---------------------------------- Public functionalities -->
    void buildGraph(istream&);
    void displayGraph();
    void depthFirstSearch();

};

#endif