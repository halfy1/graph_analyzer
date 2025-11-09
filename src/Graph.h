
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <fstream>

class Graph {
private:
    int n;
    int m;
    std::vector<std::vector<int>> adjList;
    std::vector<int> inDegree;
    std::vector<int> outDegree;

public:
    Graph();
    
    bool loadFromFile(const std::string& filename);
    
    int getVertexCount() const { return n; }
    int getEdgeCount() const { return m; }
    
    const std::vector<std::vector<int>>& getAdjList() const { return adjList; }
    
    int getInDegree(int v) const { return inDegree[v]; }
    int getOutDegree(int v) const { return outDegree[v]; }
    
    std::vector<bool> getReachableFrom(int root) const;
    
    bool isConnectedUndirected() const;
    
    void printInfo(std::ostream& out) const;
};

#endif