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
        int pred;  // Predecessor Nodes
        int index;              // index of the Node in the vector
        bool visited;           // Has the node already been visited?
    };

    int n;
public:
    int getN() const;

private:
    // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes;   // The list of nodes being represented

public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, int cap, int dur);
    void updateEdge(int src, int dest, int addCapacity, int addDuration);
    void maxCapacityPath(int src, int sink);
    void maxCapacityAndShortestPath(int src, int sink);
    void cenario1_1Output(int src, int sink);
    void indexNode(int index);
    bool cenario1Bfs(int src, int sink);
    void cenarioDoisQuatro(std::vector<std::vector<int>> v);

    struct compareNodes {
        bool operator()(const Node& n1, const Node& n2){
            return n1.cap < n2.cap;
        }
    };

    void cenario23(int src, int sink);

    void resetGraph();
    bool bfs(int src, int sink, const std::vector<std::vector<int>> &revGraph);
    int edmondsKarp(int src, int sink);
    static void drawPaths(int nrPaths, std::vector<std::vector<int>>paths, std::vector<int>crtFlow);

};


#endif //FEUP_DAL_PROJ2_GRAPH_H