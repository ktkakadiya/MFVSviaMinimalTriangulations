#ifndef SETOPR_H
#define SETOPR_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

namespace SOP
{
    bool isSubset(vector<int> vec, vector<int> subvec);
    vector<int> getUnion(vector<int> vec1, vector<int> vec2);
    vector<int> getIntersection(vector<int> vec1, vector<int> vec2);
}

#endif //SETOPR_H