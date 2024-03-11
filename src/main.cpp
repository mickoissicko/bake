#include "includes/imp.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {
    defs::isf BakeFile("Cook.bake");

    if (!BakeFile.is_open())
    {
        std::cerr << "Error opening Cook.bake" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(BakeFile, line))
    {
        if (!line.empty())
        {
            size_t start = line.find(":");
            size_t end = line.rfind(":");

            if (start != std::string::npos && end != std::string::npos && start < end)
            {
                std::string command = line.substr(start + 1, end - start - 1);
                Cook(command);
            }
        }
    }

    BakeFile.close();

    return 0;
}

