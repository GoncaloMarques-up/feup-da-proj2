//
// Created by goncalo on 25-05-2022.
//

#include "../includes/FileReader.h"

Graph FileReader::readFile(const std::string& file) {
    std::ifstream fs("../data/" + file);
    if(!fs.is_open())
        exit(EXIT_FAILURE);

    std::string data;
    getline(fs, data);
    std::stringstream ss(data);
    int numNodes, numEdges;
    ss >> numNodes >> numEdges;
    Graph graph{numNodes};
    for(int i = 0; i < numEdges; i++){
        getline(fs, data);
        ss.str(data);
        int origin, destination, capacity, duration;
        ss >> origin >> destination >> capacity >> duration;
        graph.addEdge(origin, destination, capacity, duration);
    }
    return graph;
}
FileReader::FileReader() = default;
