#ifndef OPMXCLQ_H
#define OPMXCLQ_H

#include <vector>
#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<vector<int>> getOldAllPotentialMaximalCliques(Graph* graph);
    bool isPotentialMaximalClique(Graph* graph, vector<int> vecNodes);
}

#endif //OPMXCLQ_H