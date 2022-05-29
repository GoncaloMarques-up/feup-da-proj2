//
// Created by ASUS on 22/05/2022.
//

#include "../includes/Graph.h"

Graph::Graph(int num) : n(num), nodes(num) {}

void Graph::addEdge(int src, int dest, int cap, int dur) {
    nodes[src].adj.push_back({dest-1, cap, 0, dur, 0, 0});
}

void Graph::updateEdge(int src, int dest, int addCapacity, int addDuration){
    for(auto e: nodes[src].adj){
        if(e.dest == dest){
            e.crtCap += addCapacity;
            e.crtDur += addDuration;
        }
    }
}

void Graph::cenarioDoisUm(int s, int t) {
    resetGraph();
    std::cout << "The Max Flow is: " << edmondsKarp(s,t) << std::endl;

}

int Graph::edmondsKarp(int s, int t){
    int max_flow = 0;
    int u, v;

    while(bfs(s, t)){
        int path_flow = INT_MAX;
        for (v = t; v != s; v = nodes[v].pred) {
            u = nodes[v].pred;
            for(auto e : nodes[u].adj){
                if(e.dest == v){
                    path_flow = std::min(path_flow, e.revCap);
                }
            }
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = nodes[v].pred) {
            u = nodes[v].pred;
            for(auto e : nodes[u].adj){
                if(e.dest == v){
                    e.crtCap -= path_flow;
                    e.revCap += path_flow;
                }
            }
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }
    return max_flow;
}

bool Graph::bfs(int s, int t){
    std::queue<int> q; // queue of unvisited nodes
    q.push(s);
    nodes[s]. visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();

        for (auto e : nodes[u].adj) {
            int w = e.dest;
            nodes[w].pred = u;
            if(!nodes[w].visited){
                if (w == t) {
                    return true;
                }
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
    return false;
}

void Graph::resetGraph() {
    for (int i=0; i<n; i++) {
        nodes[i].visited = false;
        nodes[i].pred = -1;
        for(auto e: nodes[i].adj){
            e.crtDur = 0;
            e.crtCap = 0;
            e.revCap = 0;
        }
    }
}