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
        int dur;                // Duration of the Crossing
        int es;
        int ef;
    };

    struct Node {
        std::list<Edge> adj;    // The list of outgoing edges (to adjacent nodes)
        int cap;                // Capacity of a node(useful for 1.1 and 1.2)
        int pred;               // Predecessor Nodes
        int index;              // index of the Node in the vector
        bool visited;           // Has the node already been visited?
        int es;
        int lf;
        int ef;
        int grauE;
        int grauS;
    };

    int n;                                  // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes;                // The list of nodes being represented
    std::vector<std::vector<int>>resGraph;  // Residual Graph
    std::vector<std::vector<int>> paths;    // Paths from src to sink
    int maxFlow{};                            // Graph Max Flow

    int groupSize{};                          // Group Size from 2.1 and 2.2
    int src21{};                              // Most Recent Source Node from 2.1
    int sink21{};                             // Most Recent Sink Node from 2.1
public:
    explicit Graph(int nodes);

    void addEdge(int src, int dest, int cap, int dur);

    void maxCapacityPath(int src);
    void cenario12(int src, int sink);
    void cenario11(int src, int sink);
    void indexNode(int index);
    bool cenario1Bfs(int src, int sink);


    struct compareNodes {
        bool operator()(const Node& n1, const Node& n2){
            return n1.cap < n2.cap;
        }
    };

    void cenario21(int src, int sink);
    void cenario22();
    void cenario23(int src, int sink);
    int bfs(int src, int sink);
    void edmondsKarp(int src, int sink);

    static bool comparePaths(const std::vector<int> &a, std::vector<int> &b){
        if(b[0] == a[0])
            return a.size() < b.size();
        return b[0] < a[0];
    }

    void cenario24();
    void cenario25();
    int calcPathTime(std::vector<int> v);
    std::vector<int> cmp_arco_atividade(Graph* g) const;

    void resetGraph();
    void resetResGraph();
    void drawPaths();
    void drawPathsWithGroup(int groupSize);
    int paretoOtimos(int curNode, int sink, int &transbordos, int &cap, int curTransbordos, int curCap, std::vector<int> &path);
    int getN() const;
};


#endif //FEUP_DAL_PROJ2_GRAPH_H