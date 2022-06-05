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

    /**
     * function to add an edge to the graph
     * @param src
     * @param dest
     * @param cap
     * @param dur
     */
    void addEdge(int src, int dest, int cap, int dur);

    /**
     * functions that calculates the path of max capacity to each node
     * @param src
     */
    void maxCapacityPath(int src);

    void cenario12(int src, int sink);
    void cenario11(int src, int sink);

    /**
     * function that associates an index with the respective node
     * @param index
     */
    void indexNode(int index);

    /**
     * functions that implementes a variation of bfs that takes in to account the capacity of the edges
     * @param src
     * @param sink
     * @return
     */
    bool cenario1Bfs(int src, int sink);


    struct compareNodes {
        bool operator()(const Node& n1, const Node& n2){
            return n1.cap < n2.cap;
        }
    };

    void cenario21(int src, int sink);
    void cenario22();
    void cenario23(int src, int sink);

    /**
     * function that implements the bfs algorithm
     * @param src
     * @param sink
     * @return true if there is a path from src to sink and flase otherwise
     */
    int bfs(int src, int sink);

    /**
     * function that implements the Edmonds-Karp algorithm
     * @param src
     * @param sink
     */
    void edmondsKarp(int src, int sink);

    /**
     * function that compares path a and b
     * @param a
     * @param b
     * @return returns true if the first element of the vectors and the size of the vectors are the same or if the first element of vector a is bigger than the first element of vector b and flase otherwise
     */
    static bool comparePaths(const std::vector<int> &a, std::vector<int> &b){
        if(b[0] == a[0])
            return a.size() < b.size();
        return b[0] < a[0];
    }

    void cenario24();
    void cenario25();

    /**
     * function that calculates the time of a path
     * @param v
     * @return the sum of the duration of all the edges in the path
     */
    int calcPathTime(std::vector<int> v);

    /**
     * function that implements a variation of the algorithms cmp earliest start and cmp latest finish
     * @param g
     * @return a vector in witch the first element is the biggest difference between the ef and lf of all nodes and the following elements the index of the nodes with this value
     */
    std::vector<int> cmp_arco_atividade(Graph* g) const;

    /**
     * function that resets resGraph puts maxFlow =0 and clears the vector pahts
     */
    void resetGraph();

    /**
     * function that resets resGraph
     */
    void resetResGraph();

    /**
     * function that draws the paths in paths
     */
    void drawPaths();

    /**
     * function that draws the paths in paths with the groups
     * @param groupSize
     */
    void drawPathsWithGroup(int groupSize);

    /**
     * function that calculates the optimal paretos of a path
     * @param curNode
     * @param sink
     * @param transbordos
     * @param cap
     * @param curTransbordos
     * @param curCap
     * @param path
     * @return cap if foundPath is true and 0 if foundPaht is false
     */
    int paretoOtimos(int curNode, int sink, int &transbordos, int &cap, int curTransbordos, int curCap, std::vector<int> &path);

    int getN() const;
};


#endif //FEUP_DAL_PROJ2_GRAPH_H