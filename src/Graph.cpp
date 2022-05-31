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

void Graph::maxCapacityPath(int src, int sink) {
    for(auto &node : nodes){
        node.cap = 0;
        node.pred = -1;
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
                dest.pred = node.index;
                queue.push(dest);
            }
        }
    }

    std::vector<int> v;
    Node *node = &nodes[sink-1];
    while(node->pred != -1){
        v.push_back(node->index);
        node = &nodes[node->pred];
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

void Graph::cenarioDoisQuatro(int s, int t) {
    int time = 0;
    int aux = t;
    int org = nodes[t].pred;
    while (org != s){
        for (auto it : nodes[org].adj){
            if (it.dest == aux){
                time += it.dur;
                break;
            }
        }
        aux = org;
        org = nodes[org].pred;
    }
    std::cout << "The group will get together in the destination " << time << " minutes after they leave";
}


void Graph::cenario23(int s, int t) {
    resetGraph();
    if(!edmondsKarp(s-1,t-1)){
        std::cout << "Nao foi Encontrado um Caminho entre as Paragens que Especificou.\n\n";
    }

}

int Graph::edmondsKarp(int s, int t){
    int maxFlow = 0;

    std::vector<std::vector<int>>resGraph;
    resGraph.resize(n, std::vector<int>(n));

    std::vector<std::vector<int>>paths;
    std::vector<int>crtFlow;

    for(int i = 0; i<n; i++){
        for(auto e : nodes[i].adj){
            resGraph[i][e.dest] = e.cap;
        }
    }

    int pathNumber=0;

    while(bfs(s, t, resGraph)){

        int pathFlow = INT_MAX;
        for (int j = t; j != s; j = nodes[j].pred) {
            int i = nodes[j].pred;
            pathFlow = std::min(pathFlow, resGraph[i][j]);
        }

        std::vector<int> newPath;
        // update residual capacities of the edges and
        // reverse edges along the path

        for (int j = t; j != s; j = nodes[j].pred) {
            int i = nodes[j].pred;
            resGraph[i][j] -= pathFlow;
            resGraph[j][i] -= pathFlow;
            newPath.push_back(j);
        }
        newPath.push_back(s);
        paths.push_back(newPath);
        pathNumber++;

        // Add path flow to overall flow
        maxFlow += pathFlow;
        crtFlow.push_back(pathFlow);
    }
    drawPaths(pathNumber, paths, crtFlow);

    std::cout << "Numero Maximo de Passageiros: " << maxFlow << "\n\n";
    return maxFlow;
}

void Graph::drawPaths(int nrPaths, std::vector<std::vector<int>>paths, std::vector<int> crtFlow){
    for(int i=0; i<nrPaths; i++){
        std::reverse(paths[i].begin(), paths[i].end());
    }

    for(int i=0; i<nrPaths; i++){
        std::cout << "Group " << i+1 << ": ";
        for(auto node : paths[i]){
            std::cout << node+1;
            if(node==paths[i].back()){
                std::cout << " | Tamanho do Grupo: " << crtFlow[i] <<"\n";
            }else{
                std::cout << " -> ";
            }
        }
    }
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
                    nodes[i].pred = u;
                    return true;
                }
                q.push(i);
                nodes[i].pred = u;
                nodes[s].visited = true;
            }
        }
    }

    return false;
}

void Graph::resetGraph() {
    for (int i=0; i<n; i++) {
        nodes[i].visited = false;
    }
}

int Graph::getN() const {
    return n;
}
