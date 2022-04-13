#include "newPotentialMaximalClique.h"
#include "oldPotentialMaximalClique.h"
#include "setOperations.h"

#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

namespace MFVS
{
    /**
     * @brief Run DFS on the current node to find its associated component
     * 
     * @param graph Graph object
     * @param nodeVal Current node
     * @param conNodes Node connection vector
     * @param curConSet Current connected set
     * @param resConSet Set of all connected sets
     * @return 
     */
    void connectedSetDFS(Graph* graph, int nodeVal, int* conNodes, vector<int> curConSet, set<vector<int>> &resConSet)
    {          
        conNodes[nodeVal] = 1;
        curConSet.push_back(nodeVal);
        sort(curConSet.begin(), curConSet.end());
        resConSet.insert(curConSet);

        for(int i : graph->mapNeighbor[nodeVal])
        {
            if(conNodes[i] == 0)
            {
                MFVS::connectedSetDFS(graph, i, conNodes, curConSet, resConSet);
            }
        }
        conNodes[nodeVal] = 0;
        curConSet.pop_back();
    }

    /**
     * @brief Get the All Contected Sets for current node
     * 
     * @param graph Graph object
     * @param node Current node
     * @return vector<vector<int>> 
     */
    vector<vector<int>> getAllContectedSets(Graph* graph, int node)
    {
        int n = graph->getTotalNodes();
        int conNodes[n] = {0};
        
        vector<vector<int>> lstConSets;
        set<vector<int>> resConSet;

        vector<int> curConSet = {node};
        conNodes[node] = 1;
        lstConSets.push_back(curConSet);
        for(int i : graph->mapNeighbor[node])
        {
            MFVS::connectedSetDFS(graph, i, conNodes, curConSet, resConSet);
            conNodes[i] = 1;
        }

        for(vector<int> conSet : resConSet)
        {
            lstConSets.push_back(conSet);
        }
        return lstConSets;
    }

    /**
     * @brief Get the Neighborhood Set of given vertex set
     * 
     * @param graph Graph object
     * @param nodeSet Vertex set
     * @param curNode Node associated to vertex set
     * @param bIncludeCurNode Flag to check whether or not to include neighbors of current node
     * @return vector<int> 
     */
    vector<int> getNeighborhoodSet(Graph* graph, vector<int> nodeSet, int curNode, bool bIncludeCurNode)
    {
        int n = graph->getTotalNodes();
        int conNodes[n] = {0};
        vector<int> setNeighborhood;

        //Set the connection vector
        for(int node : nodeSet)
        {
            if(bIncludeCurNode || node != curNode)
            {
                conNodes[node] = 1;
            }
        }

        for(int node : nodeSet)
        {
            if(bIncludeCurNode || node != curNode)
            {
                for(int neighbor : graph->mapNeighbor[node])
                {
                    if(conNodes[neighbor] == 0)
                    {
                        setNeighborhood.push_back(neighbor);
                        conNodes[neighbor] = 1;
                    }
                }
            }
        }
        return setNeighborhood;
    }

    /**
     * @brief Get all the potential maximal cliques for given graph using newly proposed method [1]
     * 
     * @param graph Graph object
     * @return vector<vector<int>> 
     */
    vector<vector<int>> getNewAllPotentialMaximalCliques(Graph* graph)
    {
        vector<vector<int>> lstPMCs;
        set<vector<int>> setPMCs;

        int n = graph->getTotalNodes();
        for(int curNode=0; curNode<n; curNode++)
        {
            vector<vector<int>> lstConSets = MFVS::getAllContectedSets(graph, curNode);
            for(vector<int> curConSet : lstConSets)
            {
                vector<int> setNeighborhood = MFVS::getNeighborhoodSet(graph, curConSet, curNode, false);
                vector<int> setUnionNeighborhood = SOP::getUnion(curConSet, setNeighborhood);

                int uCurConSetSize = (int)curConSet.size();
                int uSetUnionNeighborhoodSize = (int)setUnionNeighborhood.size();

                if(uCurConSetSize - 1 <= 2 * (n - uSetUnionNeighborhoodSize))
                {
                    if(MFVS::isPotentialMaximalClique(graph, setNeighborhood))
                    {
                        sort(setNeighborhood.begin(), setNeighborhood.end());
                        if(setPMCs.find(setNeighborhood) == setPMCs.end())
                        {
                            setPMCs.insert(setNeighborhood);
                            lstPMCs.push_back(setNeighborhood);
                        }
                    }

                    //Set of neighbors of connected set with current node neighbors also included
                    vector<int> setNeighborhoodWithCNN = MFVS::getNeighborhoodSet(graph, curConSet, curNode, true);
                    vector<int> setUnionNeighborhoodWithCNN = SOP::getUnion(setNeighborhoodWithCNN, {curNode});
                    if(MFVS::isPotentialMaximalClique(graph, setUnionNeighborhoodWithCNN))
                    {
                        sort(setUnionNeighborhoodWithCNN.begin(), setUnionNeighborhoodWithCNN.end());
                        if(setPMCs.find(setUnionNeighborhoodWithCNN) == setPMCs.end())
                        {
                            setPMCs.insert(setUnionNeighborhoodWithCNN);
                            lstPMCs.push_back(setUnionNeighborhoodWithCNN);
                        }
                    }
                }
            }
        }
        return lstPMCs;
    }
}