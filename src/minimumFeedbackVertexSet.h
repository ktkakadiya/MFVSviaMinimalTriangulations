#ifndef MINFVS_H
#define MINFVS_H

#include <vector>
#include "graph/graph.h"

using namespace std;

namespace MFVS
{
    vector<int> findMinimumFeedbackVertexSet(Graph* graph);
}

#endif //MINFVS_H