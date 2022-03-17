#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>

#include "graphNode.h"

using namespace std;

class Graph
{
    private:
        unordered_map<int, GraphNode*> mapNodes;
        unordered_map<int, int> mapEdges; //x^2-y+1 where x and y are node values and x > y
        int nNodes, nEdges;
        int nNodeVal;

        int generateEdgeKey(int fromNodeVal, int toNodeVal);
        void removeAllEdgesOfNode(GraphNode* node);

    public:
        Graph(int numNodes);
        int getTotalNodes();
        int getTotalEdges();

        int addNode();
        void removeNode(int nodeVal);
        GraphNode* getNode(int nodeVal);

        void addEdge(int fromNodeVal, int toNodeVal);
        void removeEdge(int fromNodeVal, int toNodeVal);
        bool containsEdge(int fromNodeVal, int toNodeVal);
        
        void printGraph();
};

#endif //GRAPH_H