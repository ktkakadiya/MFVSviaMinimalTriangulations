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

void writeResults(string strOutputFilePath, vector<int> lstTimes)
{
    ofstream outFile(strOutputFilePath);

    if (!outFile.is_open())
    {
        cout << "Failed to open output file!" << endl;
        exit(0);
    }
    else if(lstTimes.size() >= 7)
    {
        outFile << "Minimal separators : " << lstTimes.at(0) << " microseconds"<< endl;
        outFile << "Full blocks : " << lstTimes.at(1) << " microseconds"<<  endl;
        outFile << "Potential Maximal Cliques (old way) : " << lstTimes.at(2) << " microseconds"<<  endl;
        outFile << "Potential Maximal Cliques (new way) : " << lstTimes.at(3) << " microseconds"<<  endl;
        outFile << "Good triples : " << lstTimes.at(4) << " microseconds"<<  endl;
        outFile << "Total time (old way) : " << lstTimes.at(5) << " microseconds"<<  endl;
        outFile << "Total time (new way) : " << lstTimes.at(6) << " microseconds"<<  endl;
    }
    outFile.close();
}

int main()
{
    vector<string> lstType{"random_tree"};
    for(string strType : lstType)
    {
        for(int i=5; i<=50; i+=5)
        { 
            string strFilePath("testGraphs/" + strType + "/" + strType + "_" + to_string(i) + ".txt");
            Graph graph = initGraph(strFilePath);
            //graph.printGraph();

            vector<int> lstTimes = MFVS::findMinimumFeedbackVertexSet(&graph);

            string strOutputFilePath("results/data/" + strType + "/" + strType + "_" + to_string(i) + ".txt");
            writeResults(strOutputFilePath, lstTimes);
        }
    }
    return 0;
}