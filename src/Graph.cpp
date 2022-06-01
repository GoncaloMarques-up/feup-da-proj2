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
}



void Graph::indexNode(int index) {
    nodes[index].index = index;
}

int Graph::calcPathTime(std::vector<int> v) {
    int time=0;
    for (int i =0;i<v.size()-1;i++){
        for (auto it2 : nodes[v[i]].adj){
            if (it2.dest == v[i+1]){
                time += it2.dur;
                break;
            }
        }
    }
    return time;
}

void Graph::cenario24() {
    std::vector<int> times;
    for (auto it : paths){
        times.push_back(calcPathTime(it));
    }

    int min = times[0];
    int max =times[0];

    for (auto it : times){
        if (it<min) min =it;
        if (it>max) max =it;
    }
    int res = max-min;
    std::cout << "The group will get together in the destination " << res << " minutes after they leave";
}

std::vector<int> Graph::bfs25(Graph* g){
    for (auto &it : g->nodes){
        it.tmin = 0;
        it.tmax = 0;
    }
    std::queue<int> q;
    q.push(0);
    g->nodes[0].visited = true;

    for (int u =0;u<g->nodes.size();u++) {
        for (auto it : g->nodes[u].adj){
            if (g->nodes[it.dest].tmax == 0){
                g->nodes[it.dest].tmax = it.dur+g->nodes[u].tmax;
                g->nodes[it.dest].tmin = it.dur+g->nodes[u].tmin;
            }else{
                if (it.dur+g->nodes[u].tmax>g->nodes[it.dest].tmax) g->nodes[it.dest].tmax = it.dur+g->nodes[u].tmax;
                if (it.dur+g->nodes[u].tmin<g->nodes[it.dest].tmin) g->nodes[it.dest].tmin = it.dur+g->nodes[u].tmin;
            }
        }
    }

    int time = INT_MIN;
    for (auto it :g->nodes){
        if (it.tmax-it.tmin > time) time = it.tmax-it.tmin;
    }
    std::vector<int> v;
    for (int i =0;i<g->nodes.size();i++){
        if (g->nodes[i].tmax-g->nodes[i].tmin == time) v.push_back(i);
    }

    return v;
}

void Graph::cenario25() {
    std::set<int> s;
    for (auto it : paths){
        for (auto it2 :it){
            s.insert(it2);
        }
    }
    std::vector<int> v;
    for (auto it :s){
        v.push_back(it);
    }

    Graph* g = new Graph(v.size());

    for (int i = 0;i<v.size();i++){
        for (auto it2 : nodes[v[i]].adj){
            for (int j =0;j<v.size();j++){
                if (it2.dest == v[j]){
                    g->addEdge(i,j,it2.cap,it2.dur);
                }
            }
        }
    }

    std::vector<int> res = bfs25(g);

    std::cout << "the nodes are: ";

    for (auto it : res){
        std::cout << v[it];
    }

}


void Graph::cenario23(int src, int sink) {
    resetGraph();
    maxFlow = 0;

    maxFlow = edmondsKarp(src-1,sink-1);
    if(!maxFlow){
        std::cout << "Nao foi Encontrado um Caminho entre as Paragens que Especificou.\n\n";
    } else {
        drawPaths();
        std::cout << "Numero Maximo de Passageiros: " << maxFlow << "\n\n";
    }
}

int Graph::edmondsKarp(int src, int sink){

    std::vector<std::vector<int>>resGraph;
    resGraph.resize(n, std::vector<int>(n));

    for(int i = 0; i<n; i++){
        for(auto e : nodes[i].adj){
            resGraph[i][e.dest] = e.cap;
        }
    }

    while(bfs(src, sink, resGraph)){

        int pathFlow = INT_MAX;
        for (int j = sink; j != src; j = nodes[j].pred) {
            int i = nodes[j].pred;
            pathFlow = std::min(pathFlow, resGraph[i][j]);
        }

        std::vector<int> newPath;

        // update residual capacities of the edges and
        // reverse edges along the path
        for (int j = sink; j != src; j = nodes[j].pred) {
            int i = nodes[j].pred;
            resGraph[i][j] -= pathFlow;
            /*resGraph[j][i] -= pathFlow;*/
            newPath.push_back(j);
        }
        newPath.push_back(src);
        newPath.push_back(pathFlow);
        paths.push_back(newPath);

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }

    for(auto & path : paths){
        std::reverse(path.begin(), path.end());
    }
    std::sort(paths.begin(), paths.end(), comparePaths);

    return maxFlow;
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

bool Graph::bfs(int src, int sink, const std::vector<std::vector<int>> &resGraph){
    std::queue<int> q;
    q.push(src);
    nodes[src].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (!nodes[i].visited && resGraph[u][i] > 0) {
                if (i == sink) {
                    nodes[i].pred = u;
                    return true;
                }
                q.push(i);
                nodes[i].pred = u;
                nodes[src].visited = true;
            }
        }
    }

    return false;
}

