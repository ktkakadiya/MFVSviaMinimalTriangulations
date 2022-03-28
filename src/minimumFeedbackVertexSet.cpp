#include "minimumFeedbackVertexSet.h"
#include "minimalSeparator.h"
#include "fullComponents.h"

#include <iostream>

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
     * @brief Find minimum feedback vertex set for given graph
     * 
     * @param graph 
     */
    void findMinimumFeedbackVertexSet(Graph* graph)
    {
        //Find minimal separators
        vector<vector<int>> lstMinSeps = MFVS::findMinimalSeparator(graph);
        //printMinimalSeparators(lstMinSeps);

        vector<vector<vector<int>>> lstFullComp;
        //std::cout << "Printing full components " << endl;
        for(vector<int> minSep : lstMinSeps)
        {
            vector<vector<int>> lstComp = MFVS::getFullComponents(graph, minSep);
            lstFullComp.push_back(lstComp);
            //printFullComponents(minSep, lstComp);
        }
    }
}
