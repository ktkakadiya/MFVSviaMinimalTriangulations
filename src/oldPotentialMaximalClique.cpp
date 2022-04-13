#include "oldPotentialMaximalClique.h"
#include "minimalSeparator.h"
#include "fullComponents.h"
#include "setOperations.h"

#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

namespace MFVS
{
    /**
     * @brief DFS traversal for setting the connection vector of clique
     * 
     * @param graph Graph object
     * @param nodeVal Current node
     * @param conNode Node connection vector
     */
    void cliqueDFS(Graph* graph, int nodeVal, int* conNode)
    {
        conNode[nodeVal] = 2;
        for(int i : graph->mapNeighbor[nodeVal])
        {
            if(conNode[i] == 0)
            {
                cliqueDFS(graph, i, conNode);
            }
            else if(conNode[i] == 1)
            {
                conNode[i] = 3;
            }
        }           
    }

    /**
     * @brief Check whether gven set of vectors is a potential maximal clique for given graph
     * 
     * @param graph Graph object
     * @param vecNodes Node vertex set
     * @return true 
     * @return false 
     */
    bool isPotentialMaximalClique(Graph* graph, vector<int> vecNodes)
    {
        if(MFVS::hasFullComponents(graph, vecNodes))
            return false;

        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

        for(int node : vecNodes)
        {
            //Reset connection vector
            for(int i=0; i<n; i++)
            {
                conNodes[i] = 0;
            }
            
            //Set connection vector
            for(int node1 : vecNodes)
            {
                if(node1 != node)
                {
                    conNodes[node1] = 1;
                }
            }

            //traverse to set clique connection vector
            cliqueDFS(graph, node, conNodes);

            //Check whether all nodes are covered in traversal
            for(int node1 : vecNodes)
            {
                if(node1 != node && conNodes[node1] != 3)
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * @brief Get the maximum cardinality order for given graph
     * It is used for adding one more vertex to current potential maximal clique
     * 
     * @param graph Graph object
     * @return vector<int> 
     */
    vector<int> maxCardinalityOrder(Graph* graph)
    {
        int n = graph->getTotalNodes();

        vector<int> lstOrder;
        vector<int> vecNodeSets[n], tr(n), lb(n);

        int curNode = 0;
        vecNodeSets[0].push_back(curNode);

        int curSetIndex = 0;
        while(curSetIndex >= 0)
        {
            if(vecNodeSets[curSetIndex].size() == 0)
            {
                curSetIndex--;
                continue;
            }

            int lastNode = vecNodeSets[curSetIndex].back();
            vecNodeSets[curSetIndex].pop_back();
            if(tr[lastNode])
                continue;
            lstOrder.push_back(lastNode);

            for(int neighbor : graph->mapNeighbor[lastNode])
            {
                if(!tr[neighbor])
                {
                    lb[neighbor]++;
                    vecNodeSets[lb[neighbor]].push_back(neighbor);
                    curSetIndex = max(curSetIndex, lb[neighbor]);
                }
            }
            tr[lastNode] = 1;
        }
        return lstOrder; 
    }

    /**
     * @brief Add one more vertex to current potential maximal cliques
     * 
     * @param graph Graph object
     * @param lstPMC List of current potential maximal cliques
     * @param lstMinSep List of all minimal separators
     * @param lstSubMinSep List of all minimal separators in the subgraph
     * @param curNode Current node
     * @return vector<vector<int>> 
     */
    vector<vector<int>> oneMoreVertex(Graph* graph, vector<vector<int>>& lstPMC, vector<vector<int>>& lstMinSep, vector<vector<int>>& lstSubMinSep, int curNode)
    {
        vector<vector<int>> lstNewPMC, lstNewPMCtemp;
        for (vector<int> curPMC : lstPMC)
        {
            if(count(lstNewPMC.begin(), lstNewPMC.end(), curPMC) != 0)
            {
                continue;
            }

            bool bPMC = MFVS::isPotentialMaximalClique(graph, curPMC);
            if(bPMC)
            {
                lstNewPMC.push_back(curPMC);
                lstNewPMCtemp.push_back(curPMC);
            }
            else
            {
                vector<int> newPMC = SOP::getUnion(curPMC, {curNode});
                if(count(lstNewPMCtemp.begin(), lstNewPMCtemp.end(), newPMC) != 0)
                {
                    continue;
                }
                bool bPMC = MFVS::isPotentialMaximalClique(graph, newPMC);
                if(bPMC)
                {
                    lstNewPMC.push_back(newPMC);
                    lstNewPMCtemp.push_back(newPMC);
                }
            }
        }

        for (vector<int> subMinSep : lstSubMinSep)
        {
            vector<int> newMinSep = SOP::getUnion(subMinSep, {curNode});
            if(count(lstNewPMCtemp.begin(), lstNewPMCtemp.end(), newMinSep) != 0)
            {
                bool bPMC = MFVS::isPotentialMaximalClique(graph, newMinSep);
                if(bPMC)
                {
                    lstNewPMC.push_back(newMinSep);
                    lstNewPMCtemp.push_back(newMinSep);
                }
            }

            if(count(subMinSep.begin(), subMinSep.end(), curNode) == 0 
                && count(lstMinSep.begin(), lstMinSep.end(), subMinSep) != 0)
            {
                vector<vector<int>> lstFullComponents = MFVS::getFullComponents(graph, subMinSep);
                for(vector<int> newSubMinSep : lstSubMinSep)
                {
                    for(vector<int> fullComp : lstFullComponents)
                    {
                        vector<int> newPMC = SOP::getUnion(subMinSep, SOP::getIntersection(newSubMinSep, fullComp));
                        if(count(lstNewPMCtemp.begin(), lstNewPMCtemp.end(), newPMC) != 0)
                        {
                            continue;
                        }
                        bool bPMC = MFVS::isPotentialMaximalClique(graph, newPMC);
                        if(bPMC)
                        {
                            lstNewPMC.push_back(newPMC);
                            lstNewPMCtemp.push_back(newPMC);
                        }
                    }
                }
            }
        }
        return lstNewPMC;
    }
    
    /**
     * @brief Get the All Potential Maximal Cliques for Graph object using old method [2]
     * 
     * @param graph Graph object
     * @return vector<vector<int>> 
     */
    vector<vector<int>> getOldAllPotentialMaximalCliques(Graph* graph)
    {
        int n = graph->getTotalNodes();

        vector<vector<int>> lstPMCs(n);
        vector<vector<int>> lstMinSeps, lstSubMinSeps;

        vector<int> lstMCOrder = MFVS::maxCardinalityOrder(graph);

        vector<int> lstOrder(n);
        for(int node=0; node<n; node++)
        {
            lstOrder[lstMCOrder[node]] = node;
        }

        lstPMCs[0].push_back(lstOrder[0]);

        Graph* subGraph = new Graph(n);
        for(int node=0; node<n; node++)
        {
            int ordNode = lstMCOrder[node];
            for(int neighbor : graph->mapNeighbor[ordNode])
            {
                if(lstOrder[neighbor] < lstOrder[ordNode])
                {
                    subGraph->addEdge(neighbor, ordNode);
                }
            }

            lstSubMinSeps = MFVS::findMinimalSeparator(subGraph);
            lstPMCs = MFVS::oneMoreVertex(subGraph, lstPMCs, lstMinSeps, lstSubMinSeps, ordNode);
            lstMinSeps = lstSubMinSeps;
            for(vector<int>& curPMC : lstPMCs)
            {
                sort(curPMC.begin(), curPMC.end());
            }
            sort(lstPMCs.begin(), lstPMCs.end());
            lstPMCs.erase(unique(lstPMCs.begin(), lstPMCs.end()), lstPMCs.end());
        }
        return lstPMCs;
    }
}