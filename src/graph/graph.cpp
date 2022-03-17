#include <iostream>
#include <math.h>

#include "graph.h"

using namespace std;

/**
 * @brief Construct a new undirected Graph:: Graph object
 * @param numNodes 
 */
Graph::Graph(int numNodes)
{
    nNodes = 0;
    nEdges = 0;
    nNodeVal = 1;

    for(int i=0; i<numNodes; i++)
    {
        this->addNode();
    }
}

/**
 * Get total number of nodes in the graph
 * @return int 
 */
int Graph::getTotalNodes()
{
    return nNodes;
}

/**
 * Get total number of edges in the graph
 * @return int 
 */
int Graph::getTotalEdges()
{
    return nEdges;
}

/** 
 * Add new node into grpah
 * @return int 
 */
int Graph::addNode()
{
    GraphNode* node = new GraphNode(nNodeVal);
    mapNodes[nNodeVal] = node;
    nNodeVal++;
    nNodes++;
    return nNodeVal;
}

/**
 * Remove given node from graph
 * @param nodeVal 
 */
void Graph::removeNode(int nodeVal)
{
    if(mapNodes.find(nodeVal) != mapNodes.end())
    {
        this->removeAllEdgesOfNode(mapNodes[nodeVal]);
        delete mapNodes[nodeVal];
        mapNodes.erase(nodeVal);
        nNodes--;
    }
}

/**
 * Get node pointer from node value
 * @param nodeVal 
 * @return GraphNode* 
 */
GraphNode* Graph::getNode(int nodeVal)
{
    if(mapNodes.find(nodeVal) == mapNodes.end())
        return nullptr;
    return mapNodes[nodeVal];
}

/**
 * Add edge between two given nodes
 * @param fromNodeVal 
 * @param toNodeVal 
 */
void Graph::addEdge(int fromNodeVal, int toNodeVal)
{
    GraphNode* fromNode = this->getNode(fromNodeVal);
    GraphNode* toNode = this->getNode(toNodeVal);
    if(fromNode == nullptr || toNode == nullptr)
        return;
  
    int key = this->generateEdgeKey(fromNodeVal, toNodeVal);

    if(mapEdges.find(key) == mapEdges.end())
    {
        mapEdges[key] = 1;
        fromNode->addNeighbor(toNodeVal);
        toNode->addNeighbor(fromNodeVal);
        nEdges++;
    }
}

/**
 * Remove edge between two given nodes
 * @param fromNodeVal 
 * @param toNodeVal 
 */
void Graph::removeEdge(int fromNodeVal, int toNodeVal)
{
    GraphNode* fromNode = this->getNode(fromNodeVal);
    GraphNode* toNode = this->getNode(toNodeVal);
    if(fromNode == nullptr || toNode == nullptr)
        return;

    int key = this->generateEdgeKey(fromNodeVal, toNodeVal);
    if(mapEdges.find(key) != mapEdges.end() && mapEdges[key] == 1)
    {
        mapEdges.erase(key);
        fromNode->removeNeighbor(toNodeVal);
        toNode->removeNeighbor(fromNodeVal);
        nEdges--;
    }
}

/**
 * Check whether there is an edge between two nodes
 * @param fromNodeVal 
 * @param toNodeVal 
 * @return true 
 * @return false 
 */
bool Graph::containsEdge(int fromNodeVal, int toNodeVal)
{
    int key = this->generateEdgeKey(fromNodeVal, toNodeVal);
    if(mapEdges.find(key) != mapEdges.end() && mapEdges[key] == 1)
    {
        return true;
    }
    return false;
}

/**
 * Generate key value for edge hashmap
 * @param fromNodeVal 
 * @param toNodeVal 
 * @return int 
 */
int Graph::generateEdgeKey(int fromNodeVal, int toNodeVal)
{
    int maxNodeVal = max(fromNodeVal, toNodeVal);
    int minNodeVal = min(fromNodeVal, toNodeVal);
    int key = pow(maxNodeVal, 2) - minNodeVal + 1;
    return key;
}

/**
 * Remove all edges of the given node
 * @param node
 */
void Graph::removeAllEdgesOfNode(GraphNode* node)
{
    unordered_set<int> setNeighbors = node->getAllNeighbors();
    for(auto it = setNeighbors.begin(); it != setNeighbors.end(); it++)
    {
        int neighborVal = *it;
        this->removeEdge(node->getNodeValue(), neighborVal);
    }
}

/**
 * Print graph
 */
void Graph::printGraph()
{
    cout << "Total nodes : " << nNodes << endl;
    cout << "Total edges : " << nEdges << endl;
    cout << endl;

    cout << "Edges" << endl;
    int key = 0;
    for(int i=1; i<=nNodes; i++)
    {
        for(int j=i+1; j<=nNodes; j++)
        {
            key = pow(j, 2) - i + 1;
            if(mapEdges.find(key) != mapEdges.end())
            {
                cout << i << " " << j << endl;
            }
        }
    }
    cout << endl;

    cout << "Neighbors" << endl;
    GraphNode* node;
    for(int i=1; i<=nNodes; i++)
    {
        cout << "Neighbors of " << i << " : ";
        node = this->getNode(i);
        for(int j : node->getAllNeighbors())
        {
            cout << j << " ";
        }
        cout << endl;
    }
}