//
// Created by ASUS on 25/05/2022.
//

#include "../includes/TravelAgency.h"

TravelAgency::TravelAgency(Graph graph) : graph(std::move(graph)){
}

void TravelAgency::doisUm(int s, int t) {
    resetGraph();
    std::cout << edmondsKarp(s,t);

}

int TravelAgency::edmondsKarp(int s, int t){
    int max_flow = 0;
    int u, v;

    while(bfs(s, t)){
        int path_flow = INT_MAX;
        for (v = t; v != s; v = graph.nodes[v].pred) {
            u = graph.nodes[v].pred;
            for(auto e : graph.nodes[u].adj){
                if(e.dest == v){
                    path_flow = std::min(path_flow, e.revCap);
                }
            }
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = graph.nodes[v].pred) {
            u = graph.nodes[v].pred;
            for(auto e : graph.nodes[u].adj){
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

bool TravelAgency::bfs(int s, int t){
    std::queue<int> q; // queue of unvisited nodes
    q.push(s);
    graph.nodes[s]. visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();

        for (auto e : graph.nodes[u].adj) {
            int w = e.dest;
            graph.nodes[w].pred = u;
            if(!graph.nodes[w].visited){
                if (w == t) {
                    return true;
                }
                q.push(w);
                graph.nodes[w].visited = true;
            }
        }
    }
    return false;
}

void TravelAgency::resetGraph() {
    for (int i=1; i<=graph.n; i++) {
        graph.nodes[i].visited = false;
        graph.nodes[i].pred = -1;
        for(auto e: graph.nodes[i].adj){
            e.crtDur = 0;
            e.crtCap = 0;
            e.revCap = 0;
        }
    }
}
