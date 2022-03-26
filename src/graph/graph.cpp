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
    nNodeVal = 0;

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
    setNodes.insert(++nNodeVal);
    mapNeighbor[nNodeVal] = unordered_set<int>(0);
    nNodes++;
    return nNodeVal;
}

/**
 * Remove given node from graph
 * @param nodeVal 
 */
void Graph::removeNode(int node)
{
    if(setNodes.find(node) != setNodes.end())
    {
        this->removeAllEdgesOfNode(node);
        setNodes.erase(node);
        nNodes--;
    }
}

/**
 * Add edge between two given nodes
 * @param fromNode 
 * @param toNode 
 */
void Graph::addEdge(int fromNode, int toNode)
{
    if(setNodes.find(fromNode) == setNodes.end() || setNodes.find(toNode) == setNodes.end())
        return;
  
    int key = this->generateEdgeKey(fromNode, toNode);
    if(mapEdges.find(key) == mapEdges.end())
    {
        mapEdges[key] = 1;
        mapNeighbor[fromNode].insert(toNode);
        mapNeighbor[toNode].insert(fromNode);
        nEdges++;
    }
}

/**
 * Remove edge between two given nodes
 * @param fromNode 
 * @param toNode 
 */
void Graph::removeEdge(int fromNode, int toNode)
{
    if(setNodes.find(fromNode) == setNodes.end() || setNodes.find(toNode) == setNodes.end())
        return;

    int key = this->generateEdgeKey(fromNode, toNode);
    if(mapEdges.find(key) != mapEdges.end() && mapEdges[key] == 1)
    {
        mapEdges.erase(key);
        mapNeighbor[fromNode].erase(toNode);
        mapNeighbor[toNode].erase(fromNode);
        nEdges--;
    }
}

/**
 * Check whether there is an edge between two nodes
 * @param fromNode 
 * @param toNode 
 * @return true 
 * @return false 
 */
bool Graph::containsEdge(int fromNode, int toNode)
{
    int key = this->generateEdgeKey(fromNode, toNode);
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
int Graph::generateEdgeKey(int fromNode, int toNode)
{
    int maxNodeVal = max(fromNode, toNode);
    int minNodeVal = min(fromNode, toNode);
    int key = pow(maxNodeVal, 2) - minNodeVal + 1;
    return key;
}

/**
 * Remove all edges of the given node
 * @param node
 */
void Graph::removeAllEdgesOfNode(int node)
{
    unordered_set<int> setNeighbors = mapNeighbor[node];
    for(auto it = setNeighbors.begin(); it != setNeighbors.end(); it++)
    {
        this->removeEdge(node, *it);
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
    for(int i=1; i<=nNodes; i++)
    {
        cout << "Neighbors of " << i << " : ";
        for(int j : mapNeighbor[i])
        {
            cout << j << " ";
        }
        cout << endl;
    }
}