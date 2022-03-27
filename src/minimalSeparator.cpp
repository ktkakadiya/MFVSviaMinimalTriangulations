
#ifndef MINSEP_H
#define MINSEP_H

#include <algorithm>
#include <set>
#include <iostream>

#include "minimalSeparator.h"

using namespace std;

namespace MS
{
    void componentDFS(Graph* graph, int nodeVal, int* conNode, vector<int> &compNeighborhood)
    {
        conNode[nodeVal] = 2;
        for(int i : graph->mapNeighbor[nodeVal])
        {
            if(conNode[i] == 0)
            {
                componentDFS(graph, i, conNode, compNeighborhood);
            }
            else if(conNode[i] == 1)
            {
                compNeighborhood.push_back(i);
                conNode[i] = 3;
            }
        }           
    }

    vector<vector<int>> findMinimalSeparator(Graph* graph)
    {
        vector<vector<int>> lstMinSeps;
        set<vector<int>> setMinSeps; //To check unique separator

        unordered_set<int> lstNeighbors;

        int n = graph->getTotalNodes();
        int conNodes[n] = {0};

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
                            vector<int> compNeighborhood;
                            componentDFS(graph, k, conNodes, compNeighborhood);
                            for(int l : compNeighborhood)
                            {
                                conNodes[l] = 1;
                            }
                            sort(compNeighborhood.begin(), compNeighborhood.end());
                            if(setMinSeps.count(compNeighborhood) == 0)
                            {
                                setMinSeps.insert(compNeighborhood);
                                lstMinSeps.push_back(compNeighborhood);
                            }
                        }
                    }
                }
            }
        }

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
                            vector<int> compNeighborhood;
                            componentDFS(graph, k, conNodes, compNeighborhood);
                            for(int l : compNeighborhood)
                            {
                                conNodes[l] = 1;
                            }
                            sort(compNeighborhood.begin(), compNeighborhood.end());
                            if(setMinSeps.count(compNeighborhood) == 0)
                            {
                                setMinSeps.insert(compNeighborhood);
                                lstMinSeps.push_back(compNeighborhood);
                            }
                        }
                    }
                }
            }
        }

	    sort(lstMinSeps.begin(), lstMinSeps.end());

        std::cout << "Printing min seps" << endl;
        for(auto lv : lstMinSeps)
        {
            for(auto no : lv)
            {
                std::cout  << no << " ";
            }
            std::cout << endl;
        }
        return lstMinSeps;
    }
}


#endif //MINSEP_H