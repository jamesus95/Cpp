#include "nodedata.h"
#include <iomanip>          // to format output

#define MAXNODES 101                // data are stored with 1-indexing, not 0
#define MAX_DESC_LENGTH 50
#define MAX_INT 2147483547          // 100 less than 2^32-1, just to add an
                                    // extra layer of overflow protection.

#define GRAPH_HEADER "\nDescription\t\tFrom node   To node   Dijkstra's  path"
#define H_LINE "---------------------------------------------------------------"

using namespace std;

/**
 * @class GraphM graphm.h
 * 
 * Adjacency matrix implementation of the graph data structure. 
 * 
 * Limits and Assumptions:
 * 
 * - There are at most 100 nodes per graph
 * - Each node has a description not exceeding 50 characters in length
 * - Expect Garbage-In-Garbage-Out (GIGO) behavior. Inputs need to be sensible;
 *   out-of-bound output requests will typically get ignored and unreliable
 *   results caused by bad input are not checked (e.g. negative edge weight).
 */

class GraphM {

private:
     
    /* <!------------------- private struct: TableType -->
     * @brief Each node's min path info can be referenced in this struct.
     * @details Each `TableType` instance contains information about the
     *          min path from a "source" node to a "destination" node.
     *          The source is specified in the row index of this instance.
     *          The destination is not explicitly defined. Each node points back
     *          to the previous node in the minimum path. In that respect,
     *          every node is a potential destination. The full min path for
     *          each node can be determined by tracing back the previous 
     *          nodes in the path.
     */
    struct TableType {
        bool visited;       // whether the Node has been visited
        int dist;           // current min distance from the source (row)
        int path;           // index of the previous node in the min path from
                            // the source to... this node
        
        TableType() {       // Constructor
            visited = false;
            dist = MAX_INT;
            path = 0;
        }
    };

    NodeData* data;                // information array about the nodes
    int size;                      // number of nodes in graph
    int** C;                       // adjacency matrix, distance cost table
    TableType** T;                 // stores min path info

    // ------------------------------- private helpers
    // ----- Constructor helper
    void initialize();                                
    void copyData(NodeData*, int);                    
    void copyC(int**, int**, int);             
    void copyT(TableType**, TableType**, int); 

    // ----- Shortest Path Helper
    int shortestPath(int);                // retrieve index of nearest neighbor
    void updateTable(int, int, int, int); // update when shorter route is found
    void printPathForward(int, int) const;      // recursive print helper
    void printRow(int, int) const;              // modular row print routine
    void printRowForwardInText(int, int) const; // min path in text

public:

    /**<!---------------------------------- Constructors --> */
    GraphM();
    GraphM(const GraphM&);
    ~GraphM();

    /**<!---------------------------------- Public routines --> */
    // ------- Getters
    void displayAll() const;
    void display(int, int) const;

    // ------- Setters
    void makeEmpty();
    void buildGraph(istream&);
    void findShortestPath();      // Dijkstra's algorithm
};