//
// Created by goncalo on 25-05-2022.
//

#ifndef FEUP_DAL_PROJ2_FILEREADER_H
#define FEUP_DAL_PROJ2_FILEREADER_H

#include <fstream>
#include <sstream>
#include "Graph.h"

class FileReader {
    public:
    FileReader();

    /**
     * function that reads a file
     * @param file
     * @return a graph with the contents of the file
     */
    static Graph readFile(const std::string& file);
};


#endif //FEUP_DAL_PROJ2_FILEREADER_H
