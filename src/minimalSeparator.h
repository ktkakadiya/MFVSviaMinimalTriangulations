#include <vector>

#include "graph/graph.h"

using namespace std;

namespace MS
{
    vector<vector<int>> findMinimalSeparator(Graph* graph);
    void componentDFS(Graph* graph, int nodeVal, int* conNode, vector<int> &compNeighborhood);
}