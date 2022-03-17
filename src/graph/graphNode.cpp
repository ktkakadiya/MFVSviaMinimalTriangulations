#include <iostream>

#include "graphNode.h"

using namespace std;

GraphNode::GraphNode(int nodeValue)
{
    nodeVal = nodeValue;
}

/**
 * Get node value
 * @return int 
 */
int GraphNode::getNodeValue()
{
    return nodeVal;
}

/**
 * Set node value
 * @param nodeValue 
 */
void GraphNode::setNodeValue(int nodeValue)
{
    nodeVal = nodeValue;
}

/**
 * Add node neighbor by value
 * @param nodeValue 
 */
void GraphNode::addNeighbor(int nodeValue)
{
    setNeighbors.insert(nodeValue);
}

/**
 * Remove node neighbor by value
 * @param nodeValue 
 */
void GraphNode::removeNeighbor(int nodeValue)
{
    setNeighbors.erase(nodeValue);
}

/**
 * Get all node neighbors set
 * @param nodeValue 
 */
unordered_set<int> GraphNode::getAllNeighbors()
{
    return setNeighbors;
}

/**
 * Get the size of neighborhood
 * @return int 
 */
int GraphNode::getNeighborhoodSize()
{
    return setNeighbors.size();
}