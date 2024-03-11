#include "../includes/imp.hpp"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdbool>

// so i dont have to use 'defs::str::npos' because what's the point then?
using namespace defs;

void Oven()
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
    
    std::string Line;

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && !(Line.find("!--") == 0))
        {
            if (
                (Line.find(CookKey)     != std::string::npos  || 
                Line.find(BakeKey)      != std::string::npos  || 
                Line.find(ServeKey)     != std::string::npos) && 
                Line.find(OpeningBrace) != std::string::npos)
            {
                ShouldExecute = true;
            }

            if (ShouldExecute && Line.find("}") == 0)
            {
                ShouldExecute = false;
            }

            if (ShouldExecute)
            {
                size_t start = Line.find(":");
                size_t end = Line.rfind(":");

                if (start != str::npos && end != str::npos && start < end)
                {
                    std::string command = Line.substr(start + 1, end - start - 1);
                    Cook(command);
                }
            }
        }

        else{} // do nothing
    }

    BakeFile.close();
}
