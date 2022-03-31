#include <iostream>
#include <fstream>
#include "src/graph/graph.h"
#include "src/minimumFeedbackVertexSet.h"

using namespace std;

/**
 * Initialize graph from given file path
 * @param strFilePath 
 * @return Graph
 */
Graph initGraph(string strFilePath)
{
    ifstream inFile;
    inFile.open(strFilePath);

    if (!inFile.is_open())
    {
        cout << "Failed to open input file!" << endl;
        exit(0);
    }
    else
    {
        cout << "Opened input file!" << endl;

        int nNodes;
        inFile >> nNodes;
        Graph graph(nNodes);

        int fromNode, toNode;
        while (inFile >> fromNode && inFile >> toNode)
        {
            graph.addEdge(fromNode, toNode);
        }
        inFile.close();
        return graph;
    }
    return Graph(0);
}

int main()
{
    string strFilePath("testGraphs/manual/graph2.txt");
    Graph graph = initGraph(strFilePath);
    //graph.printGraph();
    MFVS::findMinimumFeedbackVertexSet(&graph);
    return 0;
}