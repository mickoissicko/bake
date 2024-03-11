#include "../includes/imp.hpp"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdbool>

// so i dont have to use 'defs::str::npos' because what's the point then?
using namespace defs;

bool ShouldExecute = false;

std::string Line;

void Oven()
{
    defs::isf BakeFile("Bakefile");

    if (!BakeFile.is_open())
    {
        std::cerr << "No files?" << std::endl;
        return;
    }

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && !(Line.find("!--") == 0))
        {
            if (
                (Line.find("!cook{")     != str::npos  || 
                Line.find("!main{")      != str::npos  ||
                Line.find("!bake{")      != str::npos  || 
                Line.find("!serve{")     != str::npos) && 
                Line.find("{") != str::npos)
            {
                ShouldExecute = true;
            }

            if (ShouldExecute && Line.find("}") == 0)
            {
                ShouldExecute = false;
            }

            if (ShouldExecute)
            {
                size_t start = Line.find(">");
                size_t end = Line.rfind(";");

                if (start != str::npos && end != str::npos && start < end)
                {
                    std::string command = Line.substr(start + 1, end - start - 1);

                    Cook(command);
                }
            }
        }
    }

    BakeFile.close();
}
