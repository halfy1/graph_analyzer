#include <iostream>
#include <filesystem>
#include <string>
#include "Graph.h"
#include "OrdTreeChecker.h"

namespace fs = std::filesystem;

int main() {
    fs::create_directories("outputs");

    for (const auto& entry : fs::directory_iterator("tests")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string inputFile = entry.path().string();
            std::string outputFile = "outputs/" + entry.path().stem().string() + "_out.txt";

            Graph graph;
            if (!graph.loadFromFile(inputFile))
                continue;

            OrdTreeChecker checker(graph);
            checker.performChecks();
            checker.writeResults(outputFile);
        }
    }

    return 0;
}
