/**
 * @file graphm.cpp
 * Purpose: Implementation file for the graph ADT,
 *          using the adjacency matrix data structure.
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

#include "graphm.h"

/**------------------------------------ Constructor *//**
 * @brief Default constructor. Initializes everything with empty data.
 */
GraphM::GraphM() {
    data = new NodeData[MAXNODES];
    size = 0;
    C = new int*[MAXNODES];
    for (int i = 1; i < MAXNODES; i++) {
        C[i] = new int[MAXNODES];
    }
    T = new TableType*[MAXNODES];
    for (int i = 1; i < MAXNODES; i++) {
        T[i] = new TableType[MAXNODES];
    }
    initialize();
}

/**------------------------------------ initialize() *//**
 * @brief initialize arrays and tables to default values and empty objects
 */
void GraphM::initialize() {
    for (int i = 1; i < MAXNODES; i++) {
        for (int j = 1; j < MAXNODES; j++) {
            C[i][j] = 0;
            if (i == j)
                T[i][j].dist = 0;
            else 
                T[i][j].dist = MAX_INT;
            T[i][j].path = 0;
        }
    }
}

/**------------------------------------ Copy constructor *//**
 * @param other Reference to the original graph to be copied
 */
GraphM::GraphM(const GraphM& other) {
    size = other.size;
    copyData(other.data, size);

    C = new int*[MAXNODES];
    for (int i = 1; i < MAXNODES; i++)
        C[i] = new int[MAXNODES];
    copyC(C, other.C, size);

    T = new TableType*[MAXNODES];
    for (int i = 1; i < MAXNODES; i++)
        T[i] = new TableType[MAXNODES];
    copyT(T, other.T, size);
}

/**------------------------------------ copy helper #1 *//**
 * @brief Make a copy of all the nodes in the original graph
 * 
 * @param origData original array of nodes
 * @param size number of nodes in the original graph
 */
void GraphM::copyData(NodeData* origData, int size) {
    data = new NodeData[MAXNODES];
    for (int i = 1; i <= size; i++)
        data[i] = *(new NodeData(origData[i]));
}

/**------------------------------------ copy helper #2 *//**
 * @details Make a copy of the content from the original table and store it
 *          in the corresponding location in the new table
 *          
 * @pre   The tables are expected to be square matrices of the specified size         
 *          
 * @param table Two-dimensional array to populate with copied data
 * @param origTable Two-dimensional array of integer values to be copied over.
 * @param size size of the array
 */
void GraphM::copyC(int** table, int** origTable, int size) {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++)
            table[i][j] = origTable[i][j]; 
    }
}

/**------------------------------------ copy helper #3 *//**
 * @details Make a copy of the TableTypes from the original table and store it
 *          in the corresponding location in the new table
 *          
 * @pre   The tables are expected to be square matrices of the specified size         
 *          
 * @param table Two-dimensional array to populate with copied data
 * @param origTable Two-dimensional array of integer values to be copied over.
 * @param size size of the array
 */
void GraphM::copyT(TableType** table, TableType** origTable, int size) {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            table[i][j].visited = origTable[i][j].visited;
            table[i][j].dist = origTable[i][j].dist;
            table[i][j].path = origTable[i][j].path;
        }
    }
}

/**------------------------------------ Destructor *//**
 * @brief standard destructor
 */
GraphM::~GraphM() {
    makeEmpty();
}

/**------------------------------------ makeEmpty() *//**
 * @brief Deallocate the array and tables of data
 */
void GraphM::makeEmpty() {
    for (int i = 1; i < MAXNODES; i++) {
        delete[] C[i];
        delete[] T[i];
    }
    delete[] C; delete[] T; delete[] data;
    size = 0;
    data = NULL; C = NULL; T = NULL;
}

/**------------------------------------ buildGraph() *//**
 * @brief Build the graph from raw data
 * @details The graph is represented as an adjacency matrix where rows and 
 *          columns represent source and destination nodes respectively.
 *          The edge weight connecting the source and the destination is the
 *          value of the entry.\n
 *          This routine only builds the tree; it has nothing to do with
 *          figuring out any paths, shortest or otherwise.\n
 *          Note: Uses getline from string class, included in nodedata.h
 *          
 * @warning The arrays are 1-indexed.
 * 
 * @param infile reference to the file object containing raw data. Read until
 *          a sentinel value is encountered.
 */             
void GraphM::buildGraph(istream& infile) {
    int fromNode, toNode;              // from and to node ends of edge
    int edgeWeight;                     // clear the graph of memory 

    infile >> size;                    // read the number of nodes
    if (infile.eof()) return;          // stop if no more data

    string s;                          // used to read through to end of line
    getline(infile, s);

    // read graph node information from index 1, leaving 0 empty
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);        // read node descriptions
    }

    // done reading descriptions, read edge data
    for (;;) {
        infile >> fromNode >> toNode >> edgeWeight;
        if ((fromNode == 0 && toNode == 0) || size==0) return; 
        // insert the edge into the adjacency matrix for fromNode
        if (   fromNode > 0 && toNode > 0
            && fromNode <= size && toNode <= size
            && edgeWeight >= 0)
            C[fromNode][toNode] = edgeWeight;
        
        // do not mirror into C[to][from], graph is directed
    }
}

