#ifndef GRAPH_ANALYZER_H
#define GRAPH_ANALYZER_H

#include "Graph.h"
#include <string>
#include <vector>

class GraphAnalyzer{
private:
    Graph graph;

    bool isCompleteBipartite(int m, int n) const;
    bool isStar() const;
public:
    GraphAnalyzer(const Graph& g) : graph(g) {};
    
    std::vector<std::string> analyze() const;

    bool isEmpty() const;
    bool isComplete() const;
    bool isCycle() const;
};

#endif