void Graph::resetGraph() {
    for (int i=0; i<n; i++) {
        nodes[i].visited = false;
    }
    paths.clear();
}

int Graph::getN() const {
    return n;
}


void Graph::cenario21(int src, int sink) {
    resetGraph();
    maxFlow = 0;

    std::cout << "Introduza o Tamanho do Grupo\n";
    std::cin >> groupSize;

    maxFlow = edmondsKarp(src-1,sink-1);
    if(!maxFlow) {
        std::cout << "Nao foi Encontrado um Caminho entre as Paragens que Especificou.\n\n";
    }else if(maxFlow < groupSize){
        std::cout << "O Grupo e Maior do que o Suportado. Nao ha Caminhos.\n\n";
    } else {
        drawPathsWithGroup(groupSize);
    }
}

void Graph::cenario22() {
    if(maxFlow==0){
        std::cout << "Nenhum Caminho foi Selecionado\n\n";
    }
    else{
        int increment;
        std::cout << "Introduza o Quantas Pessoas se vao Juntar ao Grupo\n";
        std::cin >> increment;
        if(groupSize + increment > maxFlow)
            std::cout << "O Numero de Passageiros Excede o Maximo Possivel\n";
        else
            drawPathsWithGroup(groupSize + increment);
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
void Graph::maxCapacityAndShortestPath(int src, int sink) {
    if(cenario1Bfs(src, sink)){
        int bfsCap = nodes[sink-1].cap;
        int minNodes = 0;
        std::vector<int> path1;
        Node *node = &nodes[sink-1];
        while(node->index != src-1){
            path1.push_back(node->index);
            minNodes++;
            node = &nodes[node->pred];
        }
        minNodes++;
        path1.push_back(node->index);

        std::reverse(path1.begin(), path1.end());

        maxCapacityPath(src, sink);
        int maxCap = nodes[sink-1].cap;
        int numNodes = 0;

        std::vector<int> path2;
        node = &nodes[sink -1];
        while(node->index != src-1){
            path2.push_back(node->index);
            numNodes++;
            node = &nodes[node->pred];
        }
        numNodes++;
        path2.push_back(node->index);

        std::reverse(path2.begin(), path2.end());

        if(numNodes == minNodes){
            std::cout << "o caminho mais curto tem também maior capacidade.\n";
            std::cout << "Capacidade:" << maxCap << "\n" << "Encaminhamento: ";

            for(int i = 0; i < path2.size(); i++){
                if(i != path2.size()-1)
                    std::cout << path2[i] + 1 << "->";
                else
                    std::cout << path2[i]+1 << "\n";
            }
        }
        else if(maxCap == bfsCap){
                std::cout << "o caminho mais curto tem também maior capacidade.\n";
                std::cout << "Capacidade:" << maxCap << "\n" << "Encaminhamento: ";

                for(int i = 0; i < path1.size(); i++){
                    if(i != path1.size()-1)
                        std::cout << path1[i] + 1 << "->";
                    else
                        std::cout << path1[i]+1 << "\n";
                }
        }
        else {
            std::cout << "Caminho de maior capacidade: ";
            for(int i = 0; i < path2.size(); i++){
                if(i != path2.size()-1)
                    std::cout << path2[i] + 1 << "->";
                else
                    std::cout << path2[i]+1 << "\n";
            }
            std::cout << "Capacidade: " << maxCap << "\n\n";

            std::cout  << "Caminho com menos transbordos: ";
            for(int i = 0; i < path1.size(); i++){
                if(i != path1.size()-1)
                    std::cout << path1[i] + 1 << "->";
                else
                    std::cout << path1[i]+1 << "\n";
            }
            std::cout << "Capacidade: " << bfsCap << "\n\n";
        }
    }
    else{
        std::cout << "não existe caminho entre os pontos selecionados";
    }
}

void Graph::cenario1_1Output(int src, int sink) {
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
            std::cout << v[i]+1 << "\n";
    }
}

bool Graph::cenario1Bfs(int src, int sink) {
    for(auto &node : nodes){
        node.cap = 0;
    }

    nodes[src-1].visited = true;
    nodes[src-1].cap = INT_MAX;
    std::queue<Node> queue;

    queue.push(nodes[src-1]);

    while (!queue.empty()){
        Node node = queue.front();
        queue.pop();
        for(auto edge : node.adj){
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
