//
// Created by goncalo on 29-05-2022.
//

#ifndef FEUP_DAL_PROJ2_TRAVELAGENCY_H
#define FEUP_DAL_PROJ2_TRAVELAGENCY_H

#include "Graph.h"

class TravelAgency {
private:
    Graph graph;
public:
    TravelAgency(Graph gn);

    void bfs(int sNode, int eNode);
};


#endif //FEUP_DAL_PROJ2_TRAVELAGENCY_H
