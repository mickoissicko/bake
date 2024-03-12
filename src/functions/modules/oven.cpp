#include "../common/common.hpp"
#include "../includes/import.hpp"
#include "../includes/defs.hpp"

using namespace defs;

void Oven()
{
    bool ShouldExecute = false;

    std::string Line;

    defs::isf BakeFile("Bakefile");

    while (std::getline(BakeFile, Line))
    {
        if (!(Line.empty()) && !(Line.find("!--") == 0))
        {
            if (
                (Line.find("!cook{") != str::npos   ||
                 Line.find("!main{") != str::npos   || // sussy
                 Line.find("!bake{") != str::npos   ||
                 Line.find("!serve{") != str::npos) &&
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

                if (
                    start != str::npos &&
                    end   != str::npos &&
                    start < end
                )
                {
                    std::string command = Line.substr(start + 1, end - start - 1);

                    size_t VarStart = command.find("[");
                    size_t VarTerm = command.find("]");

                    while (VarStart != str::npos && VarTerm != str::npos)
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
