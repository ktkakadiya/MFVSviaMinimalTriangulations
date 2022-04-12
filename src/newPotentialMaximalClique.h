#ifndef NPMXCLQ_H
#define NPMXCLQ_H

#include <vector>
#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<vector<int>> getNewAllPotentialMaximalCliques(Graph* graph);
}

#endif //NPMXCLQ_H