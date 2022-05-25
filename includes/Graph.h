#ifndef FEUP_DAL_PROJ2_GRAPH_H
#define FEUP_DAL_PROJ2_GRAPH_H

#include <vector>
#include <list>
#include <iostream>

class Graph {
    struct Edge {
        int dest;           // Destination Node
        int cap;         // Maximum Capacity of a node
        int crtCap = 0;      // Current Capacity
        int dur;         // Duration of the Crossing
        int crtDur = 0;      // Current Duration of the Crossing
    };

    struct Node {
        std::list<Edge> adj;     // The list of outgoing edges (to adjacent nodes)
        bool visited;       // Has the node already been visited?
    };

    int n;                     // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes;        // The list of nodes being represented

public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, int cap, int dur);
    void updateEdge(int src, int dest, int addCapacity, int addDuration);
};


#endif //FEUP_DAL_PROJ2_GRAPH_H