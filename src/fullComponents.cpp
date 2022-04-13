#include "fullComponents.h"
#include <algorithm>

using namespace std;

namespace MFVS
{
    /**
     * @brief Run the DFS on the given node to find its associated component
     * 
     * @param graph Graph
     * @param nodeVal Current node
     * @param conNodes Node connection vector
     * @param curIndex Current index of the node
     * @param curComponent Current component - list of nodes
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
     * @brief Get the Full Components of the graph G[V/X] has any full components
     * 
     * @param graph Graph object G = (V,E)
     * @param vecNodes Vertex set X
     * @return vector<vector<int>> 
     */
    vector<vector<int>> getFullComponents(Graph* graph, vector<int>& vecNodes)
    {
        vector<vector<int>> vecComp;

        int uSepSize = (int)vecNodes.size();
        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

        int curIndex = 2;
        for(int node : vecNodes)
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

    /**
     * @brief Check whether the graph G[V/X] has any full components
     * 
     * @param graph Graph object G = (V,E)
     * @param vecNodes Vertex set X
     * @return vector<vector<int>> 
     */
    bool hasFullComponents(Graph* graph, vector<int>& vecNodes)
    {
        int uSepSize = (int)vecNodes.size();
        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

        int curIndex = 2;
        for(int node : vecNodes)
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
                    return true;
                }
            }
        }
        return false;
    }
}