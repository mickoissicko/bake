#include <iostream>
#include <fstream>
#include <string>

bool MainFound = false;
bool BakeFound = false;
bool CookFound = false;
bool ServeFound = false;

namespace defs {
    typedef std::ifstream isf;
    typedef std::string str;
}

using namespace defs;

void VerifyFile()
{
    defs::isf BakeFile("Bakefile");

    bool InMain = false;
    bool InBake = false;
    bool InCook = false;
    bool InServe = false;

    std::string Line;

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && Line.find("!main{") != str::npos)
        {
            InMain = true;
        }
        else if (!(Line.empty()) && Line.find("!bake{") != str::npos)
        {
            InBake = true;
        }
        else if (!(Line.empty()) && Line.find("!cook{") != str::npos)
        {
            InCook = true;
        }
        else if (!(Line.empty()) && Line.find("!serve{") != str::npos)
        {
            InServe = true;
        }

        size_t bracePos = Line.find_last_of('}');
        if (bracePos != str::npos)
        {
            if (InMain)
            {
                InMain = false;
                MainFound = true;
            }
            else if (InBake)
            {
                InBake = false;
                BakeFound = true;
            }
            else if (InCook)
            {
                InCook = false;
                CookFound = true;
            }
            else if (InServe)
            {
                InServe = false;
                ServeFound = true;
            }
        }
    }

    BakeFile.close();

    if (!ServeFound || !(MainFound || BakeFound || CookFound))
    {
        std::cerr << "Missing required section" << std::endl
                  << "Or forgot to terminate a previously opened curly brace with a closing brace!"
                  << std::endl;
                  
        exit(1);
    }
}
