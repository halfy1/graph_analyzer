#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>

Graph FileHandler::readGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    int V, E;
    file >> V >> E;
    
    Graph graph(V);
    
    for (int i = 0; i < E; i++) {
        int u, v;
        file >> u >> v;
        graph.addEdge(u, v);
    }
    
    file.close();
    return graph;
}

void FileHandler::writeResultsToFile(const std::string& filename, 
                                   const std::vector<std::string>& results) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    file << "Результаты анализа графа:\n";
    for (size_t i = 0; i < results.size(); i++) {
        file << (i + 1) << ". " << results[i] << "\n";
    }
    
    file.close();
}

std::vector<std::string> FileHandler::getInputFiles(const std::string& directory) {
    std::vector<std::string> files;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                files.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Ошибка доступа к директории: " << e.what() << std::endl;
    }
    
    return files;
}