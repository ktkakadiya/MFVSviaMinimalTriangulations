#include <vector>
#include <unordered_set>

using namespace std;

class GraphNode
{
    private:
        int nodeVal;
        unordered_set<int> setNeighbors;

    public:
        GraphNode(int nodeValue);
        int getNodeValue();
        void setNodeValue(int nodeValue);

        void addNeighbor(int nodeValue);
        void removeNeighbor(int nodeValue);
        unordered_set<int> getAllNeighbors();
};