#include "fullComponents.h"
#include <algorithm>

using namespace std;

namespace MFVS
{
    /**
     * @brief Run DFS of given node to find its associated component
     * 
     * @param graph 
     * @param nodeVal 
     * @param conNodes 
     * @param curIndex 
     * @param curComponent 
     * @return int 
     */
    int componentDFS(Graph* graph, int nodeVal, int* conNodes, int curIndex, vector<int> &curComponent)
    {
        conNodes[nodeVal] = 1;
        curComponent.push_back(nodeVal);

        int uCompSize = 0;
        for(int i : graph->mapNeighbor[nodeVal])
        {
            if(conNodes[i] == 0)
            {
                uCompSize += componentDFS(graph, i, conNodes, curIndex, curComponent);
            }
            else if(conNodes[i] >= 2 && conNodes[i] < curIndex)
            {
                conNodes[i] = curIndex;
                uCompSize++;
            }
        }
        return uCompSize;
    }

    /**
     * @brief Get the Full Components given minimal separator for given graph
     * 
     * @param graph 
     * @param minSeparator 
     * @return vector<vector<int>> 
     */
    vector<vector<int>> getFullComponents(Graph* graph, vector<int>& minSeparator)
    {
        vector<vector<int>> vecComp;

        int uSepSize = (int)minSeparator.size();
        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

        int curIndex = 2;
        for(int node : minSeparator)
        {
            conNodes[node] = curIndex;
        }

        for(int curNode=0; curNode<n; curNode++)
        {
            if(conNodes[curNode] == 0)
            {
                curIndex++;
                vector<int> component;
                int compSize = componentDFS(graph, curNode, conNodes, curIndex, component);
                if(compSize == uSepSize)
                {
                    sort(component.begin(), component.end());
                    vecComp.push_back(component);
                }
            }
        }
        return vecComp;
    }
}