/**------------------------------------ findShortestPath() *//**
 * @brief Dijkstra's shortest path algorithm
 * @details greedily explore "best" neighboring nodes iteratively from the best
 *          one to the worst one.
 * @pre     Graph can be either directed or undirect, but must not
 *          contain negative edge weight.
 */
void GraphM::findShortestPath() {
    for (int i = 1; i <= size; i++) {
        // initialize row i
        for (int j = 1; j <= size; j++) {
            if (C[i][j] != 0) {
                T[i][j].dist = C[i][j];
                T[i][j].path = i;
            }
        }
        // greedily traverses to nearest neighbor, update path/dist, repeat
        int index = shortestPath(i);
        while (index != 0) {
            int pathCost = T[i][index].dist;
            for (int j = 1; j <= size; j++) {
                if (C[index][j] != 0 && pathCost + C[index][j] < T[i][j].dist)
                    updateTable(index, pathCost + C[index][j], i, j);
            }
            index = shortestPath(i);    // explore next-nearest neighbors
        }
    }
}

/**------------------------------------ getMinNeighbor() *//**
 * @brief Extracts index of the nearest neighbor of the given node.
 * @TODO  Determine if minimality should be determined via the C or T table.
 * 
 * @param i index of the source node
 * @return the index of the neighbor node nearest to node `i`
 */
int GraphM::shortestPath(int i) {
    int min = 0;
    for (int j = 1; j <= size; j++) {
        if (C[i][j] != 0 && !T[i][j].visited) {
            // update j if the node is the first encountered or is smaller
            if (min == 0 || C[i][j] < C[i][min])
                min = j;
        }
    }
    if (min != 0)
        T[i][min].visited = true;
    return min;
}

/**------------------------------------ updateTable() *//**
 * @brief update the distance/path table after the greedy algorithm finds a more
 *        optimal path.
 *        
 * @param path the index of the node previous to this node in the min path
 * @param dist the distance from the source (node `from`) to this node
 * @param from the source node
 * @param to the destination node (i.e. this node)
 */
void GraphM::updateTable(int path, int dist, int from, int to) {
    T[from][to].dist = dist;
    T[from][to].path = path;
}

// ----------------------------------------------------------
// -----------------------------------   Printing routines --
// ----------------------------------------------------------

/**------------------------------------ displayAll() *//**
 * @brief public graph textual output
 * @details Displays shortest path information from every node to every
 *          reachable node.
 */
void GraphM::displayAll() const {    
    cout << GRAPH_HEADER << endl;
    cout << H_LINE << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for (int j = 1; j <= size; j++) {
            if (i != j) {
                cout << "\t\t   ";         // padded whitespace for data output
                printRow(i,j);
            }
        }
    }
    cout << H_LINE << endl;
    cout << "End of graph printout\n" << endl;
}

/**------------------------------------ printRow() *//**
 * @brief   Helper subroutine for displayAll()
 * @details Displays shortest path info for one row. Expects GIGO response,
 *          although this subroutine is to be used internally only.
 * 
 * @param from index of the source node
 * @param to index of the destination node
 */
void GraphM::printRow(int from, int to) const {
    if(from > size || to > size) return;
    cout << setw(10) << from << setw(10) << to;
    if (T[from][to].dist == MAX_INT)
        cout <<  setw(10) << "----";          // no way to get there
    else {
        cout << setw(10) << T[from][to].dist << "\t";
        // traverses the shortest path backwards, from dest to src
        printPathForward(from, to);
    }
    cout << endl;
}

/**------------------------------------ printBackwards() *//**
 * @brief helper subroutine for printRow()
 * @details post-order recursion to achieve forward printing (from src to dest)
 * 
 * @param from index of source node
 * @param to index of current destination node (a node along the min path)
 */
void GraphM::printPathForward(int from, int to) const {
    if(to < 1) return;
    else {
        printPathForward(from, T[from][to].path);     // postorder recursion
        cout << setw(3) << to;                        // for reverse printing
    }
}



/**------------------------------------ display() *//**
 * @brief Displays detailed min path output for one route
 * 
 * @param from index of source node
 * @param to   index of destination node
 */
void GraphM::display(int from, int to) const {
    printRow(from, to);
    printRowForwardInText(from, to);
}

/**------------------------------------ printRowForwardInText() *//**
 * @brief   display() helper
 * @details Post-order recursion to achieve forward printing (from src to dest)
 *          of the min path requested in string presentational format.
 * 
 * @param from source node
 * @param to current destination node
 */
void GraphM::printRowForwardInText(int from, int to) const {
    if(to < 1) return;
    else {
        printRowForwardInText(from, T[from][to].path);
        cout << data[to] << endl;
    }
}
