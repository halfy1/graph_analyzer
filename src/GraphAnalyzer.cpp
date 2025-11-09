#include "GraphAnalyzer.h"
#include <algorithm>

bool GraphAnalyzer::isEmpty() const
{
    for (int i = 0; i < graph.getVertexCount(); i++){
        if (graph.getDegree(i) != 0) return false;
    }
    return true;
}

bool GraphAnalyzer::isComplete() const {
    int V = graph.getVertexCount();
    if (V == 0 ) return true;

    int exepectDegree = V - 1;
    for (int i = 0; i < V; i++){
        if (graph.getDegree(i) != exepectDegree) return false;
    }
    return true;
}

bool GraphAnalyzer::isCycle() const {
    int V = graph.getVertexCount();
    if (V < 3) return false;

    if (!graph.isConnected()) return false;

    for (int i = 0; i < V; i++) {
        if (graph.getDegree(i) !=2) return false;
    }

    return true;
}

bool GraphAnalyzer::isStar() const {
    int V = graph.getVertexCount();
    if (V < 2) return false;
    
    int centerCount = 0;
    int leafCount = 0;
    
    for (int i = 0; i < V; i++){
        int d = graph.getDegree(i);
        if (d == V - 1) {
            centerCount++;
        } else if (d == 1){
            leafCount++;
        } else {
            return false;
        }
    }
    
    return centerCount == 1 && leafCount == V - 1;
}

bool GraphAnalyzer::isCompleteBipartite(int m, int n) const {

    if (m == 0 || n == 0) return false;

    if (m * n != graph.getEdgeCount()) return false;
    
    // В полном двудольном K(m,n):
    // - m вершин имеют степень n
    // - n вершин имеют степень m
    
    int countDegreeM = 0;
    int countDegreeN = 0;
    
    for (int i = 0; i < graph.getVertexCount(); i++) {
        int d = graph.getDegree(i);
        if (d == m) countDegreeM++;
        else if (d == n) countDegreeN++;
        else return false;  // есть вершина с неправильной степенью
    }
    
    return (countDegreeM == n && countDegreeN == m);
}

std::vector<std::string> GraphAnalyzer::analyze() const {
    std::vector<std::string> results;
    int V = graph.getVertexCount();

    if (isEmpty()) {
        results.push_back("Пустой K" + std::to_string(V));
    }

    if (isComplete()) {
        results.push_back("Полный K" + std::to_string(V));
    }

    if (isCycle()) {
        results.push_back("Цикл C" + std::to_string(V));
    }
    
    if (isStar()) {
        results.push_back("Звездный S" + std::to_string(V - 1));
    }

    auto bipartiteInfo = graph.isBipartite();
    if (!isEmpty()) {
        auto bipartiteInfo = graph.isBipartite();
        if (bipartiteInfo.first) {
            int m = bipartiteInfo.second.first;
            int n = bipartiteInfo.second.second;

            if (isCompleteBipartite(m, n)) {
                results.push_back("Полный двудольный K" + std::to_string(m) + "," + std::to_string(n));
            } else {
                results.push_back("Двудольный");
            }
        }
    }

    if (results.empty()) {
        results.push_back("Ни один из перечисленных");
    }

    return results;
}
