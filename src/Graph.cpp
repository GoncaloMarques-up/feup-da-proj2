//
// Created by ASUS on 22/05/2022.
//

#include <chrono>
#include "../includes/Graph.h"

Graph::Graph(int num) : n(num), nodes(num) {}

void Graph::addEdge(int src, int dest, int cap, int dur) {
    nodes[src].adj.push_back({dest, cap, dur});
}

void Graph::maxCapacityPath(int src) {
    for(Node &node : nodes){
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
}


void Graph::cenario12(int src, int sink) {
    if (cenario1Bfs(src, sink)) {
        int mintransbordos = -1, transbordos = -1;
        int minCap = nodes[sink - 1].cap;
        int it = sink - 1;
        while (it != src - 1) {
            mintransbordos++;
            it = nodes[it].pred;
        }
        maxCapacityPath(src);
        int maxCap = nodes[sink - 1].cap;
        it = sink - 1;
        while (it != src - 1) {
            transbordos++;
            it = nodes[it].pred;
        }
        std::vector<int> shortPath, longPath;

        for(Node &node : nodes){
            node.visited = false;
        }

        paretoOtimos(src - 1, sink, mintransbordos, minCap, -1, INT_MAX, shortPath);

        for(Node &node : nodes){
            node.visited = false;
        }

        paretoOtimos(src-1, sink, transbordos, maxCap, -1, INT_MAX, longPath);

        if(shortPath == longPath){
            std::reverse(shortPath.begin(), shortPath.end());
            std::cout << "caminho com menos transbordos e maior capacidade (os pareto otimos são iguais): \n" << "capacidade: " << minCap << "\n" << "caminho: ";

            for (int node: shortPath) {
                std::cout << node;
                if (node != sink)
                    std::cout << " -> ";
            }
            std::cout << "\n";
        }
        else{
            std::reverse(shortPath.begin(), shortPath.end());
            std::cout << "caminho com menos transbordos: \n" << "capacidade: " << minCap << "\n" << "caminho: ";

            for (int node: shortPath) {
                std::cout << node;
                if (node != sink)
                    std::cout << " -> ";
            }
            std::cout << "\n numero de transbordos: " << mintransbordos << "\n";

            std::reverse(longPath.begin(), longPath.end());
            std::cout << "caminho com maior capacidade: \n" << "capacidade: " << maxCap << "\n" << "caminho: ";

            for (int node: longPath) {
                std::cout << node;
                if (node != sink)
                    std::cout << " -> ";
            }
            std::cout << "\n numero de transbordos: " << transbordos << "\n\n";
        }
    } else {
        std::cout << "não existe caminho entre os nós " << src << " e " << sink << std::endl;
    }
}

int Graph::paretoOtimos(int curNode, int sink, int &transbordos, int &cap, int curTransbordos, int curCap, std::vector<int> &path){
    if((curTransbordos == transbordos && curNode != sink-1) || nodes[curNode].visited){
        return 0;
    }

    if(curNode == sink-1){
        path.clear();
        path.push_back(curNode+1);
        if(curTransbordos < transbordos)
            transbordos = curTransbordos;
        return curCap;
    }

    int capacity;
    bool foundPath = false;
    int count = 0;

    for(Edge edge : nodes[curNode].adj){
        if(edge.cap >= cap){
            int dest = edge.dest;
            capacity = paretoOtimos(dest, sink, transbordos, cap, curTransbordos+1, std::min(edge.cap, nodes[curNode].cap), path);
            if(capacity){
                if(capacity >= cap)
                    cap = capacity;
                path.push_back(curNode+1);
                foundPath = true;
            }
        }
        else{
            count++;
        }
    }
    if(count == nodes[curNode].adj.size())
        nodes[curNode].visited = true;

    return foundPath ? cap : 0;
}


void Graph::indexNode(int index) {
    nodes[index].index = index;
}

bool Graph::cenario1Bfs(int src, int sink) {
    for(Node &node : nodes){
        node.cap = 0;
        node.pred = -1;
    }

    nodes[src-1].visited = true;
    nodes[src-1].cap = INT_MAX;
    std::queue<Node> queue;

    queue.push(nodes[src-1]);

    while (!queue.empty()){
        Node node = queue.front();
        queue.pop();
        for(Edge edge : node.adj){
            int min = std::min(node.cap, edge.cap);
            Node &dest = nodes[edge.dest];
            if(!dest.visited){
                dest.visited = true;
                dest.pred = node.index;
                if(min > dest.cap){
                    dest.cap = min;
                }
                if(dest.index == sink-1)
                    return true;
                queue.push(dest);
            }
        }
    }
    return false;
}

void Graph::cenario11(int src, int sink) {
    maxCapacityPath(src);

    std::vector<int> v;
    Node *node = &nodes[sink-1];
    while(node->index != src-1){
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
            std::cout << v[i]+1 << "\n\n";
    }
}

void Graph::cenario21(int src, int sink) {
    resetGraph();
    std::cout << "Introduza o Tamanho do Grupo\n";
    std::cin >> groupSize;
    src21 = src-1; sink21 = sink-1;

    edmondsKarp(src21,sink21);
    if(!maxFlow or !groupSize) {
        std::cout << "Nao foi Encontrado um Caminho entre as Paragens que Especificou.\n\n";
    }else if(maxFlow < groupSize){
        std::cout << "O Grupo e Maior do que o Suportado. Nao ha Caminhos.\n\n";
    } else {
        drawPathsWithGroup(groupSize);
    }
}

void Graph::cenario22() {
    if(maxFlow==0 or groupSize ==0){
        std::cout << "Nenhum Caminho foi Selecionado\n\n";
    }
    else{
        int increment;
        std::cout << "Numero Atual de Passageiros: " << groupSize << "\n";
        std::cout << "Introduza o Quantas Pessoas se vao Juntar ao Grupo\n";
        std::cin >> increment;
        groupSize+=increment;
        edmondsKarp(src21, sink21);
        if(groupSize > maxFlow){
            std::cout << "O Numero de Passageiros Excede o Maximo Possivel\n";
            groupSize-=increment;
        }
        else
            drawPathsWithGroup(groupSize);
    }
}

void Graph::cenario23(int src, int sink) {
    resetGraph();
    groupSize = INT_MAX;
    edmondsKarp(src-1,sink-1);
    if(!maxFlow){
        std::cout << "Nao foi Encontrado um Caminho entre as Paragens que Especificou.\n\n";
    } else {
        drawPaths();
        std::cout << "Numero Maximo de Passageiros: " << maxFlow << "\n\n";
    }
}

void Graph::cenario24() {
    std::vector<int> times;
    for (const std::vector<int>& path : paths){
        times.push_back(calcPathTime(path));
    }

    int min = times[0];
    int max =times[0];

    for (int it : times){
        if (it<min) min =it;
        if (it>max) max =it;
    }
    int res = max-min;
    std::cout << "O Ultimo Grupo Chega ao Destino " << res << " Minutos Depois de Partir\n";
}

void Graph::cenario25() {
    auto* g = new Graph(this->n);

    for (std::vector<int> path :paths){
        for(int i =1;i<path.size()-1;i++){
            for (Edge edge : nodes[path[i]].adj){
                if (edge.dest == path[i+1]){
                    g->addEdge(path[i],path[i+1],edge.cap,edge.dur);
                    break;
                }
            }
        }
    }

    std::vector<int> res = cmp_arco_atividade(g);

    std::cout << "O tempo máximo que um dos gurpos vai esperar é: " << res[0] << " minutos nos nós: ";

    for (int i =1;i<res.size();i++){
        std::cout << res[i]+1 << " ";
    }

    std::cout << "\n";

}

void Graph::edmondsKarp(int src, int sink){
    int pathFlow;

    while((pathFlow = bfs(src, sink)) and maxFlow < groupSize){

        std::vector<int> newPath;

        int cur = sink;
        while (cur != src) {
            int prev = nodes[cur].pred;
            resGraph[prev][cur] -= pathFlow;
            resGraph[cur][prev] += pathFlow;
            newPath.push_back(cur);
            cur = prev;
        }

        newPath.push_back(src);
        newPath.push_back(pathFlow);
        std::reverse(newPath.begin(), newPath.end());
        paths.push_back(newPath);

        maxFlow += pathFlow;
    }

    std::sort(paths.begin(), paths.end(), comparePaths);
}

int Graph::bfs(int src, int sink){
    for(Node &node : nodes){
        node.visited= false;
    }
    std::queue<std::pair<int, int>> q;
    nodes[src].visited = true;
    q.push({src, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (Edge edge: nodes[cur].adj) {
            if (!nodes[edge.dest].visited && resGraph[cur][edge.dest]) {
                nodes[edge.dest].pred = cur;
                int newFlow = std::min(flow, resGraph[cur][edge.dest]);
                if (edge.dest == sink) return newFlow;
                q.push({edge.dest, newFlow});
                nodes[edge.dest].visited = true;
            }
        }
    }

    return false;
}

void Graph::drawPaths(){
    for(int i=0; i<paths.size(); i++){
        std::cout << "Grupo " << i+1 << ": ";
        for(int j = 1; j< paths[i].size(); j++){
            std::cout << paths[i][j]+1;
            if(j != paths[i].size()-1){
                std::cout << " -> ";
            }
        }
        std::cout << " | Tamanho do Grupo: " << paths[i][0] <<"\n";
    }
}

void Graph::drawPathsWithGroup(int tamGrupo){
    int i=0;
    do{
        std::cout << "Grupo " << i+1 << ": ";

        for(int j = 1; j< paths[i].size(); j++){
            std::cout << paths[i][j]+1;
            if(j != paths[i].size()-1){
                std::cout << " -> ";
            }
        }
        std::cout << " | Tamanho do Grupo: " << tamGrupo + std::min(paths[i][0]-tamGrupo, 0) <<"\n";
        tamGrupo -= paths[i][0];
        i++;
    }while(tamGrupo>0);
}

int Graph::calcPathTime(std::vector<int> v) {
    int time=0;
    for (int i =1;i<v.size()-1;i++){
        for (Edge edge : nodes[v[i]].adj){
            if (edge.dest == v[i+1]){
                time += edge.dur;
                break;
            }
        }
    }
    return time;
}

std::vector<int> Graph::cmp_arco_atividade(Graph* g) const{

    for (Node &node : g->nodes){
        node.es = 0;
        node.pred = -1;
        node.grauE = 0;
        node.ef = INT_MAX;
    }
    for (Node &node : g->nodes){
        for (Edge &edge : node.adj){
            g->nodes[edge.dest].grauE +=1;
        }
    }

    std::queue<int> q;
    for (const Node& node :g->nodes){
        if (node.grauE ==0) q.push(node.index);
    }

    int durMin = -1;

    while (!q.empty()){
        int v = q.front();
        q.pop();
        if (durMin < g->nodes[v].es){
            durMin = g->nodes[v].es;
        }
        for (Edge edge :g->nodes[v].adj){
            int dest = edge.dest;
            if (g->nodes[dest].es < g->nodes[v].es+ edge.dur){
                g->nodes[dest].es = g->nodes[v].es+ edge.dur;
                g->nodes[dest].pred = v;
            }
            g->nodes[dest].grauE -=1;
            if (g->nodes[dest].grauE ==0) q.push(dest);
        }
    }

    auto* g2 =  new Graph(this->n);

    for (int i =0;i<g->n;i++){
        for (Edge edge : g->nodes[i].adj){
            g2->addEdge(edge.dest,i,edge.cap,edge.dur);
        }
    }

    for (Node &node : g2->nodes){
        node.lf = durMin;
        node.grauS = 0;
    }
    for (Node &node : g2->nodes){
        for (Edge &edge : node.adj){
            g2->nodes[edge.dest].grauS +=1;
        }
    }

    for (int i =0;i<g2->n;i++){
        if (g2->nodes[i].grauS ==0) q.push(i);
    }

    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (Edge edge : g2->nodes[v].adj){
            int dest = edge.dest;
            if (g2->nodes[dest].lf > g2->nodes[v].lf - edge.dur){
                g2->nodes[dest].lf = g2->nodes[v].lf - edge.dur;
            }
            g2->nodes[dest].grauS -=1;
            if (g2->nodes[dest].grauS == 0) q.push(dest);
        }
    }

    for (int i =0;i<g->n;i++){
        g->nodes[i].lf = g2->nodes[i].lf;
    }

    int time =INT_MIN;

    for (Node &node :g->nodes){
        for (Edge &edge : node.adj){
            edge.es =  node.es;
            edge.ef = edge.es + edge.dur;
            if (edge.ef < g->nodes[edge.dest].ef) g->nodes[edge.dest].ef = edge.ef;
        }
    }

    for (const Node& node : g->nodes){
        if (node.lf-node.ef> time) time =node.lf-node.ef;
    }

    std::vector<int> v;
    v.push_back(time);
    for (int i =0;i<g->n;i++){
        if (time == g->nodes[i].lf-g->nodes[i].ef){
            v.push_back(i);
        }
    }
    return v;
}

void Graph::resetGraph() {
    for (int i=0; i<n; i++) {
        nodes[i].visited = false;
    }
    resetResGraph();
    maxFlow = 0;
    paths.clear();
}

void Graph::resetResGraph(){
    resGraph.clear();
    resGraph.resize(n, std::vector<int>(n));
    for(int i = 0; i<n; i++){
        for(Edge e : nodes[i].adj){
            resGraph[i][e.dest] = e.cap;
        }
    }
}

int Graph::getN() const {
    return n;
}
