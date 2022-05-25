#ifndef FEUP_DAL_PROJ2_GRAPH_H
#define FEUP_DAL_PROJ2_GRAPH_H

#include <vector>
#include <list>
#include <iostream>

class Graph {
    struct Edge {
        int dest;           // Destination Node
        double cap;         // Maximum Capacity of a node
        double crtCap;      // Current Capacity
        double dur;         // Duration of the Crossing
        double crtDur;      // Current Duration of the Crossing
    };

    struct Node {
        list<Edge> adj;     // The list of outgoing edges (to adjacent nodes)
        bool visited;       // Has the node already been visited?
    };

    int n;                     // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes;        // The list of nodes being represented

public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, double cap, double dur);
    void updateEdge(int src, int dest, double addCapacity, double addDuration);
};


#endif //FEUP_DAL_PROJ2_GRAPH_H