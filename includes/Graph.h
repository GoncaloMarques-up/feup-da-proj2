#ifndef FEUP_DAL_PROJ2_GRAPH_H
#define FEUP_DAL_PROJ2_GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <float.h>

using namespace std;

class Graph {
    struct Edge {
        int dest;           // Destination Node
        double cap;         // Maximum Capacity of a node
        double dur;         // Duration of the Crossing
    };

    struct Node {
        list<Edge> adj;     // The list of outgoing edges (to adjacent nodes)
        double totalCap;    // Total Capacity Acumulated
        int pred;           // ID of the Predecessor Node
        bool visited;       // Has the node already been visited?
    };

    int n;                     // Graph size (vertices are numbered from 1 to n)
    bool hasDir = true;        // false: undirect; true: directed
    vector<Node> nodes;        // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);
};


#endif //FEUP_DAL_PROJ2_GRAPH_H