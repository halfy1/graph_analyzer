#include "OrdTreeChecker.h"
#include <fstream>
#include <iostream>

OrdTreeChecker::OrdTreeChecker(const Graph& g) 
    : graph(g), hasUniqueRoot(false), rootVertex(-1), 
      allNonRootHaveInDegreeOne(false), allReachableFromRoot(false),
      isOrdTree(false), isTreeCounted(false) {}

void OrdTreeChecker::checkRoot() {
    int n = graph.getVertexCount();
    rootCandidates.clear();
    
    for (int v = 1; v <= n; v++) {
        if (graph.getInDegree(v) == 0) {
            rootCandidates.push_back(v);
        }
    }
    
    if (rootCandidates.size() == 1) {
        hasUniqueRoot = true;
        rootVertex = rootCandidates[0];
    } else {
        hasUniqueRoot = false;
    }
}

void OrdTreeChecker::checkInDegrees() {
    if (!hasUniqueRoot) {
        allNonRootHaveInDegreeOne = false;
        return;
    }
    
    int n = graph.getVertexCount();
    wrongInDegreeVertices.clear();
    
    for (int v = 1; v <= n; v++) {
        if (v == rootVertex) continue;
        
        if (graph.getInDegree(v) != 1) {
            wrongInDegreeVertices.push_back(v);
        }
    }
    
    allNonRootHaveInDegreeOne = wrongInDegreeVertices.empty();
}

void OrdTreeChecker::checkReachability() {
    if (!hasUniqueRoot) {
        allReachableFromRoot = false;
        return;
    }
    
    int n = graph.getVertexCount();
    unreachableVertices.clear();
    
    std::vector<bool> reachable = graph.getReachableFrom(rootVertex);
    
    for (int v = 1; v <= n; v++) {
        if (v == rootVertex) continue;
        
        if (!reachable[v]) {
            unreachableVertices.push_back(v);
        }
    }
    
    allReachableFromRoot = unreachableVertices.empty();
}

void OrdTreeChecker::checkTreeCounted() {
    int n = graph.getVertexCount();
    int m = graph.getEdgeCount();
    
    isTreeCounted = (m == n - 1);
}

void OrdTreeChecker::performChecks() {
    checkRoot();
    checkInDegrees();
    checkReachability();
    checkTreeCounted();
    
    isOrdTree = hasUniqueRoot && allNonRootHaveInDegreeOne && allReachableFromRoot;
}

void OrdTreeChecker::printResults(std::ostream& out) const {
    int n = graph.getVertexCount();
    int m = graph.getEdgeCount();
    
    out << "Граф: n=" << n << ", m=" << m << std::endl << std::endl;
    
    out << "1. Наличие единственного корня: ";
    if (hasUniqueRoot) {
        out << "да (вершина " << rootVertex << ")" << std::endl;
    } else {
        out << "нет" << std::endl;
        out << "   Полустепени захода: ";
        for (int v = 1; v <= n; v++) {
            out << "deg⁻(" << v << ")=" << graph.getInDegree(v);
            if (v < n) out << ", ";
        }
        out << std::endl;
    }
    
    out << "2. Полустепени захода (кроме корня) равны 1: ";
    if (!hasUniqueRoot) {
        out << "не применимо" << std::endl;
    } else if (allNonRootHaveInDegreeOne) {
        out << "да" << std::endl;
    } else {
        out << "нет" << std::endl;
        out << "   Нарушения: ";
        for (size_t i = 0; i < wrongInDegreeVertices.size(); i++) {
            int v = wrongInDegreeVertices[i];
            out << "v" << v << "(deg⁻=" << graph.getInDegree(v) << ")";
            if (i < wrongInDegreeVertices.size() - 1) out << ", ";
        }
        out << std::endl;
    }
    
    out << "3. Достижимость всех вершин из корня: ";
    if (!hasUniqueRoot) {
        out << "не применимо" << std::endl;
    } else if (allReachableFromRoot) {
        out << "да" << std::endl;
    } else {
        out << "нет" << std::endl;
        out << "   Недостижимые: ";
        for (size_t i = 0; i < unreachableVertices.size(); i++) {
            out << unreachableVertices[i];
            if (i < unreachableVertices.size() - 1) out << ", ";
        }
        out << std::endl;
    }
    
    out << "4. Древочисленность (q=p-1): ";
    out << m << "=" << (n-1) << " - ";
    if (isTreeCounted) {
        out << "да" << std::endl;
    } else {
        out << "нет" << std::endl;
    }
    
    out << std::endl << "ИТОГ: ";
    if (isOrdTree) {
        out << "ордерево";
    } else {
        out << "не ордерево";
    }
    out << ", ";
    if (isTreeCounted) {
        out << "древочисленный";
    } else {
        out << "не древочисленный";
    }
    out << std::endl;
}

void OrdTreeChecker::writeResults(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи " << filename << std::endl;
        return;
    }
    
    printResults(file);
    file.close();
    
    std::cout << "Результаты записаны в файл: " << filename << std::endl;
}