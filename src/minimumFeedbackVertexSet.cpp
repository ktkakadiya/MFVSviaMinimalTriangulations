#include "minimumFeedbackVertexSet.h"
#include "minimalSeparator.h"
#include "fullComponents.h"
#include "oldPotentialMaximalClique.h"
#include "newPotentialMaximalClique.h"
#include "setOperations.h"

#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std;

namespace MFVS
{
    /**
     * @brief Construct full blocks
     * 
     * @param lstMinSeps Set of minimal separators
     * @param lstFullComp Set of full components for each separators
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
     * @brief Construct good triples of graph
     * 
     * @param lstMinSeps Set of minimal separators
     * @param lstFullBlock Set of full blocks for each separators
     * @param lstPMC Set of potential maximal cliques
     * @return vector<vector<vector<int>>>
     */
    vector<vector<int>> constructGoodTriples(vector<vector<int>> lstMinSeps, vector<vector<vector<int>>> lstFullBlock, vector<vector<int>> lstPMC)
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

        //Sort triples based on block sizes
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
    vector<int> findMinimumFeedbackVertexSet(Graph* graph)
    {
        //tree width for maximum induced forest is 1
        int treeWidth = 1;

        vector<int> lstTimes;
        auto start = high_resolution_clock::now();

        //Find minimal separators
        vector<vector<int>> lstMinSeps = MFVS::findMinimalSeparator(graph);

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
        lstTimes.push_back(duration1.count());

        start = high_resolution_clock::now();
        
        //Generate all full components
        vector<vector<vector<int>>> lstFullComp;
        for(vector<int> minSep : lstMinSeps)
        {
            vector<vector<int>> lstComp = MFVS::getFullComponents(graph, minSep);
            lstFullComp.push_back(lstComp);
        }

        //Generate all full blocks
        vector<vector<vector<int>>> lstFullBlock = MFVS::constructFullBlocks(lstMinSeps, lstFullComp);

        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop-start);
        lstTimes.push_back(duration2.count());
        
        start = high_resolution_clock::now();

        //Find all potential maximal cliques using the method mentioned in [2]
        vector<vector<int>> lstOldPMC = MFVS::getOldAllPotentialMaximalCliques(graph);

        stop = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop-start);
        lstTimes.push_back(duration3.count());

        start = high_resolution_clock::now();

        //Find all potential maximal cliques using the method mentioned in [1]
        vector<vector<int>> lstNewPMC = MFVS::getNewAllPotentialMaximalCliques(graph);

        stop = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop-start);
        lstTimes.push_back(duration4.count());
        
        start = high_resolution_clock::now();

        //Construct good triples
        //For each triplet, it contains minimal separator index, full block index, and pmc index
        vector<vector<int>> lstTripletIdx = MFVS::constructGoodTriples(lstMinSeps, lstFullBlock, lstOldPMC);

        stop = high_resolution_clock::now();
        auto duration5 = duration_cast<microseconds>(stop-start);
        lstTimes.push_back(duration5.count());

        int oldTotal = duration1.count() + duration2.count() + duration3.count() + duration5.count();
        int newTotal = duration1.count() + duration2.count() + duration4.count() + duration5.count();
        lstTimes.push_back(oldTotal);
        lstTimes.push_back(newTotal);

        return lstTimes;
    }
}
