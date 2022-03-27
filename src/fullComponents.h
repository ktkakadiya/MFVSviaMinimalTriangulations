#ifndef FULCOM_H
#define FULCOM_H

#include <vector>

#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<vector<int>> getFullComponents(Graph* graph, vector<int>& minimalSep);
}

#endif //FULCOM_H