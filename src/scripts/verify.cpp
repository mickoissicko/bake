#include "../includes/imp.hpp"

#include <iostream>
#include <fstream>

bool MainFound = false;
bool BakeFound = false;
bool CookFound = false;
bool ServeFound = false;

std::string Line;

using namespace defs;

void VerifyFile()
{
    defs::isf BakeFile("Bakefile");

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && Line.find("!main{") != str::npos)
        {
            MainFound = true;
        }
        else if (!(Line.empty()) && Line.find("!bake{") != str::npos)
        {
            BakeFound = true;
        }
        else if (!(Line.empty()) && Line.find("!cook{") != str::npos)
        {
            CookFound = true;
        }
        else if (!(Line.empty()) && Line.find("!serve{") != str::npos)
        {
            ServeFound = true;
        }
    }

    BakeFile.close();

    if (!ServeFound || !(MainFound || BakeFound || CookFound))
    {
        std::cerr << "No exit or entry point?" << std::endl;

        exit(1);
    }
}
