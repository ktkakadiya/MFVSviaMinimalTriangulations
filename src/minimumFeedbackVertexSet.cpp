#include "minimumFeedbackVertexSet.h"
#include "minimalSeparator.h"
#include "fullComponents.h"
#include "oldPotentialMaximalClique.h"
#include "newPotentialMaximalClique.h"
#include "setOperations.h"

#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std;

namespace MFVS
{
    /**
     * @brief Print all minimal separators
     * 
     * @param lstMinSeps 
     */
    void printMinimalSeparators(vector<vector<int>> lstMinSeps)
    { 
        std::cout << "Printing min seps" << endl;
        for(auto lv : lstMinSeps)
        {
            for(auto no : lv)
            {
                std::cout  << no << " ";
            }
            std::cout << endl;
        }
    }

    /**
     * @brief Print full components of minimal separator
     * 
     * @param minSep 
     * @param lstComponent
     */
    void printFullComponents(vector<int> minSep, vector<vector<int>> lstComponent)
    { 
        std::cout << "Minimal Separator " << endl;
        for(auto no : minSep)
        {
            std::cout  << no << " ";
        }
        std::cout << endl;

        std::cout << "Full componenets " << endl;
        for(auto lv : lstComponent)
        {
            for(auto no : lv)
            {
                std::cout  << no << " ";
            }
            std::cout << endl;
        }
    }

    /**
     * @brief Print all potential maximal cliques of graph
     * 
     * @param lstPMC 
     */
    void printPotentialMaximalCliques(vector<vector<int>> lstPMC)
    { 
        std::cout << "Printing potential maximal cliques" << endl;
        for(auto pmc : lstPMC)
        {
            for(auto no : pmc)
            {
                std::cout  << no << " ";
            }
            std::cout << endl;
        }
    }

    /**
     * @brief Construct good triplets of graph
     * 
     * @param lstMinSeps 
     * @param lstFullComp 
     * @return vector<vector<vector<int>>>
     */
    vector<vector<vector<int>>> constructFullBlocks(vector<vector<int>> lstMinSeps, vector<vector<vector<int>>> lstFullComp)
    {
        vector<vector<vector<int>>> lstFullBlock;
        int n = lstMinSeps.size();
        for(int i=0; i<n; i++)
        {
            vector<vector<int>> lstSepFullBlock;
            for(vector<int> fullComp : lstFullComp[i])
            {
                vector<int> fullBlock = SOP::getUnion(lstMinSeps[i], fullComp);
                lstSepFullBlock.push_back(fullBlock);
            }
            lstFullBlock.push_back(lstSepFullBlock);
        }
        return lstFullBlock;
    }

    /**
     * @brief Construct good triplets of graph
     * 
     * @param lstMinSeps 
     * @param lstFullBlock 
     * @param lstPMC 
     * @return vector<vector<vector<int>>>
     */
    vector<vector<int>> constructGoodTriplet(vector<vector<int>> lstMinSeps, vector<vector<vector<int>>> lstFullBlock, vector<vector<int>> lstPMC)
    {
        vector<vector<int>> lstTripletIdx;
        int np = lstPMC.size();
        int nm = lstMinSeps.size();
        for(int i=0; i<nm; i++)
        {
            for(int k=0; k<np; k++)
            {
                if(SOP::isSubset(lstPMC[k], lstMinSeps[i]))
                {
                    vector<int> vecGoodIdx;
                    int nb = lstFullBlock[i].size();
                    for(int j=0; j<nb; j++)
                    {
                        if(SOP::isSubset(lstFullBlock[i][j], lstPMC[k]))
                        {
                            vecGoodIdx.push_back(i);
                            vecGoodIdx.push_back(j);
                            vecGoodIdx.push_back(k);
                        }
                    }
                    lstTripletIdx.push_back(vecGoodIdx);
                }
            }
        }

        //Sort triplets based on block sizes
        auto comparator = [&](vector<int> triplet1, vector<int> triplet2) 
        {
            if (lstFullBlock[triplet1[0]][triplet1[1]].size() != lstFullBlock[triplet2[0]][triplet2[1]].size()) 
            {
                return lstFullBlock[triplet1[0]][triplet1[1]].size() < lstFullBlock[triplet2[0]][triplet2[1]].size();
            }
            else 
            {
                return triplet1 < triplet2;
            }
	    };
        sort(lstTripletIdx.begin(), lstTripletIdx.end(), comparator);
        return lstTripletIdx;
    }

    /**
     * @brief Find minimum feedback vertex set for given graph
     * 
     * @param graph 
     */
    void findMinimumFeedbackVertexSet(Graph* graph)
    {
        int treeWidth = 1;

        auto start = high_resolution_clock::now();

        //Find minimal separators
        vector<vector<int>> lstMinSeps = MFVS::findMinimalSeparator(graph);
        //printMinimalSeparators(lstMinSeps);

        //Remove separators of sie treewidth + 1
        for(auto i = lstMinSeps.begin(); i != lstMinSeps.end(); ++i)
        {
            if((int)(*i).size() > treeWidth + 1)
            {
                lstMinSeps.erase(i);
                i--;
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop-start);
        cout << "Minsep : " << duration1.count() << endl;
        
        start = high_resolution_clock::now();
        
        vector<vector<vector<int>>> lstFullComp;
        //std::cout << "Printing full components " << endl;
        for(vector<int> minSep : lstMinSeps)
        {
            vector<vector<int>> lstComp = MFVS::getFullComponents(graph, minSep);
            lstFullComp.push_back(lstComp);
            //printFullComponents(minSep, lstComp);
        }

        //Get full blocks
        vector<vector<vector<int>>> lstFullBlock = MFVS::constructFullBlocks(lstMinSeps, lstFullComp);

        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop-start);
        cout << "Full blocks : " << duration2.count() << endl;
        
        start = high_resolution_clock::now();

        //Find all potential maximal cliques
        vector<vector<int>> lstOldPMC = MFVS::getOldAllPotentialMaximalCliques(graph);
        printPotentialMaximalCliques(lstOldPMC);

        stop = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop-start);
        cout << "old PMCs : " << duration3.count() << endl;

        start = high_resolution_clock::now();
        
        //Find all potential maximal cliques
        vector<vector<int>> lstNewPMC = MFVS::getNewAllPotentialMaximalCliques(graph);
        printPotentialMaximalCliques(lstNewPMC);

        stop = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop-start);
        cout << "new PMCs : " << duration4.count() << endl;

        start = high_resolution_clock::now();

        //Construct good triplets
        //For each triplet, it contains minimal separator index, full block index, and pmc index
        vector<vector<int>> lstTripletIdx = MFVS::constructGoodTriplet(lstMinSeps, lstFullBlock, lstOldPMC);

        stop = high_resolution_clock::now();
        auto duration5 = duration_cast<microseconds>(stop-start);
        cout << "Triple : " << duration5.count() << endl;

        cout << "Total : " << duration1.count() + duration2.count() + duration3.count() + duration5.count() << endl;
    }
}
