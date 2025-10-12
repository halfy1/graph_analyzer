#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <utility>

class Graph
{
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<int> degree;
public:

    Graph(int vertices = 0);

    void addEdge(int u, int v);
    int getVertexCount() const {return V;}
    int getEdgeCount() const;
    const std::vector<int>& getNeighbors(int vertex) const { return adj[vertex];}
    int getDegree(int vertex) const {return degree[vertex];}
    const std::vector<int>& getDegrees() const { return degree;}


    bool isConnected() const;
    std::pair<bool, std::pair<int,int>> isBipartite() const;

    void clear();
    void resize(int vertices);
};

#endif
