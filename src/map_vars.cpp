#include "../import/common.hpp"

using namespace defs;

std::map<std::string, std::string> Vars;

std::string ThrowVal(const std::string &value)
{
    auto it = Vars.find(value);
    
    if (it != Vars.end())
    {
        return it -> second;
    }

    return "";
}

void VerifyFile()
{
    defs::isf BakeFile("Bakefile");

    bool MainFound  = false;
    bool BakeFound  = false;
    bool CookFound  = false;
    bool ServeFound = false;
    bool InMain     = false;
    bool InBake     = false;
    bool InCook     = false;
    bool InServe    = false;

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
        else if (
            !(Line.empty()) && Line.find("!serve{") != str::npos ||
            Line.find("!serve{}") != str::npos
        )
        {
            InServe = true;
        }

        size_t BracePosition = Line.find_last_of('}');
        if (BracePosition != str::npos)
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

        size_t AssignVar = Line.find(":");
        size_t VarStart = Line.find("[");
        size_t VarTerm = Line.find("]");

        if (AssignVar != str::npos && VarStart != str::npos && VarTerm != str::npos)
        {
            std::string Var = Line.substr(0, AssignVar);
            std::string Val = Line.substr(VarStart + 1, VarTerm - VarStart - 1);
            Vars[Var] = Val;
        }
    }

    BakeFile.close();

    if (!ServeFound)
    {
        std::cerr << "Missing required section to exit" << std::endl;

        exit(1);
    }

    else if (!(MainFound || CookFound || BakeFound))
    {
        std::cerr << "Missing required section to start" << std::endl;

        exit(1);
    }
}

