#ifndef ORDTREECHECKER_H
#define ORDTREECHECKER_H

#include "Graph.h"
#include <string>

class OrdTreeChecker {
private:
    const Graph& graph;
    
    bool hasUniqueRoot;
    int rootVertex;
    std::vector<int> rootCandidates;
    
    bool allNonRootHaveInDegreeOne;
    std::vector<int> wrongInDegreeVertices;
    
    bool allReachableFromRoot;
    std::vector<int> unreachableVertices;
    
    bool isOrdTree;
    bool isTreeCounted;
    
    void checkRoot();
    void checkInDegrees();
    void checkReachability();
    void checkTreeCounted();

public:
    explicit OrdTreeChecker(const Graph& g);
    
    void performChecks();
    
    void writeResults(const std::string& filename) const;
    
    void printResults(std::ostream& out) const;
};

#endif