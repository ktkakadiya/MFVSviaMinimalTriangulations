#include "setOperations.h"

#include <algorithm>
using namespace std;

namespace SOP
{
    /**
     * @brief Check whether a set is subset of other set
     * 
     * @param vec Main set
     * @param subvec Subset
     * @return true 
     * @return false 
     */
    bool isSubset(vector<int> vec, vector<int> subvec)
    {
        unordered_set<int> set;
        for(int a : vec)
        {
            set.insert(a);
        }
        for(int a : subvec)
        {
            set.insert(a);
        }

        if(set.size() == vec.size())
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Get the Union of two vectors
     * 
     * @param vec1 Set 1
     * @param vec2 Set 2
     * @return vector<int> 
     */
    vector<int> getUnion(vector<int> vec1, vector<int> vec2)
    {
        unordered_set<int> set;
        for(int a : vec1)
        {
            set.insert(a);
        }
        for(int a : vec2)
        {
            set.insert(a);
        }

        vector<int> vec(set.begin(), set.end());
        return vec;
    }

    /**
     * @brief Get the Intersection of two vectors
     * 
     * @param vec1 
     * @param vec2 
     * @return vector<int> 
     */
    vector<int> getIntersection(vector<int> vec1, vector<int> vec2)
    {
        vector<int> vec;
        unordered_map<int, int> itemCount;
        for(int a : vec1)
        {
            if(itemCount.find(a) == itemCount.end())
            {
                itemCount[a] = 1;
            }
        }
        for(int a : vec2)
        {
            if(itemCount.find(a) != itemCount.end())
            {
                itemCount[a] = 2;
            }
        }

        for(auto it : itemCount)
        {
            if(it.second == 2)
            {
                vec.push_back(it.first);
            }
        }

        return vec;
    }
}