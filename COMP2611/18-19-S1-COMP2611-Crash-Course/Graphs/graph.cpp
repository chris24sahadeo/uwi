#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "constants.h"
#include "graph.h"


int main(){

    Graph *graph = newGraph(MAX_V);
    buildGraph(graph);
    printGraph(graph);
    DFTGraph(graph, 3);
    printPath(graph, "D");

    return 0;
}
