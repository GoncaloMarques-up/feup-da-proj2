//
// Created by ASUS on 25/05/2022.
//

#ifndef FEUP_DAL_PROJ2_TRAVELAGENCY_H
#define FEUP_DAL_PROJ2_TRAVELAGENCY_H

#include "Graph.h"
#include <queue>
#include <ostream>

class TravelAgency {

    Graph graph;
    TravelAgency(Graph graph);

    void doisUm(int s, int t);

    void resetGraph();
    bool bfs(int s, int t);
    int edmondsKarp(int s, int t);
};


#endif //FEUP_DAL_PROJ2_TRAVELAGENCY_H
