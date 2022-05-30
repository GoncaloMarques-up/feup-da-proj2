//
// Created by ASUS on 22/05/2022.
//

#include "../includes/Graph.h"

Graph::Graph(int num) : n(num), nodes(num) {}

void Graph::addEdge(int src, int dest, int cap, int dur) {
    nodes[src].adj.push_back({dest, cap, 0, dur, 0});
}

void Graph::updateEdge(int src, int dest, int addCapacity, int addDuration){
    for(auto e: nodes[src].adj){
        if(e.dest == dest){
            e.crtCap += addCapacity;
            e.crtDur += addDuration;
        }
    }
}

void Graph::maxCapacityPath() {
    int src, sink;
    std::cout << "Introduza a Paragem Inicial e a Final [1-" << n << "]\n";
    std::cin >> src >> sink;
    for(auto &node : nodes){
        node.cap = 0;
        node.pred.push_back(-1);
    }

    nodes[src-1].cap = INT_MAX;

    std::priority_queue<Node, std::vector<Node> ,compareNodes> queue;

    queue.push(nodes[src-1]);

    while(!queue.empty()){
        Node node = queue.top();
        queue.pop();
        for(Edge edge : node.adj){
            int min = std::min(node.cap, edge.cap);
            Node &dest = nodes[edge.dest];
            if(min > dest.cap){
                dest.cap = min;
                dest.pred[0] = node.index;
                queue.push(dest);
            }
        }
    }

    std::vector<int> v;
    Node *node = &nodes[sink-1];
    while(node->pred[0] != -1){
        v.push_back(node->index);
        node = &nodes[node->pred[0]];
    }

    v.push_back(node->index);
    std::reverse(v.begin(), v.end());

    std::cout << "Capacidade Maxima: " << nodes[sink-1].cap << '\n' << "Encaminhamento: ";

    for(int i = 0; i < v.size(); i++){
        if(i != v.size()-1)
            std::cout << v[i] + 1 << "->";
        else
            std::cout << v[i]+1 << "\n";
    }
}

void Graph::indexNode(int index) {
    nodes[index].index = index;
}


void Graph::cenarioDoisUm(int s, int t) {
    resetGraph();
    std::cout << "The Max Flow is: " << edmondsKarp(s-1,t-1) << std::endl;

}

int Graph::edmondsKarp(int s, int t){
    int maxFlow = 0;

    std::vector<std::vector<int>>resGraph;
    resGraph.resize(n, std::vector<int>(n));

    std::vector<std::vector<int>>paths;
    paths.resize(n, std::vector<int>(n));

    for(int i = 0; i<n; i++){
        for(auto e : nodes[i].adj){
            resGraph[i][e.dest] = e.cap;
        }
    }


    while(bfs(s, t, resGraph)){

        int pathFlow = INT_MAX;
        for (int j = t; j != s; j = nodes[j].pred.back()) {
            int i = nodes[j].pred.back();
            pathFlow = std::min(pathFlow, resGraph[i][j]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (int j = t; j != s; j = nodes[j].pred.back()) {
            int i = nodes[j].pred.back();
            resGraph[i][j] -= pathFlow;
            resGraph[j][i] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }


    return maxFlow;
}

bool Graph::bfs(int s, int t, const std::vector<std::vector<int>> &resGraph){
    std::queue<int> q;
    q.push(s);
    nodes[s].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (!nodes[i].visited && resGraph[u][i] > 0) {
                if (i == t) {
                    nodes[i].pred.push_back(u);
                    return true;
                }
                q.push(i);
                nodes[i].pred.push_back(u);
                nodes[s].visited = true;
            }
        }
    }

    return false;
}

void Graph::resetGraph() {
    for (int i=0; i<n; i++) {
        nodes[i].visited = false;
        nodes[i].pred.clear();
    }
}
