import networkx as nx
import os

def generate_graph(strType, func, multi=5):
    if os.path.isdir(strType) == False:
        os.mkdir(strType)
    for i in range(1,11):
        nodes = i * multi
        strPath = strType + "/" + strType + "_" + str(nodes) + ".txt";
        with open(strPath, 'w') as f:
            f.write(str(nodes) + "\n")
        with open(strPath, 'ab') as f:
            g = func(nodes)
            nx.write_edgelist(g, f, data=False)

def main():
    generate_graph("complete", nx.complete_graph)
    generate_graph("cycle", nx.cycle_graph)
    generate_graph("path", nx.path_graph)
    generate_graph("star", nx.star_graph)
    generate_graph("random_internet", nx.random_internet_as_graph)
    generate_graph("random_tree", nx.random_tree)

if __name__ == "__main__":
    main()