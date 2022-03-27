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
     * @brief Find minimum feedback vertex set for given graph
     * 
     * @param graph 
     */
    void findMinimumFeedbackVertexSet(Graph* graph)
    {
        //Find minimal separators
        vector<vector<int>> lstMinSeps = MFVS::findMinimalSeparator(graph);
        printMinimalSeparators(lstMinSeps);

        //MFVS::getFullComponents();
    }
}
