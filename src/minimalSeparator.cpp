#include <algorithm>
#include <set>
#include <iostream>

#include "minimalSeparator.h"

using namespace std;

namespace MFVS
{
    /**
     * @brief DFS to enumerate current minimal separator
     * 
     * @param graph Grah object
     * @param nodeVal Current node
     * @param conNode Node connection vector
     * @param curMinSep Current minimal separator
     */
    void minSepDFS(Graph* graph, int nodeVal, int* conNode, vector<int> &curMinSep)
    {
        conNode[nodeVal] = 2;
        for(int i : graph->mapNeighbor[nodeVal])
        {
            if(conNode[i] == 0)
            {
                minSepDFS(graph, i, conNode, curMinSep);
            }
            else if(conNode[i] == 1)
            {
                curMinSep.push_back(i);
                conNode[i] = 3;
            }
        }           
    }

    /**
     * @brief Generate all minimal separators of given graph
     * 
     * @param graph 
     * @return vector<vector<int>> 
     */
    vector<vector<int>> findMinimalSeparator(Graph* graph)
    {
        vector<vector<int>> lstMinSeps;
        set<vector<int>> setMinSeps; //To check unique separator

        unordered_set<int> lstNeighbors;

        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

        //Check neighborhood set of each vertices as minimal separator
        for(int curNode=0; curNode<n; curNode++)
        {    
            if(graph->mapNeighbor[curNode].size() > 0)
            {
                //Reset connection vector
                for(int i=0; i<n; i++)
                {
                    conNodes[i] = 0;
                }

                //Set connection vector
                conNodes[curNode] = 1;
                lstNeighbors = graph->mapNeighbor[curNode];
                for(int curNeighbor : lstNeighbors)
                {
                    conNodes[curNeighbor] = 1;
                }

                for(int curNeighbor : lstNeighbors)
                {
                    for(int k : graph->mapNeighbor[curNeighbor])
                    {
                        if(conNodes[k] == 0)
                        {
                            vector<int> curMinSep;
                            minSepDFS(graph, k, conNodes, curMinSep);
                            for(int l : curMinSep)
                            {
                                conNodes[l] = 1;
                            }
                            sort(curMinSep.begin(), curMinSep.end());
                            if(setMinSeps.count(curMinSep) == 0)
                            {
                                setMinSeps.insert(curMinSep);
                                lstMinSeps.push_back(curMinSep);
                            }
                        }
                    }
                }
            }
        }

        //Use generated separators to enumerate more separators
        for(int i=0; i<(int)lstMinSeps.size(); i++)
        {
            vector<int> minSep = lstMinSeps[i];
            for(int node : minSep)
            {
                //Reset connection vector
                for(int j=0; j<n; j++)
                {
                    conNodes[j] = 0;
                }

                //set neighbors and separator connection vector
                for(int curNeighbor : graph->mapNeighbor[node])
                {
                    conNodes[curNeighbor] = 1; 
                }
                for(int sepNode : minSep)
                {
                    conNodes[sepNode] = 1;
                }

                for(int curNeighbor : graph->mapNeighbor[node])
                {
                    for(int k : graph->mapNeighbor[curNeighbor])
                    {
                        if(conNodes[k] == 0)
                        {
                            vector<int> curMinSep;
                            minSepDFS(graph, k, conNodes, curMinSep);
                            for(int l : curMinSep)
                            {
                                conNodes[l] = 1;
                            }
                            sort(curMinSep.begin(), curMinSep.end());
                            if(setMinSeps.count(curMinSep) == 0)
                            {
                                setMinSeps.insert(curMinSep);
                                lstMinSeps.push_back(curMinSep);
                            }
                        }
                    }
                }
            }
        }

	    sort(lstMinSeps.begin(), lstMinSeps.end());
        return lstMinSeps;
    }
}