#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>

using namespace std;

class Graph
{
    private:
        int nNodes, nEdges, nNodeVal;
        unordered_set<int> setNodes;


        int generateEdgeKey(int fromNode, int toNode);
        void removeAllEdgesOfNode(int node);

    public:
        unordered_map<int, int> mapEdges; //x^2-y+1 where x and y are node values and x > y
        unordered_map<int, unordered_set<int>> mapNeighbor;
        
        Graph(int numNodes);
        int getTotalNodes();
        int getTotalEdges();

        int addNode();
        void removeNode(int node);

        void addEdge(int fromNode, int toNode);
        void removeEdge(int fromNode, int toNode);
        bool containsEdge(int fromNode, int toNode);
        
        void printGraph();
};

#endif //GRAPH_H