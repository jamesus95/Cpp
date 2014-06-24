/**
 * @file graphl.cpp
 * Purpose: Implementation file for the graph ADT,
 *          using the adjacency list data structure.
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        April 29 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the public routine(s)
 * that uses them.
 */

/**
 * @mainpage Graph ADT algorithms
 * 
 * @section Introduction
 * This project implements the Graph ADT using both adjacency matrix and
 * adjacency list data structures.\n
 * Each implementation is used for a different task:
 * - Dijkstra's shortest path algorithm
 * - Depth-first processing
 * 
 * @section Assumptions
 * - Each graph can have at most 100 nodes.
 * - Each node can have a description of length 50 characters at maximum.
 * - Adjacency-Matrix Graphs do not support negative edge weight, because 
 *   Dijkstra's algorithm does not work with those.
 */

#include "graphl.h"

/**<!---------------------------------- Constructor -->
 * @brief Default graph constructor
 * @details Initializes graph to NULL nodes
 */
GraphL::GraphL() {
    nodes = new GraphNode*[DEFAULT_SIZE];
    for (int i = 0; i < DEFAULT_SIZE; i++)
        nodes[i] = NULL;
}

/**<!---------------------------------- Destructor -->
 * @brief Destructor
 * @details Deallocate the edges, then deallocate the nodes
 */
GraphL::~GraphL() {
    for (int i = 1; i <= size; i++) {
        if(nodes[i] != NULL) {
            deleteNodes(nodes[i]->head);    // helper to delete the edges
            nodes[i]->head = NULL;
        }
    }
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (nodes[i] != NULL)
            delete nodes[i];
    }
    delete[] nodes; nodes = NULL;
}

/**<!---------------------------------- deleteNodes() -->
 * @brief private helper to deallocate EdgeNodes
 * @details Post-order deletion of EdgeNodes in a linkedlist.
 * 
 * @param toDelete pointer to the EdgeNode that needs to be deleted
 */
void GraphL::deleteNodes(EdgeNode* toDelete) {
    if (toDelete != NULL) {
        deleteNodes(toDelete->next);
        toDelete->next = NULL;
        delete toDelete;
    }
}

/**<!---------------------------------- buildGraph() -->
 *
 * @brief   public graph initializer from data file.
 * @details Build a graph with nodes, edges, and edge weights
 * @pre     Assume data file to be well-formed. See example data file for
 *          the format.\n
 *          Assume a maximum of 100 nodes, each having a description at no more
 *          than 50 characters long.
 * @warning Invalid data entries are ignored (negative edge weights, overflow
 *          references, etc.)   
 *          
 * @param infile    reference to the istream object containing the data file's 
 *                  content
 */
void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;
    infile >> size;             // read size
    if (infile.eof()) { 
        size = 0;
        return;
    }

    // consume the rest of the line for safety
    string s;
    getline(infile, s);

    // read nodes' descriptions
    for (int i = 1; i <= size; i++) {
        GraphNode* newGraphNode = new GraphNode();  // allocate node
        newGraphNode->head = NULL;
        newGraphNode->visited = false;
        getline(infile, newGraphNode->s);           // write content
        nodes[i] = newGraphNode;                    // store into array
    }

    // read edge data
    for (;;) {
        infile >> fromNode >> toNode;
        if ((fromNode == 0 && toNode == 0) || size == 0) return;
        if (fromNode > 0 && toNode > 0 && fromNode <= size && toNode <= size) {
            EdgeNode* newNode = new EdgeNode();     // allocate node
            newNode->next = nodes[fromNode]->head;  // write content
            newNode->toIndex = toNode;              // chain into linkedlist..
            nodes[fromNode]->head = newNode;        // ..in FILO order
        }
    }
}

/**<!---------------------------------- displayGraph() -->
 * @brief   public method to output the graph's string representation
 * @details Displays to standard output.
 */
void GraphL::displayGraph() {
    cout << "\nStart of graph output" << endl;
    cout << H_LINE << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node" << setw(3) << i << "\t\t" << nodes[i]->s << endl;
        EdgeNode* current = nodes[i]->head;
        while (current != NULL) {
            cout << "   edge" << setw(3) << i 
                << setw(3) << current->toIndex << endl;
            current = current->next;
        }
        cout << endl;
    }
    cout << H_LINE << endl;
}

/**<!---------------------------------- depthFirstSearch() -->
 * @brief   Depth-first traversal and processing of the graph.
 * @warning Not actually a search routine.
 */
void GraphL::depthFirstSearch() {
    cout << "\n\nDepth-first Ordering: ";
    makeAllUnvisited();
    int visitCount = 0;
    int node = 1;
    while (visitCount < size) {
        if (!nodes[node]->visited) {
            exploreNodeEdge(node, visitCount);
            cout << endl;
        }
        node++;     // go through the GraphNodes one by one
    }
    cout << endl;
}

/**<!---------------------------------- makeAllUnvisited() -->
 * @brief   Traversal initializer.
 * @details Clear all the nodes' visit status from a previous processing step.
 */
void GraphL::makeAllUnvisited() {
    for (int i = 1; i <= size; i++)
        nodes[i]->visited = false;
}

/**<!---------------------------------- exploreNodeEdge() -->
 * @brief   private helper to process edge nodes in depth-first order
 * 
 * @param   node        current EdgeNode being explored
 * @param   visitCount  Processing record of the graph
 */
void GraphL::exploreNodeEdge(int node, int& visitCount) {
    cout << node << " ";                            // process
    nodes[node]->visited = true;                    // mark 
    visitCount++;                                   // keep record

    // move on to next nodes in depth-first order
    EdgeNode* e = nodes[node]->head;                // start at path's head
    while (e != NULL) {
        if (!nodes[e->toIndex]->visited)
            exploreNodeEdge(e->toIndex, visitCount);// go to next node in path
        e = e->next;                                // consume and repeat
    }
}
