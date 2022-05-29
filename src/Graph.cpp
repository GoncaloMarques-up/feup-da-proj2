//
// Created by ASUS on 22/05/2022.
//

#include <algorithm>
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


void Graph::maxCapacityPath(int s, int t) {
    for(auto &node : nodes){
        node.cap = 0;
        node.pred = -1;
    }

    nodes[s-1].cap = INT_MAX;

    std::priority_queue<Node, std::vector<Node> ,compareNodes> queue;

    queue.push(nodes[s-1]);

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
    Node *node = &nodes[t-1];
    while(node->pred != -1){
        v.push_back(node->index);
        node = &nodes[node->pred];
    }

    v.push_back(node->index);
    std::reverse(v.begin(), v.end());

    std::cout << "capacidade máxima: " << nodes[t-1].cap << '\n' << "encaminhamento: ";

    for(int i = 0; i < v.size(); i++){
        if(i != v.size()-1)
            std::cout << v[i] + 1 << "->";
        else
            std::cout << v[i]+1;
    }
}

void Graph::indexNode(int index) {
    nodes[index].index = index;
}





