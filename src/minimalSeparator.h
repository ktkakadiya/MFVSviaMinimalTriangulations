#ifndef MINSEP_H
#define MINSEP_H

#include <vector>
#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<vector<int>> findMinimalSeparator(Graph* graph);
    void componentDFS(Graph* graph, int nodeVal, int* conNode, vector<int> &compNeighborhood);
}

#endif //MINSEP_H