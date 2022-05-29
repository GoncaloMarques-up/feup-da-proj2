#include <iostream>

#include "includes/Menu.h"
#include "includes/FileReader.h"

int main(){
    //Menu m;
    //m.run();
    //std::cout << "Hello World";
    Graph g = FileReader::readFile("in01.txt");
    g.maxCapacityPath(1, 50);
    return 0;
}
