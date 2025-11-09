#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"
#include "GraphAnalyzer.h"
#include "FileHandler.h"
#include <filesystem>

int main() {
    std::string inputDir = "data/input/";
    std::string outputDir = "data/output/";
    
    try {
        auto inputFiles = FileHandler::getInputFiles(inputDir);
        
        if (inputFiles.empty()) {
            std::cout << "В директории " << inputDir << " не найдено файлов с графами\n";
            return 1;
        }
        
        for (const auto& inputFile : inputFiles) {
            std::cout << "Обрабатывается файл: " << inputFile << std::endl;
            
            Graph graph = FileHandler::readGraphFromFile(inputFile);
            
            GraphAnalyzer analyzer(graph);
            auto results = analyzer.analyze();
            
            std::string outputFile = outputDir + 
                                   std::filesystem::path(inputFile).stem().string() + 
                                   "_result.txt";
            
            FileHandler::writeResultsToFile(outputFile, results);
            
            std::cout << "Результаты записаны в: " << outputFile << std::endl;
            std::cout << "Типы графа: ";
            for (const auto& result : results) {
                std::cout << result << " ";
            }
            std::cout << "\n\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}