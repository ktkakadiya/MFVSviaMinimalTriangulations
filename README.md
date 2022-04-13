# FVSviaTriangulations
The FVSviaTriangulations repository implements the method proposed in [1] for finding the Minimum Feedback Vertex Set for a given undirected graph using Potential Maximal Cliques.

## Table of contents
* [Introduction](#introduction)
* [Built with](#built-with)
* [Getting started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
* [Project strcuture](#project-strcuture)
* [References](#references)

## Introduction
A Feedback Vertex Set (FVS) for a graph G = (V, E) is a vertex set F ⊆ V such that vertex set F contains at least one vertex from every cycle of the graph. In other words, a feedback vertex set is a set of vertices whose deletion from the graph would result in an acyclic graph. A feedback vertex set with the minimum cardinality for a graph is called the Minimum Feedback Vertex Set.

## Built with
* Algorithm implementation : C++
* Data preparation and analysis : Python
* Automation tool : Make

## Getting started
### Prerequisites
* GNU C++ compiler
* Python (version 3)

### Installation
* Generate input data: 
  - `python testGraphs\generate_script.py`
* Create executable
  - `make`
* Run the executable (Windows OS)
  - `.\app.exe`
* Generate output graphs (Manual)
  - Generate step wise bar chart : `python results\generate_bar.py`
  - Generate cardinality vs. time line chart : `python results\generate_line.py`
  - Generate pmc method comparison line chart : `python results\generate_pmc_bar.py`

## Project strcuture
* **src** - Contains all the source code files.
* **objectFiles** - Contains all the \*.o files. 
* **testGraphs** - Contains all the input graph data text files.
* **results** - Contains all the execution result files.
* **app.cpp** - Main file of the project.

## References
1. Fedor V. Fomin and Yngve Villanger. 2009. Finding Induced Subgraphs via Minimal Triangulations. Proceedings of STACS 2010.
2. V. Bouchitt ́e and I. Todinca, Treewidth and Minimum Fill-in: Grouping the Minimal Separators, SIAM Journal on Computing, 31 (2001), pp. 212–232.
3. Anne Berry, Jean Paul Bordat, and Olivier Cogis. 1999. Generating All the Minimal Separators of a Graph. In Proceedings of the 25th International Workshop on Graph-Theoretic Concepts in Computer Science (WG ’99). Springer-Verlag, Berlin, Heidelberg, 167–172.
