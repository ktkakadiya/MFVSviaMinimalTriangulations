#ifndef PMXCLQ_H
#define PMXCLQ_H

#include <vector>
#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<vector<int>> getAllPotentialMaximalCliques(Graph* graph);
    bool isPotentialMaximalClique(Graph* graph, vector<int> vecNodes);
}

#endif //PMXCLQ_H