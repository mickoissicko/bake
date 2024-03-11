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

    const std::string CookKey      = ">cook";
    const std::string BakeKey      = ">bake";
    const std::string ServeKey     = ">serve";
    const std::string OpeningBrace = "{";
    
    bool ShouldExecute = false;
    bool ShouldIgnore  = false;
    
    std::string line;

    while (std::getline(BakeFile, line))
    {
        if (
                !(line.empty()) && 
                !(line.find("!") == 0)
        )
        {
            if (
                (line.find(CookKey)     != std::string::npos  || 
                line.find(BakeKey)      != std::string::npos  || 
                line.find(ServeKey)     != std::string::npos) && 
                line.find(OpeningBrace) != std::string::npos)
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
