#ifndef FEUP_DAL_PROJ2_GRAPH_H
#define FEUP_DAL_PROJ2_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <iostream>

class Graph {
    struct Edge {
        int dest;               // Destination Node
        int cap;                // Maximum Capacity of a node
        int crtCap = 0;         // Current Capacity
        int dur;                // Duration of the Crossing
        int crtDur = 0;         // Current Duration of the Crossing
        int revCap;             // Capacity of the Reverse Edge
    };

    struct Node {
        std::list<Edge> adj;     // The list of outgoing edges (to adjacent nodes)
        int dist;                // Distance to the Initial Node
        int pred;                // Predecessor Node
        bool visited;            // Has the node already been visited?
    };

public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, int cap, int dur);
    void updateEdge(int src, int dest, int addCapacity, int addDuration);

    int n;                      // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes;    // The list of nodes being represented

    void cenarioDoisUm(int s, int t);

    void resetGraph();
    bool bfs(int s, int t);
    int edmondsKarp(int s, int t);
};


#endif //FEUP_DAL_PROJ2_GRAPH_H