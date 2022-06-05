#include "includes/Menu.h"

int main(){
//    Menu m;
//    m.run();
    FileReader f;
    Graph g = f.readFile("in01_b.txt");

    std::cout <<g.calcPathTime({3,9,27,44}) << " ";
    std::cout <<g.calcPathTime({3,9,35,31,48,44}) << " ";
    return 0;
}
