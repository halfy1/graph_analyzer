#include "Graph.h"
#include <iostream>
#include <queue>

Graph::Graph() : n(0), m(0) {}

bool Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return false;
    }
    
    file >> n >> m;
    
    if (n <= 0 || m < 0) {
        std::cerr << "Ошибка: некорректные значения n или m" << std::endl;
        return false;
    }
    
    adjList.resize(n + 1);
    inDegree.resize(n + 1, 0);
    outDegree.resize(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        file >> u >> v;
        
        if (u < 1 || u > n || v < 1 || v > n) {
            std::cerr << "Ошибка: вершина вне диапазона [1, " << n << "]" << std::endl;
            return false;
        }
        
        adjList[u].push_back(v);
        outDegree[u]++;
        inDegree[v]++;
    }
    
    file.close();
    return true;
}

std::vector<bool> Graph::getReachableFrom(int root) const {
    std::vector<bool> reachable(n + 1, false);
    if (root < 1 || root > n) {
        return reachable;
    }
    
    std::queue<int> q;
    q.push(root);
    reachable[root] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adjList[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    
    return reachable;
}

bool Graph::isConnectedUndirected() const {
    if (n == 0) return true;
    
    std::vector<std::vector<int>> undirectedAdj(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : adjList[u]) {
            undirectedAdj[u].push_back(v);
            undirectedAdj[v].push_back(u);
        }
    }
    
    std::vector<bool> visited(n + 1, false);
    std::queue<int> q;
    q.push(1);
    visited[1] = true;
    int visitedCount = 1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : undirectedAdj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                visitedCount++;
                q.push(v);
            }
        }
    }
    
    return visitedCount == n;
}

void Graph::printInfo(std::ostream& out) const {
    out << "Граф: n = " << n << ", m = " << m << std::endl;
    out << "Список рёбер:" << std::endl;
    for (int u = 1; u <= n; u++) {
        for (int v : adjList[u]) {
            out << "  " << u << " -> " << v << std::endl;
        }
    }
    out << std::endl;
}