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

void Graph::cenarioDoisQuatro(std::vector<std::vector<int>> v) {
    std::vector<int> times;
    for (auto it : v){
        int time=0;
        for (int i =0;i<it.size()-1;i++){
            for (auto it2 : nodes[it[i]].adj){
                if (it2.dest == it[i+1]){
                    time += it2.dur;
                    break;
                }
            }
        }
        times.push_back(time);
    }

    int min = times[0];
    int max =times[0];

    for (auto it : times){
        if (it<min) min =it;
        if (it>max) max =it;
    }
    std::cout << "The group will get together in the destination " << max-min << " minutes after they leave";
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
