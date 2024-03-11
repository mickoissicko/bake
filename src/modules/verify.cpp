#include "../includes/defs.hpp"

#include <iostream>
#include <map>
#include <fstream>

void VerifyFile()
{
    std::map<std::string, std::string> Vars;
    
    defs::isf BakeFile("Bakefile");

    bool MainFound = false;
    bool BakeFound = false;
    bool CookFound = false;
    bool ServeFound = false;
    bool InMain = false;
    bool InBake = false;
    bool InCook = false;
    bool InServe = false;

    std::string Line;

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && Line.find("!main{") != std::string::npos)
        {
            InMain = true;
        }
        else if (!(Line.empty()) && Line.find("!bake{") != std::string::npos)
        {
            InBake = true;
        }
        else if (!(Line.empty()) && Line.find("!cook{") != std::string::npos)
        {
            InCook = true;
        }
        else if (
            !(Line.empty()) && Line.find("!serve{") != std::string::npos ||
            Line.find("!serve{}") != std::string::npos
        )
        {
            InServe = true;
        }

        size_t BracePosition = Line.find_last_of('}');
        if (BracePosition != std::string::npos)
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

        size_t VarAssign = Line.find(":");
        size_t VarStart = Line.find("[");
        size_t VarTerminate = Line.find("]");

        if (
            VarAssign    != std::string::npos  &&
            VarStart     != std::string::npos  &&
            VarTerminate != std::string::npos
        )
        {
            std::string Var = Line.substr(0, VarAssign);
            std::string Val = Line.substr(VarStart + 1, VarTerminate - VarStart - 1);
            Vars[Var] = Val;
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
