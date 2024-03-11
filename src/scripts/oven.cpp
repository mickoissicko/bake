#include "../includes/imp.hpp"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdbool>

// so i dont have to use 'defs::str::npos' because what's the point then?
using namespace defs;

void oven()
{
    defs::isf BakeFile("Bakefile");

    if (!BakeFile.is_open())
    {
        std::cerr << "No files?" << std::endl;
        return;
    }

    std::string line;
    
    bool ShouldExecute = false;

    while (std::getline(BakeFile, line))
    {
        if (!line.empty())
        {
            if (
                (line.find(">cook") != str::npos   || 
                 line.find(">bake") != str::npos   ||  // ._. rawr
                 line.find(">serve") != str::npos) && 
                 line.find("{") != str::npos
            )
            {
                ShouldExecute = true;
            }

            if (ShouldExecute && line.find("}") == 0)
            {
                ShouldExecute = false;
            }

            if (ShouldExecute)
            {
                size_t start = line.find(":");
                size_t end = line.rfind(":");

                if (start != str::npos && end != str::npos && start < end)
                {
                    std::string command = line.substr(start + 1, end - start - 1);
                    Cook(command);
                }
            }
        }
    }

    BakeFile.close();
}
