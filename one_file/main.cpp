#include "common.hpp"

std::map<std::string, std::string> Vars;

int main()
{
    VerifyFile();
    Oven();

    return 0;
}

void Oven()
{
    bool ShouldExecute = false;

    std::string Line;

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
                (Line.find("!cook{") != std::string::npos   ||
                 Line.find("!main{") != std::string::npos   || // very sussy
                 Line.find("!bake{") != std::string::npos   ||
                 Line.find("!serve{") != std::string::npos) &&
                Line.find("{") != std::string::npos)
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

                if (
                    start != std::string::npos &&
                    end   != std::string::npos &&
                    start < end
                )
                {
                    std::string command = Line.substr(start + 1, end - start - 1);

                    size_t VarStart = command.find("[");
                    size_t VarTerm = command.find("]");

                    while (VarStart != std::string::npos && VarTerm != std::string::npos)
                    {
                        std::string Var = command.substr(VarStart + 1, VarTerm - VarStart - 1);
                        std::string Val = ThrowVal(Var);
                        command.replace(VarStart, VarTerm - VarStart + 1, Val);

                        VarStart = command.find("[");
                        VarTerm = command.find("]");
                    }

                    Cook(command);
                }
            }
        }
    }

    BakeFile.close();
}

std::string ThrowVal(const std::string & value)
{
    auto it = Vars.find(value);
    if (it != Vars.end())
    {
        return it -> second;
    }

    return "";
}

void Cook(const std::string & command)
{
    int result = std::system(command.c_str());

    if (result == 1)
    {
        std::cerr << "Error!" << std::endl
                  << "Exception at: " << std::endl
                  << result << std::endl;
    }
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

        size_t AssignVar = Line.find(":");
        size_t VarStart = Line.find("[");
        size_t VarTerm = Line.find("]");

        if (AssignVar != std::string::npos && VarStart != std::string::npos && VarTerm != std::string::npos)
        {
            std::string Var = Line.substr(0, AssignVar);
            std::string Val = Line.substr(VarStart + 1, VarTerm - VarStart - 1);
            Vars[Var] = Val;
        }
    }

    BakeFile.close();

    if (!ServeFound || !(MainFound || BakeFound || CookFound))
    {
        std::cerr << "Missing required section" << std::endl
                  << "Or forgot to terminate a previously opened curly brace with a closing brace"
                  << std::endl
                  << "It could also be that I can't access the 'Bakefile'"
                  << std::endl;

        exit(1);
    }
}
