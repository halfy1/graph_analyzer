#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "Graph.h"
#include <string>
#include <vector>

class FileHandler {
public:
    static Graph readGraphFromFile(const std::string& filename);
    static void writeResultsToFile(const std::string& filename, const std::vector<std::string>& results);
    static std::vector<std::string> getInputFiles(const std::string& directory);
};

#endif

