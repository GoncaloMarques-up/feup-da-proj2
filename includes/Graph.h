#ifndef FEUP_DAL_PROJ2_GRAPH_H
#define FEUP_DAL_PROJ2_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <set>
#include <iostream>
#include <climits>
#include <algorithm>

class Graph {
    struct Edge {
        int dest;               // Destination Node
        int cap;                // Maximum Capacity of an edge
        int crtCap = 0;         // Current Capacity
        int dur;                // Duration of the Crossing
        int crtDur = 0;         // Current Duration of the Crossing
        int revCap;             // Capacity of the Reverse Edge
    };

    struct Node {
        std::list<Edge> adj;    // The list of outgoing edges (to adjacent nodes)
        int dist;               // Distance to the Initial Node
        int cap;                // Capacity of a node(useful for 1.1 and 1.2)
        std::vector<int> pred;  // Predecessor Nodes
        int index;              // index of the Node in the vector
        bool visited;           // Has the node already been visited?
    };

    int n;                     // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes;   // The list of nodes being represented

public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, int cap, int dur);
    void updateEdge(int src, int dest, int addCapacity, int addDuration);
    void maxCapacityPath();
    void indexNode(int index);

    struct compareNodes {
        bool operator()(const Node& n1, const Node& n2){
            return n1.cap < n2.cap;
        }
    };

    void cenarioDoisUm(int s, int t);

    void resetGraph();
    bool bfs(int s, int t, const std::vector<std::vector<int>> &revGraph);
    int edmondsKarp(int s, int t);
    void findPath(int s, int t, int a, std::vector<std::vector<int>> &paths, std::vector<std::vector<int>> &oPaths);
    void discoverPaths(int s, int t);
};


#endif //FEUP_DAL_PROJ2_GRAPH_H